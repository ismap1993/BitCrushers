/* 
 * File:   Mapa.cpp
 * Author: alfon
 * 
 * Created on 17 de marzo de 2016, 21:25
 */

#include "Mapa.h"
#include "Plataforma.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enemigo.h"
#include "BossFinal.h"

using namespace std;

Mapa::Mapa() {
    //constructor vacio
    matrizEnemigosA=new int*[99];
    for(int i=0; i<99;i++){
        matrizEnemigosA[i]=new int[4];
    }
    
    matrizEnemigosC=new int*[99];
    for(int i=0; i<99;i++){
        matrizEnemigosC[i]=new int[4];
    }
    
    arrayVotos = new vector<sf::Sprite*>();
    
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
    //metodo que elimina el mapa
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            delete[] _tilemap[l][y];
        }
        delete[] _tilemap[l];
    }
    delete[] _tilemap;
}

void Mapa::leerMapa(int numMapa){
    _numLayers=0;
    //cargo la textura del fondo
    if(!fond.loadFromFile("resources/background.jpg")){
        std::cerr << "Error cargando la imagen background.png";
        exit(0);
    }
    fondo.setTexture(fond);

    //creo el objeto xml
    TiXmlDocument doc;
    if(numMapa==1)doc.LoadFile("resources/PP/nivel3PP.tmx");
    if(numMapa==2)doc.LoadFile("resources/PSOE/nivel1PSOE.tmx");
    if(numMapa==3)doc.LoadFile("resources/CIUDADANOS/nivel1CIUDADANOS.tmx");
    if(numMapa==4)doc.LoadFile("resources/PODEMOS/nivel1PODEMOS.tmx");
    TiXmlElement* map = doc.FirstChildElement("map");
    
    //leo sus atributos
    map->QueryIntAttribute("width",&_width);
    map->QueryIntAttribute("height",&_height);
    map->QueryIntAttribute("tilewidth",&_tileWidth);
    map->QueryIntAttribute("tileheight",&_tileHeigth);
    
    
    //Leemos las diferentes imagenes que nos sirven para hacer el rect de las texturas
    TiXmlElement *img = map->FirstChildElement("tileset");
    
    int numTil=0;
    while(img){
        numTil++;
        img=img->NextSiblingElement("tileset");
    }
    
    
    string filename;

    img = map->FirstChildElement("tileset");
    //guardamos en filename el spritesheet
    while(img){
        filename=(string)img->FirstChildElement("image")->Attribute("source");
        img=img->NextSiblingElement("tileset");
    }  
    
    //leemos las diferentes capas
    _tilesetTexture.loadFromFile(filename);
    TiXmlElement *layer = map->FirstChildElement("layer");
    while(layer){
        _numLayers++;
        layer= layer->NextSiblingElement("layer");
    }  
    
    //Reserva de memoria para saber el numnero de capas y el tamaño 
    _tilemap=new int**[_numLayers];
    for(int i=0; i<_numLayers; i++){
        _tilemap[i]=new int*[_height];
    }
    
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemap[l][y]=new int[_width];
        }
    }

    TiXmlElement *data;
    //leemos el atributo imagen
    layer = map->FirstChildElement("layer");
    string *name=new string[_numLayers];
    int j=0;
    int l=0;
    //leo los tiles del xml y avanzo a la siguiente posicion
    while(layer){
        data= layer->FirstChildElement("data")->FirstChildElement("tile");
        name[j]= (string)layer->Attribute("name");
            while(data){
                for(int y=0; y<_height; y++){
                    for(int x=0; x<_width;x++){
                        data->QueryIntAttribute("gid",&_tilemap[l][y][x]);
                        data=data->NextSiblingElement("tile");
                    }
                }
            }
        l++;
        layer= layer->NextSiblingElement("layer");
        j++;
    }
      
    //Reserva de memoria para los sprites
    _tilemapSprite=new sf::Sprite***[_numLayers];
      
    for(int l=0; l<_numLayers; l++){
        _tilemapSprite[l]=new sf::Sprite**[_height];
    }
      
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            _tilemapSprite[l][y]= new sf::Sprite*[_width];
            for(int x=0; x<_width; x++){
                _tilemapSprite[l][y][x]=new sf::Sprite();
            }
        }
    } 
    sf::Texture aux;  
    
    //falta el corte
    
    int columns = _tilesetTexture.getSize().x / _tileWidth;
    int rows = _tilesetTexture.getSize().y / _tileHeigth;
    
    cout<<columns<<" "<<rows<<endl; 
    
    _tilesetSprite =new sf::Sprite[columns*rows];     
    int t=0;
    for(int y=0; y<rows; y++){
        for(int x=0; x<columns;x++){
              _tilesetSprite[t].setTexture(_tilesetTexture);
              //_tilesetSprite[t].setTextureRect(sf::IntRect(left,top,width,height));//ojo si hay dos imagenes
              _tilesetSprite[t].setTextureRect(sf::IntRect(x*_tileWidth,y*_tileHeigth,_tileWidth,_tileHeigth));
              t++;
        }
    }
    
    
    /**
    for(int y=0; y<t; y++)
    {
     cout<<_tilesetSprite[y].getTextureRect().left<<" ";
     cout<<_tilesetSprite[y].getTextureRect().top<<" ";
      cout<<_tilesetSprite[y].getTextureRect().width<<" ";
       cout<<_tilesetSprite[y].getTextureRect().height<<endl;
    }**/
    
    //cout<<t<<endl;
   
    //asignacion sprite
      
    for(int l=0; l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width;x++){
                int gid=_tilemap[l][y][x]-1;
                if(gid>=rows*columns){
                    cout<<gid<<endl;
                    cout<<rows<<endl;
                    cout<<columns<<endl;
                    cout<<"Error aaaa"<<endl;
                }
                else if(gid>0){   

                    _tilemapSprite[l][y][x]=new sf::Sprite(_tilesetTexture,_tilesetSprite[gid].getTextureRect());
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth,y*_tileHeigth);
                }
                else{
                    _tilemapSprite[l][y][x]=NULL;
                }
            }
        }
    }
      
    /////////////////////Resumen
    cout<<endl;
    cout<<"Resumen:"<<endl;
    cout<<"Heigth= "<<_height<<endl;
    cout<<"Width= "<<_width<<endl;
    cout<<"TileWidth= "<<_tileWidth<<endl;
    cout<<"TileHeigth= "<<_tileHeigth<<endl;
    cout<<"Numero de capas= "<<_numLayers<<endl;
    cout<<"Nombre del tileset= "<<filename[0]<<endl;
    cout<<"Nombre del tileset= "<<filename[1]<<endl;
    cout<<endl;
    
     TiXmlElement *suelo = map->FirstChildElement("objectgroup");
     string nombre;
     int filas=0;
     string xString, yString, widthString, heightString;
     int x, y, width, height;
     

     while(suelo){
         nombre=(string) suelo->Attribute("name");
         if(nombre=="Suelo"){
             cout<<"nombre: "<<nombre<<endl;
             TiXmlElement *object = suelo->FirstChildElement("object");
             while(object){
                
                xString = (string) object->Attribute("x");
                yString = (string) object->Attribute("y");
                widthString = (string) object->Attribute("width");
                heightString = (string) object->Attribute("height");
                
                x=atoi(xString.c_str());
                y=atoi(yString.c_str());
                width=atoi(widthString.c_str());
                height=atoi(heightString.c_str());
                
                /*Se crean los rectangulos que colisionan*/
                sf::RectangleShape* colision = new sf::RectangleShape(sf::Vector2f(width, height));
                colision->setPosition(x,y);
                arraySuelo.push_back(colision);
               
                

                /*cout<<"x: "<<x<<endl;
                cout<<"y: "<<y<<endl;
                cout<<"width: "<<width<<endl;
                cout<<"heigth: "<<height<<endl;
                cout<<"----"<<endl;*/
                object = object->NextSiblingElement("object");
                filas++;
             }   
         }
         suelo = suelo->NextSiblingElement("objectgroup");
     }
     
     TiXmlElement *paredes = map->FirstChildElement("objectgroup");
     
     while(paredes){
         nombre=(string) paredes->Attribute("name");
         if(nombre=="Paredes"){
              cout<<"nombre: "<<nombre<<endl;
              TiXmlElement *object = paredes->FirstChildElement("object");
              while(object){
                xString = (string) object->Attribute("x");
                yString = (string) object->Attribute("y");
                widthString = (string) object->Attribute("width");
                heightString = (string) object->Attribute("height");
                
                x=atoi(xString.c_str());
                y=atoi(yString.c_str());
                width=atoi(widthString.c_str());
                height=atoi(heightString.c_str());
                
                sf::RectangleShape* colision = new sf::RectangleShape(sf::Vector2f(width, height));
                colision->setPosition(x,y);
                arrayParedes.push_back(colision);
                
                /*cout<<"x: "<<x<<endl;
                cout<<"y: "<<y<<endl;
                cout<<"width: "<<width<<endl;
                cout<<"heigth: "<<height<<endl;
                cout<<"----"<<endl;
                */
                object = object->NextSiblingElement("object");
                filas++;
              }
         }
         paredes = paredes->NextSiblingElement("objectgroup");
     }
     
