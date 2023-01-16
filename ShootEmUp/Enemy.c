#include "Enemy.h"
#include "Common.h"
#include "Scene.h"

Enemy *Enemy_New(Scene *scene, int type, Vec2 position)
{
    Enemy *self = (Enemy *)calloc(1, sizeof(Enemy));
    AssertNew(self);

    self->scene = scene;
    self->position = position;
    self->type = type;
    self->state = ENEMY_FIRING;
    self->health = 3;
    self->lastShot = 0;

    Assets *assets = Scene_GetAssets(self->scene);
    switch (type)
    {
    case ENEMY_FIGHTER:
        self->worldW = 64 * PIX_TO_WORLD;
        self->worldH = 64 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter;
        break;

    default:
        assert(false);
        break;
    }

    return self;
}

void Enemy_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void Enemy_Update(Enemy *self)
{
    if (self->lastShot++ > 100) {
        self->lastShot = 0;
        Vec2 velocity = Vec2_Set(-4.0f, 1.0f);
        Bullet *bullet = Bullet_New(
                self->scene, self->position, velocity, BULLET_FIGHTER, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
    }
}

void Enemy_Render(Enemy *self)
{
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Assets *assets = Scene_GetAssets(scene);
    Camera *camera = Scene_GetCamera(scene);

    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = {0};

    dst.h = 48 * PIX_TO_WORLD * scale;
    dst.w = 48 * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);

    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;

    SDL_RenderCopyExF(renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
}

void Enemy_Damage(Enemy *self, int damage)
{
    self->health = self->health - damage;
    if (self->health <= 0) {
        self->state = ENEMY_DEAD;
    }
}
