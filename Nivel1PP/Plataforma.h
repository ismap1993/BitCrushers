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
    Plataforma(int x, int y, int numMapa);
    Plataforma(const Plataforma& orig);
    virtual ~Plataforma();
    
    sf::Sprite spritePlat;
    sf::Texture texPlat;
    void move();
    int direccion;
    
private:
    int posx;
    int posy;
    float recorrido;
    
    
    
    sf::Clock tiempoRecorrido;
    float tiempo;
    
    

};

#endif	/* PLATAFORMA_H */

