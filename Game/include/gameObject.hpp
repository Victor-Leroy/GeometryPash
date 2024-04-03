#include <SFML/Audio.hpp>

class Game {
public:
    enum GameState {
        TITLE_SCREEN,
        GAMEPLAY,
    };

    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture groundBackgroundTexture;
    sf::Sprite groundBackgroundSprite;
    sf::Music music; // Add a music member variable
    GameState state;
    

    Game() : window(sf::VideoMode(1280, 720), "Game"), ground(sf::Vector2f(1280.0f, 5.0f)) { // Set the window size to 1280x720
        window.setFramerateLimit(60); // Limit the frame rate to 60 FPS
        ground.setPosition(0, 530);
        state = TITLE_SCREEN;

        // Load the ground background texture
        if (!groundBackgroundTexture.loadFromFile("../ressources/sprites/gdbackground.png")) {
               // handle error
        }


        // Set the ground background texture to the sprite
        groundBackgroundSprite.setTexture(groundBackgroundTexture);
        float groundBackgroundScaleX = static_cast<float>(window.getSize().x) / groundBackgroundTexture.getSize().x;
        float groundBackgroundScaleY = static_cast<float>(window.getSize().y) / groundBackgroundTexture.getSize().y;
        groundBackgroundSprite.setScale(groundBackgroundScaleX, groundBackgroundScaleY);
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
        if (!font.loadFromFile("../ressources/fonts/OXYGENE1.ttf")) {
            std::cout << "Error loading font" << std::endl;
            // Handle error appropriately
        }

        // Background setup
        sf::Texture menuBackgroundTexture;
        sf::Sprite menuBackgroundSprite;
        if (!menuBackgroundTexture.loadFromFile("../ressources/gfx/background.png")) {
            std::cout << "Error loading background texture" << std::endl;
            // Handle error
        }
        menuBackgroundSprite.setTexture(menuBackgroundTexture);
        float backgroundScaleX = static_cast<float>(window.getSize().x) / menuBackgroundTexture.getSize().x;
        float backgroundScaleY = static_cast<float>(window.getSize().y) / menuBackgroundTexture.getSize().y;
        menuBackgroundSprite.setScale(backgroundScaleX, backgroundScaleY);
        menuBackgroundSprite.setColor(sf::Color(0, 128, 255)); // Optional: Add transparency

        // Title setup
        sf::Sprite titleScreenFont;
        sf::Texture titleScreenTexture;
        if (!titleScreenTexture.loadFromFile("../ressources/gfx/title.png")) {
            std::cout << "Error loading title texture" << std::endl;
            // Handle error
        }
        titleScreenFont.setTexture(titleScreenTexture);
        titleScreenFont.setScale(0.5f, 0.5f); // Adjust scaling as needed
        titleScreenFont.setPosition(window.getSize().x / 2 - titleScreenFont.getGlobalBounds().width / 2, window.getSize().y / 4);

        // Play button setup
        sf::Sprite playButton;
        sf::Texture playButtonTexture;
        if (!playButtonTexture.loadFromFile("../ressources/gfx/titlePlay.png")) {
            std::cout << "Error loading play button texture" << std::endl;
            // Handle error
        }
        playButton.setTexture(playButtonTexture);
        playButton.setScale(0.5f, 0.5f); // Original scale
        playButton.setPosition(window.getSize().x / 2 - playButton.getGlobalBounds().width / 2, titleScreenFont.getPosition().y + titleScreenFont.getGlobalBounds().height + 20);

        float originalScale = 0.5f;
        float hoverScale = 0.6f; // Scale when hovered
        sf::Clock clock; // Clock to manage smooth transitions

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            // Hover effect and click detection for play button
            bool isHovering = playButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            float currentScale = playButton.getScale().x;
            float scaleChange = clock.restart().asSeconds() * 2; // Speed of the scale change

            if (isHovering) {
                if (currentScale < hoverScale) {
                    currentScale += scaleChange;
                    if (currentScale > hoverScale) currentScale = hoverScale;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    // Here, transition to the gameplay
                    state = GAMEPLAY;
                    return; // Exit the title screen loop
                }
            } else {
                if (currentScale > originalScale) {
                    currentScale -= scaleChange;
                    if (currentScale < originalScale) currentScale = originalScale;
                }
            }
            playButton.setScale(currentScale, currentScale);

            window.clear();
            window.draw(menuBackgroundSprite);
            window.draw(titleScreenFont);
            window.draw(playButton);
            window.display();
        }
    }


    void gameplay() {
        titleScreen();

        std::string level_name("../ressources/level/1.txt");
        LevelObject level(level_name);

        Player player;
        ScrollingBackground background(window.getSize().x);
        sf::Clock clock;

        for (sf::Sprite sprite : level.getListOfSpritesReference()){
                window.draw(sprite);
        }

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


      void run() {
        while (window.isOpen()) {
            switch (state) {
                case TITLE_SCREEN:
                    titleScreen();
                    break;
                case GAMEPLAY:
                    gameplay(); // You'll implement this method
                    break;
            }
        }
    }
};