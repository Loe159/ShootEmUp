#include "Text.h"
#include "Scene.h"

Text *Text_New(Scene *scene, SDL_Color color, char content[], Vec2 position, int worldW, int worldH)
{
    Text *self = (Text *)calloc(1, sizeof(Text));
    AssertNew(self);

    self->scene = scene;
    self->color = color;
    self->position = position;
    self->worldW = worldW;
    self->worldH = worldH;

    int i = 0;
    while (content[i]) {
        self->content[i] = content[i];
        i++;
    }

    // On récupère des infos essentielles (communes à tout objet)
    Assets *assets = Scene_GetAssets(scene);
    SDL_Renderer *renderer = Scene_GetRenderer(scene);

    self->surface = TTF_RenderText_Solid(assets->font, &self->content, self->color);
    self->texture = SDL_CreateTextureFromSurface(renderer, self->surface);

    // On ajuste la taille du texte en fonction de la police et du contenu
    TTF_SizeText(scene->assets->font, self->content, &self->worldW, &self->worldH);

    // On met à jour les informations de position et taille.
    self->area.x = self->position.x;
    self->area.y = self->position.y;
    self->area.w = self->worldW;
    self->area.h = self->worldH;


    SDL_RenderCopy(renderer, self->texture, NULL, &self->area);

    return self;
}

void Text_Delete(Text *self)
{
    if (!self) return;
    free(self);
}

void Text_Update(Text *self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene *scene = self->scene;
    Assets *assets = Scene_GetAssets(scene);
    SDL_Renderer *renderer = Scene_GetRenderer(scene);

    self->surface = TTF_RenderText_Solid(assets->font, &self->content, self->color);

    // On ajuste la taille du texte en fonction de la police et du contenu
    TTF_SizeText(scene->assets->font, self->content, &self->worldW, &self->worldH);

    // On met à jour les informations de position et taille.
    self->area.x = self->position.x;
    self->area.y = self->position.y;
    self->area.w = self->worldW;
    self->area.h = self->worldH;

    self->texture = SDL_CreateTextureFromSurface(renderer, self->surface);
}

void Text_Render(Text *self)
{
    Scene *scene = self->scene;
    SDL_Renderer *renderer = Scene_GetRenderer(scene);
    SDL_RenderCopy(renderer, self->texture, NULL, &self->area);
}