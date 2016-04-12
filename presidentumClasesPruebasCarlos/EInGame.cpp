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

    return pinstance;
}

EInGame::EInGame(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EInGame::Handle(){
    
    std::cout << "EInGame: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

void EInGame::Init(){
    
    rectangulo.setSize(sf::Vector2f(300, 200));
    rectangulo.setOutlineColor(sf::Color::Blue);
    rectangulo.setFillColor(sf::Color::Blue);
    rectangulo.setOutlineThickness(2);
    rectangulo.setOrigin(rectangulo.getSize().x/2,rectangulo.getSize().y/2);
    rectangulo.setPosition(_context->window->getSize().x/2, _context->window->getSize().y/2);
    
}

void EInGame::Update(){
    
    if(!initState){
        Init();
        initState = true;
    }
    
    rectangulo.rotate(0.2);
    
    Render();

}

void EInGame::Render(){
    
    _context->window->clear(sf::Color::White); //COLOR DE FONDO BLANCO    
    _context->window->draw(rectangulo);
    _context->window->display();
    
}

void EInGame::generarRecorte(){
    
    
    
}

Juego* EInGame::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

EInGame::~EInGame(){
                            //Destruccion de la instancia 
    std::cout << "EInGame ha sido eliminada. "  << std::endl;
    _context = 0;
    pinstance = 0;
    
}