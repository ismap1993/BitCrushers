/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

//#define kVel 15

#include "Jugador.h"
#include <fstream>
#include <cstring>

#include "Juego.h"
#include "Escena.h"

#include "EIntro.h"
#include "EMenu.h"
#include "EMenuInGame.h"
#include "ECinematica.h"
#include "EInGame.h"

#include "Enemigo.h"
#include "NPC.h"

static int carlos(){
    
    
    //---------PRUEBAS DE CARLOS-----------------
    
    //Juego* juego = new Juego();
    //juego->Init();
    
    std::cout<<"Holaa"<<std::endl;
    
    Enemigo* pruebaEnemy = new Enemigo();
    std::cout<<"pruebaEnemy: "<< &pruebaEnemy << std::endl;
    
    
    
    return 0;
}