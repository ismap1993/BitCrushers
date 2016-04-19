/* 
 * File:   Plataforma.h
 * Author: Aitor
 *
 * Created on 19 de abril de 2016, 17:52
 */

#ifndef PLATAFORMA_H
#define	PLATAFORMA_H
#include <SFML/Graphics.hpp>

class Plataforma {
public:
    Plataforma(int x, int y);
    Plataforma(const Plataforma& orig);
    virtual ~Plataforma();
    
    sf::Sprite spritePlat;
    sf::Texture texPlat;
    void move();
    
private:
    int posx;
    int posy;
    float recorrido;
    int direccion;
    
    
    sf::Clock tiempoRecorrido;
    float tiempo;
    
    

};

#endif	/* PLATAFORMA_H */

