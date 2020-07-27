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
    lc::board brd{};
    //lc::piece pwn = lc::make_pawn(BLACK);
    //brd.at("a1");
    std::cout << int(brd["a1"]) << '\n';
    
    print(brd);
    return 0;
}