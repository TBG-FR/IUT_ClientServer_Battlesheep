/*
    ** select.c -- a select() demo
    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <sys/time.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    #define MYPORT 3490 
    #define BACKLOG 10
	
	#define NB_CLIENTS 4

    int main(void)
    {
    	int sockfd, client_fd[NB_CLIENTS];  // sock_fd : point de connexion, new_fd : socket de transit
    	int maxfd;
        struct sockaddr_in my_addr;    // adresse de transport de la socket coté serveur
        struct sockaddr_in their_addr; // adresse de transport de la socket coté client
        fd_set readfds;
        fd_set originalfds;
        int yes = 1;
        char msg[100];
		
    	// Créer point de connextion et attente
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			perror("Creation socket : ");
			exit(EXIT_FAILURE);
		}
        if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
        {
			perror("Options socket : ");
			exit(EXIT_FAILURE);
        }
        
        // Configuration de l'adresse de transport        
        my_addr.sin_family = AF_INET;         // type de la socket
        my_addr.sin_port = htons(MYPORT);     // port, converti en reseau
        my_addr.sin_addr.s_addr = INADDR_ANY; // adresse, devrait être converti en reseau mais est egal à 0
        bzero(&(my_addr.sin_zero), 8);        // mise a zero du reste de la structure

		// Creation du point de connexion : on ajoute l'adresse de transport dans la socket		
        if((bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))) == -1)
        {
        	perror("Creation point connexion");
			exit(EXIT_FAILURE);
        }

		// Attente sur le point de connexion
        if(listen(sockfd, BACKLOG) == -1)
        {
        	perror("Listen socket : ");
			exit(EXIT_FAILURE);
        }
    	
		// EX2_1_V1 : CONNECTER TOUS LES USERS, PUIS GERER LES SETS DE SOCKETS
		
    	// attendre n clients
    	unsigned int sin_size = sizeof(struct sockaddr);
		
		int i = 0;
		for(i = 0; i < NB_CLIENTS; i++) {
			
			printf("[INFO] Attente du client #N \n");
			
			if((client_fd[i] = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
				perror("[ERR] Accept (un des client) \n");
				close(sockfd);
				exit(EXIT_FAILURE);
			}
			
			printf("[INFO] Client #N connecté depuis %s \n", inet_ntoa(their_addr.sin_addr));
			
			
		}
    	
    	// Determination du max
		maxfd = 0;
		
		for(i = 0; i < NB_CLIENTS; i++) {
			
			if(client_fd[i] > maxfd) { maxfd = client_fd[i]+1; }
		}
    		
    	printf("maxfd = %d\n", maxfd);
    	
    	// Creation des ensemble en lecture et ecriture
    	// Un "original" est nécessaire : les ensemble sont modifies par select
	    FD_ZERO(&originalfds);
	    FD_ZERO(&readfds);
	    
    	// Ajouter les deux sockets de com dans le select en lecture
		for(i = 0; i < NB_CLIENTS; i++) {
		
			FD_SET(client_fd[i], &originalfds);
			
		}

    	// Boucle ici
    	while(1)
    	{	        
	        readfds = originalfds; // => INFO : Remet à "zéro" 'readfds' car on ne peut pas le tester ('FD_ISSET') plusieurs fois sinon
	        
        	// Select doit être parametre avec le numero max du descripteur, +1
			printf("debut du select \n");
    	    if (select(maxfd, &readfds, NULL, NULL, NULL) == -1) // => INFO : active la surveillance
        	{
        		perror("[ERR] Problème lors du Select");
				for(i = 0; i < NB_CLIENTS; i++) { close(client_fd[i]); }
        		close (sockfd);
        		exit(EXIT_FAILURE);
        	}

    	// Controler si les sockets on ete lues ou ecrites
		
			for(i = 0; i < NB_CLIENTS; i++) {
				
				if (FD_ISSET(client_fd[i], &readfds)) {
					
					//bzero(&msg, 100);				
					printf("[INFO] Message de Client #0%s \n", i);
					
					if(recv(client_fd[i], &msg, 100, 0) == -1)
						perror("[ERR] Réception (recv) : ");
					
					int j = 0;
					for(j = 0; j < NB_CLIENTS; j++) {
						
						if(i != j) {
							
							if(send(client_fd[j], msg, 100, 0) == -1)
								perror("[ERR] Envoi du msg à un des clients");
							
						}
						
					}
					
					printf("[MESSAGE] [%s=>*] : %d \n", i, msg);
				
					continue;
				
				}
				
    		}
			
    	}
    	   	            
    	// Agir en consequence
		for(i = 0; i < NB_CLIENTS; i++) { close(client_fd[i]); }
        close (sockfd);
        
        return 0;
    } 