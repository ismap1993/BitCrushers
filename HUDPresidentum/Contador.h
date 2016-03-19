

#ifndef CONTADOR_H
#define	CONTADOR_H

#include <SFML/Graphics.hpp>
#include "Motor2D.h"
#include "Reloj.h"
#include "State.h"
#include "Sprites.h"
#include <sstream>
#include "Texto.h"
#include "Personaje.h"

class Contador {
public:
    Contador();
   
    void Iniciar();
    void invContador(Reloj* inv);
    void setTemp(int );

private:
    void updateVidas(int );
    void updateReloj();
    int getTemp();
    

   
    int contadores;
    int contador_aux;
    int temp;
    Reloj *reloj;
    Reloj *relojIcono;
    
    bool contando;
      

    Sprites* img_tiempo;
    
    string fuente;
    int tamFuente;
    
    
};

#endif	/* CONTADOR_H */

