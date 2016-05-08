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
 * 
*/

#include "BossFinal.h"
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

BossFinal::BossFinal() : patrullaje(true) {
    
    std::cout<<"hola, soy un enemigo vacio"<<std::endl;
    
    
}

BossFinal::BossFinal(bool valorPatrullaje, float posx, float posy, int type){
    
    std::cout<<"JEFE creado"<<std::endl;
    
    patrullaje=valorPatrullaje;
    x=posx;
    y=posy+40;
 
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    leerXML();

    // 1 PP. 2 PSOE. 3 CS. 4 PODEMOS
    
    tipo=type;
    
    switch(tipo){
        case 1:
            if(!texturaEnemigo.loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Mariano";
            }
             
            break;
        case 2:
            if(!texturaEnemigo.loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Pedro";
            }
            
            break;
        case 3:
            if(!texturaEnemigo.loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Albert";
            } 
            break;
        case 4:
            if(!texturaEnemigo.loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Pablo";
            }
            break;
            
    }
    
    spriteSheet.setTexture(texturaEnemigo);    
    spriteSheet.setOrigin(matriz[0][2]/2, matriz[0][3]/2);
    spriteSheet.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
    
    spriteSheet.setPosition(x, y);
    
    direccion=1;
    
    proyectiles = new vector<Proyectil*>();
    paso=0;
    golpeosSegundo;
    golpeoXseg=0;
    golpeado=false;
    activado = false; //si nos acercamos lo suficiente al bss final despertará y empezara a moverse
    hp= 10;
}


bool BossFinal::getPatrullaje(){
    
    return patrullaje;
    
}

void BossFinal::setPatrullaje(bool valorPatrullaje){
    
    patrullaje = valorPatrullaje;
    
}

BossFinal::~BossFinal() {
}

void BossFinal::leerXML(){
    int posX=0;
    int linea=1;
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    fin.open("resources/marianospritesheet.xml"); // abrir el xml que se va a leer
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
    /*
    if(linea>2){
        for(int i=0; i<=18;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
           }
            cout << endl;
        }
    }
    */
}

void BossFinal::draw(sf::RenderWindow& window){
    window.draw(spriteSheet);
}

