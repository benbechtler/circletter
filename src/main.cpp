#include <iostream>
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.hpp"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "circletter" };
    window.setFramerateLimit(144);
    sf::Event event;

    float mouseX;
    float mouseY;

    //loading in the background file
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./background.jpg")) {
        std::cout << "Failed to load background texture" << std::endl;
        return EXIT_FAILURE;
    }

    //todo: remove fonts not needed to reduce filesize
    //loading the font
    sf::Font font;
    if (!font.loadFromFile("./OpenSans-Regular.ttf")) {
        std::cout << "Failed to load font" << std::endl;
        return EXIT_FAILURE;
    }


    //temp letters to be replaced once old code is added
    std::string levelLetters = "retstel";

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

        //make the circle that follows mouse (mostly for debug)
        sf::CircleShape mouseChaser(25.f);
        mouseChaser.setFillColor(sf::Color(50, 255, 50, 192));
        mouseChaser.setPosition(mouseX-mouseChaser.getRadius(), mouseY-mouseChaser.getRadius());
        //std::cout << "Mouse Position: " << mouseX << ", " << mouseY << std::endl;

        //draw the rest of the fucking owl
        /*
         *step 1: get letters and words from old code
         *-todo: skipping this for now to make things a little simpler, going to clean up old code and make it a header file at some point
         *step 2: add letters to circle
         *-todo: set relative coords of each letter to the circle and make some formula to take x number of letters and make a layout
         *step 3: determine layout
         *-todo: some sort of crossword formula?
         *step 4: draw the layout
         *-todo: make some rounded rectangles and follow the layout from step 3
         *step 5: make all the input or something idk i just work here
         *todo: add handling for dragging over letters and typing the letters
        */

        //add letters to the circle
        sf::Text letter1(levelLetters[0], font, 500);
        sf::FloatRect letter1Bounds = letter1.getLocalBounds();
        letter1.setOrigin(letter1Bounds.width/2, letter1Bounds.height/2);
        letter1.setScale(1.0/levelLetters.length()*2*letterDisplay.getRadius()/letter1Bounds.width,1.75/levelLetters.length()*letterDisplay.getRadius()/letter1Bounds.height);
        letter1.setPosition(letterDisplay.getRadius()+letterDisplay.getPosition().x,letterDisplay.getPosition().y);

        //add stuff to buffer
        window.draw(background);
        window.draw(letterDisplay);
        window.draw(mouseChaser);
        window.draw(letter1);

        //display the buffer
        window.display();

        std::cout << "\n" << std::endl;
    }
}
