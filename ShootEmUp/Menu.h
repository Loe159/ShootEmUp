#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;


/// @brief Structure repr�sentant un menu.
typedef struct Menu_s
{
    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief La zone du menu, incluant sa taille et son positionnement
    SDL_Rect area;

    /// La position du menu dans le rendu
    Vec2 position;

    /// La largeur du menu
    int worldW;

    /// La hauteur du menu
    int worldH;

    // @brief Les ids du premier et dernier id de boutons, peut �tre r�cup�r� par assets->menu[...]
    int firstButtonId;
    int lastButtonId;
    int currentButtonId;

    /// @brief Textures utilis�es pour le rendu. Chaque texture correspond � un bouton actif.
    SDL_Texture *texture[4];
} Menu;

/// @brief Cr�e un nouveau menu.
/// @param scene la sc�ne.
/// @param firstButtonId le premier identifiant du bouton
/// @param lastButtonId le dernier identifiant du bouton
/// @param position la position du menu
/// @param worldW la largeur du menu
/// @param worldH la hauteur du menu
/// /// @return Le menu cr��.
Menu *Menu_New(Scene *scene, int firstButtonId, int lastButtonId, Vec2 position, int worldW, int worldH);

/// @brief D�truit un menu.
/// Cette m�thode est appel�e par la sc�ne.
/// @param self le menu.
void Menu_Delete(Menu *self);

/// @brief Met � jour le bouton actif en fonction de la navigation active.
/// @param self le menu.
/// @param ui_navigation l'identifiant de la navigation active
void Menu_Update_Active_Button(Menu *self, int *ui_navigation);

/// @brief Dessine le menu dans le moteur de rendu.
/// @param self le menu.
void Menu_Render(Menu *self);
