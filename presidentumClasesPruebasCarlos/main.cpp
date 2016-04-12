#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

#define kVel 15

#include <fstream>
#include <cstring>

#include "Juego.h"
#include "Escena.h"

#include "EIntro.h"
#include "EMenu.h"
#include "EMenuInGame.h"
#include "ECinematica.h"
#include "EInGame.h"

using namespace std;

int main(){
    
     
     
    //---------PRUEBAS DE CARLOS-----------------
    
    Juego* juego = new Juego();
    juego->Init();
    
    std::cout<<"Holaa"<<std::endl;
    
    
    return 0;

}

