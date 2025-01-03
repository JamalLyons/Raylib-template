#include "AudioResourceManager.h"
#include <stdexcept>
#include <iostream>
#include <filesystem>

#include "../includes/constants.h"

AudioResourceManager::AudioResourceManager() {
    InitAudioDevice();
    // I disabled this because I prefer to load audio using the raw function.
    // I will keep this in the template just for functionality, however if this is enabled
    // then audio will be loaded at runtime using the file paths which will require the user to
    // install the audio files in the release build.
    //
    // The workaround I found for development was to use the AudioResourceManager::buildAudioHeaders()
    // function when adding new source files to the project and simply calling AudioResourceManager::playRawAudio()
    // when playing sounds. The function will cache the wave data on the first time it is called.
    // I'm still new to c++ programming but right now I cant find a good API for this class and keep the
    // dynamic header file functionality. If the header files are not known at compile time then
    // the code will not build, and we need to build them to get the audio headers loaded and cached...
    // loadAudioResources();
}

AudioResourceManager::~AudioResourceManager() {
    unloadAllAudio();
    CloseAudioDevice();
}

void AudioResourceManager::loadAudioResources() {
    for (const auto &[key, path] : predefinedAudioPaths) {
        if (!audioResources.contains(key)) {
            if (const Sound sound = LoadSound(path.c_str()); sound.stream.buffer == nullptr) {
                std::cerr << "Error: Failed to load sound from path: " << path << std::endl;
            } else {
                audioResources[key] = sound;
                std::cout << "Loaded audio: " << key << std::endl;
            }
        }
    }
}


void AudioResourceManager::playAudio(const std::string &key) {
    if (audioResources.contains(key)) {
        if (const Sound &sound = audioResources[key]; sound.stream.buffer != nullptr) {
            std::cout << "Playing audio: " << key << std::endl;
            PlaySound(sound);
        } else {
            std::cerr << "Error: Audio '" << key << "' is not valid!" << std::endl;
        }
    } else {
        std::cerr << "Error: Audio key '" << key << "' not found!" << std::endl;
    }
}

void AudioResourceManager::stopAudio(const std::string &key) {
    if (audioResources.contains(key)) {
        if (const Sound &sound = audioResources[key]; sound.stream.buffer != nullptr) {
            std::cout << "Stopping audio: " << key << std::endl;
            StopSound(sound);
        } else {
            std::cerr << "Error: Audio '" << key << "' is not valid!" << std::endl;
        }
    } else {
        std::cerr << "Error: Audio key '" << key << "' not found!" << std::endl;
    }
}


void AudioResourceManager::unloadAudio(const std::string &key) {
    if (audioResources.contains(key)) {
        UnloadSound(audioResources[key]);
        audioResources.erase(key);
    } else {
        std::cerr << "Error: Audio key '" << key << "' not found!" << std::endl;
    }
}

void AudioResourceManager::unloadAllAudio() {
    for (auto &[key, sound] : audioResources) {
        UnloadSound(sound);
    }
    audioResources.clear();
}

void AudioResourceManager::buildAudioHeaders() {
    if constexpr (!Config::buildAudioHeaders) {
        std::cout << "Audio headers building disabled." << std::endl;
        return;
    }

    std::cout << "Building audio headers..." << std::endl;

    const std::string outputDir = "../resources/audio/headers/";
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directories(outputDir);
        std::cout << "Created output directory: " << outputDir << std::endl;
    }

    for (const auto &[key, path] : predefinedAudioPaths) {
        // Load the wave file
        const Wave wave = LoadWave(path.c_str());
        if (!wave.data) {
            std::cerr << "Error: Failed to load wave data: " << path << std::endl;
            continue;
        }

        // Generate a sanitized output header file name
        const std::string filename = path.substr(path.find_last_of("/\\") + 1);
        const std::string sanitizedFilename = filename.substr(0, filename.find_last_of('.')) + "_audio.h";
        const std::string outputPath = outputDir + sanitizedFilename;

        std::cout << "Building header: " << outputPath << std::endl;

        // Export the wave as a C header
        if (!ExportWaveAsCode(wave, outputPath.c_str())) {
            TraceLog(LOG_ERROR, "Failed to export wave as C header file: %s", outputPath.c_str());
        } else {
            TraceLog(LOG_INFO, "Wave exported as C header file successfully: %s", outputPath.c_str());
        }

        // Unload the wave to free memory
        UnloadWave(wave);
    }

    std::cout << "Finished building audio headers." << std::endl;
}

void AudioResourceManager::playRawAudio(const std::string &key, const Wave &wave) {
    if (!audioResources.contains(key)) {
        std::cout << "Caching loaded audio file: " << key << "" << std::endl;
        audioResources[key] = LoadSoundFromWave(wave);
    }

    PlaySound(audioResources[key]);
}
