#include "Scene.h"

Scene *Scene_New(SDL_Renderer *renderer)
{
    Scene *self = (Scene *)calloc(1, sizeof(Scene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = Assets_New(renderer);
    self->camera = Camera_New(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    self->input = Input_New();
    self->player = Player_New(self, PLAYER_MAIN);
    self->waveIdx = 0;
    self->enemyKilled = 0;
    self->state = GAME_START;
    self->gameMode = MODE_SOLO;
    self->restart = false;


    // Cr�ation des menus
    Vec2 position = {0, 0};
    self->startMenu = Menu_New(self, 0, 2, position, 16, 9);
    self->pauseMenu = Menu_New(self, 3, 4, position, 16, 9);
    self->gameOverMenu = Menu_New(self, 5, 5, position, 16, 9);

    SDL_Color white = {255, 255, 255};
    Vec2 scorePos = {10, 10};
    char score[] = "Score 0";
    self->score = Text_New(self, white, score, scorePos, 200, 50);
    Mix_PlayMusic(Mix_LoadMUS("../Assets/Sound/Music/start_music.mp3"), -1); //Jouer infiniment la musique
    Mix_VolumeMusic(MIX_MAX_VOLUME / 3); // Réduit le volume de la musique
    Mix_AllocateChannels(32); //Allouer 32 canaux

    return self;
}

void Scene_Delete(Scene *self)
{
    if (!self) return;

    Assets_Delete(self->assets);
    Camera_Delete(self->camera);
    Input_Delete(self->input);
    Player_Delete(self->player);

    for (int i = 0; i < self->enemyCount; i++)
    {
        Enemy_Delete(self->enemies[i]);
        self->enemies[i] = NULL;
    }
    for (int i = 0; i < self->bulletCount; i++)
    {
        Bullet_Delete(self->bullets[i]);
        self->bullets[i] = NULL;
    }

    free(self);
}

void Scene_UpdateLevel(Scene *self)
{
    if (self->enemyCount > 0)
    {
        return;
    }else self->waveIdx++;
    Enemy *enemy;
    switch (self->waveIdx) {
        case 1:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 2:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 3:
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 4:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.0f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 3.0f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 5:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(14.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 2.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(14.0f, 1.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 6:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(14.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(13.0f, 2.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(14.0f, 1.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 0.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 7:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(14.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 5.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 5.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 8:
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 2.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 1.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 0.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 5.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 6.5f));
            Scene_AppendEnemy(self, enemy);
            break;
        case 9:
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 2.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_BOSS, Vec2_Set(14.0f, 1.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 4.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 3.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 2.5f));
            Scene_AppendEnemy(self, enemy);
            enemy = Enemy_New(self, ENEMY_FIGHTER, Vec2_Set(15.0f, 1.5f));
            Scene_AppendEnemy(self, enemy);
            break;

        default:
            break;
    }
}

bool Scene_Update(Scene *self)
{
    Player *player = self->player;

    // Met � jour les entr�es utilisateur
    Input_Update(self->input);

    // La position du bouton actif dans les menus
    int *ui_nav = &self->input->ui_navigation;

    // Param�trage des actions de chaque bouton
    if (self->input->enterPressed){
        switch (self->state) {
            case GAME_START:
                if (*ui_nav == self->startMenu->firstButtonId) {
                    self->state = GAME_PLAYING; // commencer la partie en solo
                    self->gameMode = MODE_SOLO;
                    Mix_PlayMusic(Mix_LoadMUS("../Assets/Sound/Music/scene_music.mp3"), -1); //Jouer infiniment la musique
                }
                if (*ui_nav == (self->startMenu->firstButtonId+1)) {
                    self->state = GAME_PLAYING; // commencer la partie en multijoueur
                    self->gameMode = MODE_MULTI;
                    Mix_PlayMusic(Mix_LoadMUS("../Assets/Sound/Music/scene_music.mp3"), -1); //Jouer infiniment la musique
                    self->socket = Socket_New(self, "localhost", 12347); // connexion au socket
                    self->mate = Player_New(self, PLAYER_MATE); // cr�ation du co�quipier
                }
                else if (*ui_nav == self->startMenu->lastButtonId) self->input->quitPressed = true; // quitter le jeu
                break;
            case GAME_PAUSED:
                if (*ui_nav == self->pauseMenu->firstButtonId) {
                    self->state = GAME_PLAYING; // reprendre la partie
                }
                else self->input->quitPressed = true; // quitter la partie
                break;
            case GAME_OVER:
                self->input->quitPressed = true; // quitter la partie
        }
    }

    // Param�trage de la touche "echap"
    if (self->input->escapePressed){
        switch (self->state) {
            case GAME_PLAYING:
                // Mettre la partie en pause et selectionner le bouton du haut
                *ui_nav = self->pauseMenu->firstButtonId;
                self->state = GAME_PAUSED;
                break;
            case GAME_PAUSED:
                self->state = GAME_PLAYING; // reprendre la partie
                break;
            default:
                self->input->quitPressed = true; // quitter la partie
                break;
        }
    }

    int i;
    switch (self->state) {
        case GAME_START:
            Menu_Update_Active_Button(self->startMenu, ui_nav);
            break;
        case GAME_PAUSED:
            Menu_Update_Active_Button(self->pauseMenu, ui_nav);
            break;
        case GAME_PLAYING:
            if (self->gameMode == MODE_MULTI){
                /// Obtention du "code d'actions" (i.e. chaque chiffre correspond � une action -> 101 = le joueur va � droite et tire
                int actions = (self->input->hAxis+2)*100 + (self->input->vAxis+2)*10 + self->input->shootPressed;
                // V�rifie si un message a �t� re�u par le socket
                if (Socket_Get_Data(self->socket)){
                    // Convertir la cha�ne de caract�re en int
                    self->mate->mateH = (int)(self->socket->buf[0]-'2');
                    self->mate->mateV = (int)(self->socket->buf[1]-'2');
                    self->mate->mateShoot = self->socket->buf[2]-'0';
                }
                int i = 0;
                // V�rifie si le "code d'action" est le m�me que la pr�c�dente frame, pour �viter de faire trop de requ�te au serveur
                if (self->socket->messageToSend != actions){
                    self->socket->messageToSend = actions;
                    Socket_Send_Data(self->socket); // Envoyer l'action � l'autre joueur
                }
            }
            i = 0;
            while (i < self->bulletCount)
            {
                Bullet *bullet = self->bullets[i];
                bool removed = false;

                Bullet_Update(bullet);

                bool outOfBounds =
                        (bullet->position.x < -1.0f) ||
                        (bullet->position.x > 17.0f) ||
                        (bullet->position.y < -1.0f) ||
                        (bullet->position.y > 10.0f);

                if (outOfBounds)
                {
                    // Supprime le tir
                    Scene_RemoveBullet(self, i);
                    removed = true;
                    continue;
                }

                if (bullet->fromPlayer)
                {
                    // Teste les collisions avec les ennemis
                    for (int j = 0; j < self->enemyCount; j++)
                    {
                        Enemy *enemy = self->enemies[j];
                        float dist = Vec2_Distance(bullet->position, enemy->position);
                        if (dist < bullet->radius + enemy->radius)
                        {
                            // Inflige des dommages � l'ennemi
                            Enemy_Damage(enemy, 1);

                            // Supprime le tir
                            Scene_RemoveBullet(self, i);
                            removed = true;
                            break;
                        }
                    }
                }
                else
                {
                    // Teste la collision avec le joueur
                    float dist = Vec2_Distance(bullet->position, self->player->position);
                    if (dist < bullet->radius + player->radius)
                    {
                        // Inflige des dommages au joueur
                        Player_Damage(player, 1);

                        // Supprime le tir
                        Scene_RemoveBullet(self, i);
                        removed = true;
                    }
                }

                // Passe au prochain tir
                if (removed == false)
                {
                    i++;
                }
            }

            // -------------------------------------------------------------------------
            // Met � jour les ennemis

            i = 0;
            while (i < self->enemyCount)
            {
                Enemy *enemy = self->enemies[i];
                bool removed = false;

                Enemy_Update(enemy);

                if (enemy->state == ENEMY_DEAD)
                {
                    // Supprime l'ennemi
                    Scene_RemoveEnemy(self, i);
                    removed = true;
                    self->enemyKilled++;
                }

                // Passe au prochain ennemi
                if (removed == false)
                {
                    i++;
                }
            }

            // Actualisation du texte qui affiche le score.
            char content[16] = "Score: ";
            int enemyKilled = self->enemyKilled;
            sprintf(content + strlen(content), "%d       ", enemyKilled); // ajout d'espace pour �craser la cha�ne de caract�re pr�c�dente (pas propre)
            i = 0;
            while (content[i]){
                self->score->content[i] = content[i];
                i++;
            }
            Text_Update(self->score);

            // -------------------------------------------------------------------------
            // Met � jour le joueur

            Player_Update(self->player);
            if (self->gameMode == MODE_MULTI){
                Player_Update(self->mate);
            }


            // -------------------------------------------------------------------------
            // Met � jour le niveau

            Scene_UpdateLevel(self);
            break;
    }

    return self->input->quitPressed;
}

void Scene_Render(Scene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = Scene_GetRenderer(self);
    Assets *assets = Scene_GetAssets(self);
    SDL_RenderCopy(renderer, assets->layers[0], NULL, NULL);
    SDL_RenderCopy(renderer, assets->layers[1], NULL, NULL);


    if (self->state == GAME_START) {
        // Affichage du menu start
        Menu_Render(self->startMenu);
    }
    else if (self->state == GAME_PLAYING || self->state == GAME_PAUSED || self->state == GAME_OVER){
            // Affichage du score
            Text_Render(self->score);

            // Affichage des bullets
            int bulletCount = self->bulletCount;
            for (int i = 0; i < bulletCount; i++)
            {
                Bullet_Render(self->bullets[i]);
            }

            // Affichage des ennemis
            int enemyCount = self->enemyCount;
            for (int i = 0; i < enemyCount; i++)
            {
                Enemy_Render(self->enemies[i]);
            }

        switch (self->gameMode) {
            case MODE_SOLO:
                // Affichage du joueur
                Player_Render(self->player);
                break;

            case MODE_MULTI:
                // Affichage des deux joueurs
                Player_Render(self->player);
                Player_Render(self->mate);
                break;
        }
    }
    if (self->state == GAME_PAUSED) {
        // Affichage du menu de pause
        Menu_Render(self->pauseMenu);
    }
    if (self->state == GAME_OVER) {
        // Affichage du menu de fin du jeu
        Menu_Render(self->gameOverMenu);
    }
}

void Scene_AppendObject(void *object, void **objectArray, int *count, int capacity)
{
    int index = *count;
    if (index >= capacity)
        return;

    if (objectArray[index] != NULL)
    {
        assert(false);
        abort();
    }

    objectArray[index] = object;
    (*count)++;
}

void Scene_AppendEnemy(Scene *self, Enemy *enemy)
{
    Scene_AppendObject(
        enemy,
        (void **)(self->enemies),
        &(self->enemyCount),
        ENEMY_CAPACITY
    );
}

void Scene_AppendBullet(Scene *self, Bullet *bullet)
{
    Scene_AppendObject(
        bullet,
        (void**)(self->bullets),
        &(self->bulletCount),
        BULLET_CAPACITY
    );
}

void Scene_RemoveObject(int index, void **objectArray, int *count)
{
    int lastIndex = *count - 1;
    assert(0 <= index && index < *count);

    if (objectArray[index] == NULL)
    {
        assert(false);
        abort();
    }

    if (index == lastIndex)
    {
        // Supprime le pointeur
        objectArray[index] = NULL;
    }
    else
    {
        // Remplace le pointeur par le dernier du tableau
        objectArray[index] = objectArray[lastIndex];
        objectArray[lastIndex] = NULL;
    }
    (*count)--;
}

void Scene_RemoveEnemy(Scene *self, int index)
{
    Enemy_Delete(self->enemies[index]);
    Scene_RemoveObject(index, (void **)(self->enemies), &(self->enemyCount));
}

void Scene_RemoveBullet(Scene *self, int index)
{
    Bullet_Delete(self->bullets[index]);
    Scene_RemoveObject(index, (void **)(self->bullets), &(self->bulletCount));
}
