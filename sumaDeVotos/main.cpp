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
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: sumaDeVotos");

     // Texto
    sf::Font font;  
    if (!font.loadFromFile("resources/fonts/calibri.ttf"))
        return EXIT_FAILURE;
    
    sf::Font fontpixelated;  
    if (!fontpixelated.loadFromFile("resources/fonts/pixelated.ttf"))
        return EXIT_FAILURE;
    
    sf::Text hudVotos("VOTOS:", fontpixelated, 30);
    hudVotos.setPosition(450,-2);
    hudVotos.setCharacterSize(30);
    hudVotos.setColor(sf::Color::Black);
    
    sf::Text hudVotosValue("0", fontpixelated, 30);
    hudVotosValue.setPosition(565,-2);
    hudVotosValue.setCharacterSize(30);
    hudVotosValue.setColor(sf::Color::Black);
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/pedro.png"))
    {
        std::cerr << "Error cargando la imagen pedro.png";
        exit(0);
    }
    
    //Cargo la imagen donde reside la textura del voto
    sf::Texture texvoto;
    if (!texvoto.loadFromFile("resources/sobres.png"))
    {
        std::cerr << "Error cargando la imagen sobres.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
      
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(46/2,139/2);
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(450, 430);

    //ARRAY DE VOTOS  
    vector<sf::Sprite*>* votos = new vector<sf::Sprite*>(); //DEFINICOIN DEL VECTOR DE PUNTEROS A SPRITE
    
    for(int i=0;i<6;i++){
        
        votos->push_back(new sf::Sprite(texvoto));                   //SE AÑADE &Sprite AL VECTOR
        (*votos)[i]->setTextureRect(sf::IntRect(0*44, 0*50, 44, 50));  //A CADA OBJETO DEL VECTOR SE LE CORRIGE LA TEXTURA
        (*votos)[i]->setOrigin(64/2,32/2);                             //AJUSTE DEL ORIGEN DEL SPRITE
        
    }
 
    //POSICIONAMIENTO DE LOS MUROS
    (*votos)[0]->setPosition(200, 382); 
    (*votos)[1]->setPosition(459, 254);
    (*votos)[2]->setPosition(724, 320); 
    (*votos)[3]->setPosition(849, 384);
    (*votos)[4]->setPosition(957, 287); 
    (*votos)[5]->setPosition(100, 290);
    
    //INICIALIZACION DE LA VARIABLE DE CONTEO DE VOTOS
    int votosValue = 0; 
    
    sf::RectangleShape suelo(sf::Vector2f(1280, 500));
    suelo.setPosition(0,500);
    suelo.setOutlineThickness(1.0f);
    suelo.setFillColor(sf::Color(120,66,0));
    suelo.setOutlineColor(sf::Color::Black);

    while (window.isOpen()){  
        int i=0;
        while(votos!=NULL && i < votos->size()){
            
            //SE COMPRUEBA LA COLISION DEL SPRITE CON TODOS LOS VOTOS PRESENTES
            if(sprite.getGlobalBounds().intersects((*votos)[i]->getGlobalBounds())){ 
              
                delete (*votos)[i];                                     //LIBERA LA MEMORIA RESERVADA A ESE VOTO
                votos->erase(votos->begin() + i);                      //ELIMINA LA POSICION DEL VECTOR DONDE ESTABA EL VOTO
                votosValue++;                                        //AUMENTA EN 1 EL CONTEO DE VOTOS
                
                std::cout << "Voto conseguido.." << std::endl;       
                std::cout << "Votos restates:  " << votos->size() << std::endl;
                break;  
            }
             i++;   //NO HUBO COLISION ENTRE LOS DOS SPRITES COMPARADOS
        }
        if(votos!=NULL)
        if(votos->empty()){
            delete votos;
            votos = NULL;
        }
    
        //std::cout << event.key.code << std::endl;
      hudVotosValue.setString(toString(votosValue)); //PARSEA Y ENVIA LOS VOTOS OBTENIDOS AL HUD
        
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
        
        if(votos!=NULL)for(sf::Sprite* i : *votos)window.draw(*i);        //RECORRE EL VECTOR DE VOTOS
        window.draw(hudVotosValue); //VALOR NUMERICO DE LOS VOTOS
        window.draw(sprite);        //PERSONAJE
        window.draw(hudVotos);      //CARTEL DE VOTOS
        window.draw(suelo);         //SUELO
        
        window.display();
       
        
    }
    
    return 0;
}