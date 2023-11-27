#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "TicTacToe.h"

class AI{
public:
    int pickSpot(TicTacToe* game){
        std::vector<int> choices;

        for(int i = 0; i < 9; i++)
        {
            if(game->board[i] == '-'){
                choices.push_back(i+1);
                //std::cout << "Choices are: " << i+1 << std::endl;
            }
        }

        srand(time(NULL));
        int choice = choices[rand() % choices.size()];
        return choice;
    }
};