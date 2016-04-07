/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EInGame.cpp
 * Author: chiri
 * 
 * Created on 7 de abril de 2016, 17:57
 */



#include <stdio.h>
#include <iostream>

#include "EInGame.h"
#include "Juego.h"
#include "Escena.h"

using namespace std;

EInGame* EInGame::pinstance = 0;
EInGame* EInGame::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new EInGame(context);

    pinstance->Handle(); // //En el momento en el que se crea el estado, se activa este estado en el contexto
    return pinstance;
}

EInGame::EInGame(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EInGame::Handle(){
    
    std::cout << "EInGame: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

Juego* EInGame::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}