#pragma once

#include "Settings.h"
#include "Timer.h"

/// @brief Initialise les librairies utilis�es par le jeu.
/// @param sdlFlags les flags pour la SDL.
/// @param imgFlags les flags pour la SDL Image.
void Game_Init(int sdlFlags, int imgFlags);

/// @brief Quitte les librairies utilis�es par le jeu.
void Game_Quit();

/// @brief Temps global du jeu.
extern Timer *g_time;

/// @brief Enumération représentant les états possibles du jeu.
typedef enum GameState_e
{
    GAME_START,
    GAME_PLAYING,
    GAME_PAUSED,
    GAME_OVER
} GameState;
