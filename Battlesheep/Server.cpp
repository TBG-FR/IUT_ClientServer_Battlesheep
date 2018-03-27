#include "Server.h"

void /*Server::*/pool_management(int socket) {

    thread Client(client_management, socket);
    Client.detach();
    sleep(1);

}

void /*Server::*/client_management(int socket) {

    char buffer[BUFFERSIZE]; //string buffer[BUFFERSIZE];
    char * arg;
    //char *args[MAX_ARGS];
    int args_it = 0;

    while(1) {

        // Reset/Remise à zéro du buffer, mais aussi des arguments
        bzero(&buffer, BUFFERSIZE);
        char *args[MAX_ARGS]; 
        args_it = 0;

        // Attente de la réception d'une requête
        if(recv(socket, &buffer, BUFFERSIZE, 0) == -1) { perror("[ERR] Réception"); }

        // Découpage ("Tokenization") de la requête
        arg = strtok(buffer, " ");
        while(arg != NULL && args_it < MAX_ARGS) {
            args[args_it] = arg;
            args_it++;
            arg = strtok(NULL, " ");
        }

        // Envoi des arguments au parser 
        parser(args_it, args);

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

bool /*Server::*/parser(int argc, char *argv[]) {

    for(int i=0; i<argc; i++) { cout << " - " << argv[i]; }
    cout << endl << endl; /* TEMP */

    cout << "PARSE_CHAR_ARGS" << endl;

    if(argc <= 0) {

        switch(argv[0]) {

            /*
            case "CONN": //ServerRequests.CONN
                cout << "CONN TEST";
                break;
            */

        }

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

	}*/

}

bool /*Server::*/registration(string username, string password, bool second_step) { }

bool /*Server::*/authentification(string username, string password) { }

/*
// Should never be used
Server::Server() {}
Server::~Server() {}
*/