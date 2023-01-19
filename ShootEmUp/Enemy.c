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
    self->timer = 0;
    self->velocity = 0;
    Assets *assets = Scene_GetAssets(self->scene);
    switch (type)
    {
    case ENEMY_FIGHTER:
        self->size = 1;
        self->maxHealth = 3;
        self->health = self->maxHealth;
        self->bulletType = BULLET_FIGHTER;
        self->bulletSpeed = 1;
        self->worldW = 64 * PIX_TO_WORLD;
        self->worldH = 64 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter;
        break;
    case ENEMY_BOSS:
        self->size = 1.25;
        self->maxHealth = 6;
        self->health = self->maxHealth;
        self->bulletType = BULLET_BOSS;
        self->bulletSpeed = 2;
        self->worldW = 128 * PIX_TO_WORLD;
        self->worldH = 128 * PIX_TO_WORLD;
        self->radius = 0.8f;
        self->texture = assets->boss;
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
    if (self->timer%50==0) {
        Vec2 velocity = Vec2_Set(-4.0f*(self->bulletSpeed), 1.0f);
        Bullet *bullet = Bullet_New(
                self->scene, self->position, velocity, self->bulletType, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
    }

    if (self->timer%10==0){
        self->velocity = cos(self->timer*5);
    }
    self->timer ++;
    Vec2 velocity = Vec2_Set(0, self->velocity);
    self->position = Vec2_Add(self->position, Vec2_Scale(velocity, Timer_GetDelta(g_time)*3));

}

void Enemy_Render(Enemy *self)
{
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Assets *assets = Scene_GetAssets(scene);
    Camera *camera = Scene_GetCamera(scene);

    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = {0};

    dst.h = 48 * PIX_TO_WORLD * scale * self->size;
    dst.w = 48 * PIX_TO_WORLD * scale * self->size;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);

    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;

    SDL_RenderCopyExF(renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);


    // Et on affiche sa barre de vie
    dst.h = 7 * PIX_TO_WORLD * scale;
    dst.w = 50 * PIX_TO_WORLD * scale;
    dst.y -= 10 * PIX_TO_WORLD * scale;
    dst.x -= 2 * PIX_TO_WORLD * scale;

    // Mettre la vie sur 5
    int health = (int)((float)self->health/(float)self->maxHealth*5.0f);

    SDL_RenderCopyExF(
            renderer, assets->health[health], NULL, &dst, 0.0f, NULL, 0);
}

void Enemy_Damage(Enemy *self, int damage)
{
    self->health = self->health - 1;
    printf("%d\n", self->health);
    if (self->health <= 0) {
        self->state = ENEMY_DEAD;
        Mix_PlayChannel(2, Mix_LoadWAV("../Assets/Sound/Fx/crash.wav"), 0);
    }
}
