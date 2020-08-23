#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "chess.hpp"

namespace lc = light_chess;

void render_board(sf::RenderWindow& window, const lc::board& board, std::array<sf::Sprite,6>& white_pieces, std::array<sf::Sprite,6>& black_pieces)
{
    static const std::array<int,6> board_to_sprite_idx = {5,3,2,4,2,1};
    for(uint i = 0 ; i < 8 ; ++i)
    {
        for(uint j = 0 ; j < 8 ; ++j)
        {
            const lc::piece tmp = board.at(i,j);
            if(tmp != 0)
            {
                if(lc::is_black(tmp))
                {
                    sf::Sprite& tmp_sprite = black_pieces[board_to_sprite_idx[tmp & VALUE_MASK]];
                    tmp_sprite.setPosition(i*152,j*152);
                    window.draw(tmp_sprite);
                }
                else
                {
                    sf::Sprite& tmp_sprite = white_pieces[board_to_sprite_idx[tmp & VALUE_MASK]];
                    tmp_sprite.setPosition(i*152,j*152);
                    window.draw(tmp_sprite);
                }
            }
        }
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "LightChess");
    const sf::Color clear_color(sf::Color(21, 94, 133));

    sf::Texture tex;
    if (!tex.loadFromFile("assets/textures_1.png")) // ,sf::IntRect(0, 0, 152, 152)
    {
        std::cerr << "No texture\n";
        return -1;
    }

    std::array<sf::Sprite,6> white_pieces;
    std::array<sf::Sprite,6> black_pieces;
    for(int i = 0 ; i < 6 ; ++i)
    {
        auto& sprite1 = white_pieces[i];
        sprite1.setTexture(tex);
        sprite1.setTextureRect(sf::IntRect(0 + 152*i, 0, 152, 152));
        sprite1.setScale(100.f/152.f,100.f/152.f/* 100/152,100/152 */);
        
        auto& sprite2 = black_pieces[i];
        sprite2.setTexture(tex);
        sprite2.setTextureRect(sf::IntRect(0 + 152*i, 152, 152, 152));
        const auto& scale = sprite2.getScale();
        sprite2.setScale(152/100,152/100);
        //std::cout << sprite2.getScale().x << " , " << sprite2.getScale().y << '\n';
    }

    lc::chess_game gaem;

    
    std::vector<sf::RectangleShape> board;

    for(uint i = 0 ; i < 8 ; ++i)
    {
        for(uint j = 0 ; j < 8 ; ++j)
        {
            if((i+j) & 1)
            {
                sf::RectangleShape rect({100,100});
                rect.setPosition(100*i,100*j);
                board.push_back(rect);
            }
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(clear_color);
        
        for(const auto& rect : board)
            window.draw(rect);
        render_board(window,gaem.get_board(),white_pieces,black_pieces);

        //window.draw(white_pieces[3]);
        window.display();
    }

    return 0;
}