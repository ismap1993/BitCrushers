/* 
 * File:   Player.cpp
 * Author: linuxero
 * 
 * Created on March 5, 2014, 7:43 AM
 */

#include "Player.h"

Player::Player(): renderState(), physicsState() {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

void Player::Init(sf::Texture &tex, float posX, float posY, float speedX, float speedY, float maxSpeedX, float maxSpeedY){

	renderState.SetTexture(tex);
	
	physicsState.SetPosition(posX, posY);
	physicsState.SetSpeed(speedX, speedY);
	physicsState.SetMaxSpeed(maxSpeedX, maxSpeedY);
}

void Player::Update(sf::Vector2f velocity, sf::Time elapsedTime){

	physicsState.SetSpeed(velocity);
	physicsState.Update(elapsedTime);
}

void Player::Draw(sf::RenderWindow& window){

	renderState.GetSprite().setPosition(physicsState.GetPosition());
	window.draw(renderState.GetSprite());
}

void Player::DrawWithInterpolation(sf::RenderWindow& window, float interpolation){

	renderState.Draw(window, physicsState.GetPreviousPosition(), physicsState.GetPosition(), interpolation);
}