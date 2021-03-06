/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.h
 * Author: alfon
 *
 * Created on 16 de marzo de 2016, 13:33
 */

#ifndef MAPA_H
#define	MAPA_H
#include <SFML/Graphics.hpp>
#include "Plataforma.h"
#include "Enemigo.h"



class Mapa {
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    
    void leerMapa(int numMapa);
    int getTile(int x, int y);
    void dibuja(sf::RenderWindow &window);
    void dibujaEnemigosC(sf::RenderWindow& window);
    void dibujaEnemigosA(sf::RenderWindow& window);
    void dibujaVotos(sf::RenderWindow& window);
    void dibujaPlataformas(sf::RenderWindow& window);
    
    /*Para dibujar enemigos desde el main.
     Estas matrices tienen las POSICIONES (x,y) de los enemigos*/
    int** matrizEnemigosA;
    int** matrizEnemigosC;

    
    sf::Sprite  fondo;
    int _width;
    int _tileWidth;
    std::vector<sf::RectangleShape*> arraySuelo;
    std::vector<sf::RectangleShape*> arrayParedes;
    std::vector<Plataforma*> arrayPlataformas;
    std::vector<sf::Sprite> arrayVotos;
//    std::vector<sf::RectangleShape*> arrayEnemigosC;
//    std::vector<sf::RectangleShape*> arrayEnemigosA;
//    std::vector<Enemigo*> arrayEnemigosC;
//    std::vector<Enemigo*> arrayEnemigosA;


private:
    
    int ***_tilemap;
    int _numLayers;
    int _height;
    int _tileHeigth;
    
    sf::Sprite ****_tilemapSprite;
    sf::Sprite *_tilesetSprite;
    sf::Sprite te;
    sf::Sprite spriteVoto;
    
    sf::Texture _tilesetTexture;
    sf::Texture m_tileset;
    sf::Texture fond;
    sf::Texture texVoto;
   
     
    sf::VertexArray m_vertices;
    
   
};

#endif	/* MAPA_H */

