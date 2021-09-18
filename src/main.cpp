#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "ball.hpp"

int main(void)
{
	sf::RenderWindow window{sf::VideoMode(600, 600), "Window", sf::Style::Default};
	
	sf::Font font;
	
	if(!font.loadFromFile("../assets/font.otf"))
	{
		printf("\x1b[31mError:\x1b[0m couldn't load font.\n");
		exit(-1);
	}
	
	sf::Text textFps;
	textFps.setFont(font);
	textFps.setCharacterSize(20);
	textFps.setFillColor(sf::Color::Green);
	textFps.setOutlineColor(sf::Color::Black);
	textFps.setStyle(sf::Text::Bold);
	
	sf::Clock deltaClock;
	float deltaCount = 0.f;
	float deltaTime = 0.f;
	
	std::vector<Ball> balls;
	balls.reserve(50);
	
	for(int i = 0; i < 50; i++)
	{
		balls.push_back(Ball( sf::Vector2f( rand() % 600, rand() % 600 ) ));
	}
	
	while(window.isOpen())
	{
		deltaCount = deltaClock.restart().asSeconds();
		
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		
		
		deltaTime += deltaCount;
		while(deltaTime > 1.f/120.f)
		{
			// balls[0].pos = sf::Vector2f( sf::Mouse::getPosition(window) );
			
			textFps.setString(std::to_string(static_cast<int>(1.f / deltaTime)));
			
			window.clear();
			
			for(auto &ball : balls)
			{
				ball.update(deltaTime);
				ball.collide(balls);
				window.draw(ball);
			}
			
			window.draw(textFps);
			
			deltaTime -= 1.f/60.f;
		}
		
		window.display();
	}
	
	return 0;
}