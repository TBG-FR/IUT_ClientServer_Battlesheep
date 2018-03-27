#include "exercice1.h"

/* ----- ----- DEFINITIONS ----- ----- */

#define MYPORT 3490    // Port du point de connexion
#define BACKLOG 10     // Combien de connexion en attente autorise-t-on ?
#define MAXDATASIZE 100 // Nombre maximal d'octer a envoyer en une fois

#define NB_THREADS 2 // Nombre de Threads dans notre Pool

//CSemaphore Pool_Access(1);
//CSemaphore Pool_NB(1);
//int Threads = 0;

/*
 * Reçoit un ID de socket et renvoie le Daytime au client correspondant
 */
void daytime_thread(int socket) {

    // On recupere l'heure et la date
    struct timeval time_value;
    gettimeofday(&time_value, NULL);
    char* date_string = ctime(&(time_value.tv_sec));

    // TEMPORISATION
    printf("[INFO] Envoi de la requête au client...");
    sleep(2);

    // On envoie l'heure et la date [+ Affichage Erreur]
    if(send(socket, date_string, strlen(date_string), 0) == -1)
        perror("[ERR] Envoi de la date/heure (send) : ");

    // On ferme le point de connexion au client [+Affichage Erreur]
    if(close(socket) == -1)
        perror("[ERR] Fermeture de la socket (close) : ");

    //Pool_NB.wait();
    //Threads--;
    //Pool_NB.notify();

}

/*
 * Gère l'accès au Pool de Threads (Critique)
 */
void pool_management(int socket) {

    //Pool_Access.wait(); // SYNC - Demander l'accès au Pool

    //Pool_NB.wait();

    //if(Threads < NB_THREADS) {

        std::thread Daytime(daytime_thread, socket);
        Daytime.detach();
        sleep(1);

        //Threads++;
        //Pool_NB.notify();

    //}

    //else {

        //Pool_NB.notify();
        // Attendre (Aucun thread n'est libre, on attend donc un Notify + Threads > NB_THREADS)

    //}

    //Pool_Access.notify(); // SYNC - Libérer l'accès au Pool

}

/*
 * Serveur Daytime en version 'pthread'
 */
int exercice1(void)
	{
        int sockfd, new_fd;  // sock_fd : point de connexion, new_fd : socket de transit
        struct sockaddr_in my_addr;    // adresse de transport de la socket coté serveur
        struct sockaddr_in their_addr; // adresse de transport de la socket coté client
        int sin_size; // Taille d'une adresse de transport
        int yes = 1;
        char* date_string; // Chaine de caractere contenant la date
        struct timeval time_value;

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
        while(1)
        {

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

        return EXIT_SUCCESS;
	}
