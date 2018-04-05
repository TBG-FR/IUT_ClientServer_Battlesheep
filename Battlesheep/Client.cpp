#include "Client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT_C 3490    // Port (serveur)
#define BUFFERSIZE_C 500 // Taille du buffer

int client_main(/*int socket*/) {
    
    // Variables liées à la socket/connexion
    int sock_serv;  // sock_serv : point de connexion
    struct sockaddr_in serv_addr;    // adresse de transport (adresse du serveur)
	int addrlen;
	char buffer[BUFFERSIZE_C];
    
    // Création du point de connexion
    sock_serv = socket(AF_INET, SOCK_STREAM, 0);    
    if(sock_serv == -1) {

        perror("[Erreur] Impossible de créer le point de connexion !");
        return EXIT_FAILURE;

    }
    
    // Demande de l'adresse IP du serveur
    char input_addr[15] = "127.0.0.1";
    cout << "Veuillez entrer l'adresse IP du serveur" << endl;
    cin >>  input_addr;
        
	// Configuration de l'adresse de transport
	serv_addr.sin_family = AF_INET;         // type de la socket
	serv_addr.sin_port = htons(MYPORT_C);     // port, converti en reseau
	serv_addr.sin_addr.s_addr = inet_addr(input_addr); // adresse, convertie en int [PAS DE conversion réseau nécessaire]
	//serv_addr.sin_addr.s_addr = gethostbyname(input_addr); // adresse, convertie en int [PAS DE conversion réseau nécessaire]
	bzero(&(serv_addr.sin_zero), 8);        // mise a zero du reste de la structure
	
    // Vérification de l'adresse
	if(serv_addr.sin_addr.s_addr == INADDR_NONE) {

        perror("[Erreur] Adresse IP du serveur invalide !");
        return EXIT_FAILURE;

	}
			
	// Connexion
    addrlen = sizeof(serv_addr);
	if(connect(sock_serv, (struct sockaddr*)&serv_addr, addrlen) == -1){

        perror("[Erreur] Connexion impossible !");
        return EXIT_FAILURE;

	}

    // Variables utiles pour la gestion des commandes/arguments
    vector<string> args;
    int min_args = 0, max_args = 0;
    string input;
    bool again = true;

    // Variables dédiées au Jeu
    Status game_status_c = NONE;

   // TODO : Inscription, Connexion, parties publiques/privées, Gestion créer/rejoindre
    /*
    // Démarrage du jeu en tant que P1 ou P2
    if(input == "new") { send(sock_serv, "GNEW public", strlen("GNEW public"), 0); }
    else if(input == "join") { send(sock_serv, "JOIN ________", strlen("JOIN ___________"), 0); }
    else { again = true; }

    cout << "Voulez vous créer une partie ou en rejoindre une ?" << endl;
    cout << "(Tapez 'new' pour créer, 'join' pour rejoindre)" << endl;
    */

    while(game_status_c == NONE) {

        switch(client_reception(sock_serv, args)) {

            case -1:
                // Message d'erreur ?
                break;

            case TEMP_CONN_PLAYER_ONE:
                game_status_c = ONE_PLAYER;
                break;

            case TEMP_CONN_PLAYER_TWO:
                game_status_c = TWO_PLAYERS;
                break;

            default:
                // do nothing
                break;

        }

    }

    while(game_status_c == ONE_PLAYER) {
        
        send(sock_serv, "GNEW public", strlen("GNEW public"), 0);

        switch(client_reception(sock_serv, args)) {

            case -1:
                // Message d'erreur ?
                break;

            case GAME_CREATION_SUCCESS_GAME_CREATED:
                cout << "[INFO] La partie a été créée avec succès !" << endl;
                game_status_c = GAME_CREATED;
                break;

            case GAME_CREATION_ERROR_COMMON_UNKNOWN:
                cout << "[ERREUR] Problème lors de la création de la partie..." << endl;
                break;

            default:
                // do nothing
                break;

        }

    }
    
    while(game_status_c == GAME_CREATED) {

        //TODO : Définition de la taille de la grille

    }

    while(game_status_c == TWO_PLAYERS) {

        //TODO : déroulement du jeu à partir de l'étape "TWO_PLAYERS"

    }

    // TODO : Suite du déroulement du jeu puis fermeture de la socket à la fin

}

int client_reception(int socket, vector<string> &args) {

    char buffer[BUFFERSIZE];
    char* arg;

    while(1) {

        // Remise à zéro du buffer et des arguments
        bzero(&buffer, BUFFERSIZE);
        args.clear();

        // Attente de la réception d'une requête
        if(recv(socket, &buffer, BUFFERSIZE, 0) == -1) {

            perror("[Erreur] Erreur de réception !");
            return EXIT_FAILURE;

        }

        // Découpage ("Tokenization") de la requête
        arg = strtok(buffer, " ");
        while(arg != NULL /*&& args_it < MAX_ARGS*/) {

            cout << "[" << arg << "] ";
            args.push_back(arg);

            arg = strtok(NULL, " ");
        }
        
        //if (instanceof<int>(stoi_noex(args.at(0))) { return stoi_noex(args.at(0); }
        //else { return -1; }
        return stoi_noex(args.at(0));

    }

}

//bool parser(int argc, char *argv[]) {}
//bool parser(vector<string> args);


