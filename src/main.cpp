#include <iostream>
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "circletter" };
    window.setFramerateLimit(60);
    sf::Event event;
    float mouseX;
    float mouseY;
    sf::Texture backgroundTexture;
    std::string levelLeters = "retstel";
    if (!backgroundTexture.loadFromFile("./background.jpg")) {
        std::cout << "Failed to load background texture" << std::endl;
    }
    while (window.isOpen())
    {
        while (window.pollEvent(event)) {
            switch (event.type) {
                //window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                //key pressed
                case sf::Event::KeyPressed:
                    break;

                //window resized
                case sf::Event::Resized:
                    window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    break;

                //detecting mouse movement
                case sf::Event::MouseMoved:
                    mouseX = event.mouseMove.x;
                    mouseY = event.mouseMove.y;
                    break;

                //defaulting to ignoring events
                default:
                    break;
            }
        }
        //clear the window for next frame
        window.clear();



        //making sprite for the background, applying texture, then making it be scaled to the size of the window
        sf::Sprite background;
        background.setTexture(backgroundTexture);
        background.scale(sf::Vector2f(window.getView().getSize().x/background.getLocalBounds().width, window.getView().getSize().y/background.getLocalBounds().height));

        //make circle to display letters
        sf:sf::CircleShape letterDisplay(window.getView().getSize().y*.224);
        letterDisplay.setFillColor(sf::Color(75, 75, 75, 224));
        letterDisplay.setPosition(window.getView().getSize().x/2-letterDisplay.getRadius(), window.getView().getSize().y/1.3-letterDisplay.getRadius());

        //make the circle that follows mouse
        sf::CircleShape mouseChaser(25.f);
        mouseChaser.setFillColor(sf::Color(50, 255, 50, 192));
        mouseChaser.setPosition(mouseX-mouseChaser.getRadius(), mouseY-mouseChaser.getRadius());

        //add stuff to buffer
        window.draw(background);
        window.draw(letterDisplay);
        window.draw(mouseChaser);

        //display the buffer
        window.display();
    }
}
