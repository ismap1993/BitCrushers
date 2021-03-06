/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.cpp
 * Author: alfon
 * 
 * Created on 5 de abril de 2016, 19:31
 */
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Jugador.h"
#include "Camara.h"
#include "Mapa.h"
#include "Proyectil.h"
#include <SFML/Audio.hpp>
#include "Mapa.h"
#include "Proyectil.h"
#include "Juego.h"
#include "Mundo.h"
#include "EInGame.h"


using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")

Jugador* Jugador::pinstance = 0;
Jugador* Jugador::Instance(){
    
    if(pinstance == 0) pinstance = new Jugador();

    return pinstance;
}

Jugador::Jugador() {
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}

void Jugador::iniciarJugador(float x, float y, int politic, bool activado){
    vidas=10;
    vidasPrincipales=3;
    
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    
    politico=politic;
    leerXML();
    switch(politico){
        case 1:
            if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pablospritesheet.png";
            }
            break;
        case 2:
            if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura de albertspritesheet.png";
            }
            break;
        case 3:
            if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura de marianospritesheet.png";
            }
            break;
        case 4:
            if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
            }
            break;
            
    }
    
    
    sprite.setTexture(texturaJugador);
    //Le pongo el centroide donde corresponde
    // w=78 h=148 en todos los sprites menos en los de ataque
    sprite.setOrigin(39, 74);
   
    sprite.setOrigin((matriz[0][2])/2,(matriz[0][3])/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
    
    sprite.setPosition(x, y);
//    std::cout<<sprite.getPosition().x<<" estamos en estas dos coordenadas "<<sprite.getPosition().y<<std::endl;
    tieneLLave = false;
    activo = activado;
    alturaSuelo=sprite.getPosition().y+10;
    
    posicionJugador.x=x;
    posicionJugador.y=y;
    salto=false;
    velocidadMovimiento=3;
    velocidadSalto=12;
    velocidadJugador.x=0;
    velocidadJugador.y=0;
    muerto=false;
    direccionPro=1;//para saber la direccion del proyectil. Derecha: 1. Izquierda 2.
    
    proyectiles = new vector<Proyectil*>();
    golpeado=false;
    col=0;
    paso=0;
    golpeoXseg=0;
    eliminadoA=-1;
    eliminadoC=-1;
    
    ///////////////////////////BUFFER DE SONIDO////////
    
   
    if (!bufferSalto.loadFromFile("resources/FX/Salto.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    
   
    soundSalto.setBuffer(bufferSalto);
    
    if (!bufferAtaque.loadFromFile("resources/FX/ATAQUE.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    
   
    soundAtaque.setBuffer(bufferAtaque);

    
    
    ///////////////////////////SETEO DEL CONTROLADOR////////
    
    
    for(int i=0; i<8;i++){  //Busca un mando conectado
        
        if(sf::Joystick::isConnected(i)){
            
            controllerIndex = i;
            std::cout<<"Mando encontrado en puerto: "<<controllerIndex<<std::endl; 
            break;
        }
        
    }
    
}

void Jugador::leerXML(){
    int posX=0;
    int linea=1;
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    switch(politico){
        case 1:
            fin.open("resources/pablospritesheet.xml");
                
            break;
        case 2:
            fin.open("resources/albertspritesheet.xml");
                
            break;
        case 3:
            fin.open("resources/marianospritesheet.xml");
                
            break;
        case 4:
            fin.open("resources/pedrospritesheet.xml");
                
            
            break;
            
    } // abrir el xml que se va a leer
    
    
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
        if(linea==15){break;}
    }
    //Esto es para imprimir la matriz obtenida en consola
    /*
    if(linea>2){
        for(int i=0; i<=11;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
            }
            cout << endl;
        }
    }
    cout<<"presidentumClases"<<endl;
    */
}

void Jugador::draw(){
    if(muerto==false){
         Juego::Instance()->window->draw(sprite);
         dibujarProyectiles();
        //std::cout<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    }
    //std::cout<<sprite.getPosition().y<<std::endl;
    
    
    //    //PRUEBAS DEL MANDO
//    if(sf::Joystick::isButtonPressed(controllerIndex,0)){
//        std::cout<<"Mando: A "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,1)){
//         std::cout<<"Mando: B "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,2)){
//         std::cout<<"Mando: X "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,3)){
//         std::cout<<"Mando: Y "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,4)){
//         std::cout<<"Mando: L "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,5)){
//         std::cout<<"Mando: R "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,6)){
//         std::cout<<"Mando: Select "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,7)){
//         std::cout<<"Mando: Start "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,8)){
//         std::cout<<"Mando: JoyClickL "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,9)){
//         std::cout<<"Mando: JoyClickR "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovY) ==  100){
//        std::cout<<"Mando: UP "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovY) ==  -100){
//        std::cout<<"Mando: DOWN "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  -100){
//        std::cout<<"Mando: LEFT "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  100){
//        std::cout<<"Mando: RIGHT "<<std::endl;
//
//    }
}

sf::Sprite Jugador::getSprite(){
    return sprite;
}

//estoy pasando por parametro los vectores de sprites por el handle (que es una guarrada) porque no puedo hacerlo en el main
//una vez con la maquina de estado podremos accedera ellos sin pasarlo por parametro
void Jugador::handle(){
  
    /*sf::Clock golpeoTime;
    float golpeo=0;
    
    golpeo= golpeoTime.getElapsedTime().asSeconds();
    if(golpeo>0.5 && direccionPro==1){
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
        sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        golpeoTime.restart();
    }

    if(golpeo>0.5 && direccionPro==0){
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
        sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        golpeoTime.restart();
    }
*/

    const float gravedad =0.5;

    
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
//        if(politico==2 || politico ==3){
//            disparar();
//        }else{
            std::cout<<matriz[1][2]<<" "<<matriz[1][3]<<std::endl;
            sprite.setOrigin(matriz[2][2]/2,matriz[1][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
            sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
//        }
    }*/
    bool enelsuelo=false;
    int i=0;
    
     for(i=0; i<Mundo::Instance()->mapa->arraySuelo.size(); i++){
         if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arraySuelo[i]->getGlobalBounds())){   
             if(this->getSprite().getPosition().y<Mundo::Instance()->mapa->arraySuelo[i]->getPosition().y){
                 /*Solo se subira a la plataforma si el personaje se encuentra por encima de esta, es decir: 
                  SI posicion Y del personaje < posicion Y plataforma */
                velocidadJugador.y = 0;//EInGame::Instance()->mundo->mapa->
                alturaSuelo=Mundo::Instance()->mapa->arraySuelo[i]->getPosition().y-90;
                enelsuelo=true;
             }else{
                 velocidadJugador.y=1;
             }
         }
     }
 
    int choque=-1; //0 der, 1 izq, -1 nada
    int j=0;
    for(j=0; j<Mundo::Instance()->mapa->arrayParedes.size(); j++){
        if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arrayParedes[j]->getGlobalBounds())){
            if(this->getSprite().getPosition().x<Mundo::Instance()->mapa->arrayParedes[j]->getPosition().x){
                choque=0;
            }else if(this->getSprite().getPosition().x>Mundo::Instance()->mapa->arrayParedes[j]->getPosition().x){
                choque=1;
            }
        }
    }
    
    int choquePlat;
    int k=0;

    for(k=0; k<Mundo::Instance()->mapa->arrayPlataformas.size(); k++){
        if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arrayPlataformas[k]->spritePlat.getGlobalBounds())){  
            if(this->getSprite().getPosition().y<Mundo::Instance()->mapa->arrayPlataformas[k]->spritePlat.getPosition().y){
                alturaSuelo=Mundo::Instance()->mapa->arrayPlataformas[k]->spritePlat.getPosition().y-90;
                enelsuelo=true;
                if(Mundo::Instance()->mapa->arrayPlataformas[k]->direccion==1){
                    posicionJugador.x+=0.9;
                }else{
                    posicionJugador.x-=0.9;
                }

                
                choquePlat=0;
            }
        }
    }
    
    if(enelsuelo==true){
        posicionJugador.y=alturaSuelo+36.5;
    }else{
        //cout<<"ESTOY EN EL AIRE!!!"<<endl;
        alturaSuelo=580;
    }
    
    
    if(vidasPrincipales!=0){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Joystick::isButtonPressed(controllerIndex,3)){
        politico=1;
        switch(politico){
        case 1:
            if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pablospritesheet.png";
            }
            break;
        case 2:
            if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura de albertspritesheet.png";
            }
            break;
        case 3:
            if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura de marianospritesheet.png";
            }
            break;
        case 4:
            if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
            }
            break;
            
    }
    }
    
    }
    
    if(vidasPrincipales!=0){
            
        
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Joystick::isButtonPressed(controllerIndex,1)){
        politico=2;
        Camara *cam;
        
        switch(politico){
            case 1:
                if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                    std::cerr<<"Error al cargar la textura de pablospritesheet.png";
                }
                break;
            case 2:
                if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                    std::cerr<<"Error al cargar la textura de albertspritesheet.png";
                }
                break;
            case 3:
                if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                    std::cerr<<"Error al cargar la textura de marianospritesheet.png";
                }
                break;
            case 4:
                if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                    std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
                }
                break;

        }
    }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
        
    }
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  100){
        
        direccion=1;

        direccionPro=1;
        //camara->moveRight(this);

        velocidadJugador.x = velocidadMovimiento;
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)

        paso= pasoTime.getElapsedTime().asSeconds();
        if(paso>=0 && paso<=0.2){
            sprite.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
        }
         if(paso>0.2){
             if(paso>0.4){
                 pasoTime.restart();
             }
            sprite.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));

        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  -100){
        
        direccion=0;
        
        direccionPro=0;
        
        //camara->moveLeft(this);

            velocidadJugador.x = -velocidadMovimiento;
            

            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
            
             paso= pasoTime.getElapsedTime().asSeconds();
            if(paso>=0 && paso<=0.2){
                sprite.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
               // std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
            }
             if(paso>0.2){
                 if(paso>0.4){
                     pasoTime.restart();
                 }
                sprite.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
                
            }
            
            
            
        //}  
        
        
        
    }
    
    /*else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();
        
        
        if(golpeoXseg>0.5){
                
                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
                sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                velocidadJugador.x = 0;
                golpeosSegundo.restart();
            }
        
        if(direccion==1){
            if(golpeoXseg>0.5){
                
                sprite.setOrigin(matriz[0][2]/4,matriz[0][3]/2);
                sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                velocidadJugador.x = 0;
                golpeosSegundo.restart();
            }
            
            
        }
        
        else if(direccion==0){
            if(golpeoXseg>0.5){
                sprite.setOrigin(-20,matriz[0][3]/2);
                sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                velocidadJugador.x = 0;
                golpeosSegundo.restart();
            }
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
        }
    }*/
    
    else{
        velocidadJugador.x = 0;
        if(direccionPro==1){
            sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                sprite.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
            }
        }
        else{ 
            sprite.setOrigin(matriz[6][2]/2,matriz[6][3]/2);
            sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
            }
        }
    }
    
    
    
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)  || sf::Joystick::isButtonPressed(controllerIndex,2)){
        golpeoXseg=golpeosSegundo.getElapsedTime().asMilliseconds();
        soundAtaque.play();
        
//        if(golpeoXseg>9.1){
//                
//                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
//                sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
//                velocidadJugador.x = 0;
//                golpeosSegundo.restart();
//            }
        
        if(direccion==1){
            if(golpeoXseg>9.1){
                
                sprite.setOrigin(matriz[0][2]/4,matriz[0][3]/2);
                sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                velocidadJugador.x = 0;
                
                golpeosSegundo.restart();
                if(politico == 1 || politico == 4){
                    golpeando();
                }else{
                    disparar();
                }
                
            }
            
            
        }
        
        else if(direccion==0){
            if(golpeoXseg>9.1){
//                std::cout<<"Barros "<<sprite.getOrigin().x<<" "<<sprite.getOrigin().y<<std::endl;
                sprite.setOrigin(60,matriz[2][3]/2);
                sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
//                std::cout<<"de vulgaridad"<<sprite.getOrigin().x<<" "<<sprite.getOrigin().y<<std::endl;
                velocidadJugador.x = 0;
//                std::cout<<"soy el mas gyuay"<<std::endl;
                golpeosSegundo.restart();
                if(politico == 1 || politico == 4){
                    golpeando();
                }else{
                    disparar();
                }
                //sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
                //sprite.setPosition(sprite.getOrigin().x + 50, 0);
//                if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))){
//                    
//                    sprite.setOrigin(60,matriz[2][3]/2);
//                }
                
            }
            //sprite.setOrigin(1000000,matriz[0][3]/2);
            //sprite.setPosition(sprite.getOrigin().x + 50, 0);
        }
        
        
        
        
    }
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  100 && sf::Joystick::isButtonPressed(controllerIndex,0))){
        
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
        sprite.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        
        
        
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  -100 && sf::Joystick::isButtonPressed(controllerIndex,0))){
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
        sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
    }
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::isButtonPressed(controllerIndex,0)) && salto){
        
        
                velocidadJugador.y = -velocidadSalto;
                salto = false;
                soundSalto.play(); 
    }

    if(!salto){
        velocidadJugador.y += gravedad;
       // cout<<"pos Y "<<posicionJugador.y<<endl;
        //cout<<"altura suelo "<<alturaSuelo<<endl;
        
    }        
    else
        velocidadJugador.y = 0;

    if(choque==0){
        velocidadJugador.x=-1;
    }
    if(choque==1){
        velocidadJugador.x=1;
    }
    posicionJugador += velocidadJugador;

    salto = posicionJugador.y+10  >= alturaSuelo;
