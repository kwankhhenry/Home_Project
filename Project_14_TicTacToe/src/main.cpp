#include <iostream>
#include <string.h>
#include "TicTacToe.h"
#include "AI.h"

int main(){

    bool doYouWantToPlay = true;
    while(doYouWantToPlay){
        std::cout << "Welcome to Tic Tac Toe! You are about to go against "
                  << "the master of Tic Tac Toe. Are you ready? I hope so!\n BUT FIRST, you "
                  << "must pick what character you want to be and which character I will be\n";
        std::cout << "Enter a single character that will represent you on the board: ";

        char playerToken;
        std::cin >> playerToken;

        std::cout << "Enter a single character that will represent your opponent on the board: ";
        char opponentToken;
        std::cin >> opponentToken;

        TicTacToe* game = new TicTacToe(playerToken, opponentToken);

        AI* ai = new AI();

        std::cout << "\nNow we can start the game.  To play, enter a number and your token shall be "
                  << "put in this place.\nThe numbers go from 1-9, left to right.  We shall see who will win this round.";
        game->printIndexBoard();
        std::cout << "\n";

        while(game->gameOver() == "Not over!")
        {
            if(game->currentMarker == game->userMarker){
                std::cout << "It's your turn! Enter a spot for your token\n";
                int spot;
                std::cin >> spot;
                while(!game->playTurn(spot)){
                    std::cout << "Try again. " << spot << " is invalid. This spot is already taken"
                              << " or it is out of range.\n";
                    std::cin >> spot;
                }
                std::cout << "You picked " << spot << "!";
            }
            else{
                std::cout << "It's my turn!\n";
                int aiSpot = ai->pickSpot(game);
                game->playTurn(aiSpot);
                std::cout << "I picked " << aiSpot << "!";
            }
            std::cout << "\n";
            game->printBoard();
        }
        std::cout << game->gameOver() << std::endl;
        std::cout << "\n";
        std::cout << "Do you want to play again? Enter Y if you do. Enter anything else "
                  << "if you are tired of me.\n";
        char response;
        std::cin >> response;

        doYouWantToPlay = (response == 'Y');
        std::cout << "\n";
    }

    return 0;
}