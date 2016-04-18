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
using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")


Jugador::Jugador() {
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}

Jugador::Jugador(float x, float y, int politico, bool activado){
    
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
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
    std::cout<<sprite.getPosition().x<<" estamos en estas dos coordenadas "<<sprite.getPosition().y<<std::endl;
    tieneLLave = false;
    activo = activado;
    alturaSuelo=sprite.getPosition().y+10;
    
    posicionJugador.x=x;
    posicionJugador.y=y;
    salto=false;
    velocidadMovimiento=1;
    velocidadSalto=5;
    velocidadJugador.x=0;
    velocidadJugador.y=0;
    muerto=false;

}

void Jugador::leerXML(){
    int posX=0;
    int linea=1;
    
    
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    fin.open("resources/pablospritesheet.xml"); // abrir el xml que se va a leer
    

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
        if(linea==14){break;}
    }
    //Esto es para imprimir la matriz obtenida en consola
    if(linea>2){
        for(int i=0; i<11;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
            }
            cout << endl;
        }
    }
    cout<<"presidentumClases"<<endl;
}

void Jugador::draw(sf::RenderWindow& window){
    if(muerto==false){
        window.draw(sprite);
    }
    
     //std::cout<<sprite.getPosition().y<<std::endl;
}

sf::Sprite Jugador::getSprite(){
    return sprite;
}

void Jugador::handle(sf::Event event, sf::RenderWindow &window, Mapa *mapa, Camara *camara){
    
    /*sf::RectangleShape suelo(sf::Vector2f(1280, 500));
    suelo.setPosition(0,500);
    suelo.setOutlineThickness(1.0f);
    suelo.setFillColor(sf::Color(120,66,0));
    suelo.setOutlineColor(sf::Color::Black);
    */
    
    //sf::Vector2f posicionJugador(sprite.getPosition().x, sprite.getPosition().y);
    //sf::Vector2f velocidadJugador(0, 0);
    const float gravedad = 0.1;
    //int alturaSuelo = suelo.getPosition().y - 65;
    //int alturaSuelo = sprite.getPosition().y+10;
    //float velocidadSalto = 100, velocidadMovimiento = 5;
    
    //bool salto= false;
    //sprite.setPosition(posicionJugador);
    
    switch(event.type){
        case sf::Event::Closed:
            window.close();
            break;
        
        case sf::Event::KeyPressed:
            
            switch(event.key.code){
                
            }
 
    }
    
    /*CAIDAS*/
    if(mapa->getTile(this->getSprite().getPosition().x, this->getSprite().getPosition().y+64)>1){
                                velocidadJugador.y = 0;
                                alturaSuelo=this->getSprite().getPosition().y;
                                
                                 //std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)<<std::endl;
    }else if(mapa->getTile(this->getSprite().getPosition().x, this->getSprite().getPosition().y+64)==1){
            
            //std::cout<<"holaaaaaa"<<std::endl;
            //std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y+32)<<std::endl;
            
            alturaSuelo=580;
            
            if(this->getSprite().getPosition().y>400){ //MUERTE!!
                //std::cout<<"ID= "<< personaje->getPosition().y<<std::endl;
                
                //muerto=true;
                alturaSuelo=500;
                //velocidadJugador.y = 0;
                //personaje->setPosition(personaje->getPosition().x, 690);
            }
            
            //velocidadJugador.y = aux;
     }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        camara->moveRight(this);
        //std::cout<<"ID= "<< mapa->getTile(this->getSprite().getPosition().x, this->getSprite().getPosition().y)<<std::endl;
        if(mapa->getTile(this->getSprite().getPosition().x, this->getSprite().getPosition().y)>1){
            std::cout<<"ID= choque derecho!"<<std::endl;
            velocidadJugador.x = -5;    
        }else{
            velocidadJugador.x = velocidadMovimiento;
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
            sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        camara->moveLeft(this);
        
        if(mapa->getTile(this->getSprite().getPosition().x, this->getSprite().getPosition().y)>1){
            std::cout<<"ID= choque izquierdo!"<<std::endl;
            velocidadJugador.x = 5;    
        }else{
            velocidadJugador.x = -velocidadMovimiento;
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
            sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        }  
    }
    else{
        velocidadJugador.x = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
        sprite.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
        sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && salto){
                velocidadJugador.y = -velocidadSalto;
                salto = false;
    }

    if(!salto)
        velocidadJugador.y += gravedad;
    else
        velocidadJugador.y = 0;

    posicionJugador += velocidadJugador;

    salto = posicionJugador.y + 10 >= alturaSuelo;
    //std::cout<<posicionJugador.x<<"ammm"<<posicionJugador.y<<std::endl;
    if(salto){
        sprite.setPosition(0, alturaSuelo-10);
        //posicionJugador.y = alturaSuelo - 10;
        
    }
        
    sprite.setPosition(posicionJugador);
}