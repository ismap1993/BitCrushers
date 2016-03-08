#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
using namespace std;

#define kVel 15


string toString(int integer){
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}
 

int main()
{
    ////////////////////////////////////////////
        
    int numero = 2;
    int* puntero_a_numero = &numero;
    
    int** puntero_segundo_nivel = &puntero_a_numero;
    
    
    std::cout<< "> puntero_a_numero: " << puntero_a_numero << std::endl;
    std::cout<< "> &puntero_a_numero: " << &puntero_a_numero << std::endl;
    std::cout<< "> *puntero_a_numero: " << *puntero_a_numero << std::endl;
    std::cout<< "> &puntero_a_numero: " << &puntero_a_numero << std::endl;
    std::cout<< "> *puntero_segundo_nivel: " << *puntero_segundo_nivel << std::endl;
    std::cout<< "> numero: " << numero << std::endl;
    
    
    /////////////////////////////////////////////
    
    std::cout<<std::endl;
    std::cout<< "Entregable: sumaDeVotos (Carlos)" << std::endl;

    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1280, 600), "Entregable: sumaDeVotos");

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
    if (!tex.loadFromFile("resources/caracol.png"))
    {
        std::cerr << "Error cargando la imagen caracol.png";
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
    sf::Sprite voto(texvoto);
      
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(64/2,32/2);
    voto.setOrigin(64/2,32/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(300, 482);

    
    //ARRAY DE VOTOS  
    vector<sf::Sprite*> votos; //DEFINICOIN DEL VECTOR DE PUNTEROS A SPRITE
    
    for(int i=0;i<6;i++){
        //voto.setTextureRect(sf::IntRect(0*44, 0*50, 44, 50));
        
        votos.push_back(new sf::Sprite(texvoto)); //SE AÑADE &Sprite AL VECTOR
        votos[i]->setTextureRect(sf::IntRect(0*44, 0*50, 44, 50));
        
    }
 
    //POSICIONAMIENTO DE LOS MUROS
    votos[0]->setPosition(200, 382); 
    votos[1]->setPosition(459, 254);
    votos[2]->setPosition(724, 320); 
    votos[3]->setPosition(849, 384);
    votos[4]->setPosition(957, 287); 
    votos[5]->setPosition(1187, 290);
    
    int votosValue = 0;
    
    sf::RectangleShape suelo(sf::Vector2f(1280, 500));
    suelo.setPosition(0,500);
    suelo.setOutlineThickness(1.0f);
    suelo.setFillColor(sf::Color(120,66,0));
    suelo.setOutlineColor(sf::Color::Black);
  
    
    
    while (window.isOpen()){  
        
        int i=0;
        while(i < votos.size()){
            
            if(sprite.getGlobalBounds().intersects(votos[i]->getGlobalBounds())){
              
                delete votos[i];
                votos.erase(votos.begin() + i);
                votosValue++;
                std::cout << "Voto conseguido.." << std::endl;
                break;
                
            }
             std::cout << "size: " << votos.size() << std::endl;
             i++;
            
        }
        
        

      hudVotosValue.setString(toString(votosValue));
        //std::cout << std::size(votos_old) << std::endl;
        

        
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
                            sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
                            //Escala por defecto
                            sprite.setScale(1,-1);
                            sprite.setRotation(180);
                            sprite.move(kVel,0);
                            
                        break;

                        case sf::Keyboard::Left:
                            sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
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
        
        window.clear(sf::Color(sf::Color::White));
        
        for(sf::Sprite* n : votos)window.draw(*n); //VOTOS
        window.draw(hudVotosValue);
        window.draw(sprite);
        window.draw(hudVotos);
        window.draw(suelo);
        
        window.display();
       
        
    }
    
    return 0;
}