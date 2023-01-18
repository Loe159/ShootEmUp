#include "Player.h"
#include "Scene.h"
#include "Common.h"

Player *Player_New(Scene *scene)
{
    Player *self = (Player *)calloc(1, sizeof(Player));
    AssertNew(self);

    Assets *assets = Scene_GetAssets(scene);

    self->texture = assets->player;


    self->scene = scene;
    self->position = Vec2_Set(1.0f, 4.5f);
    self->radius = 0.25f;
    self->health = 5;
    self->speed = 3.5f;

    return self;
}

void Player_Delete(Player *self)
{
    if (!self) return;
    free(self);
}

void Player_Update(Player *self) {
    // On récupère des infos essentielles (communes à tout objet)
    Scene *scene = self->scene;
    Input *input = Scene_GetInput(scene);

    // Empêcher le joueur d'aller en dehors de la scène.
    if (self->position.x < 0.0f+24*PIX_TO_WORLD && input->hAxis < 0.0f) input->hAxis = 0;
    else if (self->position.x > 10.0f && input->hAxis > 0.0f) input->hAxis = 0;
    if (self->position.y < 0.0f+24*PIX_TO_WORLD && input->vAxis < 0.0f) input->vAxis = 0;
    else if (self->position.y > 9.0f-24*PIX_TO_WORLD && input->vAxis > 0.0f) input->vAxis = 0;

    // Mise à jour de la vitesse en fonction de l'état des touches
    Vec2 velocity = Vec2_Set(input->hAxis, input->vAxis);

    // Mise à jour de la position
    self->position = Vec2_Add(self->position, Vec2_Scale(velocity, Timer_GetDelta(g_time)*(self->speed)));

    if (input->shootPressed){
        Vec2 velocity = Vec2_Set(10.0f, 0.0f);
        Vec2 offset = {22 * PIX_TO_WORLD, 0};
        Bullet *bullet = Bullet_New(
                self->scene, Vec2_Add(self->position, offset), velocity, BULLET_PLAYER, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
    }
}

void Player_Render(Player *self) {
    // On récupère des infos essentielles (communes à tout objet)
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Assets *assets = Scene_GetAssets(scene);
    Camera *camera = Scene_GetCamera(scene);

    // On calcule la position en pixels en fonction de la position
    // en tuiles, la taille de la fenêtre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = {0};

    // Changez 48 par une autre valeur pour grossir ou réduire l'objet
    dst.h = 48 * PIX_TO_WORLD * scale;
    dst.w = 48 * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);

    // Le point de référence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;

    // On affiche en position dst (unités en pixels)
    SDL_RenderCopyExF(
            renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);

    // Et on affiche sa barre de vie
    dst.h = 7 * PIX_TO_WORLD * scale;
    dst.w = 50 * PIX_TO_WORLD * scale;
    dst.y -= 10 * PIX_TO_WORLD * scale;
    dst.x -= 2 * PIX_TO_WORLD * scale;
    SDL_RenderCopyExF(
            renderer, assets->health[self->health], NULL, &dst, 0.0f, NULL, 0);
}

void Player_Damage(Player *self, int damage)
{
    // Enlever de la vie au joueur et finir le jeu s'il n'a plus de vie
    if (self->health) self->health--;
    else self->scene->state = GAME_OVER;
}