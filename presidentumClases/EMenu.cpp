/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMenu.cpp
 * Author: chiri
 * 
 * Created on 5 de abril de 2016, 19:41
 */

#include <stdio.h>
#include <iostream>
#include "EMenu.h"
#include "EIntro.h"

using namespace std;

EMenu* EMenu::pinstance = 0;
EMenu* EMenu::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new EMenu(context);

    pinstance->Handle(); // //En el momento en el que se crea el estado, se activa este estado en el contexto
    return pinstance;
}

EMenu::EMenu(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EMenu::Handle(){
    
    std::cout << "EMenu: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

Juego* EMenu::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}