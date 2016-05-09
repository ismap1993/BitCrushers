#include <SFML/OpenGl.hpp>
#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Camara.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "Mapa.h"
#include <math.h> 
#include "Jugador.h"
#include "Enemigo.h"
#include "BossFinal.h"
//velocidad a la que se mueve el personaje
#define kVel 10
#define UPDATE_TICK_TIME 1000/15



int main(){
    int numMapa=1;// 1 PP. 2 PSOE. 3 CS. 4 PODEMOS
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    int width=1066;
    int height=600;
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Entregable: Nivel 1 + colisiones!");
    //sf::RenderWindow window(window = new RenderWindow(new VideoMode(800, 600), "GLTEST", Styles.Default, settings));
    /*sf::RenderWindow window(sf::VideoMode(width, height), "title", sf::Style::Default, settings);
    std::cout <<"pruebaaaaaaaaa"<< window.getSettings().antialiasingLevel << std::endl;
    */
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    //Creo un personaje para poder moverlo
    //sf::RectangleShape *personaje = new sf::RectangleShape(sf::Vector2f(20, 20));
    float posx = 200; //para que sean floats
    float posy = 359;
        int modoJefe=0; //si esta en 1, hay pelea

    Jugador* player = new Jugador(posx, posy, 2, true);
    //player->leerXML();
        
    ///////////////////////////BUFFER DE SONIDO////////
    sf::SoundBuffer bufferSobre;
    sf::Sound soundSobre;
    if (!bufferSobre.loadFromFile("resources/FX/SOBRE.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    soundSobre.setBuffer(bufferSobre);
    
    sf::SoundBuffer bufferHurt;
    sf::Sound soundHurt;
    if (!bufferHurt.loadFromFile("resources/FX/HURT.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    soundHurt.setBuffer(bufferHurt);
    
    
    
    sf::SoundBuffer buffer;
    if(numMapa==1){
        if (!buffer.loadFromFile("resources/PP/PP.flac"))
        return -1; // error  
    } 
    if(numMapa==2){
        if (!buffer.loadFromFile("resources/PSOE/PSOE.flac"))
        return -1; // error  
    } 
    if(numMapa==3){
        if (!buffer.loadFromFile("resources/CIUDADANOS/CIUDADANOS.flac"))
        return -1; // error  
    } 
    if(numMapa==4){
        if (!buffer.loadFromFile("resources/PODEMOS/PODEMOS.flac"))
        return -1; // error  
    } 
    
    

    //declaro el mapa y lo cargo con la funcion leerMapa(). Esto lee el tmx y lo guarda
    Mapa *mapa = new Mapa();
    mapa->leerMapa(numMapa);
    
    
    /*CREACION BOSS FINAL!*/
    BossFinal* boss = new BossFinal(true, mapa->posxBoss, mapa->posyBoss, numMapa);// 1 PP. 2 PSOE. 3 CS. 4 PODEMOS
    sf::Sprite*  spriteBoos = new sf::Sprite(boss->getSprite());
    sf::Texture texMuro;
    if(numMapa==1){
        if (!texMuro.loadFromFile("resources/PP/MUROPP.png")) {
                                std::cerr << "Error cargando la imagen voto.png";
                                exit(0);
        }
    }
    
    if(numMapa==2){
        if (!texMuro.loadFromFile("resources/PSOE/MUROPSOE.png")) {
                                std::cerr << "Error cargando la imagen voto.png";
                                exit(0);
        }
    }
    
     if(numMapa==3){
        if (!texMuro.loadFromFile("resources/CIUDADANOS/MUROCIUDADANOS.png")) {
                                std::cerr << "Error cargando la imagen voto.png";
                                exit(0);
        }
    }
    
     if(numMapa==4){
        if (!texMuro.loadFromFile("resources/PODEMOS/MUROPODEMOS.png")) {
                                std::cerr << "Error cargando la imagen voto.png";
                                exit(0);
        }
    }
    sf::Sprite* muroJefe = new sf::Sprite(texMuro);
    muroJefe->setPosition(mapa->posxBoss-950, mapa->posyBoss-355);
           

    //Creo la camara con el ancho y el largo de la ventana, ademas le paso la cantidad de pixeles que se mueve el personaje y el mapa
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel/3, *mapa);
    //creacion de vectores de enemigos
    std::vector<Enemigo*>* cuerpo = new std::vector<Enemigo*>();
    std::vector<Enemigo*>* distancia = new std::vector<Enemigo*>();
    
    //vectores auxiliares para que colisione el jugador con los sprites
    std::vector<sf::Sprite>* cuerpoAux = new std::vector<sf::Sprite>();
    std::vector<sf::Sprite>* distanciaAux = new std::vector<sf::Sprite>();
    
    //creo un vector de fondos para ponerlo detras del mapa
    std::vector<sf::Sprite*> fondos;
    //variable para saber cuantas veces he de pintar el fondo ya que el mapa tiene mas pixeles que el fondo
    int cuantasVecesDeboPintarElFondo=(mapa->_tileWidth*mapa->_width)/mapa->fondo.getGlobalBounds().width;
    cuantasVecesDeboPintarElFondo=trunc(cuantasVecesDeboPintarElFondo)+1;
    
    //cargo la textura del fondo
    sf::Texture tex;
    if(numMapa==1){
           if (!tex.loadFromFile("resources/background.jpg"))
        {
          std::cerr << "Error cargando la imagen background.jpg";
           exit(0);
        }
    }
    
    if(numMapa==2){
           if (!tex.loadFromFile("resources/backgroundPSOE.jpg"))
        {
          std::cerr << "Error cargando la imagen background.jpg";
           exit(0);
        }
    }
    
    if(numMapa==3){
           if (!tex.loadFromFile("resources/backgroundCS.jpg"))
        {
          std::cerr << "Error cargando la imagen background.jpg";
           exit(0);
        }
    }
    
    if(numMapa==4){
           if (!tex.loadFromFile("resources/backgroundPODEMOS.jpg"))
        {
          std::cerr << "Error cargando la imagen background.jpg";
           exit(0);
        }
    }
    //relleno el vector de fondos con el valor cuantasVecesDeboPintarElFondo
    for(int i=0; i<cuantasVecesDeboPintarElFondo; i++){
        fondos.push_back(new sf::Sprite());
        fondos[i]->setTexture(tex);
        fondos[i]->setPosition(mapa->fondo.getGlobalBounds().width*i, 0);
    }
    //lleno los vectores. 
    for(int i=0; i<4; i++){
        cuerpo->push_back(new Enemigo(true, mapa->matrizEnemigosC[i][0],mapa->matrizEnemigosC[i][1], 0, numMapa));
        cuerpoAux->push_back(cuerpo->at(i)->getSprite());
    }
    for(int i=0; i<4; i++){
        distancia->push_back(new Enemigo(true, mapa->matrizEnemigosA[i][0],mapa->matrizEnemigosA[i][1], 1, numMapa));
        distanciaAux->push_back(distancia->at(i)->getSprite());

    }
    
    /********RELOJES Y TIEMPO*********/
    sf::Clock relojGolpe;
    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;
     float tiempo;
     
    
    /*********MUSICA****************/
    sf::Sound musica;
    musica.setBuffer(buffer);
    musica.setLoop(true);
    musica.play(); 
    
    /**********BUCLE PRINCIPAL*************/
    while (window.isOpen()){
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event)){

            switch(event.type){
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                       /* case sf::Keyboard::Right:
                            //muevo a la derecha el personaje y la camara con el metodo moveRight
                            personaje->move(kVel, 0);
                            camara->moveRight(*personaje);
                            std::cout<<"ID= "<< mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)<<std::endl;
                            if(mapa->getTile(personaje->getPosition().x, personaje->getPosition().y)==4){
                                personaje->move(-kVel, 0);
                            }
                        break;*/
                        case sf::Keyboard::Z:
                            musica.stop();
                        break;
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            //std::cout << event.key.code << std::endl;
                        break;
                              
                    }
            }
        }     
        
/****************************************************************************/        
        if(!player->muerto){     //CONTORLA QUE EL HANDLE SE BLOQUEE
            player->handle(event, window, mapa, camara, *cuerpoAux, *distanciaAux, *spriteBoos);
            //int a;
        }
             
        else
            camara->cartelGameOver(window, player);
        
        
            if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME){
                timeElapsed = updateClock.restart();
                //manejadores de los enemigos
                for(int i=0; i<cuerpo->size(); i++){
                   cuerpo->at(i)->handle(player);    
                }
                for(int j=0; j<distancia->size(); j++){
                   distancia->at(j)->handle(player);
                }
                boss->handle(player);
            }
        
       
        
        /**Render**/
        window.clear();
         
        //dibujo los fondos
        /*for(sf::Sprite* q : fondos){
            window.draw(*q); 
        }*/
        
                

        //dibujo el mapa con su metodo
        mapa->dibuja(window);
        
        //window.draw(suelo);
//        for(int i=0; i<mapa->arrayVotos.size();i++){
//          window.draw(mapa->arrayVotos[i]);
//        }
        mapa->dibujaVotos(window);
        //dibujo los dos vectores de los enemigos
        for(int i=0; i<cuerpo->size(); i++){
            cuerpo->at(i)->draw(window);
        }
        for(int j=0; j<distancia->size(); j++){
           distancia->at(j)->draw(window);
        }
        
        
         //dibujo el jefe final
        boss->draw(window);
        
        //muro de bloqueo para pelea con jefe
        if(player->getSprite().getPosition().x>mapa->posxBoss-400){
            modoJefe=1; //En cuanto sobrepasa cierta area, empieza el modo jefe
            if(player->getSprite().getPosition().x>mapa->posxBoss-300){//La camara se bloquea
                camara->desplazamientoCamara=0;
            }
        }
        
        if(modoJefe==1){ //Entonces el muro se dibuja tooodo el rato...
            window.draw((*muroJefe));
            if(player->getSprite().getGlobalBounds().intersects(muroJefe->getGlobalBounds())){
                //...y tiene colisiones con el jugador para no dejarle volver atras
                std::cout<<"CHOQUE!"<<std::endl;
                player->posicionJugador.x=player->posicionJugador.x+5;
            }
        }
        
        
        mapa->dibujaPlataformas(window);
        //dibujo el personaje
        //player->draw(window);
        
        //Para eliminar los enemigos de los vectores
        if(player->politico==1 || player->politico == 4){
            if(player->eliminadoC!=-1){
                delete cuerpo->at(player->eliminadoC);
                cuerpo->erase(cuerpo->begin()+player->eliminadoC);
                player->eliminadoC=-1;
            }
            if(player->eliminadoA!=-1){
                delete distancia->at(player->eliminadoA);
                distancia->erase(distancia->begin()+player->eliminadoA);
                player->eliminadoA=-1;
            }
            if(player->bossTocado){
                boss->hp-=2;
                std::cout<<"el boss tiene"<<boss->hp<<std::endl;
                player->bossTocado = false;
            }
        }
        
        
        int i=0;
        //compruebo que los proyectiles del jugador se destruyen ya sea por que recorren una distancia determinadad
        //o porque golpean a los NPC. 
        //IMP si el proyectil del jugador colisiona con otro del NPC que ocurre? el mundo se destruiria y nada podria volver a ser como antes...
        for(i=0; i<player->proyectiles->size();i++){
            player->proyectiles->at(i)->dibuja(window);
            if(player->proyectiles->at(i)->destruir()){
                if(!player->proyectiles->empty()){
                    //Hay que comprobar que el vector no este vacio cuando quiera eliminar un objeto
                    delete player->proyectiles->at(i);
                    player->proyectiles->erase(player->proyectiles->begin()+i);
                }
                
            }else{
                for(int j=0; j<distancia->size(); j++){
                    if(player->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(distancia->at(j)->getSprite().getGlobalBounds())){
                        delete distancia->at(j);
                        distancia->erase(distancia->begin()+j);
                        distanciaAux->erase(distanciaAux->begin()+j);
                        player->enemigosEliminados++;
                        if(!player->proyectiles->empty()){
                            delete player->proyectiles->at(i);
                            player->proyectiles->erase(player->proyectiles->begin()+i);
                        }
                    }
                }
                for(int j=0; j<cuerpo->size(); j++){
                    if(player->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(cuerpo->at(j)->getSprite().getGlobalBounds())){
                        delete cuerpo->at(j);
                        cuerpo->erase(cuerpo->begin()+j);
                        cuerpoAux->erase(cuerpoAux->begin()+j);
                        player->enemigosEliminados++;
                        if(!player->proyectiles->empty()){
                            delete player->proyectiles->at(i);
                            player->proyectiles->erase(player->proyectiles->begin()+i);
                        }
                    }
                }
                if(player->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(boss->getSprite().getGlobalBounds())){
                    boss->hp-=1;
                    std::cout<<"el boss tiene"<<boss->hp<<std::endl;
                    if(!player->proyectiles->empty()){
                        delete player->proyectiles->at(i);
                        player->proyectiles->erase(player->proyectiles->begin()+i);
                    }
                }
            }
        }
        
        //AQUI IMPRIMO LOS PROYECTILES DE LOS ENEMIGOS
        int y=0, j=0;
        for(y=0; y<distancia->size(); y++){
            //imprimimos los proyectiles
            for(j=0; j<distancia->at(y)->proyectiles->size();j++){
                distancia->at(y)->proyectiles->at(j)->dibuja(window);
                if(distancia->at(y)->proyectiles->at(j)->destruir()){
                    if(!distancia->at(y)->proyectiles->empty()){
                        delete distancia->at(y)->proyectiles->at(j);
                        distancia->at(y)->proyectiles->erase(distancia->at(y)->proyectiles->begin()+j);
                        soundHurt.play();
                    }
                    
                }else{
                    if(distancia->at(y)->proyectiles->at(j)->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())){
                        std::cout<<"El proyectil ha danyado al juagdor"<<std::endl;
                        if(!distancia->at(y)->proyectiles->empty()){
                            delete distancia->at(y)->proyectiles->at(j);
                            distancia->at(y)->proyectiles->erase(distancia->at(y)->proyectiles->begin()+j);
                            soundHurt.play();
                        }
                        tiempo= relojGolpe.getElapsedTime().asSeconds();
                        player->golpeado=true;
                        
                        //player->vidas=player->vidas-1;
                        
                        if(player->seleccionJugador==1){
                            player->vidas=player->vidas-1;
                        }
                        
                        if(player->seleccionJugador==2){
                            player->vidasMiniaturas1=player->vidasMiniaturas1-1;
                            if(player->vidasMiniaturas1<0){
                                player->vidasMiniaturas1=0;
                            }
                            
                        }
                        
                        if(player->seleccionJugador==3){
                            player->vidasMiniaturas2=player->vidasMiniaturas2-1;
                            if(player->vidasMiniaturas2<0){
                                player->vidasMiniaturas2=0;
                            }
                            
                        }
                        
                        if(player->vidas<0)player->vidas=0;
                        if(player->vidasPrincipales<0)player->vidasPrincipales=0;
                        std::cout<<"El jugador ahora tiene: "<<player->vidas<<"vidas"<<std::endl;
                    }
                }
            }
            
        }
        j=0;
            for(j=0; j<boss->proyectiles->size();j++){
                boss->proyectiles->at(j)->dibuja(window);
                if(boss->proyectiles->at(j)->destruir()){
                    if(!boss->proyectiles->empty()){
                        delete boss->proyectiles->at(j);
                        boss->proyectiles->erase(boss->proyectiles->begin()+j);
                        soundHurt.play();
                    }
                    
                }else{
                    if(boss->proyectiles->at(j)->getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds())){
                        std::cout<<"El proyectil ha danyado al juagdor"<<std::endl;
                        if(!boss->proyectiles->empty()){
                            delete boss->proyectiles->at(j);
                            boss->proyectiles->erase(boss->proyectiles->begin()+j);
                            soundHurt.play();
                        }
                        tiempo= relojGolpe.getElapsedTime().asSeconds();
                        player->golpeado=true;
                        
                        //player->vidas=player->vidas-1;
                        
                        if(player->seleccionJugador==1){
                            player->vidas=player->vidas-2;
                        }
                        
                        if(player->seleccionJugador==2){
                            player->vidasMiniaturas1=player->vidasMiniaturas1-2;
                            if(player->vidasMiniaturas1<0){
                                player->vidasMiniaturas1=0;
                            }
                            
                        }
                        
                        if(player->seleccionJugador==3){
                            player->vidasMiniaturas2=player->vidasMiniaturas2-2;
                            if(player->vidasMiniaturas2<0){
                                player->vidasMiniaturas2=0;
                            }
                            
                        }
                        
                        if(player->vidas<0)player->vidas=0;
                        if(player->vidasPrincipales<0)player->vidasPrincipales=0;
                        std::cout<<"El jugador ahora tiene: "<<player->vidas<<"vidas"<<std::endl;
                    }
                }
            }
        
        
        //setteo la camara
        camara->draw(window, player);
        
        window.draw(camara->getHudVotos());
        window.draw(camara->getHudVotosValue());
        window.draw(camara->getContador());
        window.draw(camara->getContadorValue());
        
        if(player->seleccionJugador==2){
            window.draw(camara->getMiniatura1());
            window.draw(camara->getMiniatura1vida());
            camara->actualizarVidasMiniaturas(player->vidasMiniaturas1, player->politico, player->seleccionJugador);
            if(player->vidasMiniaturas1>0 || player->ultimo==2){
                player->draw(window);
                //delete *player->seleccionJugador=2;
            }
            /*if(player->vidasMiniaturas1==0){
                if(player->vidasMiniaturas2>0){
                    player->seleccionJugador=3;
                }
                if(player->vidasPrincipales!=0){
                    player->seleccionJugador=1;
                }
            }*/
            if(player->vidasMiniaturas1==0){
                //player->getSprite().getPosition().x;
                //player->velocidadMovimiento=0;
                //player->getSprite().setScale(100,100);
                player->posicionJugador.x=200;
                if(player->vidasMiniaturas2>0){
                    player->seleccionJugador=3;
                }
                
                if(player->vidasPrincipales>0){
                    player->seleccionJugador=1;
                }
                 
            }
            
        }
        
        if(player->seleccionJugador==3){
            window.draw(camara->getMiniatura2());
            window.draw(camara->getMiniatura2vida());
            camara->actualizarVidasMiniaturas(player->vidasMiniaturas2, player->politico, player->seleccionJugador);
            if(player->vidasMiniaturas2>0 || player->ultimo==3){
                player->draw(window);
                //delete *player->seleccionJugador=3; 
            }
            
            if(player->vidasMiniaturas2==0){
                //player->getSprite().getPosition().x;
                //player->velocidadMovimiento=0;
                //player->getSprite().setScale(100,100);
                player->posicionJugador.x=200;
                if(player->vidasMiniaturas1>0){
                    player->seleccionJugador=2;
                }
                
                if(player->vidasPrincipales>0){
                    player->seleccionJugador=1;
                } 
            }
            
        }
        
        window.draw(camara->getBarraVida());
        window.draw(camara->getVidas());
        window.draw(camara->getVidasPrincipales());
        
        if(player->seleccionJugador==1){
            window.draw(camara->getBarraVida());
            window.draw(camara->getVidas());
            window.draw(camara->getVidasPrincipales());
            camara->actualizarVidas(player->vidas, player->politico, player->seleccionJugador);
            camara->actualizarVidasPrincipales(player->vidasPrincipales, player->seleccionJugador);
            if(player->vidasPrincipales>0 && player->ultimo==1){
                //std::cout<<"MUERTOOOOOOOOO EL 11111111::::"<<player->vidasPrincipales<<std::endl;
                player->draw(window);
                //delete *player->seleccionJugador=1;
            }
            
            if(player->vidasPrincipales==0){
                //player->getSprite().getPosition().x;
                //player->velocidadMovimiento=0;
                //player->getSprite().setScale(100,100);
                player->posicionJugador.x=200;
                if(player->vidasMiniaturas1>0){
                    player->seleccionJugador=2;
                }
                
                if(player->vidasMiniaturas2>0){
                    player->seleccionJugador=3;
                } 
            }
        }
        
           
        camara->actualizarTiempo();
        //camara->actualizarVidas(player->vidas, player->politico, player->seleccionJugador);
        
        /*if(player->vidasPrincipales==0){
            player->vidasMiniaturas1=player->vidasMiniaturas1;
            if(player->vidasMiniaturas1==0){
                std::cout<<"MUERTOS TODOSSSSSSSSSS"<<std::endl;
                player->vidasMiniaturas2=player->vidasMiniaturas2;
                if(player->vidasMiniaturas2==0){
                    player->muerto=true;
                    std::cout<<"MUERTOS TODOSSSSSSSSSS"<<std::endl;
                }
            }
            //player->muerto=true;
            std::cout<<"MUERTOS TODOSSSSSSSSSS"<<std::endl;
        }*/
        
        //if(player->seleccionJugador==1){
            if(player->vidas==0){
                /*if(player->vidasPrincipales==0){
                    player->muerto=true;
                }*/
                
                /*if(player->vidasMiniaturas1==0){
                    player->muerto=true;
                }
                
                if(player->vidasMiniaturas2==0){
                    player->muerto=true;
                }
                 */
                //player->muerto=true;
                player->vidasPrincipales=player->vidasPrincipales-1;

                if(player->vidasPrincipales>0){//resucita con una vida menos
                    //player->muerto=false;
                    player->vidas=10;
                    player->posicionJugador.x=200;
                    camara->resetearCamara();
                }
            }
        
        /*if(player->vidasMiniaturas1==0){
            player->muerto=true;
        }
        
        if(player->vidasMiniaturas2==0){
            player->muerto=true;
        }
        */
        
        
        
        
        
        //camara->actualizarVidasPrincipales(player->vidasPrincipales, player->seleccionJugador);
        
        //}
        
        /*if(player->seleccionJugador==2 || player->seleccionJugador==3){
            player->vidasPrincipales=0;
        }*/
        
        
       
        //std::cout<<"Cout para saber en que linea a veces me peta (Alfonso)"<<std::endl; 
        for(int i=0; i<mapa->arrayVotos->size(); i++){
            if(mapa->arrayVotos->at(i)->getGlobalBounds().intersects(player->getSprite().getGlobalBounds())){
                std::cout<<"El personaje ha tocado un voto"<<std::endl;
                delete mapa->arrayVotos->at(i);
                mapa->arrayVotos->erase(mapa->arrayVotos->begin()+i);
                //Aitor, aqui tienes que hacer una variable que incremente, asi te mostrara los votos que llevas
                camara->sumaVotos(1);
                soundSobre.play();
            }
        }
        if(boss->hp < 1){
            camara->cartelFinal(window, player);
        }
        //camara->cartelFinal(window, player);
        //camara->cartelGameOver(window, player);
        if(player->muerto){     //CONTORLA QUE APAREZCA EL CARTEL DE GAME OVER
            camara->cartelGameOver(window, player);
            musica.stop();
            std::cout<<"HA MUEEEEERTO!!!"<<std::endl;
        }
        
        window.display();
    }
    std::cout<<"Cout para saber en que linea a veces me peta (Alfonso)2"<<std::endl;

    return 0;
}