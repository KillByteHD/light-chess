#include "chess.hpp"

#include <iostream>
#include <cstdlib>

namespace lc = light_chess;

int main(void)
{
    lc::chess_game gaem;

    std::cout << "\e[31mRed\e[0m is White and \e[34mBlue\e[0m is \e[90mBlack\e[0m\n";

    std::string in;
    do
    {
        print(gaem.get_board());
        std::cout << "> ";
        std::getline (std::cin, in);
  
        
        //std::cout << "Invalid move ex: \"a1 a2\"\n";
        lc::position from;
        lc::position to;

        from[0] = in[0];
        from[1] = in[1];

        to[0] = in[3];
        to[1] = in[4];
        std::cout << ((gaem.move(from,to)) ? "moved\n" : "didn't move\n");
        

        //std::cout << "\"" << in << "\"\n";
    } 
    while(in != "exit");
    

    
    // piece  black white
    // PAWN   0x09  0x01
    // KNIGHT 0x0a  0x02
    // BISHOP 0x0b  0x03
    // ROOK   0x0c  0x04
    // QUEEN  0x0d  0x05
    // KING   0x0e  0x06


    return 0;
}