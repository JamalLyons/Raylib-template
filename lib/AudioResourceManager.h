//
// Created by codingwithjamal on 1/2/2025.
//

#ifndef AUDIORESOURCEMANAGER_H
#define AUDIORESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include "raylib.h"

class AudioResourceManager {
public:
    // Constructor: Initializes the audio device
    AudioResourceManager();

    // Destructor: Cleans up all loaded resources and closes the audio device
    ~AudioResourceManager();

    // Play a sound resource
    void playAudio(const std::string &key);

    // Stop a sound resource
    void stopAudio(const std::string &key);

    // Unload a specific sound resource
    void unloadAudio(const std::string &key);

    // Load predefined sound resources
    void loadAudioResources();

    // Unload all loaded sound resources
    void unloadAllAudio();

private:
    std::unordered_map<std::string, Sound> audioResources;
    std::unordered_map<std::string, std::string> predefinedAudioPaths = {
        // Sound effects
        {"spring-effect", "../resources/audio/spring.wav"},
        // Background music
        // {"menu-background-music", "../resources/audio/background-music.wav"}
    };
};

#endif //AUDIORESOURCEMANAGER_H
