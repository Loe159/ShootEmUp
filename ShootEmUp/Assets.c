#include "Assets.h"

typedef struct TextureSpec_s
{
    SDL_Texture **ptr;
    char *path;
} TextureSpec;

typedef struct FontSpec_s
{
    TTF_Font **ptr;
    char *path;
    int size;
} FontSpec;

Assets *Assets_New(SDL_Renderer *renderer)
{
    Assets *self = (Assets *)calloc(1, sizeof(Assets));
    AssertNew(self);

    // -------------------------------------------------------------------------
    // Chargement des textures

    TextureSpec texSpecs[] = {
        { &self->background,     "../Assets/Background/background.png"   },
        { &self->menus[0],     "../Assets/UI/start_0.png"   },
        { &self->menus[1],     "../Assets/UI/start_1.png"   },
        { &self->menus[2],     "../Assets/UI/start_2.png"   },
        { &self->menus[3],     "../Assets/UI/pause_0.png"   },
        { &self->menus[4],     "../Assets/UI/pause_1.png"   },
        { &self->menus[5],     "../Assets/UI/pause_2.png"   },
        { &self->menus[6],     "../Assets/UI/game_over_0.png"   },
        { &self->menus[7],     "../Assets/UI/game_over_1.png"   },
        { &self->health[0],     "../Assets/UI/health_0.png"   },
        { &self->health[1],     "../Assets/UI/health_1.png"   },
        { &self->health[2],     "../Assets/UI/health_2.png"   },
        { &self->health[3],     "../Assets/UI/health_3.png"   },
        { &self->health[4],     "../Assets/UI/health_4.png"   },
        { &self->health[5],     "../Assets/UI/health_5.png"   },
        { &self->player, "../Assets/Player/player.png"},
        { &self->playerBullet,  "../Assets/Player/bullet_default.png" },
        { &self->fighter,       "../Assets/Enemy/fighter.png"         },
        { &self->fighterBullet, "../Assets/Enemy/fighter_bullet.png"  },
        { &self->boss,       "../Assets/Enemy/boss.png"         },
        { &self->tracker,       "../Assets/Enemy/tracker.png"         },
        { &self->sender,       "../Assets/Enemy/sender.png"         },
        { &self->bossBullet, "../Assets/Enemy/boss_bullet.png"  },
    };
    int texSpecCount = sizeof(texSpecs) / sizeof(TextureSpec);

    for (int i = 0; i < texSpecCount; i++)
    {
        SDL_Texture **texPtr = texSpecs[i].ptr;
        char *path = texSpecs[i].path;

        *texPtr = IMG_LoadTexture(renderer, path);
        if (*texPtr == NULL)
        {
            printf("ERROR - Loading texture %s\n", path);
            printf("      - %s\n", SDL_GetError());
            assert(false);
            abort();
        }
    }

    // -------------------------------------------------------------------------
    // Chargement des polices

    FontSpec fontSpecs[] = {
        { &self->font, "../Assets/Fonts/exo_space.ttf", 50 }};
    int fontSpecCount = sizeof(fontSpecs) / sizeof(FontSpec);

    for (int i = 0; i < fontSpecCount; i++)
    {
        TTF_Font **fontPtr = fontSpecs[i].ptr;
        char *path = fontSpecs[i].path;
        int size = fontSpecs[i].size;

        *fontPtr = TTF_OpenFont(path, size);
        if (*fontPtr == NULL)
        {
            printf("ERROR - Loading font %s\n", path);
            printf("      - %s\n", TTF_GetError());
            assert(false);
            abort();
        }
        self->font = *fontPtr;
    }


    return self;
}

void Assets_Delete(Assets *self)
{
    if (!self) return;

    // -------------------------------------------------------------------------
    // Lib�re les textures

    SDL_Texture **texPointers[] = {
        &self->player,
        &self->playerBullet,
        &self->fighter,
        &self->fighterBullet,
    };
    int count = sizeof(texPointers) / sizeof(SDL_Texture **);

    for (int i = 0; i < count; i++)
    {
        if (*texPointers[i])
            SDL_DestroyTexture(*(texPointers[i]));
    }

    free(self);
}