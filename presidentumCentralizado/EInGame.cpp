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
#include <fstream>
#include "EInGame.h"
#include "Juego.h"
#include "Jugador.h"
#include "Escena.h"
#include <string> 
#include <cstring>

using namespace std;

using std::ifstream;
using std::cout;
using std::endl;


const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")

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
    
    mundo = Mundo::Instance();
    mundo->crearMundo(1);
    std::cout<<"Mundo: "<<Mundo::Instance()<<std::endl;
    
}

void EInGame::Update(){
    
    if(!initState){
        Init();
        initState = true;
    }
    
    mundo->Update();
    
    Render();

}

void EInGame::Render(){
    
    _context->window->clear(sf::Color::White); //COLOR DE FONDO BLANCO    
    mundo->Render();
    _context->window->display();
    
}

Juego* EInGame::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

EInGame::~EInGame(){
                            //Destruccion de la instancia 
    
    
    delete mundo;
    mundo = 0;
    //delete Jugador::Instance();
    _context = 0;
    pinstance = 0;
    std::cout << "EInGame ha sido eliminada. "  << std::endl;
    
}