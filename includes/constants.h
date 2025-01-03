//
// Created by codingwithjamal on 1/2/2025.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Config {
    static constexpr int FPS = 30;
    static constexpr int WindowWidth = 800;
    static constexpr int WindowHeight = 450;
    static constexpr auto WindowTitle = "CodingWithJamal Raylib Template";

    static constexpr bool buildAudioHeaders = true;
}

enum class GameActivityState {
    MENU,
    PLAYING,
    PAUSED,
    LOADING,
    SETTINGS,
    GAME_OVER
};


#endif //CONSTANTS_H
