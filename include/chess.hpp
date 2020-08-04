#ifndef CHESS_HPP
#define CHESS_HPP

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

#define WHITE 0b0000
#define BLACK 0b1000

#define COLOR_MASK 0b1000
#define VALUE_MASK 0b0111

#define ARE_OPOSITE_COLOR(p1,p2) (p1 & COLOR_MASK) != (p2 & COLOR_MASK)

//#define DEFAULT_MOVE {"a1","a1"}

//#define NUMBERS_REPRESENTATION

namespace light_chess
{

    using piece = int8_t;
    //enum class piece : int8_t 
    //{ NONE=0, PAWN=1, KNIGHT=2, BISHOP=3, ROOK=4, QUEEN=5, KING=6 };

    using piece_color = int8_t;
    using position = char[2];
    using move_t = position[2];

    template<class T, uint N, uint M>
    using mat = std::array<std::array<T,M>,N>;

    //template<uint N, uint M>
    //using sub_board = mat<piece,N,M>;


    std::array<int8_t,2> diff(const position p1, const position p2)
    {
        return std::array<int8_t,2>{ static_cast<char>((p1[0]-'a') - (p2[0]-'a')) , static_cast<char>((p1[1]-'1') - (p2[1]-'1')) };
    }

    static constexpr piece __make_piece(const piece pce, const piece_color clr) { return clr | pce; }
    constexpr piece make_pawn(const piece_color clr)   { return __make_piece(PAWN  ,clr); }
    constexpr piece make_knight(const piece_color clr) { return __make_piece(KNIGHT,clr); }
    constexpr piece make_bishop(const piece_color clr) { return __make_piece(BISHOP,clr); }
    constexpr piece make_rook(const piece_color clr)   { return __make_piece(ROOK  ,clr); }
    constexpr piece make_queen(const piece_color clr)  { return __make_piece(QUEEN ,clr); }
    constexpr piece make_king(const piece_color clr)   { return __make_piece(KING  ,clr); }

    constexpr bool is_black(const piece pce) { return (pce & COLOR_MASK) == WHITE; }
    constexpr bool is_white(const piece pce) { return (pce & COLOR_MASK) == BLACK; }



    class board
    {
        private:
            mat<piece,8,8> data;
            uint8_t info_bitmask;
            move_t last_move;
            piece last_move_capture;
        public:
            board()
            {
                const unsigned long default_board[8] = { 0x0c0a0b0e0d0b0a0c ,
                                                         0x0909090909090909 ,
                                                         0x0000000000000000 ,
                                                         0x0000000000000000 ,
                                                         0x0000000000000000 ,
                                                         0x0000000000000000 ,
                                                         0x0101010101010101 ,
                                                         0x0402030605030204 };
                mat<piece,8,8>* brd = (mat<piece,8,8>*) &(*default_board);
                this->data = *brd;
            }

            constexpr board(mat<piece,8,8> t_data) : data(t_data), info_bitmask(0), last_move{0}, last_move_capture(NONE) {};

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

            void set(position pos, piece pce)
            {
                (*this)[pos] = pce;
            }


