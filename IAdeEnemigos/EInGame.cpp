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
    
    mundo = new Mundo(1);
    
    
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
    mundo->Render();
    _context->window->display();
    
}

int** EInGame::getRecorte(){
    
    return matrizRecorte;
    
}

int** EInGame::generarRecorte(){
    int posX=0;
    int linea=1;
    
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    fin.open("resources/albertspritesheet.xml"); // abrir el xml que se va a leer
    

    // comenzamos a leer cada una de las lineas
    while (!fin.eof()){

        // esto es para controlar el tamanyo maximo de cada linea
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
        int n = 0;

        // cada linea va almacenada en un vector
        const char* token[MAX_TOKENS_PER_LINE] = {};

        // parseamos las lineas, separando cada elemento de la linea por comillas (")
        token[0] = strtok(buf, DELIMITER);

        if (token[0]){
            for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
                token[n] = strtok(0, DELIMITER);

                if (linea<=2) break; // si no hay mas, se termina el bucle
                //SOLO nos interesa a partir de la linea 2 del XML
                if(linea>2){
                    //Vamos almacenando en la matriz segun el parametro que nos interesa en el orden correcto
                    if(n==3){ //El tercer elemento corresponde a x
                        matrizRecorte[posX][0]=atoi(token[n]);
                    }

                    if(n==5){ //El quinto elemento corresponde a y
                        matrizRecorte[posX][1]=atoi(token[n]);
                    }

                    if(n==7){ //El septimo elemento corresponde a w
                        matrizRecorte[posX][2]=atoi(token[n]);
                    }

                    if(n==9){ //El noveno elemento corresponde a h
                        matrizRecorte[posX][3]=atoi(token[n]);
                        posX++;
                        break;
                    }
                }        
            }
        }

        linea++;
        if(linea==14){break;}
    }
    //Esto es para imprimir la matriz obtenida en consola
    if(linea>2){
        for(int i=0; i<11;i++){
            for (int j=0;j<4;j++){
                std::cout << "Matriz["<< i <<"]["<< j << "] =" << matrizRecorte[i][j] <<std::endl;
            }
             std::cout << std::endl;
        }
    }
    
    return matrizRecorte;
    
}

Juego* EInGame::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

EInGame::~EInGame(){
                            //Destruccion de la instancia 
    
    
    delete mundo;
    _context = 0;
    pinstance = 0;
    std::cout << "EInGame ha sido eliminada. "  << std::endl;
    
}