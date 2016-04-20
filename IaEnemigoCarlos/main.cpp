/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Camara.h"
#include <iostream>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include "Mapa.h"
#include <math.h> 
#include "Jugador.h"
#include "Enemigo.h"

#define kVel 10

#include "Jugador.h"
#include <fstream>
#include <cstring>

int main(){ 
    
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum!"); 
     sf::Event event;
    sf::Texture texture;
    if(!texture.loadFromFile("resources/background.jpg")){
        std::cerr<<"error al cargar el background";
        exit(0);
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    std::cout<<"sprite cargado"<<std::endl;
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    Jugador* player = new Jugador(200, 340, 2, true);//le pasamos la posicion X e Y donde se colocará el sprite. 
                                                    //El tercer parametro es que personaje es, solo puede ser hasta el 4. 1.Pablo 2.Albert 3.Rajoy 4.Pedro
                                                    //El cuarto parametro es para saber si está activado el personaje en el array de personajes ya que solo un personaje se puede mostrar.
    //player->leerXML();//PREGUNTA    ¿es mejor que la matriz deonde se guardan los datos del psrite sheet sea global de la clase Juego o que cada jugador tenga su propia matriz aunque sea la misma?

    Mapa *mapa = new Mapa();
    mapa->leerMapa(1);
    Camara* camara = new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    Enemigo* enemigo = new Enemigo(500, 340, 2, true, true);
    
   
    while(window.isOpen()){
    
        window.clear(sf::Color::White);
        
        mapa->dibujaA(window);
        
        player->draw(window);
        
        enemigo->draw(window);
        enemigo->update();
        
        player->handle(event, window, mapa, camara);
        //enemigo->handle(event, window, mapa, camara);
        
    
        
        while (window.pollEvent(event)){  
            switch(event.type){     
                case sf::Event::Closed:
                    window.close();
                    break;       
            }
        }
    camara->draw(window);
    window.display();
        
    }
    
    return 0;
    
}
