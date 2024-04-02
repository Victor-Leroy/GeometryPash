class Game {
public:
    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture groundBackgroundTexture;
    sf::Sprite groundBackgroundSprite;
    sf::Music music; // Add a music member variable
    

    Game() : window(sf::VideoMode(800, 600), "Game"), ground(sf::Vector2f(800.0f, 5.0f)) {
        window.setFramerateLimit(60); // Limit the frame rate to 60 FPS
        srand(static_cast<unsigned int>(time(0))); // Seed for random
        ground.setPosition(0, 530);

        // Load the ground background texture
        if (!groundBackgroundTexture.loadFromFile("../ressources/sprites/gdbackground.png")) {
               // handle error
        }

        // Set the ground background texture to the sprite
        groundBackgroundSprite.setTexture(groundBackgroundTexture);
        groundBackgroundSprite.setPosition(0, 530); // Position it below the ground line

        if (!music.openFromFile("../ressources/sfx/StereoMadness.ogg")) { // Replace with your music file path
            std::cout << "Error loading music" << std::endl;
            // Handle error (e.g., exit the game or continue without music)
        } else {
            music.setLoop(true); // Optional: Loop the music
            music.play(); // Start playing the music
        }
    }

     void titleScreen() {
        sf::Font font;
        if (!font.loadFromFile("../ressources/fonts/OXYGENE1.ttf")) { // Load a font
            // Handle error
        }
        sf::Text title("GEOMETRY DASH", font, 50); // Create a text object
        title.setFillColor(sf::Color::White);
        title.setPosition(200, window.getSize().y / 2 - 100); // Position the text

        sf::Text pressToStart("Press any key to start", font, 20);
        pressToStart.setFillColor(sf::Color::White);
        pressToStart.setPosition(250, window.getSize().y / 2); // Position the text

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Start the game if any key is pressed
                if (event.type == sf::Event::KeyPressed) {
                    return; // Return to proceed to the main game loop
                }
            }
            window.clear();
            window.draw(title);
            window.draw(pressToStart);
            window.display();
        }
    }


    void run() {
        titleScreen();
        Player player;
        ScrollingBackground background;
        sf::Clock clock;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                             player.jump();
                }
            }

            float deltaTime = clock.restart().asSeconds();

            player.update(deltaTime);
            background.update(deltaTime);

            
            background.draw(window);
            window.draw(player.sprite); // Draw the sprite instead of the sprite

            window.draw(groundBackgroundSprite);

            window.draw(groundSprite);
            window.draw(ground);
            
            window.display();
            window.clear();

        }         
    }
};
