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
#include <SFML/Graphics.hpp>
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
 
int main()
{
    
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
   fin.open("resources/fondo.xml"); // abrir el xml que se va a leer
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
    
    
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texfondo;
    if (!texfondo.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritefondo(texfondo);
    
    spritefondo.setOrigin(matriz[2][0]/2,matriz[2][0]/2);
    spritefondo.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
    spritefondo.setPosition(0,0);
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texpresi;
    if (!texpresi.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritepresi(texpresi);
    
    spritepresi.setOrigin(matriz[4][2]/2,matriz[4][3]/2);
    spritepresi.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
    spritepresi.setPosition(500,80);
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture textutorial;
    if (!textutorial.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritetutorial(textutorial);
    
    spritetutorial.setOrigin(matriz[5][2]/2,matriz[5][3]/2);
    spritetutorial.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
    spritetutorial.setPosition(500,80);
    
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texnivel;
    if (!texnivel.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritenivel(texnivel);
    
    spritenivel.setOrigin(matriz[3][2]/2,matriz[3][3]/2);
    spritenivel.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
    spritenivel.setPosition(500,80);
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texenhorabuena;
    if (!texenhorabuena.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spriteenhorabuena(texenhorabuena);
    
    spriteenhorabuena.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
    spriteenhorabuena.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
    spriteenhorabuena.setPosition(500,80);
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texfelicidades;
    if (!texfelicidades.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritefelicidades(texfelicidades);
    
    spritefelicidades.setOrigin(matriz[1][2]/2,matriz[1][3]/2);
    spritefelicidades.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
    spritefelicidades.setPosition(500,80);
    
    
     sf::Font font;  
     if (!font.loadFromFile("fonts/MyriadPro Regular.ttf"))
         return EXIT_FAILURE;
     
     sf::Font fontpixelated;  
     if (!fontpixelated.loadFromFile("fonts/MyriadPro Regular.ttf"))
         return EXIT_FAILURE;
     
     
     sf::Text opciones("Pulsa 1 para ver la introduccion""\n""\n""Pulsa 2 para ver el nivel tutorial""\n""\n" "Pulsa 3 para ver el nivel en el que te encuentras""\n""\n""Pulsa 4 para ver los puntos obtenidos en este nivel""\n""\n""Pulsa 5 para ver los creditos finales", fontpixelated, 50);
     opciones.setPosition(235,150);
     opciones.setCharacterSize(30);
     opciones.setColor(sf::Color::Black);
     
     sf::Text trans1("El pais se encuentra en un momento de gran inestabilidad politica y esta sumido en una profunda crisis economica," 
     "\n""con una gran tasa de paro, muchos casos de corrupcion, etc.""\n""\n""\n"" Tu objetivo es que tu partido llegue a presidir el gobierno." "\n" "Para ello deberas superar los distintos niveles derrotando a tus enemigos y consiguiendo el mayor numero de votos."
     "\n""Ademas, al final de cada nivel deberas enfrentarte a un jefe final y si lo deseas podras pactar con el.""\n""\n""\n""Al derrotar todos los jefes te convertiras en el presidente del pais." "\n" "Apostaras por el bipartidismo "
     "o por las nuevas fuerzas?""\n""EL PAIS TE NECESITA Y SOLO CON TU AYUDA SE PODRA ACABAR CON ESTA LOCURA.", fontpixelated, 50);
     trans1.setPosition(10,200);
     trans1.setCharacterSize(20);
     trans1.setColor(sf::Color::Black);
     
     
     
     sf::Text trans2("Este es un nivel de tutorial, sigue las indicaciones y derrota a tus enemigos", fontpixelated, 50);
     trans2.setPosition(50,200);
     trans2.setCharacterSize(22);
     trans2.setColor(sf::Color::Black);
     
     int n=1;
     
     sf::Text trans3("Te encuentras en el nivel: 2", fontpixelated, 50);
     trans3.setPosition(100,200);
     trans3.setCharacterSize(22);
     trans3.setColor(sf::Color::Black);
     
   
    
     
     sf::Text trans4("Has superado el nivel""\n" "\n""VOTOS CONSEGUIDOS: 28""\n""\n"
     "PACTO: NO REALIZADO""\n""\n""ENEMIGOS DERROTADOS: 3""\n""\n""SIMPATIZANTE LIBERADO: SI""\n"
     "\n""TIEMPO: 2m 30s" , fontpixelated, 50);
     trans4.setPosition(50,200);
     trans4.setCharacterSize(22);
     trans4.setColor(sf::Color::Black);
     
     
     sf::Text trans5("ERES EL NUEVO PRESIDENTE""\n""\n""VOTOS CONSEGUIDOS: 28""\n""\n""PACTOS REALIZADOS:3"
     "\n""\n""ENEMIGOS DERROTADOS: 15""\n""\n""SIMPATIZANTES LIBERADOS:4""\n""\n""TIEMPO: 3m 35s""\n""\n""Llegan nuevos tiempo para el pais,""\n""CIUDADANOS ha llegado al poder y se presagian grandes cambios en la sociedad.""\n""Se respiran nuevos aires.", fontpixelated, 50);
     trans5.setPosition(50,180);
     trans5.setCharacterSize(22);
     trans5.setColor(sf::Color::Black);
 
   
    int i=0;
   
   
   
   
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum");
    
   
       
    

    //Bucle del juego
    while (window.isOpen())
    { 
         
       
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
                        
                        //Mapeo del cursor.
                       
                        case sf::Keyboard::Num1:
                            i=1;
                            break;
                            
                        case sf::Keyboard::Num2:
                            i=2;
                            break;
                        
                        case sf::Keyboard::Num3:
                            i=3;
                           
                            break;
                        
                   
                            
                        case sf::Keyboard::Num4:
                            i=4;
                            break;
                        
                           case sf::Keyboard::Num5:
                            i=5;
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
        
        window.draw(spritefondo);
        if(i==0)window.draw(opciones);
        if(i==1){ window.draw(trans1); 
        window.draw(spritepresi);}
        if(i==2){ window.draw(trans2);
        window.draw(spritetutorial);} ;
        
        if(i==3){ window.draw(trans3);
        window.draw(spritenivel);}
        if(i==4) { window.draw(trans4);
        window.draw(spriteenhorabuena);}
        if(i==5) { window.draw(trans5);
        window.draw(spritefelicidades);}
       

        
        window.display();
    }

    
    return 0;
     
}

