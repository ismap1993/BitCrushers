

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include <conio.h>
#include <string.h>
 
using namespace std;
using namespace std;
using namespace sf;
/*
 * 
 */
 
 
 
#define kUpdateTimePS 1000/15
#define kVelTexto 10
 


const int MAX_CHARS_PER_LINE = 512;
 const int MAX_TOKENS_PER_LINE = 20;
 const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")
 
int main() {
    
    
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
    spritefondo.setScale(2,1);
   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
     
    /***********************************************
     *                                             * 
     *             Variables Game                  *
     *                                             *
     ***********************************************/
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texpresi;
    if (!texpresi.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritepresi(texpresi);
    
    spritepresi.setOrigin(matriz[5][2]/2,matriz[5][3]/2);
    spritepresi.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
    spritepresi.setPosition(500,80);
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture textutorial;
    if (!textutorial.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritetutorial(textutorial);
    
    spritetutorial.setOrigin(matriz[6][2]/2,matriz[6][3]/2);
    spritetutorial.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
    spritetutorial.setPosition(500,80);
    
    
    
     //Cargo la imagen donde reside la textura del sprite
    sf::Texture texnivel;
    if (!texnivel.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.jpg";
        exit(0);
    }
    
    sf::Sprite spritenivel(texnivel);
    
    spritenivel.setOrigin(matriz[4][2]/2,matriz[4][3]/2);
    spritenivel.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
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
    
    
    
    
    
      //Cargo la imagen donde reside la textura del sprite
    sf::Texture texcrush;
    if (!texcrush.loadFromFile("resources/fondo.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
    
    sf::Sprite spritecrush(texcrush);
    spritecrush.setOrigin(matriz[3][2]/2,matriz[3][3]/2);
    spritecrush.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
    spritecrush.setPosition(550,0);
    spritecrush.setScale(0.5,0.5);
    
    
    
    stringstream charString;
    sf::Time timeUpdateGame;
    sf::Clock relog;
    int numLetras = 7;
    int tamActivar = 0;
    int veces = 0;
    sf::Font font;
    if(!font.loadFromFile("resources/Fonts/MyriadPro Regular.ttf")){
        cerr << "Error al cargar fuente";
    }
    sf::Text *textos = new sf::Text[numLetras];
    charString.str("Pulsa 2 para ver la introduccion""\n""\n""Pulsa 3 para ver el nivel tutorial""\n""\n" "Pulsa 4 para ver el nivel en el que te encuentras""\n""\n""Pulsa 5 para ver los puntos obtenidos en este nivel""\n""\n""Pulsa 6 para ver los creditos finales");
    textos[0].setString(charString.str());
    charString.str("El pais se encuentra en un momento de gran inestabilidad politica y esta sumido en una profunda""\n" "crisis economica, "
    "con una gran tasa de paro, muchos casos de corrupcion, etc.""\n""\n""\n""Tu objetivo es que tu partido llegue a presidir el gobierno." "\n""Para ello deberas superar los distintos niveles""\n""derrotando a tus enemigos y consiguiendo el mayor numero de votos."
     "\n""Ademas, al final de cada nivel deberas enfrentarte a un jefe final y, si lo deseas, podras pactar con el.""\n""\n""\n""Al derrotar todos los jefes te convertiras en el presidente del pais." "\n" "Apostaras por el bipartidismo "
     "o por las nuevas fuerzas?""\n""\n""EL PAIS TE NECESITA Y SOLO CON TU AYUDA SE PODRA ACABAR CON ESTA LOCURA.");
    textos[1].setString(charString.str());
    charString.str("Este es un nivel de tutorial, sigue las indicaciones y derrota a tus enemigos");
    textos[2].setString(charString.str());
    charString.str("Te encuentras en el nivel: 2");
    textos[3].setString(charString.str());
    charString.str("Has superado el nivel""\n" "\n""VOTOS CONSEGUIDOS: 28""\n""\n"
     "PACTO: NO REALIZADO""\n""\n""ENEMIGOS DERROTADOS: 3""\n""\n""SIMPATIZANTE LIBERADO: SI""\n"
     "\n""TIEMPO: 2m 30s");
    textos[4].setString(charString.str());
    charString.str("ERES EL NUEVO PRESIDENTE""\n""\n""VOTOS CONSEGUIDOS: 28""\n""\n""PACTOS REALIZADOS: 3"
     "\n""\n""ENEMIGOS DERROTADOS: 15""\n""\n""SIMPATIZANTES LIBERADOS: 4""\n""\n""TIEMPO: 3m 35s");
    textos[5].setString(charString.str());
    charString.str("Llegan nuevos tiempo para el pais,""\n""\n""CIUDADANOS ha llegado al poder.""\n""\n""Se presagian grandes cambios.""\n""\n""Y se respiran nuevos aires.");
    textos[6].setString(charString.str());


    textos[0].setFont(font);
    textos[1].setFont(font);
    textos[2].setFont(font);
    textos[3].setFont(font);
    textos[4].setFont(font);
    textos[5].setFont(font);
     textos[6].setFont(font);
   
    
    textos[0].setColor(sf::Color(000,000,000));
    textos[1].setColor(sf::Color(000,000,000));
    textos[2].setColor(sf::Color(000,000,000));
    textos[3].setColor(sf::Color(000,000,000));
    textos[4].setColor(sf::Color(000,000,000));
    textos[5].setColor(sf::Color(000,000,000));
    textos[6].setColor(sf::Color(000,000,000));
   
    textos[0].setStyle(sf::Text::Bold);
    textos[1].setStyle(sf::Text::Bold);
    textos[2].setStyle(sf::Text::Bold);
    textos[3].setStyle(sf::Text::Bold);
    textos[4].setStyle(sf::Text::Bold);
    textos[5].setStyle(sf::Text::Bold);
    textos[6].setStyle(sf::Text::Bold);
    
    textos[0].setCharacterSize(25);
    textos[1].setCharacterSize(20);
    textos[2].setCharacterSize(25);
    textos[3].setCharacterSize(25);
    textos[4].setCharacterSize(25);
    textos[5].setCharacterSize(25);
    textos[6].setCharacterSize(25);
  
     
    /***********************************************
     *                                             * 
     *                 Start Game                  *
     *                                             *
     ***********************************************/

     
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum");
    textos[0].setPosition(sf::Vector2f(170, 200));
    textos[1].setPosition(sf::Vector2f(40, 600));
    textos[2].setPosition(sf::Vector2f(100, 200));
    textos[3].setPosition(sf::Vector2f(340, 200));
    textos[4].setPosition(sf::Vector2f(350, 200));
    textos[5].setPosition(sf::Vector2f(170, 200));
    textos[6].setPosition(sf::Vector2f(560, 600));
 
     
    timeUpdateGame = relog.getElapsedTime();
    int x=0;
    while (window.isOpen())
    {
         
        /***********************************************
         *                                             * 
         *               Imput: Vel MAX                *
         *                                             *
         ***********************************************/
         
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        
                        case sf::Keyboard::Num0:
                            x=0;
                            break;
                        
                         case sf::Keyboard::Num1:
                            x=1;
                            break;
                            
                        case sf::Keyboard::Num2:
                            x=2;
                            break;
                        
                        case sf::Keyboard::Num3:
                            x=3;
                           
                            break;
                        
                   
                            
                        case sf::Keyboard::Num4:
                            x=4;
                            break;
                            
                        case sf::Keyboard::Num5:
                            x=5;
                            break;
                         case sf::Keyboard::Num6:
                            x=6;
                            break;
                        
                           
                        
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    }
                    break;
                
            }
        }
         
        /***********************************************
         *                                             * 
         *           Update: 15 por segundo            *
         *                                             *
         ***********************************************/
         
        if(relog.getElapsedTime().asMilliseconds() - timeUpdateGame.asMilliseconds() > kUpdateTimePS){
            veces++;
            if(veces==4){
               if(tamActivar<numLetras)
                   tamActivar++;
              //  for(int i = 0; i<tamActivar;i++)
               if(x==2){
                    if(textos[1].getPosition().y>window.getSize().y/2-100)
                        textos[1].move(0,-kVelTexto);
               }
            /*   if(x==1){
                    if(textos[1].getPosition().y>window.getSize().y/2)
                        textos[1].move(0,-kVelTexto);
                    
               }*/
               
               if(x==6){
                    if(textos[6].getPosition().y>window.getSize().y/2-100)
                        textos[6].move(0,-kVelTexto);
                   
               }
               
               if(x==0){
                    if(spritecrush.getPosition().y<window.getSize().y/2){
                        spritecrush.move(0,kVelTexto);
                    
                    }else if(timeUpdateGame.asMilliseconds() > kUpdateTimePS){
                    
                        x=1;
                    }
               }
               
               veces = 0;
           }
            timeUpdateGame = relog.getElapsedTime();
        }
             
        /***********************************************
         *                                             * 
         *           Render: Vel MAX                   *
         *                                             *
         ***********************************************/
         
        window.clear(sf::Color::Black);
        window.draw(spritefondo);
        if(x==0){window.draw(spritecrush);}
        if(x==1){window.draw(textos[0]);}
        if(x==2){ window.draw(textos[1]); window.draw(spritepresi);}
        if(x==3){ window.draw(textos[2]); window.draw(spritetutorial);}
        if(x==4){ window.draw(textos[3]); window.draw(spritenivel);}
        if(x==5){ window.draw(textos[4]); window.draw(spriteenhorabuena);}
        if(x==6){ window.draw(textos[5]); window.draw(textos[6]); window.draw(spritefelicidades);}
        
       // for (int i = 0; i<tamActivar && x==0; i++){
        //    window.draw(textos[i]);
       // }
        window.display();
    }
    return 0;
}