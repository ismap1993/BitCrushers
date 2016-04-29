/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camara.cpp
 * Author: alfon
 * 
 * Created on 17 de marzo de 2016, 22:14
 */

#include "Camara.h"
#include "Mapa.h"
#include <iostream>
#include "Jugador.h"

 #include <sstream>
 #include <vector>
 #include <string> 
 #include <fstream>
 #include <cstring>
using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
 const int MAX_TOKENS_PER_LINE = 20;
 const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")
 
 template <typename T>
std::string to_string(T countdown)
{
	std::ostringstream convert ;
	convert << countdown ;
	return convert.str() ;
}

Camara::Camara(int width, int height, int desp, Mapa &map){
    
    ancho=width;
    alto=height;
    camara = new sf::View(sf::FloatRect(0,0, ancho, alto));
    desplazamientoCamara=0;
    posicionOrigenCamara=camara->getCenter().x;
    kVel=desp;
    mapa= new Mapa();
    
    mapa->_tileWidth=map._tileWidth;
    mapa->_width=map._width;
    mapa->fondo=map.fondo;
    background=mapa->fondo;
    
    /********HUD*********/  
     font.loadFromFile("fonts/MyriadPro Regular.ttf");

     fontpixelated.loadFromFile("fonts/MyriadPro Regular.ttf");
 
     hudVotos.setString("VOTOS:");
     hudVotos.setFont(fontpixelated);
     hudVotos.setPosition(65,30);
     hudVotos.setCharacterSize(20);
     hudVotos.setColor(sf::Color::White);
     
     hudVotosValue.setString("0");
     hudVotosValue.setFont(fontpixelated);
     hudVotosValue.setPosition(140,30);
     hudVotosValue.setCharacterSize(20);
     hudVotosValue.setColor(sf::Color::White);
    
     
     //temporizador

     countdown = 200;
     convertTime= to_string(countdown);


     contador.setString("TIEMPO:");
     contador.setFont(fontpixelated);
     contador.setPosition(450,30);
     contador.setCharacterSize(20);
     contador.setColor(sf::Color::White);

     contadorValue.setFont(font);
     contadorValue.setString(convertTime);
     contadorValue.setPosition(530,30);
     contadorValue.setCharacterSize(20);
     contadorValue.setColor(sf::Color::White);
     
      /*MATRIZ BIDIMENSIONAL para almacenar los 4 parametros de cada sprite*/
     
     matriz= new int*[99];
     for(int i = 0; i < 99; i++){
         matriz[i] = new int[4];
     }
 
     posX=0;
     linea=1;
     
     
    /****LECTURA DEL XML PARA EL SPRITE!!****/
     
 
   ifstream fin;
   fin.open("resources/HUDspritesheet.xml"); // abrir el xml que se va a leer
   
   
   // comenzamos a leer cada una de las lineas
   while (!fin.eof())
   {
     // esto es para controlar el tamanyo maximo de cada linea
     char buf[MAX_CHARS_PER_LINE];
     fin.getline(buf, MAX_CHARS_PER_LINE);
     int n = 0;
     
     // cada linea va almacenada en un vector
     const char* token[MAX_TOKENS_PER_LINE] = {};
     
     // parseamos las lineas, separando cada elemento de la linea por comillas (")
     token[0] = strtok(buf, DELIMITER);
     
     if (token[0])
     {
       for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
       {
         token[n] = strtok(0, DELIMITER);
         
         //SOLO nos interesa a partir de la linea 22 del XML
         if(linea>22){
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
            }
         }
 
         if (!token[n]) break; // si no hay mas, se termina el bucle
       }
     }
 
     // imprime los 4 parametros(x,y,w,h) obtenidos de cada linea en la consola
 //    for (int i = 0; i < n; i++){// n = #of tokens
 //        if(linea>22){
 //            if(i==3 || i==5 || i==7 || i==9){
 //                cout << "Token[" << i << "] = " << token[i] << endl;
 //                
 //            }  
 //        }    
 //    } 
    
     linea++;
   }
   
   //Esto es para imprimir la matriz obtenida en consola
     if(linea>22){
         for(int i=0; i<11;i++){
             for (int j=0;j<4;j++){
                 cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
             }
             cout << endl;
         }
     }
   
    //Creamos una ventana 
    //sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum");
    
    
