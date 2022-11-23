#include <SFML/Graphics.hpp>
#include <string.h>
#include <sstream>
#include <iostream>
#include <string> 

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 720), "Window!", sf::Style::Close);

    sf::Clock deltaClock;

    int score = 0;
    sf::Font mine;
    mine.loadFromFile("Minecraft.otf");
    sf::Text scoretext;
    scoretext.setFont(mine);
    scoretext.setString(std::to_string(score));
    scoretext.setCharacterSize(24);
    scoretext.setFillColor(sf::Color::White);
    scoretext.setPosition(sf::Vector2f(window.getSize().x/2, 10));

    float ballspeed = 200.f;
    float angle = 0.f;
    float radius = 10.f;
    sf::CircleShape ball(radius);
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition(window.getSize().x/2,360);
    float ballvelx = 0.f;
    float ballvely = 0.f;


    float paddlespeed = 300.f;
    sf::RectangleShape paddle1;
    paddle1.setSize(sf::Vector2f(10, 200));
    paddle1.setPosition(10, 1);

    ballvelx = -1.f;

    while(window.isOpen()) {
        sf::Event event;
        
        sf::Time dt = deltaClock.restart();   

        //Ball 
        if(ballvelx == 1.f) {
            ball.move(ballspeed * dt.asSeconds(), 0);
        } else if (ballvelx == -1.f) {
            ball.move(-ballspeed * dt.asSeconds(), 0);
        }

        if(ballvely == 1.f) {
            ball.move(0, -ballspeed * dt.asSeconds());
        } else if (ballvely == -1.f) {
            ball.move(0, ballspeed * dt.asSeconds());
        }

        //collision
        if((paddle1.getPosition().y > 0) && (paddle1.getPosition().y < 520)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                paddle1.move(0, paddlespeed * dt.asSeconds());
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                paddle1.move(0, -paddlespeed * dt.asSeconds());
            }
        }  
        if (paddle1.getPosition().y <= 0){
            paddle1.move(0, 10);
        }
        if(paddle1.getPosition().y >= 520) {
            paddle1.move(0, -10);
        }

        if(ball.getPosition().x < 0) {
            ballvelx = -1.f;
            ballvely = 0.f;
            ball.setPosition(window.getSize().x/2,360);
            score = 0;
            scoretext.setString(std::to_string(score));
        }

        if(ball.getPosition().x > 620) {
            ballvelx = -1.f;
        }

        if(ball.getPosition().y < 0) {
            ballvely = -1.f;
        }

        if(ball.getPosition().y > 700) {
            ballvely = 1.f;
        }

        if(ball.getGlobalBounds().intersects(paddle1.getGlobalBounds())) {
            ballvelx = 1.f;
            score += 1;
            ball.move(paddle1.getPosition().x+10, 0);
            scoretext.setString(std::to_string(score));
            if(ball.getPosition().y < paddle1.getPosition().y + ((paddle1.getSize().y /3))) {
                std::cout << "should move up" << std::endl;
                ballvely = 1.f;
                std::cout << ballvely << std::endl;
            }
            if(ball.getPosition().y > paddle1.getPosition().y + (paddle1.getSize().y /3)*2) {
                std::cout << "should move down" << std::endl;
                ballvely = -1.f;
                std::cout << ballvely << std::endl;
            }
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        

        window.clear();
        window.draw(scoretext);
        window.draw(paddle1);
        window.draw(ball);
        window.display();

    }

    return 0;
}