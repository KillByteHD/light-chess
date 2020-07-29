#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>
#include <vector>
#include <iostream>
#include <array>

#define NONE 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6

#define WHITE 0
#define BLACK 1

#define ARE_OPOSITE_COLOR(p1,p2) (p1 < 0 && p2 > 0) || (p1 > 0 && p2 < 0)

namespace light_chess
{

    using piece = int8_t;
    using piece_color = int8_t;
    using position = char[2];

    template<class T, uint N, uint M>
    using mat = std::array<std::array<T,M>,N>;

    //template<uint N, uint M>
    //using sub_board = mat<piece,N,M>;


    std::array<int8_t,2> diff(const position p1, const position p2)
    {
        return std::array<int8_t,2>{ (p1[0]-'a') - (p2[0]-'a') , (p1[1]-'1') - (p2[1]-'1') };
    }

    constexpr piece make_pawn(const piece_color);
    constexpr piece make_knight(const piece_color);
    constexpr piece make_bishop(const piece_color);
    constexpr piece make_rook(const piece_color);
    constexpr piece make_queen(const piece_color);
    constexpr piece make_king(const piece_color);

    //constexpr char representation(const piece);

    class board
    {
        private:
            mat<piece,8,8> data;
        public:
            board() = default;
            constexpr board(mat<piece,8,8> t_data) : data(t_data) {};

            piece at(const position pos)
            {
                return data[7-(pos[1]-'1')][pos[0]-'a'];
            }

            piece at(const uint l, const uint c)
            {
                return data[l][c];
            }

            piece& operator[](const position pos)
            {
                return data[7-(pos[1]-'1')][pos[0]-'a'];
            }

            void set(const position pos, const piece pce)
            {
                (*this)[pos] = pce;
            }


            bool move(const position from, const position to)
            {
                piece piece_to_move = (*this)[from];
                //piece tmp2 = (*this)[to];

                if(piece_to_move != NONE)
                {
                    switch(std::abs(piece_to_move))
                    {
                        const auto diffs = diff(from,to);
                        case PAWN: //TODO: 'Promotion' and 'En passant'
                        {
                            std::cout << "Matched PAWN\n";
                            
                            const int8_t diff1 = diffs[0];
                            const int8_t orientation = (diffs[1] < 0) ? -1 : 1;
                            const int8_t diff2 = orientation*diffs[1];

                            if(diff1 == NONE)
                            {
                                if(diff2 == 1)
                                {
                                    if((*this)[to] == NONE)
                                        goto MOVE;
                                }
                                else if(diff2 == 2 && from[1] == '2')
                                {
                                    const position ante_pos  = {to[0]+orientation,to[1]};
                                    if((*this)[ante_pos] == 0 && (*this)[to] == 0)
                                        goto MOVE;
                                }
                            }
                            else if((diff1 == 1 || diff1 == -1) && diff2 == 1)
                            {
                                if(ARE_OPOSITE_COLOR(piece_to_move,(*this)[to]))
                                    goto MOVE;
                                
                            }

                            goto INVALID_MOVE;
                            //break;
                        }
                        case KNIGHT:
                        {
                            std::cout << "Matched KNIGHT\n";
                            const int8_t diff1 = std::abs(diffs[0]);
                            const int8_t diff2 = std::abs(diffs[1]);
                            if((diff1 == 2 && diff2 == 1) || (diff1 == 1 && diff2 == 2))
                            {
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }

                            goto INVALID_MOVE;
                        }
                            
                            
                        case BISHOP:
                            std::cout << "Matched BISHOP\n";
                            break;
                        case ROOK:
                            std::cout << "Matched ROOK\n";
                            break;
                        case QUEEN:
                            std::cout << "Matched QUEEN\n";
                            break;
                        case KING:
                            std::cout << "Matched KING\n";
                            break;


                    }

                    MOVE:
                    (*this)[to] = piece_to_move;
                    (*this)[from] = 0;
                    return true;
                }
                
                INVALID_MOVE:
                return false; 
            }

            std::vector<position> moves(const position pos);

    };


    constexpr board init_board()
    {
        /* {
            { -1 },
        } */
        mat<piece,8,8> brd{};
        
        for(uint i = 0 ; i < 8 ; ++i)
        {
            brd[1][i] = make_pawn(BLACK);
            brd[6][i] = make_pawn(WHITE);
        }

        const uint line[2] = { 0 , 7 };
        const uint8_t clr[2] = { BLACK, WHITE };

        for(uint i = 0 ; i < 2; ++i)
        {
            brd[line[i]][0] = make_rook  (clr[i]);
            brd[line[i]][1] = make_knight(clr[i]);
            brd[line[i]][2] = make_bishop(clr[i]);
            brd[line[i]][3] = make_queen (clr[i]);
            brd[line[i]][4] = make_king  (clr[i]);
            brd[line[i]][5] = make_bishop(clr[i]);
            brd[line[i]][6] = make_knight(clr[i]);
            brd[line[i]][7] = make_rook  (clr[i]);
        }
        

        return brd;
    }


    void print(board b)
    {
        static const char repr[7] = { ' ', 'p', 'k', 'b', 'R', 'Q', 'K' };
        //std::cout << "+-+-+-+-+-+-+-+-+\n";
        for(uint i = 0 ; i < 8 ; ++i)
        {
            std::cout << "   +---+---+---+---+---+---+---+---+\n";
            printf(" %d ", 8 - i);
            for(uint j = 0 ; j < 8 ; ++j)
            {
                const piece tmp = b.at(i,j);
                printf((tmp < 0) ? "| \e[34m%c\e[0m " : "| \e[31m%c\e[0m " , repr[std::abs(tmp)]); //"\e[31m \e[0m"
            }
            std::cout << "|\n";
            
        }
        std::cout << "   +---+---+---+---+---+---+---+---+\n     a   b   c   d   e   f   g   h\n";

    }
}


#endif // PIECE_HPP