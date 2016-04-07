/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMenuInGame.cpp
 * Author: chiri
 * 
 * Created on 7 de abril de 2016, 19:46
 */

#include <stdio.h>
#include <iostream>

#include "EMenuInGame.h"
#include "Juego.h"
#include "Escena.h"

using namespace std;

EMenuInGame* EMenuInGame::pinstance = 0;
EMenuInGame* EMenuInGame::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new EMenuInGame(context);

    pinstance->Handle(); // //En el momento en el que se crea el estado, se activa este estado en el contexto
    return pinstance;
}

EMenuInGame::EMenuInGame(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EMenuInGame::Handle(){
    
    std::cout << "EMenuInGame: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

Juego* EMenuInGame::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}