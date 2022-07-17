#include <iostream>
#include <stdlib.h>

class Board {
    private:
        char board[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    public:
        Board() {}
        bool set (char c, int i) {
            if (board[i] == 'X' || board[i] == 'O' || 
                i < 1 || i > 9) {
                return false;
            } else {
                board[i] = c;
                return true;
            }
        }
        int statusGame() {
            if (
                board[1] != '1' && board[2] != '2' && board[3] != '3' &&
                board[4] != '4' && board[5] != '5' && board[6] != '6' &&
                board[7] != '7' && board[8] != '8' && board[9] != '9') 
                return -1;


            else if (board[1] == board[2] && board[2] == board[3] && board[1] != '1') return true;
            else if (board[4] == board[5] && board[5] == board[6] && board[4] != '4') return true;
            else if (board[7] == board[8] && board[8] == board[9] && board[7] != '7') return true;

            else if (board[1] == board[4] && board[4] == board[7] && board[1] != '1') return true;
            else if (board[2] == board[5] && board[5] == board[8] && board[2] != '2') return true;
            else if (board[3] == board[6] && board[6] == board[9] && board[3] != '3') return true;

            else if (board[1] == board[5] && board[5] == board[9] && board[1] != '1') return true;
            else if (board[3] == board[5] && board[5] == board[7] && board[3] != '3') return true;


            else return false;
        }
        void draw() {
            std::cout << "     |     |     " << std::endl;
            
            std::cout << "  " 
                      << board[1] << "  |  " 
                      << board[2] << "  |  " 
                      << board[3] << "  " << std::endl;

            std::cout << "_____|_____|_____" << std::endl;
            std::cout << "     |     |     " << std::endl;

            std::cout << "  " 
                      << board[4] << "  |  " 
                      << board[5] << "  |  " 
                      << board[6] << "  " << std::endl;

            std::cout << "_____|_____|_____" << std::endl;
            std::cout << "     |     |     " << std::endl;
            std::cout << "  " 
                      << board[7] << "  |  " 
                      << board[8] << "  |  " 
                      << board[9] << "  " << std::endl;

            std::cout << "     |     |     " << std::endl;
        }
};
