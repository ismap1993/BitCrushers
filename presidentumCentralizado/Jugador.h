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
#include "Mapa.h"
#include "Proyectil.h"

class Jugador {
public:
    static Jugador* Instance();
    Jugador();
    void iniciarJugador(float x, float y, int politic, bool activado);//1.Pablo 2.Albert 3.Rajoy 4.Pedro
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    sf::Sprite getSprite();
    void leerXML();
    void draw();
    void handle();
    void disparar();
    bool salto;
    int alturaSuelo;
    sf::Vector2f posicionJugador;
    float velocidadSalto;
    float velocidadMovimiento;
    sf::Vector2f velocidadJugador;
    bool muerto;
    int controllerIndex;
    
    std::vector<Proyectil*>* proyectiles;//para poder acceder desde otras clases
    
private:
    int politico;
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

