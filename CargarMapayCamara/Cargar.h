/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cargar.h
 * Author: alfon
 *
 * Created on 16 de marzo de 2016, 13:33
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
    
    sf::Sprite  fondo;
    int _width;
    int _tileWidth;
 
private:
    
    int ***_tilemap;
    int _numLayers;
    int _height;
    int _tileHeigth;
    
    sf::Sprite ****_tilemapSprite;
    sf::Sprite *_tilesetSprite;
    sf::Sprite te;
    
    sf::Texture _tilesetTexture;
    sf::Texture m_tileset;
    sf::Texture fond;
     
    sf::VertexArray m_vertices;
    
};

#endif	/* CARGAR_H */

