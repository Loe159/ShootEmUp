#include "Bullet.h"
#include "Common.h"
#include "Scene.h"

Bullet *Bullet_New(Scene *scene, Vec2 position, Vec2 velocity, int type, float angle)
{
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    AssertNew(self);

    self->position = position;
    self->velocity = velocity;
    self->type = type;
    self->angle = angle;
    self->scene = scene;
    self->fromPlayer = false;

    Assets *assets = Scene_GetAssets(scene);
    switch (type)
    {
    case BULLET_FIGHTER:
        self->size = 1;
        self->texture = assets->fighterBullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        break;

    case BULLET_BOSS:
        self->size = 2;
        self->texture = assets->bossBullet;
        self->worldW = 16 * PIX_TO_WORLD;
        self->worldH = 32 * PIX_TO_WORLD;
        self->radius = 0.15f;
        self->fromPlayer = false;
        break;

    default:
    case BULLET_PLAYER:
        self->size = 1;
        self->texture = assets->playerBullet;
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = true;
        break;
    }

    return self;
}

void Bullet_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void Bullet_Update(Bullet *self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene *scene = self->scene;
    Input *input = Scene_GetInput(scene);

    // Mise à jour de la position
    self->position = Vec2_Add(self->position, Vec2_Scale(self->velocity, Timer_GetDelta(g_time)));
}

void Bullet_Render(Bullet *self)
{
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Assets *assets = Scene_GetAssets(scene);
    Camera *camera = Scene_GetCamera(scene);

    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = {0};

    dst.h = 5 * PIX_TO_WORLD * scale * self->size;
    dst.w = 5 * PIX_TO_WORLD * scale * self->size;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);

    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;

    SDL_RenderCopyExF(renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
}