void BossFinal::handle(Jugador* jugador){
    
    //if(jugador->getSprite().getPosition().x > x-(1066*0.7)){
    if(jugador->getSprite().getPosition().x > 4600 && !activado){
        activado = true; 
    }
    if(activado && !jugador->muerto){
        std::cout<<"Soy el jefe y me estoy moviendo porque molo mucho"<<std::endl;
        int posInicioX=jugador->getSprite().getPosition().x;
        float dif=posInicioX-spriteSheet.getPosition().x;
        //Para que el personaje se mueva
        if(direccion == 1){
            if(x-400<spriteSheet.getPosition().x){
                std::cout<<"a la izq"<<std::endl;
                spriteSheet.move(-10, 0);
            }else{
                direccion = 0;
            }
        }else{
            if(x+50>spriteSheet.getPosition().x){
                std::cout<<"a la der"<<std::endl;
                spriteSheet.move(10, 0);
            }else{
                direccion = 1;
            }
        }
        //Para hacer los pasos
        if(direccion==1){
            paso= pasoTime.getElapsedTime().asSeconds();
            if(paso>=0 && paso<=0.2){
                spriteSheet.setOrigin(matriz[8][2]/2, matriz[8][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
            }
             if(paso>0.2){
                pasoTime.restart();
                spriteSheet.setOrigin(matriz[7][2]/2, matriz[7][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
            }
        }else if(direccion==0){
            paso= pasoTime.getElapsedTime().asSeconds();
            if(paso>=0 && paso<=0.2){
                spriteSheet.setOrigin(matriz[4][2]/2, matriz[4][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
            }
             if(paso>0.2){
                pasoTime.restart();
                spriteSheet.setOrigin(matriz[5][2]/2, matriz[5][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
            }
        }
        
        //Zona de golpeo
        golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();
        if(abs(dif)<60 && direccion==1 && (tipo == 2 || tipo == 4) && !golpeado && jugador->getSprite().getPosition().y < (spriteSheet.getPosition().y+20) && jugador->getSprite().getPosition().y > (spriteSheet.getPosition().y-20)){
            //golpeo a la izquierda cuerpo a cuerpo

            if(golpeoXseg>1){
                //std::cout<<"te miro y te golpeo izq"<<std::endl;
                spriteSheet.setOrigin(40, matriz[2][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                if(spriteSheet.getGlobalBounds().intersects(jugador->getSprite().getGlobalBounds())){
                    std::cout<<"te miro y te golpeo izq"<<spriteSheet.getPosition().y<<" "<<jugador->getSprite().getPosition().y<<std::endl;
                    golpeado = true;
                    jugador->golpeado=true;
                    jugador->vidas=jugador->vidas-2;
                    if(jugador->vidas<0)jugador->vidas=0;
                    std::cout<<"El jugador ahora tiene: "<<jugador->vidas<<"vidas"<<std::endl;

                }
                golpeosSegundo.restart();
            }
            golpeado = false;
        }else if(abs(dif)<60 && direccion==0 && (tipo == 2 || tipo == 4) && !golpeado && jugador->getSprite().getPosition().y < (spriteSheet.getPosition().y+20) && jugador->getSprite().getPosition().y > (spriteSheet.getPosition().y-20)){
            //golpero a la derecha cuerpo a cuerpo
            if(golpeoXseg>1){
                //std::cout<<"te miro y te golpeo dere"<<std::endl;
                spriteSheet.setOrigin(40, matriz[1][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                if(spriteSheet.getGlobalBounds().intersects(jugador->getSprite().getGlobalBounds())){
                    golpeado = true;
                    jugador->golpeado=true;
                    //std::cout<<"Le he golpeado al payaso ejeje"<<std::endl;
                    jugador->vidas=jugador->vidas-2;
                    if(jugador->vidas<0)jugador->vidas=0;
                    std::cout<<"El jugador ahora tiene: "<<jugador->vidas<<"vidas"<<std::endl;

                }
                golpeosSegundo.restart();
            }
            golpeado = false;
        }         
        else if(abs(dif)<300 && direccion==0 && (tipo == 1 || tipo == 3) && jugador->getSprite().getPosition().y < (spriteSheet.getPosition().y+52) && jugador->getSprite().getPosition().y > (spriteSheet.getPosition().y-58)){
            //golpeo a la derecha a distancia
            if(golpeoXseg>1){
                //std::cout<<"te miro y te golpeo dere a distancia"<<spriteSheet.getPosition().y<<" "<<jugador->getSprite().getPosition().y<<std::endl;
                spriteSheet.setOrigin(30, matriz[1][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                disparar();

                golpeosSegundo.restart();
            }else{
                spriteSheet.setOrigin(matriz[0][2]/2, matriz[0][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
            }
        }else if(abs(dif)<300 && direccion==1 && (tipo == 1 || tipo == 3) && jugador->getSprite().getPosition().y < (spriteSheet.getPosition().y+52) && jugador->getSprite().getPosition().y > (spriteSheet.getPosition().y-58)){
            //golpeo a la izquierda a distancia
            //jugador->getSprite().getPosition().y < (spriteSheet.getPosition().y+52) && jugador->getSprite().getPosition().y > (spriteSheet.getPosition().y-58)
            //con comprobacion para que los el npc dispare si esta en esa zona Y, para que no tire chorizos sin sentido
            if(golpeoXseg>1){
                //std::cout<<"te miro y te golpeo izq a distancia "<<spriteSheet.getPosition().y<<" "<<jugador->getSprite().getPosition().y<<std::endl;
                spriteSheet.setOrigin(50, matriz[2][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));

                disparar();

                golpeosSegundo.restart();
            }else{
                spriteSheet.setOrigin(matriz[0][2]/2, matriz[0][3]/2);
                spriteSheet.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
            }
        }

//            else{
//                if(dif<0 && !golpeado){
//                    //std::cout<<"a la izq calmarnooo" <<std::endl;
//                    spriteSheet.move(-7.5, 0);
//
//                    direccion = 1;
//                }else if(dif>=0 && !golpeado){
//                    //std::cout<<"a la der clamarno"<<std::endl;
//                    spriteSheet.move(7.5, 0);
//                    direccion = 0;
//                }else{
//                    spriteSheet.setOrigin(matriz[1][2]/2, matriz[1][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
//                    //std::cout<<"porque entro aqui?"<<std::endl;
//                    patrullaje = true;
//                    golpeado=false;
//                    //std::cout<<"holaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" <<std::endl;
//                }
//            }
        
     
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//    if(jugador->getSprite().getPosition().x > x-(1066*0.7)){
//        //condicion para que se mueva o no según su posicion. Quizas deba hacerla en el propio main.
//        //IMP el 1066 es el ancho de la camara.
//        //std::cout<<"me estoy moviento, yo soy el que comienza en:"<<x<<std::endl;
//        
//        int posInicioX=jugador->getSprite().getPosition().x;
//        float dif=posInicioX-spriteSheet.getPosition().x;
//        if(abs(dif)<200){
//            //std::cout<<"tengo que perseguir"<<std::endl;
//            patrullaje=false;
//        }else{
//            patrullaje=true;
//        }
//
//        //spriteSheet.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
//
//        if(direccion==1){
//            paso= pasoTime.getElapsedTime().asSeconds();
//            if(tipo==1){
//                if(paso>=0 && paso<=0.2){
//                    spriteSheet.setOrigin(matriz[12][2]/2, matriz[12][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[12][0], matriz[12][1], matriz[12][2], matriz[12][3]));
//                    //std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
//                }
//                 if(paso>0.2){
//                     //if(paso>0.4){
//                        //std::cout<<"ID= adiooooooooooooooooooooooooooooooooooooooos"<<std::endl;
//                        pasoTime.restart();
//                     //}
//                    spriteSheet.setOrigin(matriz[15][2]/2, matriz[15][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[15][0], matriz[15][1], matriz[15][2], matriz[15][3]));
//
//                }
//            }
//
//            else if(tipo==0){
//                if(paso>=0 && paso<=0.2){
//                    spriteSheet.setOrigin(matriz[3][2]/2, matriz[3][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
//                    //std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
//                }
//                 if(paso>0.2){
//                     //if(paso>0.4){
//                        //std::cout<<"ID= adiooooooooooooooooooooooooooooooooooooooos"<<std::endl;
//                        pasoTime.restart();
//                     //}
//                    spriteSheet.setOrigin(matriz[6][2]/2, matriz[6][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
//
//                }
//            }
//        }else if(direccion==0){
//            paso= pasoTime.getElapsedTime().asSeconds();
//            if(tipo==1){
//                if(paso>=0 && paso<=0.1){
//                    spriteSheet.setOrigin(matriz[11][2]/2, matriz[11][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
//                    //std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
//                }
//                 if(paso>0.1){
//                    if(paso>0.16){
//                        pasoTime.restart();
//                    }
//                    spriteSheet.setOrigin(matriz[16][2]/2, matriz[16][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[16][0], matriz[16][1], matriz[16][2], matriz[16][3]));
//
//                }
//
//            }else if(tipo==0){
//                if(paso>=0 && paso<=0.2){
//                    spriteSheet.setOrigin(matriz[2][2]/2, matriz[2][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
//                    //std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
//                }
//                 if(paso>0.2){
//                     //if(paso>0.4){
//                        //std::cout<<"ID= adiooooooooooooooooooooooooooooooooooooooos"<<std::endl;
//                        pasoTime.restart();
//                     //}
//
//                    spriteSheet.setOrigin(matriz[7][2]/2, matriz[7][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
//
//                }
//            }
//        }
//
//
//        if(patrullaje){
//            if(direccion == 1){
//                if(x-150<spriteSheet.getPosition().x){
//                    //std::cout<<"a la izq"<<std::endl;
//                    spriteSheet.move(-7.5, 0);
//                }else{
//                    direccion = 0;
//                }
//            }else{
//                if(x+150>spriteSheet.getPosition().x){
//                    //std::cout<<"a la der"<<std::endl;
//                    spriteSheet.move(7.5, 0);
//                }else{
//                    direccion = 1;
//                }
//            }
//        }else{
//            //std::cout<<"La diferencia entre el sprite y el NPC es de: "<<dif<<std::endl;
//            golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();
//            if(abs(dif)<60 && direccion==1 && tipo==0 && !golpeado && jugador->getSprite().getPosition().y > 280){
//                //golpeo a la izquierda cuerpo a cuerpo
//
//                if(golpeoXseg>1){
//                    //std::cout<<"te miro y te golpeo izq"<<std::endl;
//                    spriteSheet.setOrigin(60, matriz[9][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
//                    if(spriteSheet.getGlobalBounds().intersects(jugador->getSprite().getGlobalBounds())){
//                        golpeado = true;
//                        std::cout<<"Le he golpeado al payaso"<<std::endl;
//                        jugador->golpeado=true;
//                    }
//                    golpeosSegundo.restart();
//                }
//
//            }else if(abs(dif)<60 && direccion==0 && tipo == 0 && !golpeado && jugador->getSprite().getPosition().y > 280){
//                //golpero a la derecha cuerpo a cuerpo
//                if(golpeoXseg>1){
//                    //std::cout<<"te miro y te golpeo dere"<<std::endl;
//                    spriteSheet.setOrigin(20, matriz[8][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
//                    if(spriteSheet.getGlobalBounds().intersects(jugador->getSprite().getGlobalBounds())){
//                        golpeado = true;
//                        jugador->golpeado=true;
//                        //std::cout<<"Le he golpeado al payaso ejeje"<<std::endl;
//                    }
//                    golpeosSegundo.restart();
//                }
//            }else if(abs(dif)<150 && direccion==0 && tipo ==1 && jugador->getSprite().getPosition().y > 310){
//                //golpeo a la derecha a distancia
//                if(golpeoXseg>1){
//                //std::cout<<"te miro y te golpeo dere a distancia"<<std::endl;
//                    spriteSheet.setOrigin(matriz[17][2]/2, matriz[17][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
//                    disparar();
//
//                    golpeosSegundo.restart();
//                }
//            }else if(abs(dif)<150 && direccion==1 && tipo ==1 && jugador->getSprite().getPosition().y > 310){
//                //golpeo a la izquierda a distancia
//                if(golpeoXseg>1){
//                //std::cout<<"te miro y te golpeo izq a distancia"<<std::endl;
//                    spriteSheet.setOrigin(matriz[18][2]/2, matriz[18][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[18][0], matriz[18][1], matriz[18][2], matriz[18][3]));
//
//                    disparar();
//
//                    golpeosSegundo.restart();
//                }
//            }
//
//            else{
//                if(dif<0 && !golpeado){
//                    //std::cout<<"a la izq calmarnooo" <<std::endl;
//                    spriteSheet.move(-7.5, 0);
//
//                    direccion = 1;
//                }else if(dif>=0 && !golpeado){
//                    //std::cout<<"a la der clamarno"<<std::endl;
//                    spriteSheet.move(7.5, 0);
//                    direccion = 0;
//                }else{
//                    spriteSheet.setOrigin(matriz[1][2]/2, matriz[1][3]/2);
//                    spriteSheet.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
//                    //std::cout<<"porque entro aqui?"<<std::endl;
//                    patrullaje = true;
//                    golpeado=false;
//                    //std::cout<<"holaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" <<std::endl;
//                }
//            }
//        }
//    
//    }
//    
//    
    
}

void BossFinal::disparar(){
    
    float disparoAparicion=0;
    disparoAparicion=aparicionProyectil.getElapsedTime().asSeconds();
    if(direccion==0){//derecha
        if(disparoAparicion>0.35){
       

            //Al disparar, se genera un proyectil y se inserta en el vector
            Proyectil *pro = new Proyectil(1, spriteSheet.getPosition(), matriz, tipo);
            pro->crearPro();
            std::cout << "posicion X proyectil reciente:" << pro->getSprite().getPosition().y << std::endl;
            proyectiles->push_back(pro);
            /****/
            //std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
            /****/
            
        }
    }else{//izquierda
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            
            
            //Al disparar, se genera un proyectil y se inserta en el vector
            Proyectil *pro = new Proyectil(0, spriteSheet.getPosition(), matriz, 5);
            proyectiles->push_back(pro);
            /****/
            //std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
            /****/
            
        }
    }
    
}

sf::Sprite BossFinal::getSprite(){

    return spriteSheet;

}
