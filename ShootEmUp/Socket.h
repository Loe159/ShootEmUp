#pragma once


#include "Settings.h"

typedef struct Scene_s Scene;

/// @brief Structure contenant l'ensemble des paramètres du socket.
typedef struct Socket_s
{
    // L'adresse du serveur de socket
    IPaddress host;

    // La connexion au serveur TCP
    TCPsocket connection;

    // Un groupe de socket, obligatoire pour vérifier si un message est reçu sans mettre la boucle du jeu en pause.
    SDLNet_SocketSet socketSet;

    // Le message reçu par le serveur
    char buf[3];

    // Le message à envoyer au serveur
    int messageToSend;

} Socket;

/// @brief Crée la structure contenant la connexion au socket qui gère le mode multijoueur.
/// @return La structure contenant le socket.
Socket *Socket_New(Scene *scene, char host_ip[], int host_port);

/// @brief Vérifie si le socket a reçu un message
/// @param Renvoie true si un message a été reçu, false sinon
bool Socket_Get_Data(Socket *self);

void Socket_Send_Data(Socket *self);

/// @brief Ferme et détruit la connexion au socket.
/// @param self le socket.
void Socket_Delete(Socket *self);
