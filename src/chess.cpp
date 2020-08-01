#include "chess.hpp"

#include <iostream>
#include <cstdlib>

namespace lc = light_chess;

int main(void)
{
    lc::board brd;

    std::string in;
    do
    {
        print(brd);
        std::cout << "> ";
        std::getline (std::cin, in);

        
        
        //std::cout << "Invalid move ex: \"a1 a2\"\n";
        lc::position from;
        lc::position to;

        from[0] = in[0];
        from[1] = in[1];

        to[0] = in[3];
        to[1] = in[4];
        std::cout << ((brd.move(from,to)) ? "moved\n" : "didn't move\n");
        

        //std::cout << "\"" << in << "\"\n";
    } 
    while(in != "exit");
    

    
    // piece  black white old_black
    // PAWN   0x09  0x01  0xff
    // KNIGHT 0x0a  0x02  0xfe
    // BISHOP 0x0b  0x03  0xfd
    // ROOK   0x0c  0x04  0xfc
    // QUEEN  0x0d  0x05  0xfb
    // KING   0x0e  0x06  0xfa


    return 0;
}