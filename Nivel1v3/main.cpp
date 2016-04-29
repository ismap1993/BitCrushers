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
//velocidad a la que se mueve el personaje
#define kVel 10



int main(){
    
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: Nivel 1 + colisiones!");
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    //Creo un personaje para poder moverlo
    //sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
    float posx = 200; //para que sean floats
    float posy = 359;
    Jugador* player = new Jugador(posx, posy, 1, true);
    //player->leerXML();
    
    //declaro el mapa y lo cargo con la funcion leerMapa(). Esto lee el tmx y lo guarda
    Mapa *mapa = new Mapa();
    mapa->leerMapa(1);
    
    //Creo la camara con el ancho y el largo de la ventana, ademas le paso la cantidad de pixeles que se mueve el personaje y el mapa
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    std::vector<Enemigo*> arrayEnemigosA;
    std::vector<Enemigo*> arrayEnemigosC;

    for(int i=0;i<4;i++){
        Enemigo *enemigoA= new Enemigo(mapa->matrizEnemigosA[i][0], mapa->matrizEnemigosA[i][1], 0);
        arrayEnemigosA.push_back(enemigoA);
        std::cout<<"----"<<std::endl;
           std::cout<<"posx A: "<<arrayEnemigosA[i]->getSprite().getPosition().x<<std::endl;
           std::cout<<"posy A: "<<arrayEnemigosA[i]->getSprite().getPosition().y<<std::endl;
           std::cout<<"----"<<std::endl;
    }
    
    for(int i=0;i<4;i++){
        Enemigo *enemigoC= new Enemigo(mapa->matrizEnemigosC[i][0], mapa->matrizEnemigosC[i][1], 1);
        arrayEnemigosC.push_back(enemigoC);
    }
    
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
                            //std::cout << event.key.code << std::endl;
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
        
        //dibujo los enemigos A
        for(int j=0; j<arrayEnemigosA.size();j++){
           window.draw(arrayEnemigosA[j]->getSprite());
           
        }
        //dibujo los enemigos C
        for(int j=0; j<arrayEnemigosC.size();j++){
           window.draw(arrayEnemigosC[j]->getSprite());
        }
        
        //dibujo el mapa con su metodo
        mapa->dibuja(window);
        
        //window.draw(suelo);
//        for(int i=0; i<mapa->arrayVotos.size();i++){
//          window.draw(mapa->arrayVotos[i]);
//        }
        mapa->dibujaVotos(window);
       // mapa->dibujaEnemigosC(window);
       // mapa->dibujaEnemigosA(window);
        mapa->dibujaPlataformas(window);
        //dibujo el personaje
        player->draw(window);
        player->handle(event, window, mapa, camara);
        
        //setteo la camara
        camara->draw(window);
        
        window.draw(camara->getHudVotos());
        window.draw(camara->getHudVotosValue());
        window.draw(camara->getContador());
        window.draw(camara->getContadorValue());
        window.draw(camara->getSpriteVidaAlbert());
        //window.draw(camara->getSpriteVidaAlbert2());
        window.draw(camara->getSpriteAlbert());

                
        camara->actualizarTiempo();


        window.display();

    }
    
    return 0;
}