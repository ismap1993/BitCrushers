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
#include "Simpatizante.h"
#include "JefeFinal.h"
#include "Enemigo.h"
#include "Proyectil.h"

class Mundo {
public:
    static Mundo* Instance();
    
    Mundo();
    
    void crearMundo(int l);

    void Update();
    
    void Render();
    
    ~Mundo();
    
    int nivel;
    
    const int camaraVel;

    JefeFinal* jefefinal;
    
    Enemigo** enemigos;  //array de enemigos
    
    Simpatizante** simpatizantes; //array de simpatizantes
    
    Proyectil** proyectiles; //array de proyectiles
    
    Mapa* mapa;
    
    Camara* camara;
    
    
private:

       static Mundo* pinstance;
       
    
};

#endif /* MUNDO_H */

