#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

//#define kVel 15
#include "EMenu.h"
#include "Mapa.h"
#include "Camara.h"
#include "Jugador.h"
#include <fstream>
#include <cstring>







int main()
{
    //ola k ase
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum!"); 
    /*
    //cuando llamemos a Juego alli habrá que llamar al estado, pasandole estos parametros
    
    //Cargo la clase menu
    EMenu *menu = new EMenu(window.getSize().x, window.getSize().y);
    menu -> run(window);
    */
    
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    Jugador* player = new Jugador(100, 200, 1, true);//le pasamos la posicion X e Y donde se colocará el sprite. 
                                                    //El tercer parametro es que personaje es, solo puede ser hasta el 4. 1.Pablo 2.Albert 3.Rajoy 4.Pedro
                                                    //El cuarto parametro es para saber si está activado el personaje en el array de personajes ya que solo un personaje se puede mostrar.
    player->leerXML();//PREGUNTA    ¿es mejor que la matriz deonde se guardan los datos del psrite sheet sea global de la clase Juego o que cada jugador tenga su propia matriz aunque sea la misma?
    
    //Mapa *mapa = new Mapa();
    //mapa->leerMapa();
    
    //Camara *camara = new Camara(window.getSize().x, window.getSize().y, 15, mapa->fondo, mapa->_width, mapa->_tileWidth);
    //le pasamos el alto y el ancho de la ventana
    //el siguiente parametro es la distancia que se mueve la ventana cada vez que se mueve el personaje
    //le pasamos el fondo para poder consultarlo
    //el mapa->fondo nos ayuda a saber hasta donde debemos mover la camara ya que es el ancho del mapa
    //el mapa->_tileWidth nos indica el ancho del tile
   
    while(window.isOpen()){
        
        
        sf::Event event;
        while(window.pollEvent(event)){
            //player->handle(event, window);
        }
        
        
        
        
        window.clear(sf::Color::White);
        player->draw(window);
        //mapa->dibuja(window);
        //std::cout<< player->getSprite().getPosition().x <<std::endl;
        //window.draw(player->getSprite());
        
        window.display();
        
    }
    
    
    
    return 0;
    
}