//    std::cout<<"pos Y "<<posicionJugador.y<<std::endl;
//    cout<<"altura suelo"<<alturaSuelo<<endl;
//    cout<<salto<<endl;
    if(salto){
        sprite.setPosition(0, alturaSuelo-10);
//        //posicionJugador.y = alturaSuelo - 10;
//        
    }
//    cout<<"posicion X "<<posicionJugador.x<<endl;
    //cout<<"posicion Y "<<posicionJugador.y<<endl;
    if(enelsuelo==true){
                //posicionJugador.y=alturaSuelo+36.5;
    }
    
    
    
    sprite.setPosition(posicionJugador);
    
    
}

void Jugador::disparar(){
    float disparoAparicion=0;
    disparoAparicion=aparicionProyectil.getElapsedTime().asSeconds();
    if(direccionPro==1){//derecha
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            sprite.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
            sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
//            std::cout<<"Estoy golpeando y cambiadno el sprite"<<std::endl;
            if(politico==2 || politico == 3 ){
                //Al disparar, se genera un proyectil y se inserta en el vector
                Proyectil *pro = new Proyectil(direccionPro, sprite.getPosition(), matriz, politico);
                pro->crearPro();
               
                //std::cout << "posicion X proyectil reciente:" << pro->posx << std::endl;
                proyectiles->push_back(pro);
                /****/
//                std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                
                /****/
            }
        }
    }else{//izquierda
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            sprite.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
            sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
            if(politico==2 || politico == 3 ){
                //Al disparar, se genera un proyectil y se inserta en el vector
                Proyectil *pro = new Proyectil(direccionPro, sprite.getPosition(), matriz, politico);
                proyectiles->push_back(pro);
                /****/
//                std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                /****/
            }
        }
    }
}

