#include <iostream>
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

/*
 * Pantalla que muestra el menú principal del juego y el menú in-game. El menú 
 * principal definiremos las opciones de nueva partida, cargar partida, las 
 * opciones de volumen, los créditos y salir. El menú In-game cuando salga durante 
 * la partida saldrá un menú con las opciones de continuar, guardar partida y las 
 * opciones del volumen.
 */

int main(){
    
    //Creamos la ventana de juego con unas dimensiones de 1280x600
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Hacer Menu!");
    
  
    Menu menu(window.getSize().x, window.getSize().y);
    
    menu.run(window);
    
    return 0;
}