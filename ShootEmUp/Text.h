#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;


/// @brief Structure représentant un texte.
typedef struct Text_s
{
    /// @brief Scène associée.
    Scene *scene;

    /// @brief La couleur du texte
    SDL_Color color;

    /// La position du texte dans le rendu
    Vec2 position;

    /// La largeur du texte
    int worldW;

    /// La hauteur du texte
    int worldH;

    /// @brief Texture utilisée pour le rendu.
    SDL_Texture *texture;

    /// @brief Surface utilisée pour le rendu.
    SDL_Surface *surface;

    /// @brief La zone du texte, incluant sa taille et son positionnement
    SDL_Rect area;

    /// Le contenu du texte
    char content[256];
} Text;

/// @brief Crée un nouveau texte. Ce dernier doit ensuite être ajouté à la
/// scène via la méthode Scene_AppendText().
/// @param scene la scène.
/// @param color La couleur du texte
/// @param content Le contenu du texte
/// @param position La position du texte dans le rendu
/// @param worldW La largeur du texte
/// @param worldH La hauteur du texte
/// /// @return Le texte créé.
Text *Text_New(Scene *scene, SDL_Color color, char content[], Vec2 position, int worldW, int worldH);

/// @brief Détruit un texte.
/// Cette méthode est appelée par la scène.
/// @param self le texte.
void Text_Delete(Text *self);

/// @brief Met à jour le texte.
/// @param self le texte.
void Text_Update(Text *self);

/// @brief Dessine le texte dans le moteur de rendu.
/// @param self le texte.
void Text_Render(Text *self);
