#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Camara.h"
#include <iostream>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include "Cargar.h"
#include <math.h> 
#include "Jugador.h"
//velocidad a la que se mueve el personaje
#define kVel 10



int main(){
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Movimiento de la camara y cargar el mapa!");
    
    //Creo un personaje para poder moverlo
    
    float posx = 200; //para que sean floats
    float posy = 359;
    Jugador* player = new Jugador(posx, posy, 1, true);
    //player->leerXML();
    
    //declaro el mapa y lo cargo con la funcion leerMapa(). Esto lee el tmx y lo guarda
    Cargar *mapa = new Cargar();
    mapa->leerMapa();
    
    //Creo la camara con el ancho y el largo de la ventana, ademas le paso la cantidad de pixeles que se mueve el personaje y el mapa
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    
    //modifico los parametros del personaje
    
    
    //menssajes para comprobar cuanto ocupa el mapa
    /*
    std::cout<< mapa->_tileWidth <<std::endl;
    std::cout<< mapa->_width <<std::endl;
    std::cout<< mapa->_tileWidth*mapa->_width <<std::endl;
    */
    
    //creo un vector de fondos para ponerlo detras del mapa
    std::vector<sf::Sprite*> fondos;
    //variable para saber cuantas veces he de pintar el fondo ya que el mapa tiene mas pixeles que el fondo
    int cuantasVecesDeboPintarElFondo=(mapa->_tileWidth*mapa->_width)/mapa->fondo.getGlobalBounds().width;
    cuantasVecesDeboPintarElFondo=trunc(cuantasVecesDeboPintarElFondo)+1;
    
    //cargo la textura del fondo
    sf::Texture tex;
    if (!tex.loadFromFile("resources/background.jpg"))
    {
        std::cerr << "Error cargando la imagen background.jpg";
        exit(0);
    }
    
    //relleno el vector de fondos con el valor cuantasVecesDeboPintarElFondo
    for(int i=0; i<cuantasVecesDeboPintarElFondo; i++){
        fondos.push_back(new sf::Sprite());
        fondos[i]->setTexture(tex);
        fondos[i]->setPosition(mapa->fondo.getGlobalBounds().width*i, 0);
    }
    
    while (window.isOpen()){
        
        
        
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)){
            
            
            
            switch(event.type){
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }

            }
            
        }     
       
        /**Render**/
        window.clear();
        
        //dibujo los fondos
        for(sf::Sprite* q : fondos){
            window.draw(*q); 
        }
        
        //dibujo el mapa con su metodo
        mapa->dibuja(window);
        
        //dibujo el personaje
        player->draw(window);
        player->handle(event, window, mapa, camara);
        
        //setteo la camara
        camara->draw(window);
        
        window.display();

    }
    
    return 0;
}