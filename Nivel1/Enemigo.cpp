/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   Enemigo.cpp
 * Author: chiri
 * 
 * Created on 12 de abril de 2016, 20:25
 *
 * VARIABLES DE ENEMIGO HEREDADAS;
    int x; //posicion del personaje en x
    int y; //posicion del personaje en y
    int ataque; // daño que el NPC inflinje al jugador
    int hp; // vida que tiene el NPC
    //Mundo* mundo;
    //IA* ia;
    sf::Texture* spriteSheet; // spritesheet que usará el sprite
*/

#include "Enemigo.h"
#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstring>

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")

Enemigo::Enemigo(float x, float y, int tipo){
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    leerXML();
    
    if(!texturaEnemigo.loadFromFile("resources/CIUDADANOS/enemigosCIUDADANOS.png")){
        std::cerr<<"Error al cargar la textura de enemigosCIUDADANOS.png";
    }
    
    spriteEnemigo.setTexture(texturaEnemigo);
    if(tipo==0){//0 cuerpo, 1 distancia
            spriteEnemigo.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
    }else{
            spriteEnemigo.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
    }
    
    spriteEnemigo.setPosition(x, y-15);
}
Enemigo::Enemigo() : patrullaje(true) {
    
    std::cout<<"hola, soy un enemigo vacio"<<std::endl;
    
    
}

Enemigo::Enemigo(bool valorPatrullaje) : patrullaje(valorPatrullaje) {
 
//    std::cout<<"hola, soy un enemigo con un parametro, el del patrullaje."<<std::endl;
//   
//    if(!texturaEnemigo.loadFromFile("resources/CIUDADANOS/NPC-Cs (01).png")){
//        std::cerr<<"Error al cargar la textura de NPC-Cs (01).png";
//    }
//    
//    spriteSheet.setTexture(texturaEnemigo);
//    spriteSheet.scale(1.25, 1.25);
//    spriteSheet.setPosition(533, 285);
    
}


bool Enemigo::getPatrullaje(){
    
    return patrullaje;
    
}

void Enemigo::setPatrullaje(bool valorPatrullaje){
    
    patrullaje = valorPatrullaje;
    
}

Enemigo::~Enemigo() {
}

void Enemigo::leerXML(){
    int posX=0;
    int linea=1;
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    fin.open("resources/CIUDADANOS/enemigosCIUDADANOS.xml"); // abrir el xml que se va a leer
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
                        matriz[posX][0]=atoi(token[n]);
                    }

                    if(n==5){ //El quinto elemento corresponde a y
                        matriz[posX][1]=atoi(token[n]);
                    }

                    if(n==7){ //El septimo elemento corresponde a w
                        matriz[posX][2]=atoi(token[n]);
                    }

                    if(n==9){ //El noveno elemento corresponde a h
                        matriz[posX][3]=atoi(token[n]);
                        posX++;
                        break;
                    }
                }        
            }
        }
        linea++;
        if(linea==22){break;}
    }
    //Esto es para imprimir la matriz obtenida en consola
    
//    if(linea>2){
//        for(int i=0; i<=19;i++){
//            for (int j=0;j<4;j++){
//                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
//            }
//            cout << endl;
//        }
//    }
    
}

void Enemigo::draw(sf::RenderWindow& window){
    
    
//    window.draw(spriteSheet);
//    
    
}

void Enemigo::handle(){
//    
//    int posInicioX=x;
    
    
}

sf::Sprite Enemigo::getSprite(){
    return spriteEnemigo;
}

