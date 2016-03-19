/* ENTREGABLE: Movimiento con personaje principal y cambio de personajes
 * Se moverá el personaje principal con las teclas de desplazamiento
 * en cualquier dirección incluyendo el salto del personaje. Además
 * se hace el cambio de personaje seleccionandolo con los numeros del
 * teclado 1,2 y 3 respectivamente. En este caso en concreto al pulsar 
 * el 1 aparecerá Pedro Sánchez, el 2 Pablo Iglesias y el 3 Albert
 * Rivera. 
 * Además se ha juntado con el entregable golpeo personaje cuaerpo a 
 * cuerpo:
 Al pulsar la barra espaciadora el personaje usará su golpeo cuerpo a 
 cuerpo para poder matar al enemigo que habrá en pantalla para comprobar el
 funcionamiento de su habilidad.*/

#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>

#define kVel 15

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

 
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
  fin.open("resources/pedrospritesheet.xml"); // abrir el xml que se va a leer
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
        
        if (linea<=2) break; // si no hay mas, se termina el bucle
        //SOLO nos interesa a partir de la linea 22 del XML
        if(linea>2){
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
               break;
           }
        }
        //if (!token[n]) break; // si no hay mas, se termina el bucle
        
      }
    }

    linea++;
    if(linea==14){break;}
  }
  
  //Esto es para imprimir la matriz obtenida en consola
    if(linea>2){
        for(int i=0; i<11;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
            }
            cout << endl;
        }
    }
  
  //Para el tiempo que dura un golpe
  sf::Clock golpeoTime;
  float golpeo=0;
  bool der=true;//direccion del personaje
  bool izq=false;//direccion del personaje
  
  
  //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: Movimiento con personaje principal y cambio de personajes");
    
    const float grav=1;
    sf::Vector2f velocity(sf::Vector2f(0,0));
    float movespeed=1.0f, jumpspeed=50.f;
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/pedrospritesheet.png"))
    {
        std::cerr << "Error cargando la imagen pedro.png";
        exit(0);
    }

    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    
    //Le pongo el centroide donde corresponde
    // w=78 h=148 en todos los sprites menos en los de ataque
    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(500, 432);
    
    bool personaje1=true;
    
    
    sf::Texture tex2;
    if (!tex2.loadFromFile("resources/pablospritesheet.png"))
    {
        std::cerr << "Error cargando la imagen pablo.png";
        exit(0);
    }

    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite2(tex2);
    
    //Le pongo el centroide donde corresponde
    // w=78 h=148 en todos los sprites menos en los de ataque
    sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite2.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
    
    // Lo dispongo en el centro de la pantalla
    sprite2.setPosition(800, 432);
    
    bool personaje2=true;
    
    
    sf::Texture tex3;
    if (!tex3.loadFromFile("resources/albertspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen albert.png";
        exit(0);
    }

    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite3(tex3);
    
    //Le pongo el centroide donde corresponde
    // w=78 h=148 en todos los sprites menos en los de ataque
    sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite3.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
    
    // Lo dispongo en el centro de la pantalla
    sprite3.setPosition(600, 432);
    
    bool personaje3=true;
    
    
    sf::RectangleShape suelo(sf::Vector2f(1280, 500));
    suelo.setPosition(0,500);
    suelo.setOutlineThickness(1.0f);
    suelo.setFillColor(sf::Color(120,66,0));
    suelo.setOutlineColor(sf::Color::Black);
    
    sf::RectangleShape enemigo1(sf::Vector2f(50, 50));
    enemigo1.setPosition(250,432);
    enemigo1.setOutlineThickness(1.0f);
    enemigo1.setFillColor(sf::Color(120,66,0));
    enemigo1.setOutlineColor(sf::Color::Black);
    bool enemigo1vive=true;
    
    
    sf::RectangleShape enemigo2(sf::Vector2f(50, 50));
    enemigo2.setPosition(400,432);
    enemigo2.setOutlineThickness(1.0f);
    enemigo2.setFillColor(sf::Color(120,66,0));
    enemigo2.setOutlineColor(sf::Color::Black);
    bool enemigo2vive=true;
    
    int p=0;   //personaje seleccionado
    int i=0;   //intersecciones entre personajes
    
    sf::Clock saltoTime;
    float salto=0;
    
    float GRAVITY = 0.f;//variable gravity
    
  
    while (window.isOpen()){  
        
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
                           
                    switch(event.key.code) {
                        
                        
                        //Mapeo del cursor
                        case sf::Keyboard::Right:
                            if(p==1 || p!=2 || p!=3){
                                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                                sprite.move(10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                                    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
                                    sprite.move(10,0);
                                }
                            }
                            
                            if(p==2){
                                sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite2.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                                sprite2.move(10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                                    sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite2.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
                                    sprite2.move(10,0);
                                }
                            }
                            
                            if(p==3){
                                sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite3.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                                sprite3.move(10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                                    sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite3.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
                                    sprite3.move(10,0);
                                }
                            }
                            //Variables para comprobar si esta mirando a izquierda o derecha
                            der=true;
                            izq=false;
                            
                        break;

                        case sf::Keyboard::Left:
                            if(p==1 || p!=2 || p!=3){
                                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
                                sprite.move(-10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                                    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
                                    sprite.move(-10,0);
                                }
                            }
                            
                            if(p==2){
                                sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite2.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
                                sprite2.move(-10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                                    sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite2.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
                                    sprite2.move(-10,0);
                                }
                            }
                            
                            if(p==3){
                                sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite3.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
                                sprite3.move(-10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                                    sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite3.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
                                    sprite3.move(-10,0);
                                }
                            }
                            //Variables para comprobar si esta mirando a izquierda o derecha
                            der=false;
                            izq=true;
                            
                        break;
                        
                        case sf::Keyboard::Up:
                            //velocity.y=-jumpspeed;
                            salto = saltoTime.getElapsedTime().asSeconds();
                            if(p==1 || p!=2 || p!=3){
                                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                
                                /*if(sprite.getPosition().y > suelo.getPosition().y){
                                    velocity.y+=gravity;
                                }*/
                                
                                sprite.move(0,-jumpspeed * salto);
                                /*if(salto>1)
                                    sprite.setPosition(0,jumpspeed);
                                */
                                /*if(jumpspeed){
                                    
                                }*/
                                
                                saltoTime.restart();
                                /*if((sf::Keyboard::Left)){
                                    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                    sprite.move(-10,0);
                                }*/
                            }
                            
                            if(p==2){
                                sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite2.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                sprite2.move(0,-2);
                                /*if((sf::Keyboard::Left)){
                                    sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite2.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                    sprite2.move(-10,0);
                                }*/
                            }
                            
                            if(p==3){
                                sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite3.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                sprite3.move(0,-2);
                                /*if((sf::Keyboard::Left)){
                                    sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite3.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                    sprite3.move(-10,0);
                                }*/
                            }
                            //Variables para comprobar si esta mirando a izquierda o derecha
                            
                        
                            
                        break;
                        
                        case sf::Keyboard::Space:
                             
                            //Dependiendo de la direccion hacia donde este mirando, se aplica un sprite u otro
                             if(der==true){
                                 //IMPORTANTE cambiar el centroide a la hora de atacar!
                                 if(p==1 || p!=2 || p!=3){
                                    sprite.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                    sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                                 }
                                 
                                 if(p==2){
                                    sprite2.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                    sprite2.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                                 }
                                 
                                 if(p==3){
                                    sprite3.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                    sprite3.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                                 }
                             }
                             if(izq==true){
                                 //IMPORTANTE cambiar el centroide a la hora de atacar!
                                 if(p==1 || p!=2 || p!=3){
                                    sprite.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
                                    sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                                 }
                                 if(p==2){
                                    sprite2.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                    sprite2.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                                 }
                                 
                                 if(p==3){
                                    sprite3.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                    sprite3.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                                 }
                             }
                             

                        break;
                        
                        
                        case sf::Keyboard::Num1:
                            
                            //personaje1=true;
                            if(p==2){
                                sprite.setPosition(sprite2.getPosition().x, sprite2.getPosition().y);
                                if(sprite.getGlobalBounds().intersects(sprite2.getGlobalBounds())){
                                    i=1;
                                }
                            }
                            
                            if(p==3){
                                sprite.setPosition(sprite3.getPosition().x, sprite3.getPosition().y);
                                if(sprite.getGlobalBounds().intersects(sprite3.getGlobalBounds())){
                                    i=2;
                                }
                            }
                            //personaje2=false;
                            //personaje3=false;
                            p=1;
                            
                        break;
                        
                        
                        case sf::Keyboard::Num2:
                            
                            //personaje2=true;
                            if(p==1 || p!=2 || p!=3){
                                sprite2.setPosition(sprite.getPosition().x, sprite.getPosition().y);
                                if(sprite2.getGlobalBounds().intersects(sprite.getGlobalBounds())){
                                    i=3;
                                }
                            }
                            if(p==3){
                                sprite2.setPosition(sprite3.getPosition().x, sprite3.getPosition().y);
                                if(sprite2.getGlobalBounds().intersects(sprite3.getGlobalBounds())){
                                    i=4;
                                }
                            }
                            
                            //personaje1=false;
                            //personaje3=false;
                            p=2;
                            
                        break;
                        
                        
                        case sf::Keyboard::Num3:
                            
                            //personaje3=true;
                            if(p==1 || p!=2 || p!=3){
                                sprite3.setPosition(sprite.getPosition().x, sprite.getPosition().y);
                                sprite.setPosition(15000000,15000000);
                                
                                if(sprite3.getGlobalBounds().intersects(sprite.getGlobalBounds())){
                                    i=5;
                                }
                            }
                            if(p==2){
                                sprite3.setPosition(sprite2.getPosition().x, sprite2.getPosition().y);
                                
                                if(sprite3.getGlobalBounds().intersects(sprite2.getGlobalBounds())){
                                    i=6;
                                }
                            }
                            
                            
                            
                            if(sprite3.getGlobalBounds().intersects(sprite.getGlobalBounds())){
                                    i=5;
                            }
                            
                            if(sprite3.getGlobalBounds().intersects(sprite2.getGlobalBounds())){
                                    i=6;
                            }
                            
                            //personaje2=false;
                            //personaje1=false;
                            p=3;
                            
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
        
        //Despues de golpear, a los 0,5s, el personaje vuelve a su posicion original (izquierda o derecha)
        golpeo= golpeoTime.getElapsedTime().asSeconds();
        if(golpeo>0.5 && der==true){
           if(p==1 || p!=2 || p!=3){ 
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
            golpeoTime.restart();
           }
           
           if(p==2){ 
            sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite2.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
            golpeoTime.restart();
           }
           
           if(p==3){ 
            sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite3.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
            golpeoTime.restart();
           }
        }
        
        if(golpeo>0.5 && izq==true){
           if(p==1 || p!=2 || p!=3){  
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
            golpeoTime.restart();
           }
           
           if(p==2){  
            sprite2.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite2.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
            golpeoTime.restart();
           }
           
           if(p==3){  
            sprite3.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite3.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
            golpeoTime.restart();
           }
        }
        
        //Muerte a los enemigos!
        if(sprite.getGlobalBounds().intersects(enemigo1.getGlobalBounds())  ||  sprite2.getGlobalBounds().intersects(enemigo1.getGlobalBounds())  ||  sprite3.getGlobalBounds().intersects(enemigo1.getGlobalBounds())){
            enemigo1vive=false;
        }
        if(sprite.getGlobalBounds().intersects(enemigo2.getGlobalBounds())  ||  sprite2.getGlobalBounds().intersects(enemigo2.getGlobalBounds())  ||  sprite3.getGlobalBounds().intersects(enemigo2.getGlobalBounds())){
            enemigo2vive=false;
        }
       
        window.clear(sf::Color(sf::Color::White));

        //window.draw(sprite);
//        if(sf::Keyboard::Num2){
//            window.draw(sprite2);
//        }
//        
//        if(sf::Keyboard::Num3){
//            window.draw(sprite3);
//        }
        if(p==1 || p!=2 || p!=3 && (i!=3 && i !=5)){
            window.draw(sprite);
        }
        if(p==2 && (i!=6 && i!=1)){
            window.draw(sprite2);
        }
        if(p==3 && (i!=4 && i!=2)){
            window.draw(sprite3);
        }
        
        
        
               
        //window.draw(sprite2);
        //window.draw(sprite3);
        window.draw(suelo);
        
        if(enemigo1vive==true){
            window.draw(enemigo1);
        }
        
        if(enemigo2vive==true){
            window.draw(enemigo2);
        }
        
        window.display();
        
    }
    
    return 0;
}