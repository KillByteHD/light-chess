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
    


    return 0;
}