void Jugador::dibujarProyectiles(){
    
    
    int i=0;
        //compruebo que los proyectiles del jugador se destruyen ya sea por que recorren una distancia determinadad
        //o porque golpean a los NPC. 
        //IMP si el proyectil del jugador colisiona con otro del NPC que ocurre? el mundo se destruiria y nada podria volver a ser como antes...
        for(i=0; i<proyectiles->size();i++){
            proyectiles->at(i)->dibuja();
            if(proyectiles->at(i)->destruir()){
                if(!proyectiles->empty()){
                    //Hay que comprobar que el vector no este vacio cuando quiera eliminar un objeto
                    delete proyectiles->at(i);
                    proyectiles->erase(proyectiles->begin()+i);
                }
                
            }else{
                for(int j=0; j<Mundo::Instance()->enemigosAdistancia->size(); j++){
                    if(proyectiles->at(i)->getSprite().getGlobalBounds().intersects(Mundo::Instance()->enemigosAdistancia->at(j)->getSprite()->getGlobalBounds())){
                        delete Mundo::Instance()->enemigosAdistancia->at(j);
                        Mundo::Instance()->enemigosAdistancia->erase(Mundo::Instance()->enemigosAdistancia->begin()+j);
                        enemigosEliminados++;
                        if(!proyectiles->empty()){
                            delete proyectiles->at(i);
                            proyectiles->erase(proyectiles->begin()+i);
                        }
                    }
                }
                for(int j=0; j<Mundo::Instance()->enemigosCuerpo->size(); j++){
                    if(proyectiles->at(i)->getSprite().getGlobalBounds().intersects(Mundo::Instance()->enemigosCuerpo->at(j)->getSprite()->getGlobalBounds())){
                        delete Mundo::Instance()->enemigosCuerpo->at(j);
                        Mundo::Instance()->enemigosCuerpo->erase(Mundo::Instance()->enemigosCuerpo->begin()+j);
                        enemigosEliminados++;
                        if(!proyectiles->empty()){
                            delete proyectiles->at(i);
                            proyectiles->erase(proyectiles->begin()+i);
                        }
                    }
                }
            }
        }
    
    
}

