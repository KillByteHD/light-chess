#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "chess.hpp"

namespace lc = light_chess;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "LightChess");
    const sf::Color clear_color(sf::Color::Black /* 21, 94, 133 */ );

    sf::Texture tex;
    if (!tex.loadFromFile("assets/textures_1.png",sf::IntRect(0, 0, 152, 152)))
    {
        std::cerr << "No texture\n";
        return -1;
    }

    std::array<sf::Sprite,6> white_pieces;
    std::array<sf::Sprite,6> black_pieces;

    lc::chess_game gaem;

    sf::Sprite sprite;
    sprite.setTexture(tex);

    
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
        
        window.display();
    }

    return 0;
}