#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>

#define kVel 15

#include <fstream>
#include <cstring>


using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

 
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")
 
/*int main()
{
 
     sf::RenderWindow window(sf::VideoMode(640, 480), "Entregable: Movimiento con personaje principal y cambio de personajes");
     
     const float gravity=1;
     int groundheight =440;
    sf::Vector2f velocity(sf::Vector2f(0,0));
    float movespeed=1.0f, jumpspeed=10.f;
    
    sf::RectangleShape rect(sf::Vector2f(20,20));
    rect.setPosition(0,0);
    rect.setFillColor(sf::Color::Blue);
     
     while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            sf::Clock tiempo;
            
            switch(event.type){
                
                
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            velocity.x=movespeed;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            velocity.x=-movespeed;
        }
        
        else
            velocity.x=0;
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            velocity.y=-jumpspeed;
        }
        
        
        
        if(rect.getPosition().y + rect.getSize().y < groundheight || velocity.y<0){
            velocity.y+=gravity;
        }
        
        else{
            rect.setPosition(rect.getPosition().x, groundheight - rect.getSize().y);
        }
        
        rect.move(velocity.x, velocity.y);
        
     }
    
     window.clear();
     window.draw(rect);
     window.display();
}*/



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
    //sprite2.setPosition(800, 432);
    
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
    //sprite3.setPosition(600, 432);
    
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
    
    window.setFramerateLimit(50);
    //float GRAVITY = 0.f;//variable gravity
    
    //const float gravity=1;
    int groundheight =440;
    sf::Vector2f velocity(sf::Vector2f(0,0));
    float movespeed=1.0f, jumpspeed=50.f;
  
    sf::Clock clock;
    //const int gravity = 500;
    bool onGround = false;
    float inAir;
    float maxInAir = 0.3f;
    
    //sf::Vector2f playerVelocity(0, gravity);
    float dt;
    
    
    sf::Vector2f playerPosition(100, 100);
    sf::Vector2f playerVelocity(0, 0);
    const float gravity = 0.2;
    int groundHeight = suelo.getPosition().y - 65;
    float jumpSpeed = 7, moveSpeed = 5;
    bool jump = false;

    
    sprite.setPosition(playerPosition);
    
    while (window.isOpen()){  
        
        float dt = clock.restart().asSeconds();
        
        
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
            
            if (event.type == sf::Event::Closed)
                window.close();
             
            
                
            
                           
                   
                        
                        //Mapeo del cursor
                       /* case sf::Keyboard::Right:
                            
                                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                                sprite.move(10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                                    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
                                    sprite.move(10,0);
                                }
                            
                            
                            
                           
                            der=true;
                            izq=false;
                            
                        break;

                        case sf::Keyboard::Left:
                            
                                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
                                sprite.move(-10,0);
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                                    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                    sprite.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
                                    sprite.move(-10,0);
                                }
                            
                            
                       
                            der=false;
                            izq=true;
                            
                        break;
                        
                        case sf::Keyboard::Up:
                           
                            salto = saltoTime.getElapsedTime().asSeconds();
                            if(p==1 || p!=2 || p!=3){
                                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                                sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                                
                                
                                
                                sprite.move(0,-jumpspeed);
                                
                                
                                saltoTime.restart();
                                
                            }
                            
                            
                            
                        
                            
                        break;
                        */
            
                              
                    
                    
                    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                        playerVelocity.x = -gravity;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                        playerVelocity.x = gravity;
                }
                else if (playerVelocity.x != 0)
                {
                        playerVelocity.x = 0;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (onGround || inAir < maxInAir))
                {
                        playerVelocity.y = -gravity;
                        inAir += dt;
                }
                else
                {
                        playerVelocity.y = gravity;
                        inAir = maxInAir;
                }

                sprite.setPosition(sprite.getPosition().x + playerVelocity.x * dt, sprite.getPosition().y + playerVelocity.y * dt);    
            sprite.move(playerVelocity.x, playerVelocity.y * dt);    
            */
        }    
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerVelocity.x = moveSpeed;
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerVelocity.x = -moveSpeed;
        else
            playerVelocity.x = 0;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && jump)
        {
            playerVelocity.y = -jumpSpeed;
            jump = false;
        }

        if(!jump)
            playerVelocity.y += gravity;
        else
            playerVelocity.y = 0;

        playerPosition += playerVelocity;

        jump = playerPosition.y + 10 >= groundHeight;

        if(jump)
            playerPosition.y = groundHeight - 10;

        sprite.setPosition(playerPosition);

        
        
        //Despues de golpear, a los 0,5s, el personaje vuelve a su posicion original (izquierda o derecha)
        golpeo= golpeoTime.getElapsedTime().asSeconds();
        if(golpeo>0.5 && der==true){
           
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
            golpeoTime.restart();
           
           
           
        }
        
        if(golpeo>0.5 && izq==true){
            
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
            sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
            golpeoTime.restart();
           
           
           
        }
        
        //Muerte a los enemigos!
        if(sprite.getGlobalBounds().intersects(enemigo1.getGlobalBounds())  ||  sprite2.getGlobalBounds().intersects(enemigo1.getGlobalBounds())  ||  sprite3.getGlobalBounds().intersects(enemigo1.getGlobalBounds())){
            enemigo1vive=false;
        }
        if(sprite.getGlobalBounds().intersects(enemigo2.getGlobalBounds())  ||  sprite2.getGlobalBounds().intersects(enemigo2.getGlobalBounds())  ||  sprite3.getGlobalBounds().intersects(enemigo2.getGlobalBounds())){
            enemigo2vive=false;
        }
       
        window.clear(sf::Color(sf::Color::White));

        window.draw(sprite);
//        if(sf::Keyboard::Num2){
//            window.draw(sprite2);
//        }
//        
//        if(sf::Keyboard::Num3){
//            window.draw(sprite3);
//        }
        
        
               
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