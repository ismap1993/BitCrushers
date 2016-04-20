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

    return pinstance;
}

EMenu::EMenu(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EMenu::Handle(){
    
    std::cout << "EMenu: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

void EMenu::Init(){
    
   
    
}

void EMenu::Update(){
    
    if(!initState){
        Init();
        initState = true;
    }
    
    //ACCIONES DE UPDATE
    
    Render();

}

void EMenu::Render(){
    

}


Juego* EMenu::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

EMenu::~EMenu(){
                            //Destruccion de la instancia 
    std::cout << "EMenu ha sido eliminada. "  << std::endl;
    _context = 0;
    pinstance = 0;
    
}