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
    sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
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
    
    sf::RectangleShape suelo(sf::Vector2f(1280, 500));
    suelo.setPosition(0,600);
    suelo.setOutlineThickness(1.0f);
    suelo.setFillColor(sf::Color(120,66,0));
    suelo.setOutlineColor(sf::Color::Black);
    
    sf::Vector2f posicionJugador(100, 100);
    sf::Vector2f velocidadJugador(0, 0);
    const float gravedad = 0.1;
    //int alturaSuelo = 100;
    int alturaSuelo = suelo.getPosition().y - 100;
    //int alturaSuelo = mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)=4;
    float velocidadSalto = 7, velocidadMovimiento = 0.3;
    bool salto = false;

    
    personaje->setPosition(posicionJugador);
    
    
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
                       /* case sf::Keyboard::Right:
                            //muevo a la derecha el personaje y la camara con el metodo moveRight
                            personaje->move(kVel, 0);
                            camara->moveRight(*personaje);
                            std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)<<std::endl;
                            if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)==4){
                                personaje->move(-kVel, 0);
                            }
                        break;*/

                        
                        
                        
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
        
        /*if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y+32)==1){
            
            //std::cout<<"holaaaaaa"<<std::endl;
            //std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y+32)<<std::endl;
            
            alturaSuelo=580;
            
            if(personaje->getPosition().y>400){
                //std::cout<<"ID= "<< personaje->getPosition().y<<std::endl;
                
                alturaSuelo=580;
                //velocidadJugador.y = 0;
                //personaje->setPosition(personaje->getPosition().x, 690);
            }
            
            //velocidadJugador.y = aux;
        }
        
        else{
            velocidadJugador.y = 0;
            alturaSuelo=personaje->getPosition().y;
        }*/
       
        if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)>1){
                                velocidadJugador.y = 0;
                                alturaSuelo=personaje->getPosition().y;
                                
                                 //std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)<<std::endl;
        }else if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y+32)==1){
            
            //std::cout<<"holaaaaaa"<<std::endl;
            //std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y+32)<<std::endl;
            
            alturaSuelo=580;
            
            if(personaje->getPosition().y>400){
                //std::cout<<"ID= "<< personaje->getPosition().y<<std::endl;
                
                alturaSuelo=580;
                //velocidadJugador.y = 0;
                //personaje->setPosition(personaje->getPosition().x, 690);
            }
            
            //velocidadJugador.y = aux;
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            //camara->moveRight(*personaje);
            
            //std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)<<std::endl;
            
            if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)==4){
                std::cout<<"ID= holaaaaaaaa"<<std::endl;
                                velocidadJugador.x = 0;
                                
                            }
            else
                velocidadJugador.x = velocidadMovimiento;
            //sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
              //                  sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        }
        
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            //camara->moveLeft(*personaje);
            velocidadJugador.x = -velocidadMovimiento;
            //sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
              //                  sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        }
        else{
            velocidadJugador.x = 0;
            
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            
            //sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
              //                  sprite.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            
            //sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
              //                  sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        }
        
        
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && salto)
        {
            velocidadJugador.y = -velocidadSalto;
            salto = false;
            
        }
        
        

        if(!salto)
            velocidadJugador.y += gravedad;
        else
            velocidadJugador.y = 0;

        posicionJugador += velocidadJugador;

        salto = posicionJugador.y + 10 >= alturaSuelo;

        if(salto)
            posicionJugador.y = alturaSuelo - 10;

        
        personaje->setPosition(posicionJugador);
        
        
        /**Render**/
        window.clear();
        
        //dibujo los fondos
        for(sf::Sprite* q : fondos){
            window.draw(*q); 
        }
        
        //dibujo el mapa con su metodo
        mapa->dibuja(window);
        
        window.draw(suelo);
        

        //dibujo el personaje
        player->draw(window);
        player->handle(event, window, mapa, camara);
        
        //setteo la camara
        camara->draw(window);
        
        window.display();

    }
    
    return 0;
}