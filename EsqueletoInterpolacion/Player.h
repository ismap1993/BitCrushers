/* 
 * File:   Player.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 7:43 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H 

#include "PhysicsState.h"
#include "Render.h"

class Player {
public:
	Player();
	Player(const Player& orig);
	virtual ~Player();
	
	void Init(sf::Texture& tex, float posX, float posY, float speedX=0.f, float speedY=0.f, float maxSpeedX=1000.f, float maxSpeedY=1000.f);
	void Update(sf::Vector2f velocity, sf::Time elapsedTime);
	void Draw(sf::RenderWindow& window);
	void DrawWithInterpolation(sf::RenderWindow& window, float interpolation);
	
private:
	Render			renderState;
	PhysicsState	physicsState;
};

#endif	/* PLAYER_H */

