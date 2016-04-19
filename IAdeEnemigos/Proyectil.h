/* 
 * File:   Proyectil.h
 * Author: Aitor
 *
 * Created on 5 de abril de 2016, 10:38
 */

#ifndef PROYECTIL_H
#define	PROYECTIL_H
#include <SFML/Graphics.hpp>

class Proyectil {
public:
    Proyectil();
    Proyectil(int direccion, int pospersonaje, int **mat, int politic); 
    Proyectil(const Proyectil& orig);
    virtual ~Proyectil();
    
    bool destruir();
    void leerSprite();
    sf::Sprite getSprite();
    void dibuja(sf::RenderWindow &window);
    Proyectil crearPro();
 

private:
    int posx;
    int posy;
    int dir; //0 izq, 1 der
    int **matriz; //Para leer spritesheet
    int disRecorrida; //Destruir el proyectil al haber recorrido 450 de distancia
    sf::Sprite spritePro;
    sf::Texture texPro;
    
    
    //Tiempo en el que se van desplazando los proyectiles
    sf::Clock proyectilClock;
    float disparoTime;
    float disparoAparicion;
    
};

#endif	/* PROYECTIL_H */

