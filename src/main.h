//
// Created by codingwithjamal on 1/1/2025.
//

#ifndef MAIN_H
#define MAIN_H

// Standard includes
#include <iostream>

// External libraries
#include "raylib.h"

// Local includes
#include "constants.h"

struct GameState;
void update(GameState& game_state);
void draw(const GameState& game_state);

#endif //MAIN_H
