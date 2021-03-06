/* ENTREGABLE: GOLPEAR CON PERSONAJE PRINCIPAL
 Al pulsar la barra espaciadora el personaje usará su golpeo cuerpo a 
 cuerpo para poder matar a los enemigos que habrán en pantalla para comprobar el
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
        //SOLO nos interesa a partir de la linea 2 del XML
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
  
  //Para golpear cada cierto tiempo
  sf::Clock golpeosSegundo;
  float golpeoXseg=0;
  
  //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: Golpear con personaje principal");
    
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/pedrospritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caracol.png";
        exit(0);
    }

    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    
    //Le pongo el centroide donde corresponde
    // w=78 h=148 en todos los sprites menos en los de ataque
    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(500, 432);
    
    sf::RectangleShape suelo(sf::Vector2f(1280, 500));
    suelo.setPosition(0,500);
    suelo.setOutlineThickness(1.0f);
    suelo.setFillColor(sf::Color(120,66,0));
    suelo.setOutlineColor(sf::Color::Black);

    
     //ARRAY DE ENEMIGOS
    vector<sf::RectangleShape*> enemigos;
    for(int i=0;i<2;i++){

        enemigos.push_back(new sf::RectangleShape(sf::Vector2f(50, 50)));
        if(i==0){
            enemigos[i]->setPosition(400,432);
        }
        if(i==1){
            enemigos[i]->setPosition(550,432);
        }
        enemigos[i]->setOutlineThickness(1.0f);
        enemigos[i]->setFillColor(sf::Color(120,66,0));
        enemigos[i]->setOutlineColor(sf::Color::Black);
    }
  
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
                            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                            sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                            //Variables para comprobar si esta mirando a izquierda o derecha
                            der=true;
                            izq=false;
                            
                        break;

                        case sf::Keyboard::Left:
                            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                            sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
                            //Variables para comprobar si esta mirando a izquierda o derecha
                            der=false;
                            izq=true;
                            
                        break;
                        
                        case sf::Keyboard::Space:
                             golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();
                            
                             //Dependiendo de la direccion hacia donde este mirando, se aplica un sprite u otro
                             if(der==true){
                                 if(golpeoXseg>0.5){
                                     //IMPORTANTE cambiar el centroide a la hora de atacar!
                                        sprite.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                                        sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                                        golpeosSegundo.restart();
                                 }
                             }
                             if(izq==true){
                                 if(golpeoXseg>0.5){
                                      //IMPORTANTE cambiar el centroide a la hora de atacar!
                                        sprite.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
                                        sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));   
                                        golpeosSegundo.restart();
                                 }

                             }
                             

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
        
        //Despues de golpear, a los 0,65s, el personaje vuelve a su posicion original (izquierda o derecha)
        golpeo= golpeoTime.getElapsedTime().asSeconds();
        if(golpeo>0.65 && der==true){
           sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
           sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
           golpeoTime.restart();
        }
        
        if(golpeo>0.65 && izq==true){
           sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
           sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
           golpeoTime.restart();
        }
        
        //Muerte a los enemigos!
        for(int j=0; j<enemigos.size(); j++){
            //Si el golpe alcanza a cualquier enemigo...
            if(sprite.getGlobalBounds().intersects(enemigos[j]->getGlobalBounds())){
                //Se destruye el enemigo
                delete enemigos[j];
                enemigos.erase(enemigos.begin() + j); //Se elimina la posicion del vector donde estaba
            }
        }
        
        window.clear(sf::Color(sf::Color::White));

        window.draw(sprite);
        for(sf::RectangleShape* i : enemigos)window.draw(*i); //Bucle para dibujar todos los enemigos vivos del vector
        window.draw(suelo);
        
//        if(enemigo1vive==true){
//            window.draw(enemigo1);
//        }
//        
//        if(enemigo2vive==true){
//            window.draw(enemigo2);
//        }
        
        window.display();
        
    }
    
    return 0;
}