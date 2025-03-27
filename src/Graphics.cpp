#include "Graphics.h"
#include "Mechanics.h"

#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;

#define FPS 120.0f

void handlePlayerInput(Player& player1, Player& player2) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
        player1.move(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) 
        player1.move(1);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        player2.move(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) 
        player2.move(1);
}

void limitFPS(sf::Clock& clock) {
    sf::Time frameTime = sf::seconds(1.0f / FPS);
    if (clock.getElapsedTime() < frameTime) {
        sf::sleep(frameTime - clock.getElapsedTime());
    }
    clock.restart();
}

std::string itos(int x) { // Just values between 0 an 7
    if (x < 0 || 7 < x)
        exit(1); // throw exeption 

    std::string res;
    res += char(x + '0');
    return res;
}

void GameOver(RenderWindow &window, Text &Message, Player &p1, Player &p2) {
    if (p1.getScore() == 7) 
        Message.setString("Player one Wins");
    else 
        Message.setString("Player two Wins");
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) 
                window.close();
            if (event->is<Event::KeyPressed>())
                return; 
        }
    
        window.clear(Color::Black);
        
        Message.setCharacterSize(20);
        Message.setFillColor(sf::Color::White);  

        
        FloatRect textRect = Message.getLocalBounds();
        Message.setPosition({SCREEN_WIDTH / 2.0f - textRect.size.x / 2.0f, 
                         SCREEN_HEIGHT / 2.0f - textRect.size.y / 2.0f});
        
       
        window.draw(Message);
        window.display();
    }
}

void StartGame() {
    Ball ball;
    ball.restart();
    
    Player Player1(true);
    Player Player2(false);

    RenderWindow window(VideoMode({(uint)SCREEN_WIDTH, (uint)SCREEN_HEIGHT}), "Pong"); 
    
    RectangleShape ballTexture({10.0f, 10.0f});
    RectangleShape Player1Texture({Player1.getW(), Player1.getH()});
    RectangleShape Player2Texture({Player2.getW(), Player2.getH()});
    Clock clock;

    Font font("/usr/share/fonts/TTF/JetBrainsMonoNerdFontMono-Regular.ttf");
    Text Score(font);
    Score.setCharacterSize(20);
    Score.setFillColor(sf::Color::White);  
    Score.setPosition({SCREEN_WIDTH / 2 - 20,0});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }
        
        if (Player1.getScore() == 7 || Player2.getScore() == 7) {
            GameOver(window, Score, Player1, Player2);
            break;
        }

        handlePlayerInput(Player1, Player2);
        window.clear(Color::Black);
        limitFPS(clock);

        ballTexture.setPosition({ball.getX(), ball.getY()});
        Player1Texture.setPosition({Player1.getX(), Player1.getY()});
        Player2Texture.setPosition({Player2.getX(), Player2.getY()});
        ball.move(&Player1, &Player2);
        if (!ball.hitsWith(&Player1) && !ball.hitsWith(&Player2)) 
            ball.checkIfPoint(Player1, Player2); 

        Score.setString(itos(Player1.getScore()) + ":" + itos(Player2.getScore()));
        window.draw(Score);
        window.draw(ballTexture);
        window.draw(Player1Texture);
        window.draw(Player2Texture);
        
        window.display();
    }
}

