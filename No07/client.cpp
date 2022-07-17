#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "board.hpp"

#define OUR 'O'
#define ENEMY 'X'

#define PORT 8080

int main() {
    int csock; 
    struct sockaddr_in saddr; 
        
    if ((csock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("Failed created a socket in server side"); 
        exit(0); 
    }
        
    memset(&saddr, 0, sizeof(saddr)); 
        
    saddr.sin_family    = AF_INET; 
    saddr.sin_addr.s_addr = INADDR_ANY; 
    saddr.sin_port = htons(PORT); 

    Board tictac;
    int stat;
    while ((stat = tictac.statusGame()) != -1) {
        int choice;
        socklen_t laddr;
        bool valid;

        laddr = sizeof(saddr); 

        do {
            tictac.draw();
            std::cout << "Enter your choice (Client Side)" << std::endl;
            std::cin >> choice;
            valid = tictac.set(OUR, choice);
            if (!valid) {
                std::cout << std::endl << "Enter the valid choices" << std::endl << std::endl;
            }
        } while(!valid);

        tictac.set(OUR, choice);

        sendto(csock, &choice, sizeof(choice), MSG_CONFIRM, (struct sockaddr *) &saddr, laddr);  

        recvfrom(csock, &choice, sizeof(choice), MSG_WAITALL, (struct sockaddr *) &saddr, &laddr);

        if (choice == 0) {
            std::cout << "Congratulation! You Win" << std::endl;
            close(csock);
            return 0;
        }

        tictac.set(ENEMY, choice);

        if ((stat = tictac.statusGame())) {
            if (tictac.statusGame() != -1) break;
            int flag = -1;
            tictac.draw();
            std::cout << "You Lose! Client Side Win!" << std::endl;
            sendto(csock, &flag, sizeof(flag), MSG_CONFIRM, (struct sockaddr *) &saddr, laddr);
            close(csock);
            return 0;
        }
    }
    
    std::cout << "Game Over the result of the game is draw" << std::endl;
    close(csock);

    return 0;

}