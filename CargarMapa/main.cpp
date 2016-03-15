#include <SFML/Graphics.hpp>
#include "Cargar.h"
#include "tinyxml2.h"
#include <Cargar.cpp>
#include <iostream>
#include <array>
#define kVel 5
/*
 * el ejecutable deberá leer de la fuente de información donde esté el mapa 
 * almacenado y mostrará los sprites y realizará el scroll horizontal correctamente. 
 */
int main(){
    
    //Creamos la ventana de juego
    
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Cargar mapa!");
    
    
    /***Shapes***/
    
    sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
    
    //Declaro los tipos de fuentes
    
    sf::Font fuenteParaPruebas;
    //como se haria una fuente dinamica?
    //Cargo las fuentes 
    if (!fuenteParaPruebas.loadFromFile("resources/arial.ttf")){
        std::cerr << "Error al cargar la fuente arial.ttf";
    }
    
    //textos que ayudan a saber en que pixel estoy
    sf::Text *cero;
    cero = new sf::Text("0", fuenteParaPruebas);
    sf::Text *quinientos;
    quinientos = new sf::Text("500", fuenteParaPruebas);
    sf::Text *mil;
    mil = new sf::Text("1000", fuenteParaPruebas);
    sf::Text *milquinientos;
    milquinientos = new sf::Text("1500", fuenteParaPruebas);
    sf::Text *dosmil;
    dosmil = new sf::Text("2000", fuenteParaPruebas);
    sf::Text *dosmilquinientos;
    dosmilquinientos = new sf::Text("2500", fuenteParaPruebas);
    
     /****Textures****/
    
    sf::Texture texturaBackground;
    if (!texturaBackground.loadFromFile("resources/background.jpg"))
    {
        std::cerr << "Error cargando la imagen background.jpg";
        exit(0);
    }
    
    /***Sprites**/
    
    sf::Sprite background(texturaBackground);
    
    /***Views***/
    
    sf::View *camara = new sf::View(sf::FloatRect(0,0, 1066, 600));
    //los dos primeros valores son para posicionar la camara. Los otros dos valores son para definir el alto y el ancho de la camara
    
    /**Map**/
    Cargar mapa;
   
    
   
    //Tranformaciones
    
    personaje->setFillColor(sf::Color::Red);
    personaje->setOutlineColor(sf::Color::Yellow);
    personaje->setOutlineThickness(10);
    personaje->setPosition(100, 415);

    cero->setColor(sf::Color::Red);
    cero->setCharacterSize(30);
    cero->setPosition(0, 0);
    
    quinientos->setColor(sf::Color::Red);
    quinientos->setCharacterSize(30);
    quinientos->setPosition(500, 0);
    
    mil->setColor(sf::Color::Red);
    mil->setCharacterSize(30);
    mil->setPosition(1000, 0);
    
    milquinientos->setColor(sf::Color::Red);
    milquinientos->setCharacterSize(30);
    milquinientos->setPosition(1500, 0);
    
    dosmil->setColor(sf::Color::Red);
    dosmil->setCharacterSize(30);
    dosmil->setPosition(2000, 0);
    
    dosmilquinientos->setColor(sf::Color::Red);
    dosmilquinientos->setCharacterSize(30);
    dosmilquinientos->setPosition(2500, 0);
    
    background.setPosition(0.0, 0.0);
    
    //aux
    int desplazamientoCamara=0;
    //tambien las variables primitiva deben ser declaradas con memoria dinamica?
    //no, solo aquellas que sean de sfml, como text o sprite
    int posicionOrigenCamara=camara->getCenter().x;
    
    
    //Bucle del juego
    while (window.isOpen()){
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
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
                            //Escala por defecto
                            personaje->move(kVel,0);
                            if(desplazamientoCamara==0){
                                if(personaje->getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
                                    //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
                                    camara->move(kVel,0);
                                    desplazamientoCamara=desplazamientoCamara+kVel; 
                                }
                                 
                            }else{
                                if(personaje->getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(background.getLocalBounds().width*0.79)){
                                    camara->move(kVel,0);
                                    desplazamientoCamara=desplazamientoCamara+kVel;  

                                }
                            }
                            
                            if(personaje->getPosition().x == 2300){
                                //este valor de 2300 es una prueba, se puede quitar
                                //cada vez que entro al if realiza el zoom, hay que controlarlo con algun contador
                                //camara->zoom(0.9);
                                //camara->setRotation(90.0);
                                //amara->setSize(533, 300);
                            }
                            /*
                            std::cout<< "Centro de la camara..."<<std::endl;
                            std::cout<< camara->getCenter().x<<std::endl;
                            std::cout<< "Posicion del sprite"<<std::endl;
                            std::cout<< personaje->getPosition().x<<std::endl;
                            */
                        break;

                        case sf::Keyboard::Left:
                            personaje->move(-kVel,0);
                            if(desplazamientoCamara!=0){
                                if(personaje->getPosition().x<= camara->getSize().x*0.4 + desplazamientoCamara && camara->getCenter().x!=posicionOrigenCamara){
                                    camara->move(-kVel,0);
                                    desplazamientoCamara=desplazamientoCamara-kVel;   
                                }
                            }
                        break;
                        
                        /*
                        case sf::Keyboard::Up:
                            personaje.move(0,-kVel); 
                            camara.move(kVel,0);

                        break;
                         */
                        /*
                        case sf::Keyboard::Down:
                            personaje.move(0,kVel);
                            camara.move(kVel,0);
                        break;
                        */
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                            std::cout << "tu madre" << std::endl;
                        break;
                              
                    }
            } 
        }
        window.clear();
        //window.draw(background);
        window.draw(*personaje);
        //window.draw(*cero);
        window.draw(*quinientos);
        window.draw(*mil);
        window.draw(*milquinientos);
        window.draw(*dosmil);
        window.draw(*dosmilquinientos);
        window.setView(*camara);
        mapa.dibuja();
        window.display();
    }
    return 0;
}