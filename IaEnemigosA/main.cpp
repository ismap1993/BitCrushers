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
#define UPDATE_TICK_TIME 1000/15

#include <fstream>
#include <cstring>

int main(){ 
    
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum!"); 
   
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
    
    std::vector<Enemigo*>* cuerpo = new std::vector<Enemigo*>();
    std::vector<Enemigo*>* distancia = new std::vector<Enemigo*>();
    
    //Enemigo *enemigo = new Enemigo(true, 530.0, 362, 1);
    //Enemigo *enemigo2 = new Enemigo(true, 1000.0, 362, 0);
    //Enemigo *enemigo3 = new Enemigo(true, 1500.0, 362, 1);
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    //le pasamos el alto y el ancho de la ventana
    //el siguiente parametro es la distancia que se mueve la ventana cada vez que se mueve el personaje
    //le pasamos el fondo para poder consultarlo
    //el mapa->fondo nos ayuda a saber hasta donde debemos mover la camara ya que es el ancho del mapa
    //el mapa->_tileWidth nos indica el ancho del tile
    
    for(int i=0; i<3; i++){
        int aux=500*(i+1);
        cuerpo->push_back(new Enemigo(true, aux,362, 0));
    }
    for(int i=0; i<3; i++){
        int aux=750*(i+1);
        distancia->push_back(new Enemigo(true, aux,362, 1));
    }
    sf::Clock relojGolpe;
    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;
     float tiempo;
    
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
                switch(event.type){
                    //Si se recibe el evento de cerrar la ventana la cierro
                    case sf::Event::Closed:
                        window.close();
                        break;
                }
        }
        window.clear(sf::Color::White);
        mapa->dibujaA(window);
        
        //Aqui intento hacer saparecer al jugador al ser golpeado
        if(!player->golpeado){
            player->draw(window);
        }else{
            if(tiempo>0.4){
                std::cout<<"ha sido golpeado"<<std::endl;
                player->golpeado=false;
                relojGolpe.restart();
            }
            tiempo= relojGolpe.getElapsedTime().asSeconds();
            if(tiempo>0.1){
                std::cout<<"ha sido golpeado"<<std::endl;
                player->golpeado=false;
            }
            relojGolpe.restart();
            
        }
        
        
        //imprimo los dos vectores (directores (perdon por la broma Carlos))
        for(int i=0; i<cuerpo->size(); i++){
            cuerpo->at(i)->draw(window);
        }
        for(int j=0; j<distancia->size(); j++){
           distancia->at(j)->draw(window);
        }
        //enemigo->draw(window);
        //enemigo2->draw(window);
        //enemigo3->draw(window);
        
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
           //enemigo->handle(player);
           //enemigo2->handle(player);
           //enemigo3->handle(player);
        }

        
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
        int y=0, j=0;
        //Compruebo que los proyectiles hagan daño al jugador, aqui habrá que bajarla la vida al colisionar
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
        

        //colisiones 
        //si descomento estas linea, el personaje desaparece por la variable 
        //booleana golpeado(varaible propia del personaje que cree) (player->golpeado=true;)
        for(i=0; i<cuerpo->size(); i++){
            if(cuerpo->at(i)->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())){
                //std::cout<<"Se han tocado y tengo que bajarle una vida"<<std::endl;
                //tiempo= relojGolpe.getElapsedTime().asSeconds();
                //player->golpeado=true;
            }
        }
//        for(j=0; j<distancia->size(); j++){
//            if(distancia->at(j)->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())){
//                //std::cout<<"Se han tocado y tengo que bajarle una vida D:"<<std::endl;
//                //tiempo= relojGolpe.getElapsedTime().asSeconds();
//                //player->golpeado=true;
//            }
//            
//        }
        
        
        
        camara->draw(window);
        
        window.display();
        
    }
    
    return 0;
    
}
