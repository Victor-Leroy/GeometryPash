class Game {
public:
    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture groundBackgroundTexture;
    sf::Sprite groundBackgroundSprite;
    sf::Music music; // Add a music member variable
    

    Game() : window(sf::VideoMode(1280, 720), "Game"), ground(sf::Vector2f(800.0f, 5.0f)) {
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

    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackgroundSprite;
    if (!menuBackgroundTexture.loadFromFile("../ressources/gfx/background.png")) {
        std::cout << "Error loading background texture" << std::endl;
        // Handle error
    }
    menuBackgroundSprite.setTexture(menuBackgroundTexture);
    menuBackgroundSprite.setScale(0.5, 0.5);
    menuBackgroundSprite.setPosition(0, 0);
    menuBackgroundSprite.setColor(sf::Color(66,232,0,120));
    
    if (!font.loadFromFile("../ressources/fonts/OXYGENE1.ttf")) { // Load a font
        // Handle error
    }
    
    sf::Font font2;
    if (!font2.loadFromFile("../ressources/fonts/pusab.ttf")) { // Load a font
        // Handle error
    }

    sf::Sprite titleScreenFont;
    sf::Texture titleScreenTexture;
    if (!titleScreenTexture.loadFromFile("../ressources/gfx/title.png")) {
        // Handle error
    }
    titleScreenFont.setTexture(titleScreenTexture);
    titleScreenFont.setScale(0.5, 0.5);
    titleScreenFont.setPosition(200, window.getSize().y / 2 - 100); // Position the text

    sf::Sprite playButton;
    sf::Texture playButtonTexture;
    if (!playButtonTexture.loadFromFile("../ressources/gfx/titlePlay.png")) {
        // Handle error
    }
    playButton.setTexture(playButtonTexture);
    playButton.setScale(0.5, 0.5);
    playButton.setPosition(300, window.getSize().y / 2 + 100); // Position the text

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (playButton.getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y))) {
                playButton.setColor(sf::Color::Yellow); // Hover effect
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Trigger "Play" action here
                    return; // Assuming this exits the title screen and proceeds to the game
                }
            } else {
                playButton.setColor(sf::Color::White);
            }
        }

        window.clear();
        window.draw(menuBackgroundSprite);
        window.draw(playButton);
        window.draw(titleScreenFont);
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
