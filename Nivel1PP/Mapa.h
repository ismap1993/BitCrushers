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
    void dibujaSimpatizante(sf::RenderWindow& window);
    void dibujaCarcelCerrada(sf::RenderWindow& window);
    void dibujaCarcelAbierta(sf::RenderWindow& window);
    
    sf::Sprite  fondo;
    int _width;
    int _tileWidth;
    std::vector<sf::RectangleShape*> arraySuelo;
    std::vector<sf::RectangleShape*> arrayParedes;
    std::vector<Plataforma*> arrayPlataformas;
    std::vector<sf::Sprite*>* arrayVotos;
//    std::vector<sf::RectangleShape*> arrayEnemigosC;
//    std::vector<sf::RectangleShape*> arrayEnemigosA;
    int** matrizEnemigosA;
    int** matrizEnemigosC;
    int posxBoss;
    int posyBoss;
    int numEnemigosC;
    int numEnemigosA;

private:
    
    int ***_tilemap;
    int _numLayers;
    int _height;
    int _tileHeigth;
    
    sf::Sprite ****_tilemapSprite;
    sf::Sprite *_tilesetSprite;
    sf::Sprite te;
    sf::Sprite *spriteVoto;
    sf::Sprite *spriteSimpa;
    sf::Sprite *spriteCarcelCerrada;
    sf::Sprite *spriteCarcelAbierta;
    
    sf::Texture _tilesetTexture;
    sf::Texture m_tileset;
    sf::Texture fond;
    sf::Texture texVoto;
    sf::Texture texSimpa;
    sf::Texture texCarcelCerrada;
    sf::Texture texCarcelAbierta;
   
     
    sf::VertexArray m_vertices;
    
};

#endif	/* MAPA_H */

