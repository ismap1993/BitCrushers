/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.h
 * Author: chiri
 *
 * Created on 12 de abril de 2016, 20:25
 */

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "NPC.h"
class Enemigo: public NPC {
public:
    Enemigo();
    Enemigo(bool valorPatrullaje);
    bool getPatrullaje();
    void setPatrullaje(bool valorPatrullaje);
    ~Enemigo();
    
private:
    bool patrullaje;

};

#endif /* ENEMIGO_H */

