/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: chiri
 * 
 * Created on 5 de abril de 2016, 17:56
 */
#include <iostream>
#include <vector>
#include <string>
#include <functional> 
#include "Juego.h"

#include "EIntro.h"
#include "EMenu.h"
#include "EMenuInGame.h"
#include "ECinematica.h"
#include "EInGame.h"

using namespace std;

Juego* Juego::pinstance = 0;
Juego* Juego::Instance(){
    
    if(pinstance == 0) pinstance = new Juego();

    return pinstance;
}

Juego::Juego(){
    
    _state = 0;
    
}

void Juego::Init(){
    //VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings(
    window = new sf::RenderWindow(sf::VideoMode(1066, 600), "Ventana de juego");
    
    sf::Clock reloj;
    
    std::cout << "Instancia de Juego: " << this  << std::endl;
    std::cout << "Pulsa la tecla 1 para cambiar al estado ECinematica."  << std::endl;
    std::cout << "Pulsa la tecla 2 para cambiar al estado EInGame."  << std::endl;
    std::cout << "Pulsa la tecla 3 para cambiar al estado EMenu."  << std::endl;
    std::cout << "Pulsa la tecla 4 para cambiar al estado EIntro."  << std::endl;
    std::cout << "Pulsa la tecla 5 para cambiar al estado EMenuInGame."  << std::endl;
    std::cout << "Pulsa la tecla 6 para consultar el estado actual."  << std::endl;
    std::cout << "Pulsa la tecla 7 para Destruir ECinematica"  << std::endl;
    std::cout << "Pulsa la tecla 8 para Destruir EMenuInGame"  << std::endl;
    
    //ECinematica::Instance(this)->Handle();
    
    //AUTOINSTANCE ///////////////////////////////////
    /*
    sf::Clock reloj1;
    bool b1 = true;
    bool b2 = true;
    bool b3 = true;
    bool b4 = true;
     */
    ///////////////////////////////////////////////////
        
    while(window->isOpen()){
       
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && reloj.getElapsedTime().asSeconds()>0.2){ECinematica::Instance(this)->Handle(); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && reloj.getElapsedTime().asSeconds()>0.2){ EInGame::Instance(this)->Handle(); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && reloj.getElapsedTime().asSeconds()>0.2){ EMenu::Instance(this)->Handle(); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && reloj.getElapsedTime().asSeconds()>0.2){ EIntro::Instance(this)->Handle(); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && reloj.getElapsedTime().asSeconds()>0.2){ EMenuInGame::Instance(this)->Handle();  reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && reloj.getElapsedTime().asSeconds()>0.2){ std::cout << "ESTADO ACTUAL: "  << this->currentState() << std::endl; reloj.restart(); }
        
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && reloj.getElapsedTime().asSeconds()>0.2){delete ECinematica::Instance(this);reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && reloj.getElapsedTime().asSeconds()>0.2){delete EInGame::Instance(this);reloj.restart(); }
 
        //AUTOINSTANCE //////////////////////////////////
        /*
        if(reloj1.getElapsedTime().asSeconds()>0.5 && b1){
            EInGame::Instance(this)->Handle();
            b1=false;
        }
        if(reloj1.getElapsedTime().asSeconds()>1 && b2){
            
            ECinematica::Instance(this)->Handle();
            b2=false;
        }
          
        if(reloj1.getElapsedTime().asSeconds()>1.7 && b3){
            delete EInGame::Instance(this);
            b3=false;
        }
        
        if(reloj1.getElapsedTime().asSeconds()>2.3 && b4){     
            b1=true;
            b2=true;
            b3=true;
            b4=true;        
            reloj1.restart();     
        }*/
        ///////////////////////////////////////
        if(sf::Joystick::isButtonPressed(1,0)){
             std::cout<<"Mando: A "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,1)){
             std::cout<<"Mando: B "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,2)){
             std::cout<<"Mando: X "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,3)){
             std::cout<<"Mando: Y "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,4)){
             std::cout<<"Mando: L "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,5)){
             std::cout<<"Mando: R "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,6)){
             std::cout<<"Mando: Select "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,7)){
             std::cout<<"Mando: Start "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,8)){
             std::cout<<"Mando: JoyClickL "<<std::endl;
              
        }
        if(sf::Joystick::isButtonPressed(1,9)){
             std::cout<<"Mando: JoyClickR "<<std::endl;
              
        }
        if(sf::Joystick::getAxisPosition(1, sf::Joystick::PovX) ==  100){
            std::cout<<"Mando: UP "<<std::endl;
              
        }
        if(sf::Joystick::getAxisPosition(1, sf::Joystick::PovX) ==  -100){
            std::cout<<"Mando: DOWN "<<std::endl;
              
        }
        if(sf::Joystick::getAxisPosition(1, sf::Joystick::PovY) ==  -100){
            std::cout<<"Mando: LEFT "<<std::endl;
              
        }
        if(sf::Joystick::getAxisPosition(1, sf::Joystick::PovY) ==  100){
            std::cout<<"Mando: RIGHT "<<std::endl;
              
        }
        // std::cout<<"Mando: "<<sf::Joystick::getAxisPosition(1, sf::Joystick::PovY)<<std::endl;
        // std::cout<<"Mando: "<<sf::Joystick::getAxisPosition(1, sf::Joystick::Axis(7))<<std::endl;
       // std::cout<<sf::Joystick::Axis::R<<std::endl;
        //std::cout<<sf::Joystick::<<std::endl;
        //sf::Joystick::
        //switch()
        
        //Bucle de obtención de eventos
        while (window->pollEvent(event)){
            
            switch(event.type){     
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                    
            
               // case sf::Keyboard::Right:
                       
                        
                            
                 //   break;
                    
                 //default:
                    //std::cout << event.key.code << std::endl;
                   // break;
                              
                      
            }
        }
        
        if(_state!=0){ //Con el valor 0, el juego dejará de pintar
           
            Update();
        }
        
    }
    
}

void Juego::Update(){

    _state->Update();
    
}

Escena* Juego::currentState(){
    
    return _state;
   
}

void Juego::setState(Escena* state){
    
    _state = state;
        
}

Juego::~Juego() {
    
   delete EInGame::Instance(this);
   std::cout << "Juego ha sido eliminado."   << std::endl;
    
    
}