bool Jugador::isMoving(){
    
    if((posicionJugador.x-posicionAnterior.x < -3.95 || posicionJugador.x-posicionAnterior.x > 1.95))
        return true;
    else if(posicionJugador.x+posicionAnterior.x == -2 || posicionJugador.x+posicionAnterior.x == 0)
        return false;
    
}

void Jugador::golpeando() {
    
//    std::cout<<"le estoy pasando los enemigos correctamente"<<Mundo::Instance()->enemigosCuerpo->size()<<" "<<Mundo::Instance()->enemigosAdistancia->size()<<std::endl;
    for(int i=0; i<Mundo::Instance()->enemigosCuerpo->size(); i++){
        if(sprite.getGlobalBounds().intersects( Mundo::Instance()->enemigosCuerpo->at(i)->getSprite()->getGlobalBounds())){
            Mundo::Instance()->enemigosCuerpo->erase(Mundo::Instance()->enemigosCuerpo->begin()+i);
            eliminadoC=i;
        }
    }
    for(int i=0; i<Mundo::Instance()->enemigosAdistancia->size(); i++){
        if(sprite.getGlobalBounds().intersects(Mundo::Instance()->enemigosAdistancia->at(i)->getSprite()->getGlobalBounds())){
            Mundo::Instance()->enemigosAdistancia->erase(Mundo::Instance()->enemigosAdistancia->begin()+i);
            eliminadoA=i;
        }
    }
    
}