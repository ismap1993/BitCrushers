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
    int getPosx();
    sf::Text getHudVotos();
    sf::Text getHudVotosValue();
    sf::Text getContador();
    sf::Text getContadorValue();
    sf::Sprite getSpriteVidaAlbert();
    sf::Sprite getSpriteVidaAlbert2();
    sf::Sprite getSpriteAlbert();

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
    sf::Text hudVotos; //Fuente VOTOS:
    sf::Text hudVotosValue; //Numero de votos
    sf::Sprite background;
    
    sf::Clock clock; //Tiempo HUD
    int countdown; //Cuenta atras HUD
    sf::Text contador; //Fuente TIEMPO:
    sf::Text contadorValue; //Valor cuenta atras
    std::string convertTime;  //Para convertir de int a String el tiempo
    
    int **matriz; //Para el spritesheet del HUD
    int posX;
    int linea;
    
    sf::Sprite spritepedro;
    sf::Sprite spritemariano;
    sf::Sprite spritepablo;
    sf::Sprite spritealbert;
    
    sf::Sprite spritevidaalbert;
    sf::Sprite spritevidaalbert2;
    sf::Sprite spritevidapedro;
    sf::Sprite spritevidamariano;
    sf::Sprite spritevidapablo;


    sf::Texture texalbert;
    sf::Texture texpedro;
    sf::Texture texmariano;
    sf::Texture texpablo;
    
    sf::Texture texvidaalbert;
    sf::Texture texvidaalbert2;
    sf::Texture texvidapedro;
    sf::Texture texvidamariano;
    sf::Texture texvidapablo;








    
};

#endif /* CAMARA_H */

