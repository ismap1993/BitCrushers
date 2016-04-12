/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EInGame.h
 * Author: chiri
 *
 * Created on 7 de abril de 2016, 17:57
 */

#ifndef EINGAME_H
#define EINGAME_H

#include "Juego.h"

class EInGame: public Escena {
public:


    void Handle();
    void Init();
    void Update();
    void Render();
    void generarRecorte();
    Juego* getContext();
    static EInGame* Instance(Juego* context);
    ~EInGame();
    
    sf::RectangleShape rectangulo;
    
protected:
    EInGame(Juego* context);
    EInGame(const EInGame &);
    EInGame &operator = (const EInGame &);

private:
    
    int ** matrizRecorte;
    static EInGame* pinstance;
    Juego* _context;
    
};

#endif /* EINGAME_H */