            bool move(const position from, const position to)
            {
                // TODO: position validation
                piece piece_to_move = (*this)[from];

                if(piece_to_move != NONE)
                {
                    const auto diffs = diff(from,to);
                    switch(piece_to_move & VALUE_MASK)
                    {
                        case PAWN: //TODO: 'Promotion' and 'En passant'
                        {
                            
                            const int8_t diff1 = diffs[0];
                            const int8_t orientation = (diffs[1] < 0) ? -1 : 1;
                            const int8_t diff2 = orientation*diffs[1];

                            if(diff1 == 0)
                            {
                                if(diff2 == 1)
                                {
                                    if((*this)[to] == NONE)
                                        goto MOVE;
                                }
                                else if(diff2 == 2 && (from[1] == '2' || from[1] == '7')) /* ((from[1] == '2' && ((*this)[to] & COLOR_MASK) == WHITE) || (from[1] == '7' && ((*this)[to] & COLOR_MASK) == BLACK)) */
                                {
                                    const position ante_pos  = {static_cast<char>(to[0]+orientation),to[1]};
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
                            const int8_t diff1 = diffs[0] & VALUE_MASK;
                            const int8_t diff2 = diffs[1] & VALUE_MASK;
                            if((diff1 == 2 && diff2 == 1) || (diff1 == 1 && diff2 == 2))
                            {
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }

                            goto INVALID_MOVE;
                        }
                        case BISHOP:
                        {
                            const int8_t diff1 = diffs[0];
                            const int8_t positive_diff1 = diff1 & VALUE_MASK;
                            const int8_t diff2 = diffs[1];
                            const int8_t positive_diff2 = diff2 & VALUE_MASK;
                            if(positive_diff1 == positive_diff2)
                            {
                                const int8_t orientation_horizontal = (diff1 < 0) ? -1 : 1;
                                const int8_t orientation_vertical = (diff2 < 0) ? -1 : 1;
                                for(int i = 1 ; i < positive_diff1 ; ++i)
                                {
                                    const position ante_pos  = {static_cast<char>(from[0]-orientation_horizontal*i), static_cast<char>(from[1]-orientation_vertical*i)};
                                    if((*this)[ante_pos] != 0)
                                        goto INVALID_MOVE;
                                }
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }

                            goto INVALID_MOVE;
                        }
                        case ROOK:
                        {
                            const int8_t diff1 = diffs[0];
                            const int8_t positive_diff1 = diff1 & VALUE_MASK;
                            const int8_t diff2 = diffs[1];
                            const int8_t positive_diff2 = diff2 & VALUE_MASK;
                            if(diff1 == 0 && diff2 != 0)
                            {
                                const int8_t orientation_horizontal = (diff2 < 0) ? -1 : 1;

                                for(int i = 1 ; i < positive_diff2 ; ++i)
                                {
                                    const position ante_pos  = {from[0],static_cast<char>(from[1]-orientation_horizontal*i)};
                                    if((*this)[ante_pos] != 0)
                                        goto INVALID_MOVE;
                                }
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }
                            else if(diff1 != 0 && diff2 == 0)
                            {
                                const int8_t orientation_vertical = (diff1 < 0) ? -1 : 1;
                                for(int i = 1 ; i < positive_diff1 ; ++i)
                                {
                                    const position ante_pos  = {static_cast<char>(from[0]-orientation_vertical*i),from[1]};
                                    if((*this)[ante_pos] != 0)
                                        goto INVALID_MOVE;
                                }
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }

                            goto INVALID_MOVE;
                        }
                        case QUEEN:
                        {
                            const int8_t diff1 = diffs[0];
                            const int8_t positive_diff1 = diff1 & VALUE_MASK;
                            const int8_t diff2 = diffs[1];
                            const int8_t positive_diff2 = diff2 & VALUE_MASK;
                            if(diff1 == 0 && diff2 != 0)
                            {
                                const int8_t orientation_horizontal = (diff2 < 0) ? -1 : 1;

                                for(int i = 1 ; i < positive_diff2 ; ++i)
                                {
                                    const position ante_pos  = {from[0],static_cast<char>(from[1]-orientation_horizontal*i)};
                                    if((*this)[ante_pos] != 0)
                                        goto INVALID_MOVE;
                                }
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }
                            else if(diff1 != 0 && diff2 == 0)
                            {
                                const int8_t orientation_vertical = (diff1 < 0) ? -1 : 1;
                                for(int i = 1 ; i < positive_diff1 ; ++i)
                                {
                                    const position ante_pos  = {static_cast<char>(from[0]-orientation_vertical*i),from[1]};
                                    if((*this)[ante_pos] != 0)
                                        goto INVALID_MOVE;
                                }
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }
                            else if(positive_diff1 == positive_diff2)
                            {
                                const int8_t orientation_horizontal = (diff1 < 0) ? -1 : 1;
                                const int8_t orientation_vertical = (diff2 < 0) ? -1 : 1;
                                for(int i = 1 ; i < positive_diff1 ; ++i)
                                {
                                    const position ante_pos  = {static_cast<char>(from[0]-orientation_horizontal*i),static_cast<char>(from[1]-orientation_vertical*i)};
                                    if((*this)[ante_pos] != 0)
                                        goto INVALID_MOVE;
                                }
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }

                            goto INVALID_MOVE;
                        }
                        case KING: // TODO: 'Castling'
                        {
                            const int8_t diff1 = diffs[0];
                            const int8_t positive_diff1 = diff1 & VALUE_MASK;
                            const int8_t diff2 = diffs[1];
                            const int8_t positive_diff2 = diff2 & VALUE_MASK;
                            if((positive_diff1 == 1 && (positive_diff2 == 1 || positive_diff2 == 0)) 
                                || (positive_diff1 == 0 && positive_diff2 == 1))
                            {
                                const piece piece_in_destiny = (*this)[to];
                                if(piece_in_destiny == NONE || ARE_OPOSITE_COLOR(piece_to_move, piece_in_destiny))
                                    goto MOVE;
                            }
                            goto INVALID_MOVE;
                        }
                    }

                    MOVE:
                    if((*this)[to] != 0)
                    {
                        last_move_capture = (*this)[to];
                    }
                    (*this)[to] = piece_to_move;
                    (*this)[from] = 0;
                    //last_move = move_t{ from , to };
                    return true;
                }
                
                INVALID_MOVE:
                return false; 
            }

            constexpr void undo()
            {

            }

            //std::vector<position> moves(const position pos);

            constexpr bool is_check(const piece_color clr)
            {
                // Exit rule is to find in the capture path of a piece the oposite color king
                for(uint i = 0 ; i < 8 ; ++i)
                {
                    for(uint j = 0 ; j < 8 ; ++j)
                    {
                        const piece current_piece = data[i][j];
                        if((current_piece & COLOR_MASK) != clr)
                        {
                            switch(current_piece & VALUE_MASK)
                            {
                                case PAWN:
                                if(clr == BLACK)
                                {

                                }
                                    break;
                                case KNIGHT:
                                    break;
                                case BISHOP:
                                    break;
                                case ROOK:
                                    break;
                                case QUEEN:
                                    break;
                                case KING:
                                    break;
                                // The default rule is to find NONE and do nothing.
                            }
                        }
                    }
                }
                return false;
            }

            constexpr bool is_checkmate();
    };



    class chess_game
    {
        private:
            enum state : uint8_t { WHITE_TURN=WHITE, BLACK_TURN=BLACK, ENDED };
            
            state current_state;
            board brd;

        public:
            chess_game() = default;
            chess_game(const board& t_brd) : current_state(state::WHITE_TURN), brd(t_brd) {}

            constexpr board get_board() { return brd; }

            bool move(const position from, const position to)
            {
                if(current_state != state::ENDED)
                {
                    if((brd[from] & COLOR_MASK) == int(current_state) )
                    {
                        const bool moved = brd.move(from,to);
                        if(moved)
                        {
                            if(brd.is_check(static_cast<piece_color>(current_state)))
                            {
                                std::cout << "IS CHECK\n";
                                //TODO: check if is 'mate' and set the game state as ENDED
                                if(false)
                                {
                                    current_state = state::ENDED;
                                }
                            }
                            else
                            {
                                current_state = static_cast<state>(COLOR_MASK ^ current_state);
                                std::cout << "TURN OF: " <<  int(current_state) << "\n";
                            }
                        }
                    }
                }
                
                return false;
            }
    };

    ///////////////////////////////////// INTERFACE /////////////////////////////////////

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
                #ifdef NUMBERS_REPRESENTATION
                    if(!tmp)
                        printf("| %d " , int(tmp));
                    else if(tmp != 9)
                        printf((tmp & COLOR_MASK) ? "|\e[34m%d\e[0m " : "| \e[31m%d\e[0m " , int(tmp));
                    else
                        printf("| \e[34m%d\e[0m ", int(tmp));
                #else
                    printf((tmp & COLOR_MASK) ? "| \e[34m%c\e[0m " : "| \e[31m%c\e[0m " , repr[tmp & VALUE_MASK]);
                #endif
                 //"\e[31m \e[0m"
            }
            std::cout << "|\n";
            
        }
        std::cout << "   +---+---+---+---+---+---+---+---+\n     a   b   c   d   e   f   g   h\n";

    }
}


#endif // CHESS_HPP