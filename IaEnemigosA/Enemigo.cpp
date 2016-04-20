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
#include <cmath> 

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")


Enemigo::Enemigo() : patrullaje(true) {
    
    std::cout<<"hola, soy un enemigo vacio"<<std::endl;
    
    
}

Enemigo::Enemigo(bool valorPatrullaje, float posx, float posy, int type){
 
   patrullaje=valorPatrullaje;
   x=posx;
   y=posy;
 
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    leerXML();
    if(!texturaEnemigo.loadFromFile("resources/CIUDADANOS/enemigosCIUDADANOS.png")){
        std::cerr<<"Error al cargar la textura de enemigosCIUDADANOS.png";
    }
    
    tipo=type;
    std::cout<<posx<<" "<<posy<<" "<<tipo<<std::endl;
    spriteSheet.setTexture(texturaEnemigo);
    if(tipo == 0){
        std::cout<<matriz[8][0]<<" "<<matriz[8][1]<<" "<<matriz[8][2]<<" "<<matriz[8][3]<<std::endl;
        spriteSheet.setOrigin(matriz[8][2]/2, matriz[8][3]/2);
        spriteSheet.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
    }else{
        spriteSheet.setOrigin(matriz[1][2]/2, matriz[1][3]/2);
        spriteSheet.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
    }
    
    spriteSheet.setPosition(x, y);
    
    direccion=1;
    
    proyectiles = new vector<Proyectil*>();
    
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
    
    if(linea>2){
        for(int i=0; i<=18;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
           }
            cout << endl;
        }
    }
    
}

void Enemigo::draw(sf::RenderWindow& window){
    /*    sf::Texture texvoto;
    if (!texvoto.loadFromFile("resources/sobres.png"))
    {
        std::cerr << "Error cargando la imagen sobres.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(texvoto);
    sprite.setPosition(500, 300);*/
    window.draw(spriteSheet);
    
    
}

void Enemigo::handle(Jugador* jugador){
    
    int posInicioX=jugador->getSprite().getPosition().x;
    float dif=posInicioX-spriteSheet.getPosition().x;
    if(abs(dif)<200){
        //std::cout<<"tengo que perseguir"<<std::endl;
        patrullaje=false;
    }else{
        patrullaje=true;
    }
    
    
    if(patrullaje){
        if(direccion == 1){
            if(x-150<spriteSheet.getPosition().x){
                std::cout<<"a la izq"<<std::endl;
                spriteSheet.move(-2.5, 0);
            }else{
                direccion = 0;
            }
        }else{
            if(x+150>spriteSheet.getPosition().x){
                std::cout<<"a la der"<<std::endl;
                spriteSheet.move(2.5, 0);
            }else{
                direccion = 1;
            }
        }
    }else{
        std::cout<<dif<<std::endl;
        if(abs(dif)<50 && direccion==1 && tipo==0){
            //golpeo a la izquierda cuerpo a cuerpo
            std::cout<<"te miro y te golpeo izq"<<std::endl;
            spriteSheet.setOrigin(matriz[8][2]/2, matriz[8][3]/2);
            spriteSheet.setTextureRect(sf::IntRect(matriz[16][0], matriz[16][1], matriz[16][2], matriz[16][3]));
        }else if(abs(dif)<50 && direccion==0 && tipo == 0){
            //golpero a la derecha cuerpo a cuerpo
            std::cout<<"te miro y te golpeo dere"<<std::endl;
            spriteSheet.setOrigin(matriz[8][2]/2, matriz[8][3]/2);
            spriteSheet.setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
        }else if(abs(dif)<150 && direccion==0 && tipo ==1){
            //golpeo a la derecha a distancia
            std::cout<<"te miro y te golpeo dere a distancia"<<std::endl;
            spriteSheet.setOrigin(matriz[1][2]/2, matriz[1][3]/2);
            spriteSheet.setTextureRect(sf::IntRect(matriz[15][0], matriz[15][1], matriz[15][2], matriz[15][3]));
            disparar();
        }else if(abs(dif)<150 && direccion==1 && tipo ==1){
            //golpeo a la izquierda a distancia
            std::cout<<"te miro y te golpeo ozq a distancia"<<std::endl;
            spriteSheet.setOrigin(matriz[1][2]/2, matriz[1][3]/2);
            spriteSheet.setTextureRect(sf::IntRect(matriz[18][0], matriz[18][1], matriz[18][2], matriz[18][3]));
            disparar();
        }
        
        else{
            if(dif<0){
                std::cout<<"a la izq calmarnooo" <<std::endl;
                spriteSheet.move(-2.5, 0);
                direccion = 1;
            }else if(dif>=0){
                std::cout<<"a la der clamarno"<<std::endl;
                spriteSheet.move(2.5, 0);
                direccion = 0;
            }else{
                spriteSheet.setOrigin(matriz[8][2]/2, matriz[8][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
                patrullaje = true;
            }
        }
        
  
        
        
    }
}

void Enemigo::disparar(){
    
    float disparoAparicion=0;
    disparoAparicion=aparicionProyectil.getElapsedTime().asSeconds();
    if(direccion==0){//derecha
        if(disparoAparicion>0.35){
       
            
                //Al disparar, se genera un proyectil y se inserta en el vector
                Proyectil *pro = new Proyectil(1, spriteSheet.getPosition(), matriz, 5);
                pro->crearPro();
                //std::cout << "posicion X proyectil reciente:" << pro->posx << std::endl;
                proyectiles->push_back(pro);
                /****/
                std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                /****/
            
        }
    }else{//izquierda
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            
            
                //Al disparar, se genera un proyectil y se inserta en el vector
                Proyectil *pro = new Proyectil(0, spriteSheet.getPosition(), matriz, 5);
                proyectiles->push_back(pro);
                /****/
                std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                /****/
            
        }
    }
    
    
    
}