//     cout<<"width "<<arrayColisiones[0]->getScale()<<endl;
//     cout<<"height "<<arrayColisiones[0]->height<<endl;
     
        TiXmlElement *plataformas = map->FirstChildElement("objectgroup");
        while(plataformas){
            
            nombre=(string) plataformas->Attribute("name");
           
            if(nombre=="Plataforma"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = plataformas->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        Plataforma *plataforma = new Plataforma(x, y, numMapa);
                        arrayPlataformas.push_back(plataforma);
                        
                        /*cout<<"x: "<<x<<endl;
                        cout<<"y: "<<y<<endl;
                        cout<<"----"<<endl;
                        */
                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             plataformas = plataformas->NextSiblingElement("objectgroup");
         }
        
         TiXmlElement *votos = map->FirstChildElement("objectgroup");
        while(votos){
            
            nombre=(string) votos->Attribute("name");
           
            if(nombre=="Votos"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = votos->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        
                        
                        if (!texVoto.loadFromFile("resources/voto.png")) {
                                std::cerr << "Error cargando la imagen voto.png";
                                exit(0);
                        }
                        
                        spriteVoto = new sf::Sprite(texVoto); 
                        spriteVoto->setPosition(x, y);
                        //spriteVoto.setTexture(texVoto);
                        //spriteVoto.setPosition(x, y);
                        
                        arrayVotos->push_back(spriteVoto);
                        
                        /*cout<<"x: "<<x<<endl;
                        cout<<"y: "<<y<<endl;
                        cout<<"----"<<endl;
                        */
                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             votos = votos->NextSiblingElement("objectgroup");
         }
     
     int iC=0;
        TiXmlElement *enemigosC = map->FirstChildElement("objectgroup");
        while(enemigosC){
            
            nombre=(string) enemigosC->Attribute("name");
           
            if(nombre=="Enemigos C"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = enemigosC->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        matrizEnemigosC[iC][0]=x;
                        matrizEnemigosC[iC][1]=y;
                        
                        cout<<"-----Pos x enemC:-------- "<<matrizEnemigosC[iC][0]<<endl;
                        cout<<"-----Pos y enemC:-------- "<<matrizEnemigosC[iC][1]<<endl;
                        iC++;
                       
                        
                       // sf::RectangleShape* enemigosC = new sf::RectangleShape(sf::Vector2f(40, 110));
                        //enemigosC->setFillColor(sf::Color::Red);
                        //enemigosC->setPosition(x,y);
                        //arrayEnemigosC.push_back(enemigoC);
                        
                        /*cout<<"x: "<<x<<endl;
                        cout<<"y: "<<y<<endl;
                        cout<<"----"<<endl;
                        */
                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             enemigosC = enemigosC->NextSiblingElement("objectgroup");
         }
        numEnemigosC=iC;
          
        int iA=0;
        TiXmlElement *enemigosA = map->FirstChildElement("objectgroup");
        while(enemigosA){
            
            nombre=(string) enemigosA->Attribute("name");
           
            if(nombre=="Enemigos A"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = enemigosA->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        matrizEnemigosA[iA][0]=x;
                        matrizEnemigosA[iA][1]=y;
                        
//                        cout<<"-----Pos x enemA:-------- "<<matrizEnemigosA[iA][0]<<endl;
//                        cout<<"-----Pos y enemA:-------- "<<matrizEnemigosA[iA][1]<<endl;
                        iA++;  
                        
                        /*cout<<"x: "<<x<<endl;
                        cout<<"y: "<<y<<endl;
                        cout<<"----"<<endl;
                        */
                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             enemigosA = enemigosA->NextSiblingElement("objectgroup");
         }
        numEnemigosA=iA;
        
        TiXmlElement *boss = map->FirstChildElement("objectgroup");
        while(boss){
            
            nombre=(string) boss->Attribute("name");
           
            if(nombre=="BOSS FINAL"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = boss->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        
        /***************************CREACION DEL BOSS FINAL!!**********************************/
                        posxBoss=x;
                        posyBoss=y;
                        
                        
                        cout<<"-----Pos x JEFE:-------- "<<posxBoss<<endl;
                        cout<<"-----Pos y JEFE:-------- "<<posyBoss<<endl;
                        
                        
                        
                        /*cout<<"x: "<<x<<endl;
                        cout<<"y: "<<y<<endl;
                        cout<<"----"<<endl;
                        */
                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             boss = boss->NextSiblingElement("objectgroup");
         }
        
        TiXmlElement *simpa = map->FirstChildElement("objectgroup");
        while(simpa){
            
            nombre=(string) simpa->Attribute("name");
           
            if(nombre=="Simpatizante"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = simpa->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        
        /***************************SIMPATIZANTE**********************************/
                        if (!texSimpa.loadFromFile("resources/RITA.png")) {
                                std::cerr << "Error cargando la imagen voto.png";
                                exit(0);
                        }
                        
                        spriteSimpa = new sf::Sprite(texSimpa); 
                        spriteSimpa->setPosition(x, y);
                        
                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             simpa = simpa->NextSiblingElement("objectgroup");
         }
        
        
        TiXmlElement *carcel = map->FirstChildElement("objectgroup");
        while(carcel){
            
            nombre=(string) carcel->Attribute("name");
           
            if(nombre=="Carcel"){
                    cout<<"nombre: "<<nombre<<endl;
                    TiXmlElement *object = carcel->FirstChildElement("object");
                    while(object){
                        xString = (string) object->Attribute("x");
                        yString = (string) object->Attribute("y");
                        
                        x=atoi(xString.c_str());
                        y=atoi(yString.c_str());
                        
                        
        /***************************CARCEL**********************************/
                        if (!texCarcelCerrada.loadFromFile("resources/CarcelCerrada.png")) {
                                std::cerr << "Error cargando la imagen CarcelCerrada.png";
                                exit(0);
                        }
                        
                        spriteCarcelCerrada = new sf::Sprite(texCarcelCerrada); 
                        spriteCarcelCerrada->setPosition(x, y);
                        
                         if (!texCarcelAbierta.loadFromFile("resources/CarcelAbierta.png")) {
                                std::cerr << "Error cargando la imagen CarcelAbierta.png";
                                exit(0);
                        }
                        
                        spriteCarcelAbierta = new sf::Sprite(texCarcelAbierta); 
                        spriteCarcelAbierta->setPosition(x, y);

                        object = object->NextSiblingElement("object");
                        filas++;
                    }
                }
             carcel = carcel->NextSiblingElement("objectgroup");
         }
//     TiXmlElement *properties = colisiones->FirstChildElement("properties");
//     string atributo;
//     while(properties){
//         atributo = properties->FirstChildElement("property")->Attribute("name");
//         cout<<"hola"<<endl;
//     }
//     cout<<"atributo: "<<atributo<<endl;

     
     
     
    //guardamos en filename el spritesheet
//    while(img){
//        filename=(string)img->FirstChildElement("image")->Attribute("source");
//        img=img->NextSiblingElement("tileset");
//    }  
    /*cout<<"Gid de las capas"<<endl;
   for(int l=0; l<_numLayers; l++)
    {
       cout<<name[l]<<endl;
        for(int y=0; y<_height; y++)
        {
            for(int x=0; x<_width;x++)
            {    
                cout<<_tilemap[l][y][x]<<" ";

                if(x==_width-1)
                {
                    cout<<endl;
                }
            }
        }
   }*/
}


void Mapa::dibuja(sf::RenderWindow& window){
    
    //dibujamos el mapa
    for(int t=0; t<_numLayers; t++){
        for(int y=0; y<_height; y++){
            for(int x=0; x<_width; x++){
                if(_tilemapSprite[t][y][x]!=NULL){                    
                    window.draw(*(_tilemapSprite[t][y][x]));
                }
            }
        }
    }
}

int Mapa::getTile(int posx, int posy){
    
    int resultado= _tilemap[0][posy/32][posx/32];

    return resultado;
}

//std::vector<sf::RectangleShape*> Mapa::getEnemigosC(sf::RenderWindow& window){
//    for(int j=0; j<arrayEnemigosC.size();j++){
//           window.draw(*arrayEnemigosC[j]);
//    }
//}

//std::vector<sf::RectangleShape*> Mapa::getEnemigosA(sf::RenderWindow& window){
//    for(int j=0; j<arrayEnemigosA.size();j++){
//           window.draw(*arrayEnemigosA[j]);
//    }
//}

void Mapa::dibujaVotos(sf::RenderWindow& window){
    if(arrayVotos!=NULL){
        for(sf::Sprite* i : *arrayVotos){
            window.draw(*i);
        }
    }
}

void Mapa::dibujaSimpatizante(sf::RenderWindow& window){
    window.draw((*spriteSimpa));
}

void Mapa::dibujaCarcelCerrada(sf::RenderWindow& window){
    window.draw((*spriteCarcelCerrada));
}

void Mapa::dibujaCarcelAbierta(sf::RenderWindow& window){
    window.draw((*spriteCarcelAbierta));
}


void Mapa::dibujaEnemigosC(sf::RenderWindow& window){
//    for(int j=0; j<arrayEnemigosC.size();j++){
//           window.draw(arrayEnemigosC[j]->getSprite());
//    }
}

void Mapa::dibujaEnemigosA(sf::RenderWindow& window){
//    for(int j=0; j<arrayEnemigosA.size();j++){
//           window.draw(arrayEnemigosA[j]->getSprite());
//    }
}

void Mapa::dibujaPlataformas(sf::RenderWindow& window){
    for(int j=0; j<arrayPlataformas.size();j++){
           window.draw(arrayPlataformas[j]->spritePlat);
           arrayPlataformas[j]->move();
    }
}