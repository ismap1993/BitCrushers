#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Camara.h"
#include <iostream>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include "Cargar.h"
#include <math.h> 
//velocidad a la que se mueve el personaje
#define kVel 10



int main(){
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Movimiento de la camara y cargar el mapa!");
    
    //Creo un personaje para poder moverlo
    sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
    
    //declaro el mapa y lo cargo con la funcion leerMapa(). Esto lee el tmx y lo guarda
    Cargar *mapa = new Cargar();
    mapa->leerMapa();
    
    //Creo la camara con el ancho y el largo de la ventana, ademas le paso la cantidad de pixeles que se mueve el personaje y el mapa
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    
    //modifico los parametros del personaje
    personaje->setFillColor(sf::Color::Red);
    personaje->setOutlineColor(sf::Color::Blue);
    personaje->setOutlineThickness(10);
    personaje->setPosition(100, 415);
    
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
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            //muevo a la derecha el personaje y la camara con el metodo moveRight
                            personaje->move(kVel, 0);
                            camara->moveRight(*personaje);
                            std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)<<std::endl;
                            if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)==4){
                                personaje->move(-kVel, 0);
                            }
                        break;

                        case sf::Keyboard::Left:
                            //muevo a la izquierda el personaje y la camara con el metodo moveLeft
                            personaje->move(-kVel, 0);
                            camara->moveLeft(*personaje);
                        break;
                        
                        case sf::Keyboard::Up:
                            
                        break;
                        
                        case sf::Keyboard::Down:
                            
                        break;
                        
                        
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
        window.draw(*personaje);
        
        //setteo la camara
        camara->draw(window);
        
        window.display();

    }
    
    return 0;
}