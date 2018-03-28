#include "Server.h"

void /*Server::*/pool_management(int socket) {

    thread Client(server_behavior, socket);
    Client.detach();
    sleep(1);

}

void server_behavior(int socket) {

    int args_it = 0; // Number of arguments returned, between 0 & MAX_ARGS;
    char* args[MAX_ARGS]; // Arguments container
    Status game_status = NONE;

    // 1 - Connection & Authentification

        /* TODO (Connection, Registration, etc) */
        game_status = ONE_PLAYER;

    // 2 - Game Management

        // 2.1 Game Creation : Entry point

        while(game_status == ONE_PLAYER) {

            cout << "whileONEP" << endl; // TEMP

            //args = server_reception(socket, args_it);
            cout << server_reception(socket, args_it, *args) << endl;            

            cout << "args[0] << args[1] << args[2]" << endl; // TEMP

            cout << args[0] << endl;

            if(args[0] == "GNEW") { 

                // Game creation
                game_status = GAME_CREATED;
                server_return(GAME_CREATION_SUCCESS_GAME_CREATED);

            }

            else {

                // Unknown instruction -> Error : Common or other ?
                //server_return(_);

            }

        }

        // 2.2 Game Creation : Grid size

        while(game_status == GAME_CREATED) {

            //args = server_reception(socket, args_it);
            cout << server_reception(socket, args_it, *args) << endl;

            if(args[0] == "SIZE") {

                //if(args[1] == instanceof(int) && args[2] == instanceof(int)) {
                if(instanceof<int>(args[1]) && instanceof<int>(args[2])) {

                    if(*args[1] > 3 && *args[2] > 3) {

                        // Grid size definition
                        game_status = GAME_CONFIGURED;
                        server_return(SIZE_DEFINITION_SUCCESS_SIZE_DEFINED);

                    }

                    else {

                        server_return(SIZE_DEFINITION_ERROR_TOO_SMALL);

                    }

                }

                else {

                    server_return(SIZE_DEFINITION_ERROR_INTEGERS_REQUIRED);

                }

                // Grid size
                game_status = GAME_CREATED;
                server_return(GAME_CREATION_SUCCESS_GAME_CREATED);

            }

            else {

                // Unknown instruction -> Error : Common or other ?
                //server_return(_);

            }

        }

        /* TEMP */ cout << "REACHED" << endl << endl;

}

bool server_reception(int socket, int args_it, char* args) {

    char buffer[BUFFERSIZE]; //string buffer[BUFFERSIZE];
    char* arg;
    //char *args[MAX_ARGS]; // The definition could be here, and the reset in the while ?
    //int args_it = 0;  // Moved to the calling function

    while(1) {

        // Reset/Remise à zéro du buffer, mais aussi des arguments
        bzero(&buffer, BUFFERSIZE);
        args_it = 0;
        //char *args[MAX_ARGS]; // The definition used to be here

        // Attente de la réception d'une requête
        if(recv(socket, &buffer, BUFFERSIZE, 0) == -1) { perror("[ERR] Réception"); }

        // Découpage ("Tokenization") de la requête
        arg = strtok(buffer, " ");
        while(arg != NULL /*&& args_it < MAX_ARGS*/) {
            
            // USE VECTORS OK ?
            cout << "[" << arg << "] ";
            cout << "[" << *arg << "]" << endl;
            args[args_it] = *arg;
            cout << "[" << args[args_it] << "]";
            cout << "[" << &args[args_it] << "]" << endl;
            args_it++;

            arg = strtok(NULL, " ");
        }

        // TODO : if args_it == 0 / args == null / etcc (VERIF) + MAX_ARGS ?

        // Retour de la requête, découpée 
        return true;


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