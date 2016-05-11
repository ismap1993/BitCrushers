/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.h
 * Author: alfon
 *
 * Created on 5 de abril de 2016, 19:31
 */


#ifndef JUGADOR_H
#define JUGADOR_H

#include <SFML/Audio.hpp>

#include "Mapa.h"
#include "Proyectil.h"
#include <vector>

class Camara;

class Jugador {
public:
    static Jugador* Instance();
    Jugador();
    Jugador(const Jugador& orig);
    void iniciarJugador(float x, float y, int politic, bool activado);//1.Pablo 2.Albert 3.Rajoy 4.Pedro
    ~Jugador();
    sf::Sprite getSprite();
    void leerXML();
    void draw();
    void dibujarProyectiles();
    void handle();
    void disparar();
    bool isMoving();
    void golpeando();
    
 
    bool salto;
    int alturaSuelo;
    sf::Vector2f posicionAnterior;
    sf::Vector2f posicionJugador;
    float velocidadSalto;
    float velocidadMovimiento;
    sf::Vector2f velocidadJugador;
    bool muerto;
    bool golpeado;
    std::vector<Proyectil*>* proyectiles;//para poder acceder desde otras clases
    float paso;
    sf::Clock pasoTime;
    int col;
    int direccion;
    sf::Clock golpeosSegundo;
    float golpeoXseg;
    int vidas;
    int vidasPrincipales;
    int politico;
    int eliminadoC;
    int eliminadoA;
    
    int enemigosEliminados=0;
    

    int controllerIndex; // identificador de mando
    
    sf::SoundBuffer bufferSalto;
    sf::Sound soundSalto;
    sf::SoundBuffer bufferAtaque;
    sf::Sound soundAtaque;
    
private:
   
    int direccionPro;
    sf::Sprite sprite;
    bool tieneLLave;
    bool activo;
    
    
    
    int** matriz;
    sf::Texture texturaJugador;
    sf::Clock aparicionProyectil;
    
    static Jugador* pinstance;
    
};

#endif /* JUGADOR_H */


/**/