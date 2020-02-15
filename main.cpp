#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(400, 400), "Minesweeper");
    
    sf::Texture texture;
    texture.loadFromFile("./sprites.png");
    sf::Sprite sprites(texture);

    //todo place bombs
    //   _FBI has entered the chat_

    //todo game loop

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            //todo get mouse button press
            //  right mb == flag thing
        }
        window.clear(sf::Color::White);

        //todo draw sprites

        window.display();
    }

    //todo restart if explodey boi

    //todo Yay if all tiles uncovered

    return 0;
}