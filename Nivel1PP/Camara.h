/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camara.h
 * Author: alfon
 *
 * Created on 17 de marzo de 2016, 22:14
 */

#ifndef CAMARA_H
#define CAMARA_H
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "Jugador.h"
 #include <string> 

class Camara {
public:
    Camara(int width, int height, int desp, Mapa &mapa);
    Camara(const Camara& orig);
    virtual ~Camara();
    
    void draw(sf::RenderWindow &window);
    void moveRight(Jugador *personaje);
    void moveLeft(Jugador *personaje);
    void sumaVotos(int votos);
    void actualizarVidas(int v, int pol);
    //void setHudVotosValue(int votoObtenido);
    int getPosx();
    sf::Sprite getHudVotos();
    sf::Text getHudVotosValue();
    sf::Sprite getContador();
    sf::Text getContadorValue();
    sf::Sprite getVidasPrincipales();
    sf::Sprite getSpriteVidaAlbert2();
    sf::Sprite getVidas();
    sf::Sprite getBarraVida();
    sf::Sprite getMiniatura1();
    sf::Sprite getMiniatura1vida();
    sf::Sprite getMiniatura2();
    sf::Sprite getMiniatura2vida();
//    sf::Clock getClock();
    void actualizarTiempo();
    
    
    
private:
    
    int ancho;
    int alto;
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int kVel;
    //sf::Time time; //PRUEBA INTERPOLACION
    
    sf::View *camara;
    
    Mapa *mapa;
    
    sf::Font font;  
    sf::Font fontpixelated;
    sf::Sprite hudVotos; //Fuente VOTOS:
    sf::Text hudVotosValue; //Numero de votos
    sf::Sprite background;
    
    sf::Clock clock; //Tiempo HUD
    int countdown; //Cuenta atras HUD
    sf::Sprite contador; //Reloj
    sf::Text contadorValue; //Valor cuenta atras
    std::string convertTime;  //Para convertir de int a String el tiempo
    int votosConseguidos;
    std::string convertVotos;
    
    int **matriz; //Para el spritesheet del HUD
    int posX;
    int linea;
    
    sf::Sprite vidas;
    sf::Sprite barraVida;
    sf::Sprite vidasPrincipales;
    sf::Sprite miniatura1;
    sf::Sprite miniatura1vida;
    sf::Sprite miniatura2;
    sf::Sprite miniatura2vida;

    sf::Texture texturaHUD;
  
};

#endif /* CAMARA_H */

