#include "Server.h"

#define MYPORT 3490		// Port du point de connexion
#define NB_THREADS 2   // Nombre de Threads dans notre Pool => NB_PLAYERS
#define BUFFERSIZE 200 // Taille du Buffer
#define BACKLOG 10     // Nombre de connexion autorisées => A changer ?

// Variables liées aux threads/sockets
int player_threads = 0;
int sockets_p[NB_THREADS];

// Variables propres au jeu
Status game_status;
int dim1 = 0, dim2 = 0;
int*** grids_p = new int**[NB_THREADS];
int** grid_filled;
int count_total, count_boats;
int count_hits_p[NB_THREADS];

void pool_management(int socket) {

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

    /*TEMP*/ cout << "-- CONN PLAYER #" << player << endl;    
    // TODO : Améliorer si on veut plus de 2 joueurs
    // -> sockets_p[player] = socket;
    sockets_p[1] = socket;
    game_status = TWO_PLAYERS;

}

void server_behavior(int socket, int player) {

    /*TEMP*/ cout << "-- CONN PLAYER #" << player << endl;
    
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

            else { server_return(GAME_CREATION_ERROR_COMMON_UNKNOWN); }

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

                        /* ----------MOVED INTO NEXT PART----------
                        // Players' Grid - Initialization
                        for(int x = 0; x < NB_THREADS; ++x) {
                            grids_p[x] = new int*[dim1];
                            for(int y = 0; y < dim1; ++y) {
                                grids_p[x][y] = new int[dim2];
                                for(int z = 0; z < dim2; ++z) { // initialize the values to whatever you want the default to be
                                    grids_p[x][y][z] = 0;
                                }
                            }
                        } */

                        // Temporary Grid - Initialization
                        grid_filled = new int*[dim1];

                        for(int x = 0; x < dim1; ++x) {
                            grid_filled[x] = new int[dim2];
                            for(int y = 0; y < dim2; ++y) {
                                grid_filled[x][y] = 0;
                            }
                        }

                        count_total = dim1 * dim2;  // NxN, NxM
                        count_boats = 0.2 * dim1 * dim2; // 0.2 * N², 0.2 * N * M
                        for(int i=0; i<NB_THREADS; i++) { count_hits_p[NB_THREADS] = 0; }

                        server_return(SIZE_DEFINITION_SUCCESS_SIZE_DEFINED);
                        game_status = GAME_CONFIGURED;

                    }

                    else { server_return(SIZE_DEFINITION_ERROR_TOO_SMALL); }

                }

                else { server_return(SIZE_DEFINITION_ERROR_INTEGERS_REQUIRED); }

            }

            else { server_return(SIZE_DEFINITION_ERROR_COMMON_UNKNOWN); }

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

            // Variables additionnelles
            bool* grid_ok_p = new bool[NB_THREADS];
            for(int i=0; i<NB_THREADS; i++) { grid_ok_p[i] = false; }

            // Pour chaque joueur, demande de la grille en boucle tant qu'elle n'est pas valide
            for(int i=0; i<NB_THREADS; i++) {

                while(grid_ok_p[i] == false) {

                    args.clear();

                    if(server_reception(sockets_p[i], args, min_args, max_args) == true && args.at(0) == "GRID") {

                        //TODO : ARGS into GRID with function stog
                        //                          = stog(args.at(2));
                        //int grid_filled[dim1][dim2] = { {0, 1, 0}, {0, 1, 0},  {0, 1, 0} };
                        grid_filled = stog(args.at(1));
                        
                        int gridcheck_answer = grid_check(*grid_filled, dim1, dim2);

                        switch(gridcheck_answer) {

                            case 0: // Correct Grid

                                // Players' Grid - Initialization
                                grids_p[i] = new int*[dim1];
                                for(int y = 0; y < dim1; ++y) {
                                    grids_p[i][y] = new int[dim2];
                                    for(int z = 0; z < dim2; ++z) { // initialize the values to whatever you want the default to be
                                        grids_p[i][y][z] = grid_filled[y][z];
                                    }
                                }
                                //*grids_p[i] = *grid_filled;
                                grid_ok_p[i] = true;
                                server_return(GAME_INITIALIZATION_SUCCESS_CORRECT_GRID);
                                // TODO Destruction du tableau grid_filled
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

                    }

                    else { server_return(GAME_INITIALIZATION_ERROR_COMMON_UNKNOWN); }

                }

            }

            // Passage au jeu
            server_return(GAME_INITIALIZATION_SUCCESS_CORRECT_GRIDS);
            game_status = INGAME;

        }

        while(game_status == INGAME) {

            // Remise à zéro des arguments, par précaution
            args.clear();

            // Définition du nombre d'arguments attendus
            min_args = 3;
            max_args = 3;

            // Variables additionnelles
            bool replay_p[NB_THREADS];
            int ennemy;

            // Mise en attente des clients puis Traitement des réponses
            for(int i = 0; i < NB_THREADS; i++) {
                
                // Nécessaire au lancement du tour
                replay_p[i] = true;

                // Définition de l'ennemi
                //TODO : améliorer pour un jeu à plus de 2 joueurs
                switch(i) {
                    case 0:
                        ennemy = 1;
                        break;

                    case 1:
                        ennemy = 0;
                        break;
                        
                    default:
                        cout << "UNDEFINED ENNEMY";
                        ennemy = -1;
                        break;
                }

                bool existing_enn = false; // Replaces 'while(replay == true && (ennemy == (0 || 1))) {'
                for(int j=0; j<NB_THREADS; j++) { if(ennemy == j) { existing_enn = true; } }            
                while(replay_p[i] == true && existing_enn == true) {

                    cout << "[INFO][TURN] Player " << i << " versus Player " << ennemy << endl;

                    args.clear();
                    replay_p[i] = false;

                    if(server_reception(sockets_p[i], args, min_args, max_args) == true && args.at(0) == "PLAY")
                    {
                        int shotdim1 = stoi_noex(args.at(1));
                        int shotdim2 = stoi_noex(args.at(2));

                        // Si le tir est bien dans la grille
                        if( shotdim1 <= dim1 || shotdim2 <= dim2) {

                            cout << "[INFO][TURN] P" << i << " shot P" << ennemy << " at [" << shotdim1 
                            << "][" << shotdim2 << " [";
                            
                            switch(grids_p[ennemy][shotdim1][shotdim2]) {

                                case 1: // Touché
                                    cout << "1 (Boat) ->  2 (Boat shot)]" << endl;

                                    server_return(GAME_PLAY_SUCCESS_TURN_PLAYED);
                                    server_return(GAME_PLAY_SUCCESS_SHOT_BOATCELL);
                                    grids_p[ennemy][shotdim1][shotdim2] = 2;
                                    count_hits_p[ennemy]++;

                                    // TODO : Check if "Coulé"
                                    
                                    // Si tous les bateaux ont été coulés
                                    //if(count_hits_p[ennemy] == count_boats) {
                                    if(count_hits_p[ennemy] == 3) { //TEMP
                                        game_status = ENDGAME;
                                        replay_p[i] = false;
                                    }
                                    else { replay_p[i] = true; }
                                    break;

                                case 2: // Déjà touché
                                    cout << "2 (Boat already shot)]" << endl;
                                    server_return(GAME_PLAY_SUCCESS_TURN_PLAYED);
                                    server_return(GAME_PLAY_SUCCESS_SHOT_ALREADYCELL);
                                    break;
                                
                                case 0: // Dans l'eau
                                    cout << "0 (Water)]" << endl;
                                    server_return(GAME_PLAY_SUCCESS_TURN_PLAYED);
                                    server_return(GAME_PLAY_SUCCESS_SHOT_EMPTYCELL);
                                    break;

                                default: // Etat inconnu
                                    cout << "? (Error ?)]" << endl;
                                    server_return(GAME_PLAY_ERROR_COMMON_UNKNOWN);
                                    replay_p[i] = true;
                                    break;

                            }

                            // INFO : Affichage des grilles des joueurs
                            cout << "[INFO][TURN] Displaying players' grids..." << endl;                            
                            for(int x=0; x<NB_THREADS; x++) {

                                cout << "----- ----- Player " << x << " - Grid Status ----- -----";

                                for(int y=0; y<dim1; y++) {

                                    cout << endl;

                                    for(int z=0; z<dim2; z++) {

                                        cout << " | " << grids_p[x][y][z];

                                    }

                                    cout << " | ";

                                }

                                cout << endl << endl;

                            }

                        }

                        else { server_return(GAME_PLAY_ERROR_OUTSIDE_BOUNDS); }

                    }

                    else { server_return(GAME_PLAY_ERROR_COMMON_UNKNOWN); replay_p[i] = false; }

                }

            }

        }

        while(game_status == ENDGAME) {

            game_status = GAME_PAUSED; // TEMP
            cout << "ENDGAME"; // TEMP

            // TODO : Proposer de rejouer

        }

        for(int i=0; i<NB_THREADS; i++) { close(sockets_p[i]); }
        // TODO : Destruction des tableaux grids_p

        /* TEMP */ cout << " 'EOF' REACHED" << endl << endl;

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

}

void server_return(int message) {

    // TODO : Send the response code (message) to the client
    // Needed : Header (R_OK or R_ER)
    //          Code (ex: 120, 220, etc)
    //
    // TODO : Add socket ? (p1 or p2)
    //          -> void server_return(int socket, int message);
    //

    for(int i=0; i<NB_THREADS; i++) {

        cout << "P[" << i << "]";
        cout << "[Server:Return] " << message << endl;

    }

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

bool registration(string username, string password, bool second_step) { }

bool authentification(string username, string password) { }
