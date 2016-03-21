
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include <SFML/System/Clock.hpp>

 #include <vector>
 #include <string> 
 #include <fstream>
 #include <cstring>


using namespace std;
using namespace sf;


 const int MAX_CHARS_PER_LINE = 512;
 const int MAX_TOKENS_PER_LINE = 20;
 const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")
 
 
 //funcion to_string
 template <typename T>
std::string to_string(T countdown)
{
	std::ostringstream convert ;
	convert << countdown ;
	return convert.str() ;
}

 int main()
{
    
    
     sf::Font font;  
     if (!font.loadFromFile("fonts/MyriadPro Regular.ttf"))
         return EXIT_FAILURE;
     
     sf::Font fontpixelated;  
     if (!fontpixelated.loadFromFile("fonts/MyriadPro Regular.ttf"))
         return EXIT_FAILURE;
     
     sf::Text hudVotos("VOTOS:", fontpixelated, 50);
     hudVotos.setPosition(200,50);
     hudVotos.setCharacterSize(20);
     hudVotos.setColor(sf::Color::White);
     
     sf::Text hudVotosValue("0", fontpixelated, 50);
     hudVotosValue.setPosition(265,50);
     hudVotosValue.setCharacterSize(20);
     hudVotosValue.setColor(sf::Color::White);
    
     
    

    //temporizador
    sf::Clock clock;
    int countdown = 31;

    //convert countdown to a string
    std::string countdownString;
   /* std::ostringstream convert;
    convert << countdown;
    countdownString = convert.str();*/

 
     sf::Text contador("TIEMPO:", fontpixelated, 50);
     contador.setPosition(470,50);
     contador.setCharacterSize(20);
     contador.setColor(sf::Color::White);
    
     sf::Text contadorValue;
     contadorValue.setFont(font);
     contadorValue.setString(countdownString);
     contadorValue.setPosition(540,50);
     contadorValue.setCharacterSize(20);
     contadorValue.setColor(sf::Color::White);
     
 

    
     /*MATRIZ BIDIMENSIONAL para almacenar los 4 parametros de cada sprite*/
     int **matriz;
     matriz= new int*[99];
     for(int i = 0; i < 99; i++){
         matriz[i] = new int[4];
     }
 
     int posX=0;
     int linea=1;
     
     
    /****LECTURA DEL XML PARA EL SPRITE!!****/
     
 
   ifstream fin;
   fin.open("resources/spriteaitor.xml"); // abrir el xml que se va a leer
   if (!fin.good()) 
     return 1; // si el fichero no existe...
   
   // comenzamos a leer cada una de las lineas
   while (!fin.eof())
   {
     // esto es para controlar el tamanyo maximo de cada linea
     char buf[MAX_CHARS_PER_LINE];
     fin.getline(buf, MAX_CHARS_PER_LINE);
     int n = 0;
     
     // cada linea va almacenada en un vector
     const char* token[MAX_TOKENS_PER_LINE] = {};
     
     // parseamos las lineas, separando cada elemento de la linea por comillas (")
     token[0] = strtok(buf, DELIMITER);
     
     if (token[0])
     {
       for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
       {
         token[n] = strtok(0, DELIMITER);
         
         //SOLO nos interesa a partir de la linea 22 del XML
         if(linea>22){
             //Vamos almacenando en la matriz segun el parametro que nos interesa en el orden correcto
            if(n==3){ //El tercer elemento corresponde a x
                matriz[posX][0]=atoi(token[n]);
             }
            
            if(n==5){ //El quinto elemento corresponde a y
                matriz[posX][1]=atoi(token[n]);
            }
            
            if(n==7){ //El septimo elemento corresponde a w
                matriz[posX][2]=atoi(token[n]);
            }
            
            if(n==9){ //El noveno elemento corresponde a h
                matriz[posX][3]=atoi(token[n]);
                posX++;
            }
         }
 
         if (!token[n]) break; // si no hay mas, se termina el bucle
       }
     }
 
     // imprime los 4 parametros(x,y,w,h) obtenidos de cada linea en la consola
 //    for (int i = 0; i < n; i++){// n = #of tokens
 //        if(linea>22){
 //            if(i==3 || i==5 || i==7 || i==9){
 //                cout << "Token[" << i << "] = " << token[i] << endl;
 //                
 //            }  
 //        }    
 //    } 
    
     linea++;
   }
   
   //Esto es para imprimir la matriz obtenida en consola
     if(linea>22){
         for(int i=0; i<11;i++){
             for (int j=0;j<4;j++){
                 cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
             }
             cout << endl;
         }
     }
   
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum");
    
    
//    std::vector<sf::Sprite> sprites;

  //  unsigned int currentSprite{ 0 };
    
    

    //Cargo la imagen donde reside la textura del sprite
    sf::Texture texalbert;
    if (!texalbert.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritealbert(texalbert);
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texpedro;
    if (!texpedro.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritepedro(texpedro);
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texmariano;
    if (!texmariano.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritemariano(texmariano);
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texpablo;
    if (!texpablo.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritepablo(texpablo);
    
     
    sf::Texture texvidaalbert;
    if (!texvidaalbert.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritevidaalbert(texvidaalbert);
    
     sf::Texture texvidaalbert2;
    if (!texvidaalbert2.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritevidaalbert2(texvidaalbert2);
    

    
    
    sf::Texture texvidapedro;
    if (!texvidapedro.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritevidapedro(texvidapedro);
     
    
    sf::Texture texvidamariano;
    if (!texvidamariano.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritevidamariano(texvidamariano);
    
     sf::Texture texvidapablo;
    if (!texvidapablo.loadFromFile("resources/spriteaitor.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritevidapablo(texvidapablo);
    
 
    
    
    //Le pongo el centroide donde corresponde
    spritealbert.setOrigin(matriz[19][2]/2,matriz[19][3]/2);
    spritepedro.setOrigin(matriz[17][2]/2,matriz[17][3]/2);
    spritemariano.setOrigin(matriz[18][2]/2,matriz[18][3]/2);
    spritepablo.setOrigin(matriz[16][2]/2,matriz[16][3]/2);
    spritevidaalbert.setOrigin(matriz[15][2]/2,matriz[15][3]/2);
    spritevidaalbert2.setOrigin(matriz[14][2]/2,matriz[14][3]/2);
    
    spritevidapedro.setOrigin(matriz[11][2]/2,matriz[11][3]/2);
    spritevidamariano.setOrigin(matriz[13][2]/2,matriz[13][3]/2);
    spritevidapablo.setOrigin(matriz[10][2]/2,matriz[10][3]/2);
    
    
    /*
     1. carapablo
     2. carapedro
     3. caramariano
     4. caraalbert
     */
    //Cojo el sprite que me interesa por defecto del sheet
    spritealbert.setTextureRect(sf::IntRect(matriz[19][0], matriz[19][1], matriz[19][2], matriz[19][3]));
    spritepedro.setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
    spritemariano.setTextureRect(sf::IntRect(matriz[18][0], matriz[18][1], matriz[18][2], matriz[18][3]));
    spritepablo.setTextureRect(sf::IntRect(matriz[16][0], matriz[16][1], matriz[16][2], matriz[16][3]));
    spritevidaalbert.setTextureRect(sf::IntRect(matriz[15][0], matriz[15][1], matriz[15][2], matriz[15][3]));
    spritevidaalbert2.setTextureRect(sf::IntRect(matriz[14][0], matriz[14][1], matriz[14][2], matriz[14][3]));
    
    spritevidapedro.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
    spritevidamariano.setTextureRect(sf::IntRect(matriz[13][0], matriz[13][1], matriz[13][2], matriz[13][3]));
    spritevidapablo.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));


    
    // Lo dispongo en el centro de la pantalla
    spritealbert.setPosition(850, 65);
    spritepedro.setPosition(50, 40);
    spritemariano.setPosition(100, 40);
    spritepablo.setPosition(150, 40);
    spritevidaalbert.setPosition(950, 65);
     spritevidaalbert2.setPosition(950, 65);
   
    spritevidapedro.setPosition(50, 70);
    spritevidamariano.setPosition(100, 70);
    spritevidapablo.setPosition(150, 70);
     
    spritealbert.setScale(1,1);
    spritepedro.setScale(0.5,0.5);
    spritemariano.setScale(0.5,0.5);
    spritepablo.setScale(0.5,0.5);
    spritevidaalbert.setScale(1,1);
    spritevidaalbert2.setScale(1,1);
 
    spritevidapedro.setScale(0.3,0.3);
    spritevidamariano.setScale(0.3,0.3);
    spritevidapablo.setScale(0.3,0.3);
    
     
       
    int i=0;

    //Bucle del juego
    while (window.isOpen())
    { 
        
         
        
        //TIMER - 30 SECONDS
                int timer = clock.getElapsedTime().asSeconds();
               

                if (timer > 0 && countdown !=0) {
                    countdown--;
                  
                    contadorValue.setString( std::to_string(countdown));
                    clock.restart();
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
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //para cambiar sprite vida principal
                         case sf::Keyboard::Right:
                            i=1;
                            break;
                         
                         case sf::Keyboard::Left:
                            i=0;
                         
                            break;
                        
                         case sf::Keyboard::Num1:
                            i=3;
                            spritealbert.setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
                            spritepedro.setScale(0.5,0.5);
                            //Escala por defecto
                            
                            spritevidaalbert.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
                            spritevidapedro.setScale(0.3,0.3);
                            
                            spritevidapedro.setTextureRect(sf::IntRect(matriz[15][0], matriz[15][1], matriz[15][2], matriz[15][3]));
                            spritevidaalbert.setScale(1,1);
                            
                            
                           
                            spritepedro.setTextureRect(sf::IntRect(matriz[19][0], matriz[19][1], matriz[19][2], matriz[19][3]));
                            spritealbert.setScale(1,1);
                           
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

                //Se pulsó una tecla, imprimo su codigo
               

            }
            
        }

        window.clear();
        
        window.draw(spritepablo);
         window.draw(spritepedro);
          window.draw(spritemariano);
           window.draw(spritealbert);
           
           window.draw(spritevidapablo);
         window.draw(spritevidapedro);
          window.draw(spritevidamariano);
           if(i==0) window.draw(spritevidaalbert);
           if(i==1) window.draw(spritevidaalbert2);
          if(i==3){ window.draw(spritepedro);
          window.draw(spritealbert);
          window.draw(spritevidaalbert);
          window.draw(spritevidapedro);}
        window.draw(hudVotosValue); //VALOR NUMERICO DE LOS VOTOS
        window.draw(hudVotos);      //CARTEL DE VOTOS
        window.draw(contadorValue); //VALOR NUMERICO De tiempo
        window.draw(contador);      //CARTEL DE contador

        
        window.display();
    }

    
    return 0;
     
}


