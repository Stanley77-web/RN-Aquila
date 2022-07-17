#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "board.hpp"

#define OUR 'X'
#define ENEMY 'O'

#define PORT 8080

int main() {
    int ssock; 
    struct sockaddr_in saddr, caddr; 
        
    if ((ssock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("Failed created a socket in server side"); 
        exit(0); 
    } 
        
    memset(&saddr, 0, sizeof(saddr)); 
    memset(&caddr, 0, sizeof(caddr)); 
        
    saddr.sin_family    = AF_INET; // IPv4 
    saddr.sin_addr.s_addr = INADDR_ANY; 
    saddr.sin_port = htons(PORT); 

    int val = 1;
    if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(0);
    }

    // Bind the socket with the server address 
    if (bind(ssock, (const struct sockaddr *) &saddr, sizeof(saddr)) < 0 ) { 
        perror("Failed binding at server side"); 
        exit(0); 
    }         

    std::cout << "Binding Succesfully" << std::endl;

    Board tictac;
    int stat;
    while ((stat = tictac.statusGame()) != -1) {
        int choice;
        socklen_t laddr;
        bool valid;

        laddr = sizeof(caddr);

        recvfrom(ssock, &choice, sizeof(choice), MSG_WAITALL, (struct sockaddr *) &caddr, &laddr);

        if (choice == -1) {
            std::cout << "Congratulation! You Win" << std::endl;
            close(ssock);
            return 0;
        }

        tictac.set(ENEMY, choice);

        if ((stat = tictac.statusGame())) {
            if (tictac.statusGame() != -1) break;
            int flag = 0;
            tictac.draw();
            std::cout << "You Lose! Client Side Win!" << std::endl;
            sendto(ssock, &flag, sizeof(flag), MSG_CONFIRM, (struct sockaddr *) &caddr, laddr);
            close(ssock);
            return 0;
        }

        do {
            tictac.draw();
            std::cout << "Enter your choice (Server Side)" << std::endl;
            std::cin >> choice;
            valid = tictac.set(OUR, choice);
            if (!valid) {
                std::cout << std::endl << "Enter the valid choices" << std::endl << std::endl;
            }
        } while(!valid);

        tictac.set(OUR, choice);

        sendto(ssock, &choice, sizeof(choice), MSG_CONFIRM, (struct sockaddr *) &caddr, laddr);        
    }

    std::cout << "Game Over the result of the game is draw" << std::endl;
    close(ssock);

    return 0;
}