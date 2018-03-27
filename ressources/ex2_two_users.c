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

    int main(void)
    {
    	int sockfd, client1_fd, client2_fd;  // sock_fd : point de connexion, new_fd : socket de transit
    	int maxfd;
        struct sockaddr_in my_addr;    // adresse de transport de la socket coté serveur
        struct sockaddr_in their_addr; // adresse de transport de la socket coté client
        fd_set readfds;
        fd_set originalfds;
        int yes = 1;
        char msg[100];

		//#region -- Sockets & All --
		
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
    	
    	// attendre deux clients
    	printf("attente du premier client…\n");
    	unsigned int sin_size = sizeof(struct sockaddr);
    	if((client1_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        {
            perror("Accept premier client : ");
            close(sockfd);
			exit(EXIT_FAILURE);
        }
        printf("premier client: connection depuis %s\n", inet_ntoa(their_addr.sin_addr));
        
    	printf("attente du deuxieme client…\n");

    	if((client2_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
        {
            perror("Accept second client : ");
            close(sockfd);
			exit(EXIT_FAILURE);
        }
        printf("second client: connection depuis %s\n", inet_ntoa(their_addr.sin_addr));
    	
    	// Determination du max
    	if (client1_fd < client2_fd) 
    		maxfd = client2_fd+1;
    	else 
    		maxfd = client1_fd+1;
    		
    	printf("maxfd = %d\n", maxfd);
		
		//#endregion
    	
    	// Creation des ensemble en lecture et ecriture
    	// Un "original" est nécessaire : les ensemble sont modifies par select
	    FD_ZERO(&originalfds);
	    FD_ZERO(&readfds);
	    
    	// Ajouter les deux sockets de com dans le select en lecture
        FD_SET(client1_fd, &originalfds);
        FD_SET(client2_fd, &originalfds);

    	// Boucle ici
    	while(1)
    	{	        
	        readfds = originalfds; // => INFO : Remet à "zéro" 'readfds' car on ne peut pas le tester ('FD_ISSET') plusieurs fois sinon
	        
        	// Select doit être parametre avec le numero max du descripteur, +1
			printf("debut du select \n");
    	    if (select(maxfd, &readfds, NULL, NULL, NULL) == -1) // => INFO : active la surveillance
        	{
        		perror("Pb select");
        		close (client1_fd);
        		close (client2_fd);
        		close (sockfd);
        		exit(EXIT_FAILURE);
        	}

    	// Controler si les sockets on ete lues ou ecrites
		
    		if (FD_ISSET(client1_fd, &readfds))
    		{
				bzero(&msg, 100);
				
            	printf("[INFO] Message de Client1 \n");
            	// A compléter…
			
				//receive
				if(recv(client1_fd, &msg, 100, 0) == -1)
						perror("[ERR] Réception (recv) : ");
					
				//write
				if(send(client2_fd, msg, 100, 0) == -1)
					perror("[ERR] Envoi du msg (send) : ");
					
				//message
				printf("[MESSAGE] [1=>2] : %s \n", msg);
				
            	continue;
    		}
			
    		if (FD_ISSET(client2_fd, &readfds))
    		{
				bzero(&msg, 100);
				
            	printf("[INFO] Message de Client2 \n");
            	// A compléter…
			
				//receive
				if(recv(client2_fd, &msg, 100, 0) == -1)
						perror("[ERR] Réception (recv) : ");
					
				//write
				if(send(client1_fd, msg, 100, 0) == -1)
					perror("[ERR] Envoi du msg (send) : ");
					
				//message
				printf("[MESSAGE] [2=>1] : %s \n", msg);
				
            	continue;
    		}
			
    	}
    	   	            
    	// Agir en consequence
        close (client1_fd);
        close (client2_fd);
        close (sockfd);
        
        return 0;
    } 