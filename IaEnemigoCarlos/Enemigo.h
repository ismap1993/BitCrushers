/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.h
 * Author: chiri
 *
 * Created on 12 de abril de 2016, 20:25
 */

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "NPC.h"
class Enemigo: public NPC {
public:
    Enemigo();
    Enemigo(float x, float y, int politic,  bool activado, bool valorPatrullaje);
    void update();
    bool getPatrullaje();
    void setPatrullaje(bool valorPatrullaje);
    sf::Sprite getSprite();
    void leerXML();
    void draw(sf::RenderWindow &window);
    void handle(sf::Event event, sf::RenderWindow& window, Mapa *mapa, Camara *camara);
    void disparar();
    bool salto;
    bool rutaCompleta;
    int alturaSuelo;
    sf::Vector2f posicionJugador;
    float velocidadSalto;
    float velocidadMovimiento;
    sf::Vector2f velocidadJugador;
    bool muerto;
    ~Enemigo();
    std::vector<Proyectil*>* proyectiles;//para poder acceder desde otras clases
private:
    bool patrullaje;
    int puntoInicial;
    int politico;
    int direccionPro;
    sf::Sprite sprite;
    bool tieneLLave;
    bool activo;
    
    int** matriz;
    sf::Texture texturaJugador;
    sf::Clock aparicionProyectil;
};

#endif /* ENEMIGO_H */

