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
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex_rompible;
    if (!tex_rompible.loadFromFile("resources/rompible.png"))
    {
        std::cerr << "Error cargando la imagen plataformasmoviles.png";
        exit(0);
    }
    
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    sf::Sprite plataforma1(tex_asc);
    sf::Sprite plataforma2(tex_asc);

    //Le pongo el centroide donde corresponde
    sprite.setOrigin(46/2,139);
    plataforma1.setOrigin(tex_asc.getSize().x/2, tex_asc.getSize().y/2);
    plataforma2.setOrigin(tex_asc.getSize().x/2, tex_asc.getSize().y/2);
 
    //Cojo el sprite que me interesa por defecto del sheet
    //sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(25, 500);        //SPRITE DE PEDRO 
    plataforma1.setPosition(200,400);     //ASCENSOR VERTICAL
    plataforma2.setPosition(420,175);     //ASCENSOR HORIZONTAL
    
    //////////////////////////////
    //ARRAY DE SUELOS ROMPIBLES
    vector<sf::Sprite*>* rompibles = new vector<sf::Sprite*>(); //DEFINICOIN DEL VECTOR DE PUNTEROS A SPRITE
    
    for(int i=0;i<4;i++)rompibles->push_back(new sf::Sprite(tex_rompible));   //SE AÑADE EL LADRILLO AL ARRAY            
 
    //POSICIONAMIENTO DE LOS LADRILLOS
    (*rompibles)[0]->setPosition(500,500);
    (*rompibles)[1]->setPosition(600,500);
    (*rompibles)[2]->setPosition(700,500);
    (*rompibles)[3]->setPosition(800,500);

    ////////////////////////////////////////////////
    
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
    sf::RectangleShape suelo3(sf::Vector2f(200, 500));
    suelo3.setPosition(900,500);
    suelo3.setFillColor(sf::Color(120,66,0));
    suelo3.setOutlineColor(sf::Color::Black);

    //ROMPIBLES*/

    sf::Clock timer;
    int velocity = 10;
    bool plataforma1_state = false;
    bool plataforma2_state = false;
    int oldpos_y=0;
    while (window.isOpen()){  
        
        //CONTORLADOR DE PLALTAFORMA 1                          //CONTROLAN LOS RECORRIDOS DE LAS PLATAFORMAS
            if(!plataforma1_state){
                plataforma1.move(0,(timer.getElapsedTime().asMilliseconds()%2*0.02)*velocity);
                if(plataforma1.getPosition().y < 420) plataforma1_state = false;
                    else plataforma1_state = true;

            }
            
            if(plataforma1_state){
                plataforma1.move(0,(timer.getElapsedTime().asMilliseconds()%2*-0.02)*velocity);
                if(plataforma1.getPosition().y > 200) plataforma1_state = true;
                    else plataforma1_state = false;
                 
            }
        
           
        //CONTORLADOR DE PLALTAFORMA 2
            if(!plataforma2_state){
                plataforma2.move((timer.getElapsedTime().asMilliseconds()%2*0.02)*velocity,0);
                if(plataforma2.getPosition().x < 800) plataforma2_state = false;
                else plataforma2_state = true;
                    
            }    
            if(plataforma2_state){
                plataforma2.move((timer.getElapsedTime().asMilliseconds()%2*-0.02)*velocity,0);
                if(plataforma2.getPosition().x > 400) plataforma2_state = true;
                else plataforma2_state = false;

            }
           
         int i=0;
         while(rompibles!=NULL && i < rompibles->size()){
           
            //SE COMPRUEBA LA COLISION DEL SPRITE CON TODOS LOS VOTOS PRESENTES
            if(sprite.getGlobalBounds().intersects((*rompibles)[i]->getGlobalBounds())){ 
               
                if(oldpos_y==0)oldpos_y = (*rompibles)[i]->getPosition().y;  //NOS QUEDAMOS CON LA POSICION INICIAL PARA CALCULAR EL RECORRIDO
                if((*rompibles)[i]->getPosition().y < oldpos_y+30){ //CUANDO EL BLOQUE SE HAYA DESPLAZADO UN RECORRIDO DADO, SE DESTRUYE
                       
                    (*rompibles)[i]->move(0,0.2); //EL BLOQUE SE VA DESPLAZANDO
                    break;
                }
                else{
                    delete (*rompibles)[i];                                     //LIBERA LA MEMORIA RESERVADA A ESE BLOQUE
                    rompibles->erase(rompibles->begin() + i);                      //ELIMINA LA POSICION DEL VECTOR DONDE ESTABA EL BLOQUE
                    break;  
                }
            }
             i++;   //NO HUBO COLISION ENTRE LOS DOS SPRITES COMPARADOS
        }
        if(rompibles!=NULL)         //DESTRUCCIÓN DEL OBJETO rompibles
        if(rompibles->empty()){
            delete rompibles;
            rompibles = NULL;
        }
        
        
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
        window.draw(plataforma1);      //ASCENSOR 1
        window.draw(plataforma2);      //ASCENSOR 2
        if(rompibles!=NULL)for(sf::Sprite* i : *rompibles)window.draw(*i);        //RECORRE EL VECTOR DE VOTOS
        
        window.display();
       
        
    }
    
    return 0;
}