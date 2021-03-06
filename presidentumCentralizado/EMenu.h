/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMenu.h
 * Author: chiri
 *
 * Created on 5 de abril de 2016, 19:41
 */

#ifndef EMENU_H
#define EMENU_H

#define MAX_NUMBER_OF_ITEMS 6

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string> 

#include "Juego.h"

class EMenu: public Escena {
public:
    
    void Handle();
    void Init();
    void Update();

    Juego* getContext();
    static EMenu* Instance(Juego* context);
    
    void Render();
    void draw(sf::RenderWindow &window, std::vector<sf::Text*> menu);
    void moveUp(std::vector<sf::Text*> menu, int &iterator);
    void moveDown(std::vector<sf::Text*> menu, int &iterator);
   
    int run(sf::RenderWindow &window);
    void nuevaPartida(sf::RenderWindow &window);
    void cargarPartida(sf::RenderWindow &window);
    void controles(sf::RenderWindow &window);
    void opciones(sf::RenderWindow &window);
    void creditos(sf::RenderWindow &window);
    //int pulsarTecla(sf::RenderWindow &window, sf::Event event);
    void submenu(sf::RenderWindow &window);
    void mostrarOpcionesInGame(sf::RenderWindow &window);
    void guardar(sf::RenderWindow &window);
    
     int GetPressedItem(){
        return selectedItemIndex;
    };
    int GetPressedItemInPausa(){
        return selectedItemIndexInPausa;
    };
    int GetPressedItemGuardar(){
        return selectedItemIndexGuardar;
    };
    int GetPressedItemSobreescribir(){
        return selectedItemIndexSobreescribir;
    };
    int GetPressedItemOpciones(){
        return selectedItemIndexOpciones;
    };
    void teclas(sf::RenderWindow &window, sf::Event event);
    
    void sobreescribir(sf::RenderWindow &window);
    void sobreescritocorrectamente(sf::RenderWindow &window);
    void reinicio();
    
    ~EMenu();
    
    
protected:
    EMenu(Juego* context);
    EMenu(const EMenu &);
    EMenu &operator = (const EMenu &);

private:
    
    bool salida;
    
    int opcionMenuppal;
    int opcionMenuInGame;
    int selectedItemIndex;
    int selectedItemIndexInPausa;
    int selectedItemIndexGuardar;
    int selectedItemIndexSobreescribir;
    int selectedItemIndexOpciones;
    
    sf::Font fuente;
    
    std::vector<sf::Text*> menu;
    std::vector<sf::Text*> menuInGame;
    std::vector<sf::Text*> guardarsino;
    std::vector<sf::Text*> sobreescribirsino;
    std::vector<sf::Text*> opcionesMenu;

    bool mostrarMenuppal;
    bool enPartida;
    bool enCargar;
    bool enOpciones;
    bool enCreditos;
    bool enControles;
    bool enPausa;
    bool guardando;
    bool sobreescrito;
    bool enSonido;
    bool enMusica;
    bool pausaopciones;
    
    sf::Sprite *background;
    
    sf::Texture texturaBackground;
    
    sf::RectangleShape *FondomenuInPausa;
    sf::RectangleShape *barrasonido;
    sf::RectangleShape *barramusica;
    sf::RectangleShape *tiradorsonido;
    sf::RectangleShape *tiradormusica;
    sf::RectangleShape *fondo;
    sf::Color *transparente;
    
    sf::String interrogacion;
    sf::Text *desea;
    sf::Text *sobreescribirText;
    sf::Text *sobreescribir2Text;
    sf::Text *sobrescrita;
    sf::Text *izquierda ;
    sf::Text *derecha;
    sf::Text *saltar; 
    sf::Text *golpear; 
    sf::Text *personaje1; 
    sf::Text *personaje2;
    sf::Text *personaje3;
    sf::Text *textocreditos;
    sf::Text *textoCargarPartida;
    sf::Text *valorsonido;
    sf::Text *valormusica;
    
    
    
    static EMenu* pinstance;
    Juego* _context;
    
};

#endif /* EMENU_H */