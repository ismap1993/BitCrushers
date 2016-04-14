/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundo.h
 * Author: chiri
 *
 * Created on 14 de abril de 2016, 18:00
 */

#ifndef MUNDO_H
#define MUNDO_H
#include "Mapa.h"

class Mundo {
public:
    Mundo(int nivel);
    void crearNivel(int nivel);

    void Render();
    
    static Mundo* Instance(int nivel);
    
    ~Mundo();
private:

       static Mundo* pinstance;
       Mapa* mapa;
    
};

#endif /* MUNDO_H */

