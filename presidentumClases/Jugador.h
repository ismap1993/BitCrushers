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

class Jugador {
public:
    Jugador();
    Jugador(int x, int y, int politico);//1.Pablo 2.Albert 3.Rajoy 4.Pedro
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    sf::Sprite getSprite();
    void leerXML();
    void draw(sf::RenderWindow &window);
    void handle(sf::Event event, sf::RenderWindow& window);
    
private:
    
    sf::Sprite sprite;
    bool tieneLLave;
    int** matriz;
    sf::Texture texturaJugador;
    
    
};

#endif /* JUGADOR_H */

