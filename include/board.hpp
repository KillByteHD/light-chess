#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>
#include <vector>
#include <iostream>

#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6

#define WHITE 0
#define BLACK 1

namespace light_chess
{

    using piece = int8_t;
    using piece_color = int8_t;
    using position = char[2];

    constexpr piece make_pawn(const piece_color);
    constexpr piece make_knight(const piece_color);
    constexpr piece make_bishop(const piece_color);
    constexpr piece make_rook(const piece_color);
    constexpr piece make_queen(const piece_color);
    constexpr piece make_king(const piece_color);

    constexpr char representation(const piece);

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
            board() = default;

            piece& operator[](const position pos)
            {
                return data[pos[0]-'a'][pos[1]-'1'];
            }

            piece* operator[](const uint pos)
            {
                return data[pos];
            }


            bool move(const position from, const position to);

            std::vector<position> moves(const position pos);

    };


    
    void print(board b)
    {
        //std::cout << "+-+-+-+-+-+-+-+-+\n";
        for(uint i = 0 ; i < 8 ; ++i)
        {
            std::cout << "+-+-+-+-+-+-+-+-+\n";
            for(uint j = 0 ; j < 8 ; ++j)
                printf("|%d", int(b[i][j]));
            std::cout << "|\n";
        }
        std::cout << "+-+-+-+-+-+-+-+-+\n";
    }
}


#endif // PIECE_HPP