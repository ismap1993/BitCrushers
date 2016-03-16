/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plataforma.h
 * Author: chiri
 *
 * Created on 15 de marzo de 2016, 20:29
 */

#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <SFML/Graphics.hpp>

class plataforma {
public:
    plataforma(sf::Texture textura);           //PREGUNTAR A FIDEL SI LAS VARIABLES DE INSTANCIA (MEMORIA DINAMCA) HAY QUE DECLARARLAS TAMBIEN COMO PUNTEROS (MEMORIA DINAMICA SOBRE MEMORIA DINAMICA)
    sf::Sprite* sprite;
    
    
    
    plataforma(const plataforma& orig);
    virtual ~plataforma();
private:

};

#endif /* PLATAFORMA_H */

