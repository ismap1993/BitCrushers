/* 
 * File:   Render.h
 * Author: linuxero
 *
 * Created on March 5, 2014, 8:08 AM
 */

#ifndef RENDER_H
#define	RENDER_H

#include <SFML/Graphics.hpp>

class Render {
public:
	Render();
	Render(const Render& orig);
	virtual ~Render();
	
	void SetTexture(sf::Texture &tex);
	void Draw(sf::RenderWindow &window, const sf::Vector2f &posPrev, const sf::Vector2f &posNew, float interpolation);
	sf::Sprite &GetSprite() { return sprite; }
	sf::Vector2f GetRenderPosition() const { return renderPos; }

private:
	sf::Sprite		sprite;
	sf::Vector2f	renderPos;
};

#endif	/* RENDER_H */

