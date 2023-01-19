#include "Socket.h"

Socket *Socket_New(Scene *scene, char *host_ip, int host_port){
    Socket *self = (Socket *)calloc(1, sizeof(Socket));
    AssertNew(self);

    // Vérifie si peut accéder au serveur
    if (SDLNet_ResolveHost(&self->host, host_ip, host_port) != 0)
    {
        printf("ERROR - Retrieving host %s:%d", host_ip, host_port);
        printf("      - %s\n", SDLNet_GetError());
        assert(false);
        abort();
    }

    // Connexion au serveur TCP
    self->connection = SDLNet_TCP_Open(&self->host);
    if (self->connection == NULL)
    {
        printf("ERROR - Connecting server %s:%d", host_ip, host_port);
        printf("      - %s\n", SDLNet_GetError());
        assert(false);
        abort();
    }

    // Crée un set de socket, et mettre le socket dedans
    self->socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(self->socketSet, self->connection);

    return self;
}

bool Socket_Get_Data(Socket *self){
    // Vérifie si un message est disponible dans le socket du set
    SDLNet_CheckSockets(self->socketSet, 10);

    // Reception du message
    if (SDLNet_SocketReady(self->connection))
    {
        int bytes_received = SDLNet_TCP_Recv(self->connection, self->buf, sizeof(self->buf));
        if (bytes_received <= 0) {
            printf("Error receiving data: %s\n", SDLNet_GetError());
            exit(2);
        }
        return true;
    }
    return false;
}

void Socket_Send_Data(Socket *self){
    // On transforme le "code d'action" en chaîne de caractère pour l'envoyer au serveur
    char str[3];
    int n = self->messageToSend;
    int i = 2;
    while (n >= 1)
    {
        str[i] = n%10+'0';
        n /= 10;
        i--;
    }
    int bytes_sent = SDLNet_TCP_Send(self->connection, str, 3);
}
