#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include <cmath>

static const float DEFAULT_RADIUS = 10.f;

struct Ball : public sf::Drawable
{
	sf::CircleShape shape;
	sf::Vector2f pos, vel, acc;
	
	Ball(sf::Vector2f pos);
	
	void update(float deltaTime);
	void collide( std::vector<Ball> &balls );
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

Ball::Ball(sf::Vector2f pos)
{
	this->pos = pos;
	this->vel = { rand() % 1000 * .5f - 250.f, rand() % 1000 * .5f - 250.f };
	this->acc = { 0.f, 0.f };
	
	this->shape = sf::CircleShape(DEFAULT_RADIUS);
	this->shape.setOrigin(DEFAULT_RADIUS, DEFAULT_RADIUS);
	this->shape.setPosition(this->pos);
}

void Ball::update(float deltaTime)
{
	acc = -vel * .01f;
	pos += vel * deltaTime;
	vel += acc * deltaTime;
	
	shape.setPosition(pos);
}

void Ball::collide(std::vector<Ball> &balls)
{
	for(auto &ball : balls)
	{
		if(&ball == this) continue;
		
		float dstx = pos.x - ball.pos.x,
		      dsty = pos.y - ball.pos.y;
		float sqDst = dstx * dstx + dsty * dsty;
		if(sqDst <= DEFAULT_RADIUS*DEFAULT_RADIUS*M_PI)
		{
			float dst = sqrtf(sqDst);
			float overlap = (dst - DEFAULT_RADIUS*2.f) * .5f;
			
			dstx = dstx * overlap / dst;
			dsty = dsty * overlap / dst;
			
			pos.x -= dstx;
			pos.y -= dsty;
			
			ball.pos.x += dstx;
			ball.pos.y += dsty;
			
			// pos.x -= dstx;
			// pos.y -= dsty;
			
			// prevPos.x += dx*2.f;
			// prevPos.y += dy*2.f;
		}
	}
	
	if(pos.x < 0 || pos.x > 600)
	{
		vel.x *= -1.f;
	}
	
	if(pos.y < 0 || pos.y > 600)
	{
		vel.y *= -1.f;
	}
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(shape, states);
}