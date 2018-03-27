#include "Server.h"



Server::Server() {
    
    int sockfd, new_fd;  // sock_fd : point de connexion, new_fd : socket de transit
    struct sockaddr_in my_addr;    // adresse de transport de la socket coté serveur
    struct sockaddr_in their_addr; // adresse de transport de la socket coté client
    int sin_size; // Taille d'une adresse de transport
    int yes = 1;

    // Creation et initialisation du point de connexion
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1)
        perror("[ERR] Creation du pt de con. (socket) : ");

    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
        perror("[ERR] Initialisation du pt de con. (setsockopt) : ");

    // Configuration de l'adresse de transport
    my_addr.sin_family = AF_INET;         // type de la socket
    my_addr.sin_port = htons(MYPORT);     // port, converti en reseau
    my_addr.sin_addr.s_addr = INADDR_ANY; // adresse, devrait être converti en reseau mais est egal à 0
    bzero(&(my_addr.sin_zero), 8);        // mise a zero du reste de la structure

    // Demarrage du point de connexion : on ajoute l'adresse de transport dans la socket
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
        perror("[ERR] Démarrage du pt de con. (bind) : ");

    // Attente sur le point de connexion
    if(listen(sockfd, BACKLOG) == -1)
        perror("[ERR] Attente sur le pt de con. (listen) : ");

    // Boucle principale de traitement des demandes client
    while(1) {

        sin_size = sizeof(struct sockaddr_in);

        // Accept est bloquant : le processus n'avance pas tant que personne ne se connecte
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size);

        // Une connexion a eu lieu : on recupere l'adresse du client
        printf("server: got connection from %s\n",
                inet_ntoa(their_addr.sin_addr)); // inet_ntoa : net to ascii

        if(new_fd == -1)
            perror("[ERR] Attente/acceptation de la connexion (accept) : ");

        else
            pool_management(new_fd);

    }

    //return EXIT_SUCCESS;

}

Server::~Server() { }


    void Server::client_management(int socket) {

    //char buffer[BUFFERSIZE];
    string buffer[BUFFERSIZE];    

    while(1) {

        //buffer.clear();
        if(recv(socket, &buffer, BUFFERSIZE, 0) == -1) { perror("[ERR] Réception"); }
        else { cout << "PARSE" << endl; /*bool parse = parser();*/ }

    }
    
    /* code */

    /*

        // On envoie l'heure et la date [+ Affichage Erreur]
        if(send(socket, date_string, strlen(date_string), 0) == -1)
            perror("[ERR] Envoi de la date/heure (send) : ");

        // On ferme le point de connexion au client [+Affichage Erreur]
        if(close(socket) == -1)
            perror("[ERR] Fermeture de la socket (close) : ");

            */

}

void Server::pool_management(int socket) {

    thread tClient(client_management, socket);
    tClient.detach();
    sleep(1);

}

bool Server::parser(int argc, char *argv[]) {



	//if argc =><= &&|| argv =><
	/*
	switch (argv[1]) {

	case "REG1":
		register(argv[2], argv[3], false);
		break;

	}*/

}

bool Server::registration(string username, string password, bool second_step) {

}

bool Server::authentification(string username, string password) {

}