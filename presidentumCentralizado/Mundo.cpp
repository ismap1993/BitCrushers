/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundo.cpp
 * Author: chiri
 * 
 * Created on 14 de abril de 2016, 18:00
 */
#include <iostream>
#include <SFML/System.hpp>
#include "Mundo.h"
#include "Juego.h"
#include "jugador.h"
#include "Camara.h"
#include "LevelFactory.h"

#define UPDATE_TICK_TIME 1000/15

Mundo* Mundo::pinstance = 0;
Mundo* Mundo::Instance(){
    
    if(pinstance == 0) pinstance = new Mundo();

    return pinstance;
}

Mundo::Mundo() : camaraVel(10) {
    
    
}

bool Mundo::crearMundo(int l){
    
    nivel = l; //NIVEL SELECCIONADO
    Jugador::Instance()->iniciarJugador(200, 340, 2, true);
    mapa = new Mapa();
    mapa->leerMapa(nivel);
    
    //CAMARA//////
    camRes = new sf::Vector2i;
    camaraVel = 3;
    camara = new Camara();
    
    
    //INICIALIZANDO Y LLENANDO LOS VECTORES DE ENEMIGOS
        
    enemigosCuerpo = new std::vector<Enemigo*>();
    enemigosAdistancia = new std::vector<Enemigo*>();

    for(int i=0; i<4; i++){

        enemigosCuerpo->push_back(new Enemigo(true, mapa->matrizEnemigosC[i][0], mapa->matrizEnemigosC[i][1], 0));

    }
    for(int i=0; i<4; i++){

        enemigosAdistancia->push_back(new Enemigo(true, mapa->matrizEnemigosA[i][0],mapa->matrizEnemigosA[i][1], 1));

    }
//        
//    ///////////////////////////BUFFER DE SONIDO////////
    
    if (!bufferSobre.loadFromFile("resources/FX/SOBRE.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    soundSobre.setBuffer(bufferSobre);
    
    if (!bufferHurt.loadFromFile("resources/FX/HURT.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    soundHurt.setBuffer(bufferHurt);
//    
//    //////////////////////////////

    if(nivel==1){
        if (!buffer.loadFromFile("resources/PP/PP.flac"))
            std::cout<<"Error cargando PP.flac"<<std::endl;  
    } 
    if(nivel==2){
        if (!buffer.loadFromFile("resources/PSOE/PSOE.flac"))
            std::cout<<"Error cargando PSOE.flac"<<std::endl;  
    } 
    if(nivel==3){
        if (!buffer.loadFromFile("resources/CIUDADANOS/CIUDADANOS.flac"))
            std::cout<<"Error cargando CIUDADANOS.flac"<<std::endl;  
    } 
    if(nivel==4){
        if (!buffer.loadFromFile("resources/PODEMOS/PODEMOS.flac"))
            std::cout<<"Error cargando PODEMOS.flac"<<std::endl;  
    } 
     
    
    
    musica.setBuffer(buffer);
    musica.setLoop(true);
    musica.play(); 
    
    
    
    return true;

}

void Mundo::Update(){
    
    
    
    if(!Jugador::Instance()->muerto)     //CONTORLA QUE EL HANDLE SE BLOQUEE
            Jugador::Instance()->handle();
             
        else
            camara->cartelGameOver();
        
    //IA DE LOS ENEMIGOS    
    
    if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME){
        timeElapsed = updateClock.restart();
        //manejadores de los enemigos
        for(int i=0; i<enemigosCuerpo->size(); i++){
           enemigosCuerpo->at(i)->handle();    
        }
        for(int j=0; j<enemigosAdistancia->size(); j++){
           enemigosAdistancia->at(j)->handle();
        }
    }
    
    
    //COLISIONES DE LOS PROYECTILES
    
    //compruebo que los proyectiles del jugador se destruyen ya sea por que recorren una distancia determinadad
    //o porque golpean a los NPC. 
    //IMP si el proyectil del jugador colisiona con otro del NPC que ocurre? el mundo se destruiria y nada podria volver a ser como antes...
    for(int i=0; i<Jugador::Instance()->proyectiles->size();i++){
        Jugador::Instance()->proyectiles->at(i)->dibuja();
        if(Jugador::Instance()->proyectiles->at(i)->destruir()){
            if(!Jugador::Instance()->proyectiles->empty()){
                //Hay que comprobar que el vector no este vacio cuando quiera eliminar un objeto
                delete Jugador::Instance()->proyectiles->at(i);
                Jugador::Instance()->proyectiles->erase(Jugador::Instance()->proyectiles->begin()+i);
            }

        }else{
            for(int j=0; j<enemigosAdistancia->size(); j++){
                if(Jugador::Instance()->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(enemigosAdistancia->at(j)->getSprite()->getGlobalBounds())){
                    delete enemigosAdistancia->at(j);
                    enemigosAdistancia->erase(enemigosAdistancia->begin()+j);
                    Jugador::Instance()->enemigosEliminados++;
                    if(!Jugador::Instance()->proyectiles->empty()){
                        delete Jugador::Instance()->proyectiles->at(i);
                        Jugador::Instance()->proyectiles->erase(Jugador::Instance()->proyectiles->begin()+i);
                    }
                }
            }
            for(int j=0; j<enemigosCuerpo->size(); j++){
                if(Jugador::Instance()->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(enemigosCuerpo->at(j)->getSprite()->getGlobalBounds())){
                    delete enemigosCuerpo->at(j);
                    enemigosCuerpo->erase(enemigosCuerpo->begin()+j);
                    Jugador::Instance()->enemigosEliminados++;
                    if(!Jugador::Instance()->proyectiles->empty()){
                        delete Jugador::Instance()->proyectiles->at(i);
                        Jugador::Instance()->proyectiles->erase(Jugador::Instance()->proyectiles->begin()+i);
                    }
                }
            }
        }
    }
    
    //ACTUALIZAR VIDA DEL PERSONAJE
    camara->actualizarVidasPrincipales(Jugador::Instance()->vidasPrincipales);
    
    //RECOGIDA DE VOTOS
    
    for(int i=0; i<mapa->arrayVotos->size(); i++)
        if(mapa->arrayVotos->at(i)->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
            std::cout<<"El personaje ha tocado un voto"<<std::endl;
            delete mapa->arrayVotos->at(i);
            mapa->arrayVotos->erase(mapa->arrayVotos->begin()+i);
            //Aitor, aqui tienes que hacer una variable que incremente, asi te mostrara los votos que llevas
            camara->sumaVotos(1);
            soundSobre.play();
        }
       
    mundoCreado = true;
}

void Mundo::Render(){
    
    
    
      mapa->dibuja();
      
      //Jugador::Instance()->proyectiles->
      
      mapa->dibujaPlataformas();
      
      mapa->dibujaVotos();
        //dibujo los dos vectores de los enemigos
        for(int i=0; i<enemigosCuerpo->size(); i++){
            enemigosCuerpo->at(i)->draw();
        }
        for(int j=0; j<enemigosAdistancia->size(); j++){
           enemigosAdistancia->at(j)->draw();
        }
      
      
        //AQUI IMPRIMO LOS PROYECTILES DE LOS ENEMIGOS
        int y=0, j=0;
        for(y=0; y<enemigosAdistancia->size(); y++){
            //imprimimos los proyectiles
            for(j=0; j<enemigosAdistancia->at(y)->proyectiles->size();j++){
                enemigosAdistancia->at(y)->proyectiles->at(j)->dibuja();
                if(enemigosAdistancia->at(y)->proyectiles->at(j)->destruir()){
                    if(!enemigosAdistancia->at(y)->proyectiles->empty()){
                        delete enemigosAdistancia->at(y)->proyectiles->at(j);
                        enemigosAdistancia->at(y)->proyectiles->erase(enemigosAdistancia->at(y)->proyectiles->begin()+j);
                        soundHurt.play();
                    }
                    
                }else{
                    if(enemigosAdistancia->at(y)->proyectiles->at(j)->getSprite().getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
                        std::cout<<"El proyectil ha danyado al juagdor"<<std::endl;
                        if(!enemigosAdistancia->at(y)->proyectiles->empty()){
                            delete enemigosAdistancia->at(y)->proyectiles->at(j);
                            enemigosAdistancia->at(y)->proyectiles->erase(enemigosAdistancia->at(y)->proyectiles->begin()+j);
                            soundHurt.play();
                        }
                        tiempo= relojGolpe.getElapsedTime().asSeconds();
                        Jugador::Instance()->golpeado=true;
                        Jugador::Instance()->vidas=Jugador::Instance()->vidas-1;
                        if(Jugador::Instance()->vidas<0)Jugador::Instance()->vidas=0;
                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;
                    }
                }
            } 
        }
      
        Jugador::Instance()->draw();

        Juego::Instance()->window->draw(camara->getHudVotos());
        Juego::Instance()->window->draw(camara->getHudVotosValue());
        Juego::Instance()->window->draw(camara->getContador());
        Juego::Instance()->window->draw(camara->getContadorValue());
        Juego::Instance()->window->draw(camara->getBarraVida());
        Juego::Instance()->window->draw(camara->getMiniatura1());
        Juego::Instance()->window->draw(camara->getMiniatura1vida());
        Juego::Instance()->window->draw(camara->getMiniatura2());
        Juego::Instance()->window->draw(camara->getMiniatura2vida());

        Juego::Instance()->window->draw(camara->getVidas());
        Juego::Instance()->window->draw(camara->getVidasPrincipales());

        camara->actualizarTiempo();
        camara->actualizarVidas(Jugador::Instance()->vidas, Jugador::Instance()->politico);

        if(Jugador::Instance()->vidas==0){
            Jugador::Instance()->muerto=true;
            Jugador::Instance()->vidasPrincipales= Jugador::Instance()->vidasPrincipales-1;

            if(Jugador::Instance()->vidasPrincipales>0){//resucita con una vida menos
                Jugador::Instance()->muerto=false;
                Jugador::Instance()->vidas=10;
                Jugador::Instance()->posicionJugador.x=200;
                camara->resetearCamara();
            }
        }
        
        
        
        camara->actualizarVidasPrincipales(Jugador::Instance()->vidasPrincipales);
        
        camara->draw();
}

void Mundo::eliminarMundo(){
    
    
    pinstance = 0;
    
}

Mundo::~Mundo() {
   
    //delete camara;
    delete mapa;
    
    mapa = 0;
    //camara = 0;
    //delete pinstance;
    
    nivel = -1;
    std::cout << "Mundo ha sido eliminado"   << std::endl;
    //std::cout<<"Mapa: "<<&mapa<<std::endl;
    //std::cout<<"Camara: "<<&camara<<std::endl;
}
