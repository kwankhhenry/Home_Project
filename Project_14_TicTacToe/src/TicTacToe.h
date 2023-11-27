#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>

class TicTacToe
{
public:
    const int board_size = 9;
    char* board;
    char userMarker;
    char aiMarker;
    char winner;
    char currentMarker;
    friend class AI;
    TicTacToe(char playerToken, char aiMarker)
    {
        this->userMarker = playerToken;
        this->aiMarker = aiMarker;
        this->winner = '-';
        this->board = setBoard();
        this->currentMarker = userMarker;
    }

    char* setBoard(){
        board = new char[board_size];
        for(int i = 0; i < board_size; i++)
        {
            board[i] = '-';
        }
        return board;
    }

    bool playTurn(int spot){
        bool isValid = withinRange(spot) && !isSpotTaken(spot);
        if(isValid){
            board[spot-1] = currentMarker;
            currentMarker = (currentMarker == userMarker) ? aiMarker : userMarker;
        }
        return isValid;
    }

    // Check if our spot is in range
    bool withinRange(int number){
        return number > 0 && number < board_size + 1;
    }

    bool isSpotTaken(int number){
        return board[number-1] != '-';
    }

    void printBoard(){
        std::cout << "\n";
        for(int i = 0; i < board_size; i++)
        {
            if(i % 3 == 0 && i != 0)
            {
                std::cout << "\n";
                std::cout << "----------------\n";
            }
            std::cout << " | " << board[i];
        }
        std::cout << "\n\n";
    }

    void printIndexBoard(){
        std::cout << "\n";
        for(int i = 0; i < board_size; i++)
        {
            if(i % 3 == 0 && i != 0)
            {
                std::cout << "\n";
                std::cout << "----------------\n";
            }
            std::cout << " | " << i+1;
        }
        std::cout << "\n";            
    }

    bool isThereAWinner(){
        bool diagonalsAndMiddles = (rightDi() || leftDi() || middleRow() || secondCol()) && board[4] != '-';
        bool topAndFirst = (topRow() || firstCol()) && board[0] != '-';
        bool bottomAndThird = (bottomRow() || thirdCol()) && board[8] != '-';

        if(diagonalsAndMiddles){
            this->winner = board[4];
        }
        else if( topAndFirst){
            this->winner = board[0];
        }
        else if( bottomAndThird){
            this->winner = board[8];
        }
        return diagonalsAndMiddles || topAndFirst || bottomAndThird;
    }

    bool topRow(){
        return board[0] == board[1] && board[1] == board[2];
    }

    bool middleRow(){
        return board[3] == board[4] && board[4] == board[5];
    }

    bool bottomRow(){
        return board[6] == board[7] && board[7] == board[8];
    }

    bool firstCol(){
        return board[0] == board[3] && board[3] == board[6];
    }

    bool secondCol(){
        return board[1] == board[4] && board[4] == board[7];
    }

    bool thirdCol(){
        return board[2] == board[5] && board[5] == board[8];
    }

    bool rightDi(){
        return board[0] == board[4] && board[4] == board[8];
    }

    bool leftDi(){
        return board[2] == board[4] && board[4] == board[6];
    }

    bool isTheBoardFilled(){
        for(int i = 0; i < board_size; i++)
        {
            if(board[i] == '-')
                return false;
        }
        return true;
    }

    std::string gameOver(){
        bool didSomeoneWin = isThereAWinner();
        if(didSomeoneWin)
        {
            std::string win_msg = "We have a winner! The winner is ";
            win_msg += this->winner;
            win_msg += "'s";
            return win_msg;
        }
        else if(isTheBoardFilled())
            return "Draw: Game Over!";
        else
            return "Not over!";
    }
};

#endif