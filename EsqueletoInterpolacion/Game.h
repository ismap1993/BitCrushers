
#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
//#include "../Includes/ResourceHolder.hpp"
#include <SFML/Graphics.hpp>
#include "Player.h"

// ID's para cargar texturas (usar con Textures::ID)
namespace Textures
{
	enum ID
	{
		Plane
	};
}

// ID's para cargar fuentes (usar con Fonts::ID)
namespace Fonts
{
	enum ID
	{
		OpenSans
	};
}




class Game : private sf::NonCopyable
{
public:
    Game();
    void			run();
    
    
private:
    void			processEvents();  // Captura y procesa eventos
    void			update(sf::Time elapsedTime);
    void			render(float interpolation);
    void			handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos
    
    
private:
    static const sf::Time	timePerFrame;
	
    
    //Recursos
    sf::Texture         contTextures;
    sf::Font		contFonts;
    
    //Graficos
    sf::RenderWindow		window;
    Player					player;
    
    //Estadisticas
    sf::Text			mStatisticsText;
    
	
	float		interpolation;
	
    //Eventos
    bool			isMovingUp;
    bool			isMovingDown;
    bool			isMovingRight;
    bool			isMovingLeft;
    bool            mIsRotatingLeft;
    bool            mIsRotatingRight;
	
	bool			firstTime;
	bool			isInterpolating;
};



#endif


