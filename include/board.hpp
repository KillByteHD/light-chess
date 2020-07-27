#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>
#include <vector>
#include <iostream>
#include <array>

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

    template<class T, uint N, uint M>
    using mat = std::array<std::array<T,M>,N>;

    //template<uint N, uint M>
    //using sub_board = mat<piece,N,M>;

    constexpr piece make_pawn(const piece_color);
    constexpr piece make_knight(const piece_color);
    constexpr piece make_bishop(const piece_color);
    constexpr piece make_rook(const piece_color);
    constexpr piece make_queen(const piece_color);
    constexpr piece make_king(const piece_color);

    constexpr char representation(const piece);

    class board
    {
        private:
            mat<piece,8,8> data;
        public:
            board() = default;
            constexpr board(mat<piece,8,8> t_data) : data(t_data) {};

            piece at(const position pos)
            {
                return data[pos[0]-'a'][pos[1]-'1'];
            }

            piece at(const uint l, const uint c)
            {
                return data[l][c];
            }

            piece& operator[](const position pos)
            {
                return data[pos[0]-'a'][pos[1]-'1'];
            }

            void set(const position pos, const piece pce)
            {
                (*this)[pos] = pce;
            }


            bool move(const position from, const position to)
            {
                piece& tmp1 = (*this)[from];
                piece& tmp2 = (*this)[to];

                if(tmp1 != 0 && tmp2 == 0)
                {
                    tmp2 = tmp1;
                    tmp1 = 0;
                    return true;
                }
                else
                    return false;

                
            }

            std::vector<position> moves(const position pos);

    };


    constexpr board init_board()
    {
        mat<piece,8,8> brd{};
        
        for(uint i = 0 ; i < 8 ; ++i)
        {
            brd[1][i] = make_pawn(WHITE);
            brd[6][i] = make_pawn(BLACK);
        }

        return brd;
    }


    void print(board b)
    {
        //std::cout << "+-+-+-+-+-+-+-+-+\n";
        for(uint i = 0 ; i < 8 ; ++i)
        {
            std::cout << "   +---+---+---+---+---+---+---+---+\n";
            printf(" %c ", 97 + i);
            for(uint j = 0 ; j < 8 ; ++j)
            {
                const piece tmp = b.at(i,j);
                printf((tmp < 0) ? "|%d " : "| %d " , int(tmp));
            }
            std::cout << "|\n";
        }
        std::cout << "   +---+---+---+---+---+---+---+---+\n     1   2   3   4   5   6   7   8\n";

    }
}


#endif // PIECE_HPP