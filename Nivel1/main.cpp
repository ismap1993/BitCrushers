#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Camara.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "Mapa.h"
#include <math.h> 
#include "Jugador.h"
#include "Enemigo.h"
//velocidad a la que se mueve el personaje
#define kVel 10
#define UPDATE_TICK_TIME 1000/15



int main(){
    
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: Nivel 1 + colisiones!");
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    ///////////////////////////SOUND////////
    /*
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("resources/PP/PP.flac"))
    return -1; // error
    
    sf::Sound musica;
    musica.setBuffer(buffer);
    musica.setLoop(true);
    musica.play();
    */
    ///////////////////////////////////////
    //Creo un personaje para poder moverlo
    //sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
    float posx = 200; //para que sean floats
    float posy = 359;
    Jugador* player = new Jugador(posx, posy, 4, true);
    //player->leerXML();
        

    //declaro el mapa y lo cargo con la funcion leerMapa(). Esto lee el tmx y lo guarda
    Mapa *mapa = new Mapa();
    mapa->leerMapa(1);
           

    //Creo la camara con el ancho y el largo de la ventana, ademas le paso la cantidad de pixeles que se mueve el personaje y el mapa
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    //creacion de vectores de enemigos
    std::vector<Enemigo*>* cuerpo = new std::vector<Enemigo*>();
    std::vector<Enemigo*>* distancia = new std::vector<Enemigo*>();

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
    //lleno los vectores
    for(int i=0; i<4; i++){
        cuerpo->push_back(new Enemigo(true, mapa->matrizEnemigosC[i][0],mapa->matrizEnemigosC[i][1], 0));
    }
    for(int i=0; i<4; i++){
        distancia->push_back(new Enemigo(true, mapa->matrizEnemigosA[i][0],mapa->matrizEnemigosA[i][1], 1));
    }
    
    /********RELOJES Y TIEMPO*********/
    sf::Clock relojGolpe;
    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;
     float tiempo;
     
     
    /**********BUCLE PRINCIPAL*************/
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
                            //std::cout << event.key.code << std::endl;
                        break;
                              
                    }
            }
        }     
        
        player->handle(event, window, mapa, camara);
        if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME){
            timeElapsed = updateClock.restart();
            //manejadores de los enemigos
            for(int i=0; i<cuerpo->size(); i++){
               cuerpo->at(i)->handle(player);
            }
            for(int j=0; j<distancia->size(); j++){
               distancia->at(j)->handle(player);
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
        
        //window.draw(suelo);
//        for(int i=0; i<mapa->arrayVotos.size();i++){
//          window.draw(mapa->arrayVotos[i]);
//        }
        mapa->dibujaVotos(window);
        //dibujo los dos vectores de los enemigos
        for(int i=0; i<cuerpo->size(); i++){
            cuerpo->at(i)->draw(window);
        }
        for(int j=0; j<distancia->size(); j++){
           distancia->at(j)->draw(window);
        }
        mapa->dibujaPlataformas(window);
        //dibujo el personaje
        player->draw(window);
        
       
        
        
        int i=0;
        //compruebo que los proyectiles del jugador se destruyen ya sea por que recorren una distancia determinadad
        //o porque golpean a los NPC. 
        //IMP si el proyectil del jugador colisiona con otro del NPC que ocurre?
        for(i=0; i<player->proyectiles->size();i++){
            player->proyectiles->at(i)->dibuja(window);
            if(player->proyectiles->at(i)->destruir()){
                delete player->proyectiles->at(i);
                player->proyectiles->erase(player->proyectiles->begin()+i);
            }else{
                for(int j=0; j<distancia->size(); j++){
                    if(player->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(distancia->at(j)->getSprite().getGlobalBounds())){
                        delete distancia->at(j);
                        distancia->erase(distancia->begin()+j);
                        delete player->proyectiles->at(i);
                        player->proyectiles->erase(player->proyectiles->begin()+i);
                    }
                }
                for(int j=0; j<cuerpo->size(); j++){
                    if(player->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(cuerpo->at(j)->getSprite().getGlobalBounds())){
                        delete cuerpo->at(j);
                        cuerpo->erase(cuerpo->begin()+j);
                        delete player->proyectiles->at(i);
                        player->proyectiles->erase(player->proyectiles->begin()+i);
                    }
                }
            }
        }
        
        //AQUI IMPRIMO LOS PROYECTILES DE LOS ENEMIGOS
        int y=0, j=0;
        for(y=0; y<distancia->size(); y++){
            //imprimimos los proyectiles
            for(j=0; j<distancia->at(y)->proyectiles->size();j++){
                distancia->at(y)->proyectiles->at(j)->dibuja(window);
                if(distancia->at(y)->proyectiles->at(j)->destruir()){
                    delete distancia->at(y)->proyectiles->at(j);
                    distancia->at(y)->proyectiles->erase(distancia->at(y)->proyectiles->begin()+j);
                }else{
                    if(distancia->at(y)->proyectiles->at(j)->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())){
                        std::cout<<"El proyectil ha danyado al juagdor"<<std::endl;
                        delete distancia->at(y)->proyectiles->at(j);
                        distancia->at(y)->proyectiles->erase(distancia->at(y)->proyectiles->begin()+j);
                        
                        tiempo= relojGolpe.getElapsedTime().asSeconds();
                        player->golpeado=true;
                    }
                }
            }
            
        }
        
        
        //setteo la camara
        camara->draw(window);
        
        window.display();

    }
    
    return 0;
}