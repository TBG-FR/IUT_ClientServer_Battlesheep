#include "Server.h"

#define MYPORT 3490		// Port du point de connexion
#define BACKLOG 10		// Combien de connexion en attente autorise-t-on ?
#define MAXDATASIZE 100 // Nombre maximal d'octer a envoyer en une fois

#define NB_THREADS 2   // Nombre de Threads dans notre Pool => NB_PLAYERS
#define BUFFERSIZE 200 // Taille du Buffer

int player_threads = 0;
Status game_status;
int sockets_p[NB_THREADS];

void /*Server::*/pool_management(int socket) {

        //if(player_threads <= NB_THREADS) {
        // TODO : Gestion des connexions p1/p2
        // CONN -> p1
        // CONN {ip/number} => p2
        
    if(player_threads == 0) {

        thread Client(server_behavior,socket,player_threads+1);
        player_threads++;
        Client.detach();
        sleep(1);

    }

    else if(player_threads == 1) {

        thread Client(add_player,socket,player_threads+1);
        player_threads++;
        Client.detach();
        sleep(1);

    }

    else {

        /* TEMP */ cout << "NB MAX DE JOUEURS ATTEINT" << endl;

    }

}

void add_player(int socket, int player) {
    
    sockets_p[1] = socket;
    game_status = TWO_PLAYERS;

}

void server_behavior(int socket, int player) {

    /*TEMP*/ cout << "-- CONN PLAYER #0" << player << endl;

    // Variables propres au jeu
    int dim1 = 0, dim2 = 0;
    int count_total, count_boats;
    int count_p1_touched, count_p2_touched;
    
    // Détermination du comportement à adopter
        // p1 -> souhaite créer une nouvelle partie
        // p2 -> souhaite rejoindre une partie existante
    /*
    switch(player) {

        case 1: // New game -> Let's create !
            socket_p1 = socket;
            //Status game_status = NONE;
            game_status = ONE_PLAYER; //TEMP
            break;

        case 2: // Existing game -> Let's join !
            socket_p2 = socket;
            game_status = TWO_PLAYERS;
            break;

        default:
            game_status = NONE;
            break;

    }*/    
    sockets_p[0] = socket;
    //Status game_status = NONE;
    game_status = ONE_PLAYER; //TEMP

    // Variables utiles pour la gestion des arguments
    vector<string> args;
    int min_args = 0, max_args = 0;

    // 1 - Connection & Authentification

        /* TODO (Connection, Registration, etc) */
        //game_status = ONE_PLAYER;

    // 2 - Game Management

        // 2.1 Game Creation : Entry point (p1)
        while(game_status == ONE_PLAYER) {

            // Remise à zéro des arguments, par précaution
            args.clear();

            // Définition du nombre d'arguments attendus
            min_args = 2;
            max_args = 3;

            // Mise en attente du client puis Traitement de la réponse
            if(server_reception(socket, args, min_args, max_args) == true && args.at(0) == "GNEW")
            {

                // REVOIR Cette partie :
                    // Que faire si ni public ni private ?
                    // SI private mais pas d'user ?
                    // etc...
                //if(args.at(2) == "private" && )

                // Game creation
                server_return(GAME_CREATION_SUCCESS_GAME_CREATED);
                game_status = GAME_CREATED;

            }

            else {

                // Unknown instruction -> Error : Common or other ?
                //server_return(_);

            }

        }

        // 2.2 Game Creation : Grid size
        while(game_status == GAME_CREATED) {

            // Remise à zéro des arguments, par précaution
            args.clear();

            // Définition du nombre d'arguments attendus
            min_args = 3;
            max_args = 3;

            // Mise en attente du client puis Traitement de la réponse
            if(server_reception(socket, args, min_args, max_args) == true && args.at(0) == "SIZE")
            {

                dim1 = stoi_noex(args.at(1));
                dim2 = stoi_noex(args.at(2));
                
                if(dim1 != -1 || dim2 != -1) {

                    if(dim1 >= 3 && dim2 >= 3) {

                        // Grid size definition
                        server_return(SIZE_DEFINITION_SUCCESS_SIZE_DEFINED);
                        game_status = GAME_CONFIGURED;

                    }

                    else { server_return(SIZE_DEFINITION_ERROR_TOO_SMALL); }

                }

                else { server_return(SIZE_DEFINITION_ERROR_INTEGERS_REQUIRED); }

            }

            else {

                // Unknown instruction -> Error : Common or other ?
                //server_return(_);

            }

        }

        // 2.3 Game Creation : Initialization

        while(game_status == GAME_CONFIGURED) {

            // Do nothing, wait for second player

        } server_return(GAME_INITIALIZATION_SUCCESS_SECOND_PLAYER);

        while(game_status == TWO_PLAYERS) {

            // Remise à zéro des arguments, par précaution
            args.clear();

            // Définition du nombre d'arguments attendus
            min_args = 2;
            max_args = 2;

            // Mise en attente des clients puis Traitement des réponses
            for(int i = 0; i < NB_THREADS; i++) {

                if(server_reception(sockets_p[i], args, min_args, max_args) == true && args.at(0) == "GRID")
                {

                    //TODO : ARGS into GRID with function stog
                    //                          = stog(args.at(2));
                    //int grid_filled[dim1][dim2] = { {0, 1, 0}, {0, 1, 0},  {0, 1, 0} };
                    int* grid_filled =  stog(args.at(2));

                    int gridcheck_answer = grid_check(grid_filled, dim1, dim2);

                    switch(gridcheck_answer) {

                        case 0: // Correct Grid
                            server_return(GAME_INITIALIZATION_SUCCESS_CORRECT_GRID);
                            game_status == INGAME;
                            break;

                        case -1: // Invalid number of boats
                            server_return(GAME_INITIALIZATION_ERROR_INVALID_NUMBER);
                            break;

                        case -2: // Invalid boat placement
                            server_return(GAME_INITIALIZATION_ERROR_INVALID_PLACEMENT);
                            break;

                        default: // Other answer
                            server_return(GAME_INITIALIZATION_ERROR_COMMON_UNKNOWN);
                            break;

                    }

                    // code here ?

                }

                else {

                    // Unknown instruction -> Error : Common or other ?
                    //server_return(_);

                }

            }

        }

        while(game_status == INGAME) {

            // PLAY TURN P1
            // CHECK GRID (stog ?)
            // CHECK ENDGAME
            // PLAY TURN P2
            // CHECK GRID (stog ?)
            // CHECK ENDGAME
            // REPEAT UNTIL END OR ERROR (DISCONNECT, ETC
            game_status = ENDGAME;

        }

        /* TEMP */ cout << "REACHED" << endl << endl;

}

