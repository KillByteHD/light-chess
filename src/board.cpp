#include "board.hpp"

#include <iostream>
#include <cstdlib>

namespace light_chess
{
    constexpr piece __make_piece(const piece pce, const piece_color clr)
    {
        return (clr) ? -pce : pce;
    }

    constexpr piece make_pawn(const piece_color clr)
    {
        return __make_piece(PAWN,clr);
    }
    
    constexpr piece make_knight(const piece_color clr)
    {
        return __make_piece(KNIGHT,clr);
    }

    constexpr piece make_bishop(const piece_color clr)
    {
        return __make_piece(BISHOP,clr);
    }

    constexpr piece make_rook(const piece_color clr)
    {
        return __make_piece(ROOK,clr);
    }

    constexpr piece make_queen(const piece_color clr)
    {
        return __make_piece(QUEEN,clr);
    }

    constexpr piece make_king(const piece_color clr)
    {
        return __make_piece(KING,clr);
    }



}

namespace lc = light_chess;

int main(void)
{
    lc::board brd = lc::init_board();
    

    lc::position from = { 'a', '7' };
    lc::position to = { 'a', '5' };
    




    //const auto asd = lc::diff(from,to);
    //std::cout << int(asd[0]) << " , " << int(asd[1]) << "\n";

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