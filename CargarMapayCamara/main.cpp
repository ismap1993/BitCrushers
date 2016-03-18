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
#define kVel 15



int main(){
    sf::RenderWindow window(sf::VideoMode(1066, 600), "SFML works!");
    /*sf::CircleShape shape(380.f);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(800.0, -20.0);*/
    sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
    Cargar *mapa = new Cargar();
    mapa->leerMapa();
    
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    
    
    personaje->setFillColor(sf::Color::Red);
    personaje->setOutlineColor(sf::Color::Blue);
    personaje->setOutlineThickness(10);
    personaje->setPosition(100, 415);
    
    std::cout<< mapa->_tileWidth <<std::endl;
    std::cout<< mapa->_width <<std::endl;
    std::cout<< mapa->_tileWidth*mapa->_width <<std::endl;
    
    std::vector<sf::Sprite*> fondos;
    int cuantasVecesDeboPintarElFondo=(mapa->_tileWidth*mapa->_width)/mapa->fondo.getGlobalBounds().width;
    cuantasVecesDeboPintarElFondo=trunc(cuantasVecesDeboPintarElFondo)+1;
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/background.jpg"))
    {
        std::cerr << "Error cargando la imagen background.jpg";
        exit(0);
    }
    
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
                            personaje->move(kVel, 0);
                            camara->moveRight(*personaje);
                        break;

                        case sf::Keyboard::Left:
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
    window.clear();
    //window.draw(mapa->fondo);
    for(sf::Sprite* q : fondos){
        window.draw(*q); 
    }
    
    mapa->dibuja(window);
    
    window.draw(*personaje);
    camara->draw(window);
    //window.draw(shape);
    window.display();

    }
    
    return 0;
}