bool server_reception(int socket, vector<string> &args, int min_args, int max_args) {

    char buffer[BUFFERSIZE];
    char* arg;

    while(1) {

        // Remise à zéro du buffer et des arguments
        bzero(&buffer, BUFFERSIZE);
        args.clear();

        // Attente de la réception d'une requête
        if(recv(socket, &buffer, BUFFERSIZE, 0) == -1) { perror("[ERR] Réception"); }

        // Découpage ("Tokenization") de la requête
        arg = strtok(buffer, " ");
        while(arg != NULL /*&& args_it < MAX_ARGS*/) {

            cout << "[" << arg << "] ";
            args.push_back(arg);

            arg = strtok(NULL, " ");
        }

        // TODO : if args_it == 0 / args == null / etcc (VERIF) + MAX_ARGS ?
        if( args.size() < min_args && args.size() > max_args ) { return false; }
        else { return true; }


    }
    /*

        // On envoie l'heure et la date [+ Affichage Erreur]
        if(send(socket, date_string, strlen(date_string), 0) == -1)
            perror("[ERR] Envoi de la date/heure (send) : ");

        // On ferme le point de connexion au client [+Affichage Erreur]
        if(close(socket) == -1)
            perror("[ERR] Fermeture de la socket (close) : ");

            */

}

void server_return(int message) {

    // TODO : Send the response code (message) to the client
    // Needed : Header (R_OK or R_ER)
    //          Code (ex: 120, 220, etc)
    //
    // TODO : Add socket ? (p1 or p2)
    //          -> void server_return(int socket, int message);
    //
    cout << "[Server:Return] " << message << endl;

}

/*
bool //Server:://parser(int argc, char *argv[]) {

    for(int i=0; i<argc; i++) { cout << " - " << argv[i]; }
    cout << endl << endl; //TEMP

    cout << "PARSE_CHAR_ARGS" << endl;

    if(argc <= 0) {

        //switch(argv[0]) {

            //case "CONN": //ServerRequests.CONN
            //    cout << "CONN TEST";
            //    break;
            

        //}

    }

    else if(argc == 1) {

        //CODE

    }

    else if(argc == 2) {

        //CODE

    }

    else if(argc == 3) {

        //CODE

    }

    else {

        //CODE

    }

	//if argc =><= &&|| argv =><
	/*
	switch (argv[1]) {

	case "REG1":
		register(argv[2], argv[3], false);
		break;

	}

}
*/

bool /*Server::*/registration(string username, string password, bool second_step) { }

bool /*Server::*/authentification(string username, string password) { }

/*
// Should never be used
Server::Server() {}
Server::~Server() {}
*/