//    std::vector<sf::Sprite> sprites;

  //  unsigned int currentSprite{ 0 };
    
    

    //Cargo la imagen donde reside la textura del sprite
    if (!texalbert.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
   
    spritealbert.setTexture(texalbert);
    
    
     //Cargo la imagen donde reside la textura del sprite
    if (!texpedro.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritepedro.setTexture(texpedro);
    
    
     //Cargo la imagen donde reside la textura del sprite
    if (!texmariano.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritemariano.setTexture(texmariano);
    
     //Cargo la imagen donde reside la textura del sprite
    if (!texpablo.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritepablo.setTexture(texpablo);
     
    if (!texvidaalbert.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritevidaalbert.setTexture(texvidaalbert);
    
    if (!texvidaalbert2.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritevidaalbert2.setTexture(texvidaalbert2);
    
    
    if (!texvidapedro.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritevidapedro.setTexture(texvidapedro);
    
    if (!texvidamariano.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritevidamariano.setTexture(texvidamariano);
    
    if (!texvidapablo.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    spritevidapablo.setTexture(texvidapablo);
 
    
    
    //Le pongo el centroide donde corresponde
    spritealbert.setOrigin(matriz[19][2]/2,matriz[19][3]/2);
    spritepedro.setOrigin(matriz[17][2]/2,matriz[17][3]/2);
    spritemariano.setOrigin(matriz[18][2]/2,matriz[18][3]/2);
    spritepablo.setOrigin(matriz[16][2]/2,matriz[16][3]/2);
    spritevidaalbert.setOrigin(matriz[15][2]/2,matriz[15][3]/2);
    spritevidaalbert2.setOrigin(matriz[14][2]/2,matriz[14][3]/2);
    
    spritevidapedro.setOrigin(matriz[11][2]/2,matriz[11][3]/2);
    spritevidamariano.setOrigin(matriz[13][2]/2,matriz[13][3]/2);
    spritevidapablo.setOrigin(matriz[10][2]/2,matriz[10][3]/2);
    
    
    /*
     1. carapablo
     2. carapedro
     3. caramariano
     4. caraalbert
     */
    //Cojo el sprite que me interesa por defecto del sheet
    spritealbert.setTextureRect(sf::IntRect(matriz[19][0], matriz[19][1], matriz[19][2], matriz[19][3]));
    spritepedro.setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
    spritemariano.setTextureRect(sf::IntRect(matriz[18][0], matriz[18][1], matriz[18][2], matriz[18][3]));
    spritepablo.setTextureRect(sf::IntRect(matriz[16][0], matriz[16][1], matriz[16][2], matriz[16][3]));
    spritevidaalbert.setTextureRect(sf::IntRect(matriz[15][0], matriz[15][1], matriz[15][2], matriz[15][3]));
    spritevidaalbert2.setTextureRect(sf::IntRect(matriz[14][0], matriz[14][1], matriz[14][2], matriz[14][3]));
    
    spritevidapedro.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
    spritevidamariano.setTextureRect(sf::IntRect(matriz[13][0], matriz[13][1], matriz[13][2], matriz[13][3]));
    spritevidapablo.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));


    
    // Lo dispongo en el centro de la pantalla
    spritealbert.setPosition(850, 65);
    spritepedro.setPosition(50, 40);
    spritemariano.setPosition(100, 40);
    spritepablo.setPosition(150, 40);
    spritevidaalbert.setPosition(950, 65);
     spritevidaalbert2.setPosition(950, 65);
   
    spritevidapedro.setPosition(50, 70);
    spritevidamariano.setPosition(100, 70);
    spritevidapablo.setPosition(150, 70);
     
    spritealbert.setScale(1,1);
    spritepedro.setScale(0.5,0.5);
    spritemariano.setScale(0.5,0.5);
    spritepablo.setScale(0.5,0.5);
    spritevidaalbert.setScale(1,1);
    spritevidaalbert2.setScale(1,1);
 
    spritevidapedro.setScale(0.3,0.3);
    spritevidamariano.setScale(0.3,0.3);
    spritevidapablo.setScale(0.3,0.3);
    /********HUD*********/

}

Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
}

void Camara::draw(sf::RenderWindow& window){
    
    //window.draw(hudVotosValue); //VALOR NUMERICO DE LOS VOTOS
    //window.draw(hudVotos);      //CARTEL DE VOTOS
    
    window.setView(*camara);
    
}

void Camara::moveRight(Jugador *personaje){
    
    if(desplazamientoCamara==0){
        //comprobamos que la posicion del personaje sea mayor que la camara y que el centro de la camara sea menor del fondo
        if(personaje->getSprite().getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(mapa->_tileWidth*mapa->_width*0.79)){
            std::cout<<(mapa->_tileWidth*mapa->_width*0.79)<<std::endl;
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            camara->move(kVel,0);
           hudVotos.move(kVel,0);
           hudVotosValue.move(kVel,0);
           contador.move(kVel, 0);
           contadorValue.move(kVel, 0);
           spritealbert.move(kVel, 0);
           spritevidaalbert.move(kVel, 0);

           std::cout<<"posicionhud "<<hudVotos.getPosition().x;
            /*PRUEBA INTERPOLACIÓN*/
            //camara->move(1*kVel*time.asSeconds(),0);
            /*PRUEBA INTERPOLACIÓN*/
            desplazamientoCamara=desplazamientoCamara+kVel; 
        }
        /*if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            camara->move(kVel,0);
            desplazamientoCamara=desplazamientoCamara+kVel; 
        }*/

    }else{
        //con esto averiguamos el margen derecho para saber cuando parar la camara al llegar al final del mapa
        int margen= background.getLocalBounds().width-(background.getLocalBounds().width*0.79);
        if(personaje->getSprite().getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(personaje->getSprite().getPosition().x+margen) &&
            (personaje->getSprite().getPosition().x+margen)<(mapa->_tileWidth*mapa->_width)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(mapa->_tileWidth*mapa->_width*0.79)){
            camara->move(kVel,0);
            hudVotos.move(kVel,0);
            hudVotosValue.move(kVel,0);
            contador.move(kVel, 0);
            contadorValue.move(kVel, 0);
            spritealbert.move(kVel, 0);
            spritevidaalbert.move(kVel, 0);

           
            /*PRUEBA INTERPOLACIÓN*/
           // camara->move(1*kVel*time.asSeconds(),0);
            /*PRUEBA INTERPOLACIÓN*/
            desplazamientoCamara=desplazamientoCamara+kVel;  

        }
    } 
}

void Camara::moveLeft(Jugador *personaje){
    
    if(desplazamientoCamara!=0){
        if(personaje->getSprite().getPosition().x<= camara->getSize().x*0.4 + desplazamientoCamara && camara->getCenter().x!=posicionOrigenCamara){
            camara->move(-kVel,0);
            hudVotos.move(-kVel,0);
            hudVotosValue.move(-kVel,0);
            contador.move(-kVel, 0);
            contadorValue.move(-kVel, 0);
            spritealbert.move(-kVel, 0);
            spritevidaalbert.move(-kVel, 0);

           
            /*PRUEBA INTERPOLACIÓN*/
            //camara->move(-1*kVel*time.asSeconds(),0);
            /*PRUEBA INTERPOLACIÓN*/
            desplazamientoCamara=desplazamientoCamara-kVel;   
        }
    }
    
}


int Camara::getPosx(){
    return camara->getCenter().x;
}

sf::Text Camara::getHudVotos(){
    return hudVotos;
}

sf::Text Camara::getHudVotosValue(){
    return hudVotosValue;
}

sf::Text Camara::getContador(){
    return contador;
}

sf::Text Camara::getContadorValue(){
    return contadorValue;
}

void Camara::actualizarTiempo(){
    int timer = clock.getElapsedTime().asSeconds();
               
    if (timer > 0 && countdown !=0){
        std::cout<<"tiempo!!! "<<countdown<<std::endl;
        countdown--;
        contadorValue.setString(to_string(countdown));
        clock.restart();
    }
}

sf::Sprite Camara::getSpriteVidaAlbert(){
    return spritevidaalbert;
}

sf::Sprite Camara::getSpriteVidaAlbert2(){
    return spritevidaalbert2;
}

sf::Sprite Camara::getSpriteAlbert(){
    return spritealbert;
}
