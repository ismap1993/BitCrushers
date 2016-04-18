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

class Mapa {
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    
    void leerMapa(int numMapa);
    int getTile(int x, int y);
    void dibuja();
    
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

#endif	/* MAPA_H */

