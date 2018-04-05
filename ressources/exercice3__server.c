    /*    ** server.c -- serveur daytime demonstration    ** a faire : ajouter la gestion des erreurs    ** a faire : faire le traitement pour le fils dans un fork    */    #include <stdio.h>    #include <stdlib.h>    #include <unistd.h>    #include <errno.h>    #include <string.h>    #include <sys/types.h>    #include <sys/socket.h>    #include <sys/time.h>    #include <time.h>    #include <netinet/in.h>    #include <arpa/inet.h>    #define MYPORT 3490    // Port du point de connexion    #define BACKLOG 10     // Combien de connexion en attente autorise-t-on ?    #define MAXDATASIZE 100 // Nombre maximal d'octer a envoyer en une fois	#define BUFFERSIZE 500 // Taille du buffer    int main(void)    {        int sockfd, new_fd;  // sock_fd : point de connexion, new_fd : socket de transit        struct sockaddr_in my_addr;    // adresse de transport de la socket coté serveur        struct sockaddr_in their_addr; // adresse de transport de la socket coté client        int sin_size; // Taille d'une adresse de transport        int yes = 1;        char* date_string; // Chaine de caractere contenant la date        struct timeval time_value;		char buffer[BUFFERSIZE];		// Creation et initialisation du point de connexion		sockfd = socket(AF_INET, SOCK_STREAM, 0);				if(sockfd == -1)			perror("[ERR] Creation du pt de con. (socket) : ");					if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)			perror("[ERR] Initialisation du pt de con. (setsockopt) : ");        // Configuration de l'adresse de transport        my_addr.sin_family = AF_INET;         // type de la socket        my_addr.sin_port = htons(MYPORT);     // port, converti en reseau        my_addr.sin_addr.s_addr = INADDR_ANY; // adresse, devrait être converti en reseau mais est egal à 0        bzero(&(my_addr.sin_zero), 8);        // mise a zero du reste de la structure		// Demarrage du point de connexion : on ajoute l'adresse de transport dans la socket        if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)			perror("[ERR] Démarrage du pt de con. (bind) : ");		// Attente sur le point de connexion        if(listen(sockfd, BACKLOG) == -1)			perror("[ERR] Attente sur le pt de con. (listen) : ");		// Boucle principale de traitement des demandes client        while(1)        {            sin_size = sizeof(struct sockaddr_in);            // Accept est bloquant : le processus n'avance pas tant que personne ne se connecte			new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);			            if(new_fd == -1)				perror("[ERR] Attente/acceptation de la connexion (accept) : ");            // TODO : Creation d'un processus fils pour gerer plusieurs demandes simultanement									switch(fork()) {								case -1:					/* erreur */					perror("[ERR] Fork processus père/fils (fork) : ");					exit(EXIT_FAILURE);									case 0:					/* processus fils */										// FERMER LE POINT DE CONNEXION DANS LE FILS					close(sockfd);					// Une connexion a eu lieu : on recupere l'adresse du client					printf("server: got connection from %s\n",						inet_ntoa(their_addr.sin_addr)); // inet_ntoa : net to ascii											// On récupère ce qu'envoie le client -> receive()					if(recv(sock_fd, &buffer, BUFFERSIZE, 0) == -1)						perror("[ERR] Réception (recv) : ");										// On traite la chaîne					buffer = "BOBBY";					// On renvoie la chaîne					if(send(new_fd, buffer, strlen(buffer), 0) == -1)						perror("[ERR] Envoi de la date/heure (send) : ");								if(close(new_fd) == -1)						perror("[ERR] Fermeture de la socket (close) : ");										exit(EXIT_SUCCESS);										break;									default:					/* processus père */								if(close(new_fd) == -1)						perror("[ERR] Fermeture de la socket (close) : ");										break;							}        }        return 0;    }