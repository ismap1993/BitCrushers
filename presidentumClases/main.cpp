#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

//#define kVel 15
#include "EMenu.h"
#include "Mapa.h"
#include "Camara.h"
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






int main()
{
    //ola k ase
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum!"); 
    /*
    //cuando llamemos a Juego alli habrá que llamar al estado, pasandole estos parametros
    
    //Cargo la clase menu
    EMenu *menu = new EMenu(window.getSize().x, window.getSize().y);
    menu -> run(window);
    */
    
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    Jugador* player = new Jugador(100, 200, 1, true);//le pasamos la posicion X e Y donde se colocará el sprite. 
                                                    //El tercer parametro es que personaje es, solo puede ser hasta el 4. 1.Pablo 2.Albert 3.Rajoy 4.Pedro
                                                    //El cuarto parametro es para saber si está activado el personaje en el array de personajes ya que solo un personaje se puede mostrar.
    player->leerXML();//PREGUNTA    ¿es mejor que la matriz deonde se guardan los datos del psrite sheet sea global de la clase Juego o que cada jugador tenga su propia matriz aunque sea la misma?
    
    //Mapa *mapa = new Mapa();
    //mapa->leerMapa();
    
    //Camara *camara = new Camara(window.getSize().x, window.getSize().y, 15, mapa->fondo, mapa->_width, mapa->_tileWidth);
    //le pasamos el alto y el ancho de la ventana
    //el siguiente parametro es la distancia que se mueve la ventana cada vez que se mueve el personaje
    //le pasamos el fondo para poder consultarlo
    //el mapa->fondo nos ayuda a saber hasta donde debemos mover la camara ya que es el ancho del mapa
    //el mapa->_tileWidth nos indica el ancho del tile
   
<<<<<<< HEAD
  
    sf::Clock clock;
    
    
    
    sf::Vector2f posicionJugador(100, 100);
    sf::Vector2f velocidadJugador(0, 0);
    const float gravedad = 0.5;
    int alturaSuelo = suelo.getPosition().y - 65;
    float velocidadSalto = 11, velocidadMovimiento = 5;
    bool salto = false;
    sf::Clock reloj; //RELOJ PARA CONTROLAR EL BOTON DE CAMBIO DE ESTADO
    
    sprite.setPosition(posicionJugador);
    
    
    //---------PRUEBAS DE CARLOS-----------------
    
    Juego* juego = new Juego();
    std::cout << "Instancia de Juego: " << &juego  << std::endl;
    std::cout << "Pulsa la tecla 1 para cambiar al estado ECinematica."  << std::endl;
    std::cout << "Pulsa la tecla 2 para cambiar al estado EMenuInGame."  << std::endl;
    std::cout << "Pulsa la tecla 3 para cambiar al estado EMenu."  << std::endl;
    std::cout << "Pulsa la tecla 4 para cambiar al estado EIntro."  << std::endl;
    std::cout << "Pulsa la tecla 5 para cambiar al estado EInGame."  << std::endl;
    std::cout << "Pulsa la tecla 6 para consultar el estado actual."  << std::endl;
    
    while (window.isOpen()){  
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && reloj.getElapsedTime().asSeconds()>0.2){ECinematica::Instance(juego); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && reloj.getElapsedTime().asSeconds()>0.2){ EMenuInGame::Instance(juego); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && reloj.getElapsedTime().asSeconds()>0.2){ EMenu::Instance(juego); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && reloj.getElapsedTime().asSeconds()>0.2){ EIntro::Instance(juego); reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && reloj.getElapsedTime().asSeconds()>0.2){ EInGame::Instance(juego);  reloj.restart(); }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && reloj.getElapsedTime().asSeconds()>0.2){ std::cout << "ESTADO ACTUAL: "  << juego->currentState() << std::endl; reloj.restart(); }

        
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            /******MOVIMIENTOS******/
            
            /*
             0. De frente
             1. Ataque derecho
             2. Ataque izquierdo
             3. Mirar derecha
             4. Caminar derecha 1
             5. Caminar derecha 2
             6. Mirar izquierda
             7. Caminar izquierda 1
             8. Caminar izquierda 2
             9. Salto derecho
             10. Salto izquierdo
             11. Proyectil (Si lo hay)
              
             Cada sprite tiene 4 parametros: x y w h
             x= posicion en eje x
             y= posicion en eje y
             w= anchura
             h= altura
             
             Estos parametros son los que se usan para indicar el sprite que
             se quiere emplear dentro del sprite sheet.
             Estan organizados en una matriz 2x2, siendo cada fila un sprite, y
             cada columna uno de los 4 parametros, quedando una matriz de 12x4
              
             Para usar cada movimiento:
             
             * sprite.setTextureRect(sf::IntRect(matriz[FILA][0], matriz[FILA][1], matriz[FILA][2], matriz[FILA][3]));
             
             Cambiar el parametro FILA de la matriz por uno de los numeros del listado de arriba.
             Siempre se usan las 4 primeras columnas, en ese orden.
             
             */
            
            
             
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //std::cout << event.key.code << std::endl;
                    //Verifico si se pulsa alguna tecla de movimiento
                    //std::cout << event.key.code << std::endl;
                    switch(event.key.code) {
                        case sf::Keyboard::Space:
                             
                            //Dependiendo de la direccion hacia donde este mirando, se aplica un sprite u otro
                             if(der==true){
                                 //IMPORTANTE cambiar el centroide a la hora de atacar!
                                 
                                    sprite.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                    sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                                 
                                 
                                 
                             }
                             if(izq==true){
                                 //IMPORTANTE cambiar el centroide a la hora de atacar!
                                 
                                    sprite.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
                                    sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                                 
                                 
                             }
                             

                        break;
                        
                        
                        
                    }
            }
            
        }
        
        
                             

                        
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            velocidadJugador.x = velocidadMovimiento;
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
=======
    while(window.isOpen()){
        
        
        sf::Event event;
        while(window.pollEvent(event)){
            //player->handle(event, window);
>>>>>>> 46bc60a011a73d2d421aba81d3a5685d3c78b415
        }
        
        
        
        
        window.clear(sf::Color::White);
        player->draw(window);
        //mapa->dibuja(window);
        //std::cout<< player->getSprite().getPosition().x <<std::endl;
        //window.draw(player->getSprite());
        
        window.display();
        
    }
    
    
    
    return 0;
    
}

