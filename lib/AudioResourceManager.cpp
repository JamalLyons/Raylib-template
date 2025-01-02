#include "AudioResourceManager.h"
#include <stdexcept>
#include <iostream>

AudioResourceManager::AudioResourceManager() {
    InitAudioDevice();
    loadAudioResources();
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
