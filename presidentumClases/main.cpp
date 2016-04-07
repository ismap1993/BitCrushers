#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

#define kVel 15
#include "EMenu.h"

#include "Jugador.h"
#include <fstream>
#include <cstring>







int main()
{
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum!"); 
    /*
    //cuando llamemos a Juego alli habrá que llamar al estado, pasandole estos parametros
    
    //Cargo la clase menu
    EMenu *menu = new EMenu(window.getSize().x, window.getSize().y);
    menu -> run(window);
    */
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    Jugador* player = new Jugador(100, 200, 1);
    //player->leerXML();//PREGUNTA    ¿es mejor que la matriz deonde se guardan los datos del psrite sheet sea global de la clase Juego o que cada jugador tenga su propia matriz aunque sea la misma?
    
    while(window.isOpen()){
        
        
        sf::Event event;
        while(window.pollEvent(event)){
            player->handle(event, window);
        }
        
        
        
        
        window.clear(sf::Color::White);
        player->draw(window);
        
        std::cout<< player->getSprite().getPosition().x <<std::endl;
        //window.draw(player->getSprite());
        
        window.display();
        
    }
    
    
    
    return 0;
    
}

