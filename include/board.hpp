#ifndef PIECE_HPP
#define PIECE_HPP

namespace light_chess
{

    using piece = int8_t;
    using piece_color = bool;

    constexpr piece make_pawn();
    constexpr piece make_knight();
    constexpr piece make_bishop();
    constexpr piece make_rook();
    constexpr piece make_queen();
    constexpr piece make_king();

    //class piece
    //{
    //    private:
    //        int8_t data;
    //    public:
    //        
//
    //};

    class board
    {
        private:
            piece data[8][8];
        public:
            

    };
}


#endif // PIECE_HPP