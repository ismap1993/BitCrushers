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
#include <vector>
#include "Mapa.h"
#include "Proyectil.h"
class Camara;

class Jugador {
public:
    Jugador();
    Jugador(float x, float y, int politico, bool activado);//1.Pablo 2.Albert 3.Rajoy 4.Pedro
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    sf::Sprite getSprite();
    void leerXML();
    void draw(sf::RenderWindow &window);
    void handle(sf::Event event, sf::RenderWindow& window, Mapa *mapa, Camara *camara);
    void disparar();
    bool salto;
    int alturaSuelo;
    sf::Vector2f posicionJugador;
    float velocidadSalto;
    float velocidadMovimiento;
    sf::Vector2f velocidadJugador;
    bool muerto;
    
    
private:

    Proyectil *proyectiles; 
    int contPro;//contador de proyectiles
    sf::Sprite sprite;
    bool tieneLLave;
    bool activo;
    
    int** matriz;
    sf::Texture texturaJugador;
    
    
};

#endif /* JUGADOR_H */

