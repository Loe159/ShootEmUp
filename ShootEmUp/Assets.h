#pragma once

#include "Settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilis�es (textures, musiques, sons...)
typedef struct Assets_s
{
    /// @brief Tableau des diff�rents menus.
    SDL_Texture *menus[7];

    /// @brief Tableau des diff�rents calques de fond.
    SDL_Texture *health[6];

    /// @brief Texture du background
    SDL_Texture *background;

    /// @brief Texture du vaisseau du joueur.
    SDL_Texture *player;

    /// @brief Texture du tir du joueur.
    SDL_Texture *playerBullet;

    /// @brief Texture du vaisseau ennemi.
    SDL_Texture *fighter;

    /// @brief Texture du tir d'un ennemi.
    SDL_Texture *fighterBullet;

    /// @brief Texture d'un boss.
    SDL_Texture *boss;

    // @brief Texture d'un ennemi renvoyeur.
    SDL_Texture *sender;

    // @brief Texture d'un ennemi traqueur.
    SDL_Texture *tracker;

    /// @brief Texture du tir d'un boss.
    SDL_Texture *bossBullet;

    /// @brief La police a utiliser pour les textes
    TTF_Font *font;
} Assets;

/// @brief Cr�e la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
Assets *Assets_New(SDL_Renderer *renderer);

/// @brief D�truit la structure contenant les assets du jeu.
/// @param self les assets.
void Assets_Delete(Assets *self);
