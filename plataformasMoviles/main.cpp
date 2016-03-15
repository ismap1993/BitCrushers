#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
using namespace std;

#define kVel 15

/* Entregable: sumaDeVotos
 * Durante la partida se comprobará que los votos aparecen, 
 * se suman al contador de votos y desaparecen de la pantalla una vez cogidos.
 */

string toString(int integer){
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}
 
int main()
{
 
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: plataformasMoviles");

     // Texto
    sf::Font font;  
    if (!font.loadFromFile("resources/fonts/calibri.ttf"))
        return EXIT_FAILURE;
    
    sf::Font fontpixelated;  
    if (!fontpixelated.loadFromFile("resources/fonts/pixelated.ttf"))
        return EXIT_FAILURE;
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/pedro.png"))
    {
        std::cerr << "Error cargando la imagen pedro.png";
        exit(0);
    }
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex_asc;
    if (!tex_asc.loadFromFile("resources/ascensor.png"))
    {
        std::cerr << "Error cargando la imagen ascensor.png";
        exit(0);
    }
    
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    sf::Sprite ascensor1(tex_asc);
    sf::Sprite ascensor2(tex_asc);
      
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(46/2,139);
    ascensor1.setOrigin(tex_asc.getSize().x/2, tex_asc.getSize().y/2);
    ascensor2.setOrigin(tex_asc.getSize().x/2, tex_asc.getSize().y/2);
 
    //Cojo el sprite que me interesa por defecto del sheet
    //sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(25, 500);        //SPRITE DE PEDRO 
    ascensor1.setPosition(200,450);     //ASCENSOR VERTICAL
    ascensor2.setPosition(420,200);     //ASCENSOR HORIZONTAL
    
    //SUELO1
    sf::RectangleShape suelo1(sf::Vector2f(100, 500));
    suelo1.setPosition(0,500);
    suelo1.setFillColor(sf::Color(120,66,0));
    suelo1.setOutlineColor(sf::Color::Black);

    //SUELO2
    sf::RectangleShape suelo2(sf::Vector2f(200, 500));
    suelo2.setPosition(300,500);
    suelo2.setFillColor(sf::Color(120,66,0));
    suelo2.setOutlineColor(sf::Color::Black);
    
    //SUELO3
    sf::RectangleShape suelo3(sf::Vector2f(150, 500));
    suelo3.setPosition(950,500);
    suelo3.setFillColor(sf::Color(120,66,0));
    suelo3.setOutlineColor(sf::Color::Black);

    //BREAKABLE GROUND
    sf::RectangleShape rompible1(sf::Vector2f(100, 30));
    rompible1.setPosition(500,500);
    rompible1.setFillColor(sf::Color::Red);
  
    
    while (window.isOpen()){  
        
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {      
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //std::cout << event.key.code << std::endl;
                    //Verifico si se pulsa alguna tecla de movimiento
                           
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            //Escala por defecto
                            sprite.setScale(1,-1);
                            sprite.setRotation(180);
                            sprite.move(kVel,0);
                            
                        break;

                        case sf::Keyboard::Left:
                            //Reflejo vertical
                            sprite.setScale(1,1);
                            sprite.setRotation(0);
                            sprite.move(-kVel,0); 
           
                        break;
                        
                        case sf::Keyboard::Up:
           
                            
                            sprite.move(0,-kVel); 
                            
                        break;
                        
                        case sf::Keyboard::Down:
                            
                            sprite.move(0,kVel); 
                            
                        break;
                        
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }
            }
        }    
        
        window.clear(sf::Color(sf::Color::White)); //FONDO EN BLANCO

        window.draw(sprite);         //PERSONAJE
        window.draw(suelo1);         //SUELO 1
        window.draw(suelo2);         //SUELO 2
        window.draw(suelo3);         //SUELO 3
        window.draw(rompible1);      //ROMPIBLE 1
        window.draw(ascensor1);      //ASCENSOR 1
        window.draw(ascensor2);      //ASCENSOR 2
        window.display();
       
        
    }
    
    return 0;
}