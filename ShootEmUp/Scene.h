#pragma once

#include "Settings.h"
#include "Common.h"

#include "Assets.h"
#include "Camera.h"
#include "Input.h"
#include "Bullet.h"
#include "Socket.h"
#include "Text.h"
#include "Menu.h"
#include "Player.h"
#include "Enemy.h"

// Nombre maximal d'ennemis actifs dans un niveau.
#define ENEMY_CAPACITY 32

// Nombre maximal de projectiles actifs dans un niveau.
#define BULLET_CAPACITY 256

/// @brief Structure reprï¿½sentant la scï¿½ne principale du jeu (niveau).
typedef struct Scene_s
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la scï¿½ne (textures, musiques, sons...)
    Assets *assets;

    /// @brief Camï¿½ra par laquelle est vue la scï¿½ne.
    Camera *camera;

    /// @brief Entrï¿½e utilisateur.
    Input *input;

    /// @brief Joueur principal.
    Player *player;

    /// @brief Joueur secondaire.
    Player *mate;

    /// @brief Les interfaces de menus à afficher
    Menu *startMenu;
    Menu *pauseMenu;
    Menu *gameOverMenu;

    /// @brief Tableau contenant les ennemis courrants.
    Enemy *enemies[ENEMY_CAPACITY];

    /// @brief Nombre d'ennemis courrants.
    int enemyCount;

    /// @brief Tableau contenant les projectiles courrants.
    Bullet *bullets[BULLET_CAPACITY];

    /// @brief Nombre de projectiles courrants.
    int bulletCount;

    // @brief Nombre d'ennemis tués, utile pour calculer le score.
    int enemyKilled;

    /// @brief Indice de la vague d'ennemis courrante.
    /// Utilisï¿½ pour implï¿½menter un niveau complet.
    int waveIdx;

    ///@brief Score du joueur en fonction de divers paramètres.
    Text* score;

    // @brief Etat du jeu (en pause, game over...)
    GameState state;

    // @brief Mode de jeu (solo/multijoueur)
    GameMode gameMode;

    // @brief Connexion à un socket TCP pour gérer le mode multijoueur.
    Socket *socket;

} Scene;

/// @brief Crï¿½e la scï¿½ne principale du jeu.
/// @param renderer moteur de rendu.
/// @return La scï¿½ne crï¿½ï¿½e.
Scene *Scene_New(SDL_Renderer *renderer);

/// @brief Dï¿½truit la scï¿½ne principale.
/// @param self la scï¿½ne.
void Scene_Delete(Scene *self);

/// @brief Met ï¿½ jour la scï¿½ne.
/// Cette fonction est appelï¿½e ï¿½ chaque tour de la boucle de rendu.
/// @param self la scï¿½ne.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool Scene_Update(Scene *self);

/// @brief Dessine la scï¿½ne dans le moteur de rendu.
/// @param self la scï¿½ne.
void Scene_Render(Scene *self);

/// @brief Ajoute un nouveau projectile ï¿½ la scï¿½ne.
/// @param self la scï¿½ne.
/// @param bullet le projectile ï¿½ ajouter (correctement initialisï¿½).
void Scene_AppendBullet(Scene *self, Bullet *bullet);

/// @brief Supprime un projectile de la scï¿½ne.
/// @param self la scï¿½ne.
/// @param index l'indice du projectile ï¿½ supprimer dans le tableau self->bullets.
void Scene_RemoveBullet(Scene *self, int index);

/// @brief Ajoute un nouvel ennemi ï¿½ la scï¿½ne.
/// @param self la scï¿½ne.
/// @param enemy l'ennemi ï¿½ ajouter (correctement initialisï¿½).
void Scene_AppendEnemy(Scene *self, Enemy *enemy);

/// @brief Supprime un ennemi de la scï¿½ne.
/// @param self la scï¿½ne.
/// @param index l'indice du l'ennemi ï¿½ supprimer dans le tableau self->enemies.
void Scene_RemoveEnemy(Scene *self, int index);



/// @brief Renvoie le moteur de rendu de la scï¿½ne.
/// @param self la scï¿½ne.
/// @return Le moteur de rendu de la scï¿½ne.
INLINE SDL_Renderer *Scene_GetRenderer(Scene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la scï¿½ne.
/// @param self la scï¿½ne.
/// @return Les assets de la scï¿½ne.
INLINE Assets *Scene_GetAssets(Scene *self)
{
    return self->assets;
}

/// @brief Renvoie la camï¿½ra de la scï¿½ne.
/// @param self la scï¿½ne.
/// @return La camï¿½ra de la scï¿½ne.
INLINE Camera *Scene_GetCamera(Scene *self)
{
    return self->camera;
}

/// @brief Renvoie les entrï¿½e utilisateur de la scï¿½ne.
/// @param self la scï¿½ne.
/// @return Les entrï¿½e utilisateur de la scï¿½ne.
INLINE Input *Scene_GetInput(Scene *self)
{
    return self->input;
}
