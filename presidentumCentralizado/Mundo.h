/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundo.h
 * Author: chiri
 *
 * Created on 14 de abril de 2016, 18:00
 */

#ifndef MUNDO_H
#define MUNDO_H
#include "Mapa.h"
#include "Simpatizante.h"
#include "BossFinal.h"
#include "Enemigo.h"
#include "Proyectil.h"

class Mundo {
public:
    
    static Mundo* Instance();
    
    Mundo();
    
    bool crearMundo(int l);

    void Update();
    
    void Render();
    
    void eliminarMundo();
    
    ~Mundo();
    
    int nivel;
    
    bool mundoCreado;
    
    //RELOJES//////////////////////
    
 
    sf::Clock relojGolpe;
    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;

    float tiempo;
    
    //MUSICA//////////////////////
    
    sf::Sound musica;
    sf::SoundBuffer bufferSobre;
    sf::Sound soundSobre;
    
    sf::SoundBuffer bufferHurt;
    sf::Sound soundHurt;
    
    sf::SoundBuffer buffer;
    
    
    //ENEMGOS////////////////////
    
    BossFinal* jefefinal;
    
    std::vector<Enemigo*>* enemigosAdistancia;  //array de enemigos a distancia
    
    std::vector<Enemigo*>* enemigosCuerpo;  //array de enemigos cuerpo a cuerpo
    
    
    Simpatizante** simpatizantes; //array de simpatizantes
    
    Proyectil** proyectiles; //array de proyectiles
    
    Mapa* mapa;
    
    //CAMARA
    
    Camara* camara; //Apuntador al objeto camara
    int camaraVel;  //desplzamiento de la camara
    sf::Vector2i* camRes; //Resolucion de la camara
    
    
    
private:


       static Mundo* pinstance;
    
};

#endif /* MUNDO_H */

