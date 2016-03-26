#pragma once

#define NULL 0

// ----- Typedef ----- //
typedef unsigned int p_uint;

// ----- Screen ----- //
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define FPS 20

// ----- Keyboard ----- //
#define NUMBER_OF_KEYS 2

#define KEY_CODE_1 SDLK_ESCAPE
#define KEY_CODE_2 SDLK_RETURN

// ----- Game ----- //
#define GAME_SPEED 6 // Days per second
#define UPDATE_TIME 3 // Days
#define START_MONEY_AMOUNT 10000
#define START_TAXATION_INHAB 0.2f
#define START_TAXATION_WORK 0.2f