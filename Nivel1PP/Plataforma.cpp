/* 
 * File:   Plataforma.cpp
 * Author: Aitor
 * 
 * Created on 19 de abril de 2016, 17:52
 */

#include "Plataforma.h"
#include <iostream>
#include <fstream>
#include <cstring>

    using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

Plataforma::Plataforma(int x, int y) {
    posx=x;
    posy=y;
    tiempo=0;
    recorrido=0;
    direccion=1; //1 derecha, 0 izquierda
    
    if (!texPlat.loadFromFile("resources/PP/PlataformaHorizontal.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    spritePlat.setTexture(texPlat);
    spritePlat.setPosition(x, y);
    tiempo= tiempoRecorrido.getElapsedTime().asSeconds();
}

Plataforma::Plataforma(const Plataforma& orig) {
}

Plataforma::~Plataforma() {
}

void Plataforma::move(){
    
//    if(direccion==1){
//        if(tiempo>3){
//            spritePlat.move(5, 0);
//            recorrido+=5;
//            tiempoRecorrido.restart();
//        }
//    }else{
//        if(tiempo>3){
//            spritePlat.move(-5,0);
//            recorrido+=5;
//            tiempoRecorrido.restart();
//        }
//    }
//    
//    if(recorrido==40){
//        if(direccion==1){
//            direccion=0;
//            recorrido=0;
//        }else{
//            direccion=1;
//            recorrido=0;
//        }
//    }
//     //cout<<tiempo<<endl;
//    tiempoRecorrido.restart();

    
//    tiempo= tiempoRecorrido.getElapsedTime().asSeconds();
//    /*USAR LA POSICION INICIAL DE LA PLATAFORMA*/
//    if(tiempo>=0 && tiempo<=2){
//        if(spritePlat.getPosition().x<posx+92){
//            spritePlat.move(0.005,0);
//        }
//    }else if(tiempo>2){
//        if(tiempo>=4){
//            tiempoRecorrido.restart();
//        }
//        if(spritePlat.getPosition().x>posx-92){
//            spritePlat.move(-0.005,0);
//        }
//        
//    }
    
    tiempo= tiempoRecorrido.getElapsedTime().asSeconds();
    if(direccion==1){
        if(tiempo>0.035){
            spritePlat.move(2.5,0);
            recorrido+=2.5;
           // cout<<spritePlat.getPosition().x<<endl;
            // cout<<"Espacio recorrido: "<<recorrido<<endl;
            tiempoRecorrido.restart();
        }
    }
    
    if(direccion==0){
        if(tiempo>0.035){
            spritePlat.move(-2.5,0);
            recorrido+=2.5;
            //cout<<spritePlat.getPosition().x<<endl;
            // cout<<"Espacio recorrido: "<<recorrido<<endl;
            tiempoRecorrido.restart();
        }
    }
    
    if(recorrido>256){
        if(direccion==1){
            direccion=0;
            recorrido=0;
            //cout<<"Cambio a izquierda"<<endl;
        }else{
            direccion=1;
            recorrido=0;
            //cout<<"Cambio a derecha"<<endl;
        } 
    }
   
    
}