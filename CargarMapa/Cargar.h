/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cargar.h
 * Author: alfon
 *
 * Created on 10 de marzo de 2016, 12:05
 */

#ifndef CARGAR_H
#define	CARGAR_H
#include <SFML/Graphics.hpp>

class Cargar {
public:
    Cargar();
    Cargar(const Cargar& orig);
    virtual ~Cargar();
    void leerMapa();
    void dibuja(sf::RenderWindow &window);
private:
    int ***_tilemap;
    int _numLayers;
    int _height;
    int _width;
    int _tileHeigth;
    int _tileWidth;
    sf::Sprite ****_tilemapSprite;
    sf::Texture _tilesetTexture;
     sf::Sprite *_tilesetSprite;
     sf::Sprite te;
     
     sf::VertexArray m_vertices;
     sf::Texture m_tileset;
     
     /*ANADIDO*/
     sf::Texture fond;
     sf::Sprite  fondo;
     
     /*ANADIDO*/

};

#endif	/* CARGAR_H */

