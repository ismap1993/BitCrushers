/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.h
 * Author: chiri
 *
 * Created on 5 de abril de 2016, 17:56
 */

#ifndef JUEGO_H
#define JUEGO_H
#include "Escena.h"

class Juego {
    
public:
    Juego();
    
    Escena* currentState();
    
    void setState (Escena* state);
    
    virtual ~Juego();
    
private:
	Escena* _state;
};

#endif /* JUEGO_H */

