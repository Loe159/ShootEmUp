#include "Menu.h"
#include "Scene.h"

Menu *Menu_New(Scene *scene, int firstButtonId, int lastButtonId, Vec2 position, int worldW, int worldH)
{
    Menu *self = (Menu *)calloc(1, sizeof(Menu));

    self->scene = scene;

    self->position = position;
    self->worldH = worldH;
    self->worldW = worldW;
    self->firstButtonId = firstButtonId;
    self->lastButtonId = lastButtonId;
    self->currentButtonId = firstButtonId;

    return self;
}

void Menu_Delete(Menu *self)
{
    if (!self) return;
    free(self);
}

void Menu_Update_Active_Button(Menu *self, int *ui_navigation){
    if (*ui_navigation < self->firstButtonId) *ui_navigation = self->lastButtonId; // Si c'est le dernier bouton, retourner au premier
    else if (*ui_navigation > self->lastButtonId) *ui_navigation = self->firstButtonId; // ...et si c'est le premier bouton, aller au dernier
    self->currentButtonId = *ui_navigation;
}

void Menu_Render(Menu *self)
{
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    Camera *camera = Scene_GetCamera(scene);
    Assets *assets = Scene_GetAssets(scene);

    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = {0};

    dst.h = self->worldH * scale;
    dst.w = self->worldW * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);

    dst.y -= dst.h;

    SDL_RenderCopyExF(renderer, assets->menus[self->currentButtonId], NULL, &dst, 0.0f, NULL, 0);
}