/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECinematica.cpp
 * Author: chiri
 * 
 * Created on 7 de abril de 2016, 19:41
 */

#include <stdio.h>
#include <iostream>

#include "ECinematica.h"
#include "Juego.h"
#include "Escena.h"

using namespace std;

ECinematica* ECinematica::pinstance = 0;
ECinematica* ECinematica::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new ECinematica(context);

    pinstance->Handle(); // //En el momento en el que se crea el estado, se activa este estado en el contexto
    return pinstance;
}

ECinematica::ECinematica(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void ECinematica::Handle(){
    
    std::cout << "ECinematica: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

Juego* ECinematica::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}