#include <SFML/Audio.hpp>

class Game {
public:
    enum GameState {
        TITLE_SCREEN,
        GAMEPLAY,
        PAUSE
    };

    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture groundBackgroundTexture;
    sf::Sprite groundBackgroundSprite;
    sf::Music music; // Add a music member variable
    sf::SoundBuffer buttonPressSoundBuffer;
    sf::Sound buttonPressSound;
    sf::Music menuMusic;
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
        menuBackgroundSprite.setColor(sf::Color(255, 105, 180)); // Optional: Add transparency

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

        if (!buttonPressSoundBuffer.loadFromFile("../ressources/sfx/playSound.ogg")) {
            std::cerr << "Failed to load button press sound" << std::endl;
            // Handle error appropriately
        }

        if (!menuMusic.openFromFile("../ressources/sfx/menuLoop.wav")) {
            std::cerr << "Failed to load menu music" << std::endl;
            // Handle error appropriately
        }
        menuMusic.setLoop(true); // Loop the music if you want
        menuMusic.play();

        buttonPressSound.setBuffer(buttonPressSoundBuffer);
        buttonPressSound.setVolume(100.f); // 

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
                    buttonPressSound.play();

                    // Transition to the gameplay after a short delay to let the sound play
                    sf::sleep(sf::seconds(buttonPressSound.getBuffer()->getDuration().asSeconds()));

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
   
    void pausePopUp(sf::Sprite& gameSceneSprite) { // add as argument the window of the game 
        sf::Vector2u windowSize = window.getSize();
        sf::RectangleShape overlay(sf::Vector2f(static_cast<float>(windowSize.x-25), static_cast<float>(windowSize.y-25)));

        overlay.setFillColor(sf::Color(0, 0, 0, 220)); // Semi-transparent black

        overlay.setPosition(12.5f, 12.5f); // Offset from the window edges


        sf::Font font;
        if (!font.loadFromFile("../ressources/fonts/pusab.ttf")) {
            std::cerr << "Error loading font for pause menu." << std::endl;
            return;
        }

        sf::Text pauseText("PAUSED PRESS ENTER TO RESUME", font, 30);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setPosition(window.getSize().x / 2 - pauseText.getLocalBounds().width / 2, window.getSize().y / 2 - pauseText.getLocalBounds().height / 2);

        // Assuming state is set to PAUSE before this function is called
        while (state == PAUSE) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        state = GAMEPLAY; // Change the game state back to gameplay
                        break;
                    }
                }
            }

            window.clear(); // Optionally clear with a background color
            // No need to draw the game scene here if it's static
            window.draw(gameSceneSprite); // Draw the game scene
            window.draw(overlay);
            window.draw(pauseText);
            window.display();
        }
    }





    void gameplay() {
        Player player;
        ScrollingBackground background("../ressources/sprites/gdbackground.png", 150.0f, window.getSize().x);    
        sf::Clock clock;
        sf::Texture texture;
        if(!texture.create(window.getSize().x, window.getSize().y)){
            std::cerr << "Error creating texture for pause menu." << std::endl;
        }
        if (!music.openFromFile("../ressources/sfx/StereoMadness.ogg")) { 
            std::cout << "Error loading music" << std::endl;
            // Handle error (e.g., exit the game or continue without music)
        } else {
            music.setLoop(true); // Optional: Loop the music
            music.play(); // Start playing the music
        }

        if (menuMusic.getStatus() == sf::Music::Playing) {
            menuMusic.stop();
        }

        Level level;
        std::vector<Obstacle> obstacles;

        loadLevelFromFile("../ressources/level/1.txt", obstacles);

        for (auto& obstacle : obstacles) {
            level.addObstacle(obstacle); // Assuming Level::addObstacle accepts Obstacle objects
        }




        bool isPaused = false;

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
            
            level.update(deltaTime);

            // Now check for collisions after updating positions
            if (player.collidesWith(level)) {
                // Handle collision
            }

            window.clear();
            background.draw(window);
            window.draw(player.sprite); 

            window.draw(groundBackgroundSprite);
            window.draw(groundSprite);
            window.draw(ground);
            
            level.draw(window); // Draw the level obstacles

            window.display();
            texture.update(window); // Capture the current window content
            sf::Sprite gameSceneSprite(texture);
            window.clear();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                isPaused= !isPaused;
                if (isPaused){
                     state = PAUSE;
                    music.pause();
                    clock.restart();
                    pausePopUp(gameSceneSprite);
                    state = GAMEPLAY;
                    music.play();
                }
            }
        }
    }


      void run() {
        while (window.isOpen()) {
            switch (state) {
                case TITLE_SCREEN:
                    titleScreen();
                    break;
                case GAMEPLAY:
                    gameplay(); 
                    break;
            }
        }
    }
};