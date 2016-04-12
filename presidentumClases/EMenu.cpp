/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.cpp
 * Author: alfon
 * 
 * Created on 14 de marzo de 2016, 11:05
 */

#include "EMenu.h"
#include <iostream>
#include <sstream>

EMenu::EMenu(float width, float height) {
    
    
    
    if(!fuente.loadFromFile("resources/alterebro-pixel-font.ttf")){
        exit(0);
    }
    int i=0;
    for(i=0; i<6; i++){
        menu.push_back(new sf::Text("elemento", fuente));
        menu[i]->setColor(sf::Color::White);
        menu[i]->setCharacterSize(50);
        
    }
    menu[0]->setColor(sf::Color::Red);
    menu[0]->setString("Nueva Partida");
    menu[0]->setPosition(sf::Vector2f(width*0.45, height/(MAX_NUMBER_OF_ITEMS) *1));
    
    menu[1]->setString("Cargar Partida");
    menu[1]->setPosition(sf::Vector2f(width*0.45, height/(MAX_NUMBER_OF_ITEMS) *1.75));
    
    menu[2]->setString("Controles");
    menu[2]->setPosition(sf::Vector2f(width*0.45, height/(MAX_NUMBER_OF_ITEMS) *2.5));
    
    menu[3]->setString("Opciones");
    menu[3]->setPosition(sf::Vector2f(width*0.45, height/(MAX_NUMBER_OF_ITEMS) *3.25));
    
    sf::String stringCreditos(L"Créditos");
    menu[4]->setString(stringCreditos);
    menu[4]->setPosition(sf::Vector2f(width*0.45, height/(MAX_NUMBER_OF_ITEMS) *4));
    
    menu[5]->setString("Salir del juego");
    menu[5]->setPosition(sf::Vector2f(width*0.45, height/(MAX_NUMBER_OF_ITEMS) *4.75));
    
    for(i=0; i<5; i++){
        menuInGame.push_back(new sf::Text("elemento", fuente)); 
        menuInGame[i]->setColor(sf::Color::White);
        menuInGame[i]->setCharacterSize(50);
    }    
    
    menuInGame[0]->setColor(sf::Color::Red);
    menuInGame[0]->setString("Continuar");
    menuInGame[0]->setPosition(sf::Vector2f(width*0.45,125));
    
    menuInGame[1]->setString("Guardar Partida");
    menuInGame[1]->setPosition(sf::Vector2f(width*0.42, 200));
    
    menuInGame[2]->setString("Controles");
    menuInGame[2]->setPosition(sf::Vector2f(width*0.45, 275));
    
    menuInGame[3]->setString("Opciones");
    menuInGame[3]->setPosition(sf::Vector2f(width*0.45, 350));
    
    menuInGame[4]->setString("Volver al menu principal");
    menuInGame[4]->setPosition(sf::Vector2f(width*0.38, 425));
    
    for(i=0; i<2; i++){
        guardarsino.push_back(new sf::Text("elemento", fuente)); 
        sobreescribirsino.push_back(new sf::Text("elemento", fuente)); 
        guardarsino[i]->setCharacterSize(50);
        sobreescribirsino[i]->setCharacterSize(50);
    }   
    
    guardarsino[0]->setColor(sf::Color::Red);
    guardarsino[0]->setString("Si");
    guardarsino[0]->setPosition(sf::Vector2f(400,225));
    
    guardarsino[1]->setString("No");
    guardarsino[1]->setPosition(sf::Vector2f(600, 225));
    
    sobreescribirsino[0]->setColor(sf::Color::Red);
    sobreescribirsino[0]->setString("Si");
    sobreescribirsino[0]->setPosition(sf::Vector2f(400,345));
    
    sobreescribirsino[1]->setString("No");
    sobreescribirsino[1]->setPosition(sf::Vector2f(600, 345));
    
    for(i=0; i<3; i++){
        opcionesMenu.push_back(new sf::Text("elemento", fuente)); 
        
        opcionesMenu[i]->setCharacterSize(50);
    }   
    
    opcionesMenu[0]->setColor(sf::Color::Red);
    opcionesMenu[0]->setString("Control de sonido");
    opcionesMenu[0]->setPosition(sf::Vector2f(280,200));
    
    opcionesMenu[1]->setString("Control de musica");
    opcionesMenu[1]->setPosition(sf::Vector2f(280, 300));
    
    opcionesMenu[2]->setString("Volver");
    opcionesMenu[2]->setPosition(menuInGame[4]->getPosition().x, menuInGame[4]->getPosition().y);
    

    
    opcionMenuppal=6;//para saber que opcion he seleccionado en el menuprincipal
    opcionMenuInGame=5;//para saber que opcion he seleccionado en el menu in game
    selectedItemIndex=0;//iterador para moverse hacia arriba y hacia abajo en los menus
    selectedItemIndexInPausa=0;
    selectedItemIndexGuardar=0;
    selectedItemIndexOpciones=0;
    selectedItemIndexSobreescribir=2;
    
    mostrarMenuppal = true;//con esto sabemos que estamos en el menu principal
    /*
    //Aqui cargo el fondo para poder lanzar el juego. Metodo: nuevaPartida
    sf::Texture *texturaBackground;
    if (!texturaBackground->loadFromFile("resources/background.jpg"))
    {
        std::cerr << "Error cargando la imagen background.jpg";
        exit(0);
    }    
    std::cout<<"hasta aqui llgo en la funcion nuevaPartida"<<std::endl;
    background =new sf::Sprite(*texturaBackground);
    background->setPosition(0.0, 0.0);
    
    */
    
    if (!texturaBackground.loadFromFile("resources/background.jpg"))
    {
        std::cerr << "Error cargando la imagen background.jpg";
        exit(0);
    }
    background = new sf::Sprite(texturaBackground);

    //booleanos para controlar en que aprte estoy del juego.
    enPartida = false;
    enCargar = false;
    enOpciones = false;
    enCreditos = false;
    enControles = false;
    enPausa=false;
    guardando=false;
    sobreescrito=false;
    enSonido=false;
    enMusica=false;
    pausaopciones=false;
            
            
    //para los metodos submenu y guardar
    FondomenuInPausa = new sf::RectangleShape(sf::Vector2f(550, 400));
    fondo = new sf::RectangleShape(sf::Vector2f(width, height));
    transparente= new sf::Color(255,255,255,128);
    FondomenuInPausa->setFillColor(sf::Color::Black);
    FondomenuInPausa->setPosition((width-FondomenuInPausa->getSize().x)/2, 100);
    fondo->setFillColor(*transparente);
    
    //para el metodo guardar
   
    interrogacion=L"¿";
    desea = new sf::Text(interrogacion+"Desea guardar la partida?", fuente);
    desea->setPosition(350, 150);
    desea->setCharacterSize(50);
    
    //para el metodo sobreescribir
    sobreescribirText = new sf::Text("Ya hay una partida guardada,", fuente);
    sobreescribirText->setPosition(350, 270);
    sobreescribirText->setCharacterSize(50);
    sobreescribir2Text = new sf::Text(interrogacion+"desea sobreescribirla?", fuente);
    sobreescribir2Text->setPosition(350, 305);
    sobreescribir2Text->setCharacterSize(50);
    sobrescrita = new sf::Text("Partida guardada correctamente", fuente);
    sobrescrita->setPosition(325, 400);
    sobrescrita->setCharacterSize(50);
    
    //metodo controles
    
    izquierda = new sf::Text("Moverse a la izquierda: Left/A", fuente);
    derecha = new sf::Text("Moverse a la derecha: Right/D", fuente);
    saltar = new sf::Text("Saltar: Up/W", fuente);
    golpear = new sf::Text("Golpear o disparar: Barra espaciadora", fuente);
    personaje1 = new sf::Text("Intercambiar personaje por el personaje principal: 1", fuente);
    personaje2 = new sf::Text("Intercambiar personaje por el primero en reserva: 2", fuente);
    personaje3 = new sf::Text("Intercambiar personaje por el segundo en reserva: 3", fuente);
    
    izquierda->setPosition(width*0.2, 100);
    izquierda->setCharacterSize(50);
    derecha->setPosition(width*0.2, 150);
    derecha->setCharacterSize(50);
    saltar->setPosition(width*0.2, 200);
    saltar->setCharacterSize(50);
    golpear->setPosition(width*0.2, 250);
    golpear->setCharacterSize(50);
    personaje1->setPosition(width*0.2, 300);
    personaje1->setCharacterSize(50);
    personaje2->setPosition(width*0.2, 350);
    personaje2->setCharacterSize(50);
    personaje3->setPosition(width*0.2, 400);
    personaje3->setCharacterSize(50);
    
    //para creditos
    textocreditos = new sf::Text("Aqui apareceran los creditos", fuente);
    textocreditos->setPosition(width*0.3, height/2);
    textocreditos->setCharacterSize(50);
    
    //para cargar
    textoCargarPartida = new sf::Text("Aqui vendria la partida cargada", fuente); //aqui irian las lineas del layout de cargar partida
    textoCargarPartida->setPosition(width/2, height/2);
    textoCargarPartida->setCharacterSize(50);
    
    //opciones
    barrasonido=new sf::RectangleShape(sf::Vector2f(210, 10));
    barrasonido->setPosition(520, 235);
    barramusica=new sf::RectangleShape(sf::Vector2f(210, 10));
    barramusica->setPosition(520, 335);
    tiradorsonido=new sf::RectangleShape(sf::Vector2f(10, 25));
    tiradorsonido->setPosition(620, 228);
    tiradorsonido->setFillColor(sf::Color::Blue);
    tiradormusica=new sf::RectangleShape(sf::Vector2f(10, 25));
    tiradormusica->setPosition(620, 328);
    tiradormusica->setFillColor(sf::Color::Blue);
    valorsonido = new sf::Text("50", fuente);
    valorsonido->setPosition(745, 210);
    valorsonido->setCharacterSize(40);
       
    valormusica = new sf::Text("50", fuente);
    valormusica->setPosition(745, 310);
    valormusica->setCharacterSize(40);
        
    
}

EMenu::EMenu(const EMenu& orig) {
}

EMenu::~EMenu() {
}

int EMenu::run(sf::RenderWindow &window){
    
    //buclue principal del juego  
    while(window.isOpen()){
    
        sf::Event event;
        while(window.pollEvent(event)){ 
            
            teclas(window, event); //llamamos a la funcion teclas
        
        }
        
        render(window); //llamamos a la funcion render

    }
  
    return 0;
    
}

void EMenu::render(sf::RenderWindow &window){
    
    //aqui mostramos en la ventana las diferentes opciones
    window.clear();
    if(mostrarMenuppal){
        //aqui estamos en el menu principal
        reinicio();
        //dibujamos el menu principal
        draw(window, menu);
        if(opcionMenuppal!=6){
            //actualizamos el valor de mostrar menuppal para que no se muestre ya que hemos pulsado la tecla enter/espacio para poder seleccionar una opcion
            mostrarMenuppal=false;
        } 
    }else{
        if(opcionMenuppal==0){
            //dibujamos el juego porque hemos pulsado nueva partida
            enPartida=true;
            nuevaPartida(window);
            if(enPausa){
                //si estoy pausado me pinta el menuingame
                submenu(window); 
                if(opcionMenuInGame==0){
                    //entramos aqui si hemos pulsado continuar en el menu de pausa
                    enPausa=false;
                    opcionMenuInGame=5;
                }if(opcionMenuInGame==1){
                    //estamos en el layout de guardar partida
                    enPausa=true;
                    guardar(window);
                    if(guardando){
                        //ahora nos pregunta si queremos sobreescribir la partida en caso de que haya una partda guardad
                        sobreescribir(window);
                        if(sobreescrito){
                            //se ha sobreeescrito correctamente la partida
                            sobreescritocorrectamente(window);
                        }
                    }
                }
            }
            
        }
        if(opcionMenuppal==1){
            //mostramos la partida cargada
            cargarPartida(window);
        }
        if(opcionMenuppal==2 || enControles){
            //dibujamos los controles
            enControles=true;
            controles(window);
            
        }
        if(opcionMenuppal==3 || enOpciones){
            //dibuamos las copiones tanto inGame como desde el menu principal
            opciones(window);
            enOpciones=true;
            /*std::cout<<"estoy o no en pausa en el if"<<std::endl;
            std::cout<<enPausa<<std::endl;*/
        }
        if(opcionMenuppal==4 || enCreditos){
            //dibujamos los creditos
            creditos(window);
            enCreditos=true;
        }
        if(opcionMenuppal==5){
            //cerramos la ventana
            window.close();
        }   
    }
    
    window.display();

}

void EMenu::draw(sf::RenderWindow& window, std::vector<sf::Text*> menu){

    //con esto dibujamos en pantalla los diferentes menus
    for(sf::Text* i : menu){
        window.draw(*i);
    }
    
}

void EMenu::teclas(sf::RenderWindow& window, sf::Event event){
    
    //con este metodo controlamos los eventos de las teclas pulsadsa
    int sonido=520;
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
                case sf::Keyboard::Right:
                    if(opcionMenuInGame==1){
                        //estoy guardando la partida
                        if(!guardando){
                            //muevo el cursor en el vector de si o no mientras estoy guardando
                            moveDown(guardarsino, selectedItemIndexGuardar);
                        }else{
                            //estoy sobreescribiendo la partida y me muevo para la siguiente posicion
                            moveDown(sobreescribirsino, selectedItemIndexSobreescribir);
                        }
                    }
                    if(enOpciones){
                        //estoy en el menu opciones tanto del menu principal como la del menu pausa
                        if(GetPressedItemOpciones()==0 && tiradorsonido->getPosition().x<=715){
                            //controlo que el tiradorsonido no se salga de su posicion, muevo el tirador y setteo su valor numero para mostrarlo por pantalla
                            tiradorsonido->move(5,0);
                            int valordelonido=tiradorsonido->getPosition().x-sonido;
                            std::stringstream po;
                            valordelonido=valordelonido/2;
                            po<<valordelonido;
                            valorsonido->setString(po.str());
                        }
                        if(GetPressedItemOpciones()==1 && tiradormusica->getPosition().x<=715){
                            //controlo que el tiraormusica no se salga de su posicion, muevo el tirador y setteo su valor numero para mostrarlo por pantalla
                            tiradormusica->move(5,0);
                            int valordelonido=tiradormusica->getPosition().x-sonido;
                            std::stringstream po;
                            valordelonido=valordelonido/2;
                            po<<valordelonido;
                            valormusica->setString(po.str());
                        }
                    }
                break;

                case sf::Keyboard::Left:
                    if(opcionMenuInGame==1){
                        //estoy guardando la partida
                        if(!guardando){
                            //muevo el cursor en el vector de si o no mientras estoy guardando
                            moveUp(guardarsino, selectedItemIndexGuardar);
                        }else{
                            //estoy sobreescribiendo la partida y me muevo para la siguiente posicion
                            moveUp(sobreescribirsino, selectedItemIndexSobreescribir);
                        }
                    }
                    if(enOpciones){
                        //estoy en el menu opciones tanto del menu principal como la del menu pausa
                        if(GetPressedItemOpciones()==0 && tiradorsonido->getPosition().x>=525){
                            tiradorsonido->move(-5,0);
                            
                            int valordelonido=(sonido-tiradorsonido->getPosition().x)*(-1);
                            std::stringstream po;
                            valordelonido=valordelonido/2;
                            po<<valordelonido;
                            valorsonido->setString(po.str());
                        }
                        if(GetPressedItemOpciones()==1 && tiradormusica->getPosition().x>=525){
                            tiradormusica->move(-5,0);
                            int valordelonido=(sonido-tiradormusica->getPosition().x)*(-1);
                            std::stringstream po;
                            valordelonido=valordelonido/2;
                            po<<valordelonido;
                            valormusica->setString(po.str());
                        }
                    }
                break;

                case sf::Keyboard::Up:
                    //nos movemos hcia arriba segun en el menu en el que estemos
                    if(mostrarMenuppal){
                        moveUp(menu, selectedItemIndex);
                    }
                    if(enPausa){
                        moveUp(menuInGame, selectedItemIndexInPausa);
                    }
                    if(enOpciones){
                        moveUp(opcionesMenu, selectedItemIndexOpciones);
                    }
                break;

                case sf::Keyboard::Down:
                    //nos movemos hacia abajo segun en el menu en el qe nos encontremos
                    if(mostrarMenuppal){
                        moveDown(menu, selectedItemIndex);
                    }
                    if(enPausa){
                        moveDown(menuInGame, selectedItemIndexInPausa);
                    }
                    if(enOpciones){
                        moveDown(opcionesMenu, selectedItemIndexOpciones);
                        selectedItemIndexOpciones=GetPressedItemOpciones();
                    }
                break;
                    
                case sf::Keyboard::Return:
                case sf::Keyboard::Space:                    
                    if(mostrarMenuppal){
                        opcionMenuppal=GetPressedItem();
                        if(opcionMenuppal==0){
                            std::cout<<"estoy dentro de Nuva Partida"<<std::endl;
                            std::cout<<enPausa<<std::endl;
                        }
                    }
                    if(enPausa){
                        //estamos en pausa
                        if(opcionMenuInGame!=1){
                            //NO hemos presionado 'continuar'
                            if(GetPressedItemInPausa()==2){
                                //estamos en controles
                                enControles=true;
                                selectedItemIndexInPausa=0;
                                int i=0;
                                //reseteamos los colores del menu
                                for(i=0; i<menuInGame.size(); i++){
                                    if(GetPressedItem()==i){
                                        menuInGame[i]->setColor(sf::Color::Red);
                                    }else{
                                        menuInGame[i]->setColor(sf::Color::White);
                                    }   
                                }
                            }
                            if(GetPressedItemInPausa()==3){
                                //estoy en Opciones
                                enOpciones=true;
                                std::cout<<"haciendo el ridiculo"<<std::endl;
                                pausaopciones=true;
                                std::cout<<"Estoy en el menu opciones"<<std::endl;
                                selectedItemIndexInPausa=0;
                                if(GetPressedItemOpciones()==2 && pausaopciones){
                                    //salimos al menu de pausa
                                    mostrarMenuppal=false;
                                    enOpciones=false;
                                    pausaopciones=false;
                                }
                            }
                            if(GetPressedItemInPausa()==4){
                                ///he presionado salir al menu principal
                                reinicio();
                                mostrarMenuppal=true;
                                enPausa=false;
                                enPartida=false;
                                opcionMenuppal=6;
                                selectedItemIndexInPausa=0;
                                //setteamos el menu para que los colores se muestren correctamente
                                int i=0;
                                    for(i=0; i<menuInGame.size(); i++){
                                        if(GetPressedItem()==i){
                                            menuInGame[i]->setColor(sf::Color::Red);
                                        }else{
                                            menuInGame[i]->setColor(sf::Color::White);
                                        }   
                                    }
                            }
                            //setteo de diferentes varaibles para poder volver al menu
                            opcionMenuInGame=GetPressedItemInPausa();
                            selectedItemIndexInPausa=0;
                            selectedItemIndexGuardar=0;
                            selectedItemIndexSobreescribir=0;
                            guardarsino[0]->setColor(sf::Color::Red);
                            guardarsino[1]->setColor(sf::Color::White);
                            sobreescribirsino[0]->setColor(sf::Color::Red);
                            sobreescribirsino[1]->setColor(sf::Color::White);
                        }else{
                            //he seleccionado guardar partida
                            if(guardando && GetPressedItemSobreescribir()==0 && !sobreescrito){
                                //sobreescribirmos
                                sobreescrito=true;
                            }
                            if(GetPressedItemGuardar()==0){
                                //hemos presionado que queremos guardar
                                guardando=true;
                            } 
                            
                        }
                    }
                    if(enOpciones){
                        //estmoas en opciones
                        if(GetPressedItemOpciones()==0){
                            //estamos en sonido
                           enSonido=true; 
                        }
                        if(GetPressedItemOpciones()==1){
                            //estamos en musica
                            enMusica=true;
                        }
                        if(GetPressedItemOpciones()==2 && !pausaopciones && !enPausa){
                            //salimos del menu opciones al menuy principal
                            mostrarMenuppal=true;
                            pausaopciones=false;
                            enOpciones=false;
                            opcionMenuppal=6;
                            //selectedItemIndexOpciones=0;
                            int i=0;
                            //reseteamos el menu
                            for(i=0; i<opcionesMenu.size(); i++){
                                if(i==0){
                                    opcionesMenu[i]->setColor(sf::Color::Red);
                                }else{
                                    opcionesMenu[i]->setColor(sf::Color::White);
                                }   
                            }
                            
                        }
                        selectedItemIndexOpciones=GetPressedItemOpciones();
                        
                    }if(GetPressedItemOpciones()==2){
                        //salimos al menu de pausa
                        enOpciones=false;
                        enPausa=true;
                        pausaopciones=false;
                        selectedItemIndexOpciones=0;
                        int i=0;
                        //reseteamos el menuIKnGame y el menu de opciones
                        for(i=0; i<opcionesMenu.size(); i++){
                            if(i==0){
                                opcionesMenu[i]->setColor(sf::Color::Red);
                            }else{
                                opcionesMenu[i]->setColor(sf::Color::White);
                            }   
                        }
                        for(i=0; i<menuInGame.size(); i++){
                            if(i==0){
                                menuInGame[i]->setColor(sf::Color::Red);
                            }else{
                                menuInGame[i]->setColor(sf::Color::White);
                            }   
                        }
                    }
                    
   
                break;

                //Tecla ESC para salir
                case sf::Keyboard::Escape:
                    if(mostrarMenuppal){
                        //si estoy en el menu principal y pulso ESC salgo de la pantalla
                        window.close();
                    }
                    if(enPartida){
                        //estoy en eljuego
                        if(enPausa){
                            //estoy en pausa
                            selectedItemIndexInPausa=0;
                            int i=0;
                            //seteto el menu
                            for(i=0; i<menuInGame.size(); i++){
                                if(GetPressedItem()==i){
                                    menuInGame[i]->setColor(sf::Color::Red);
                                }else{
                                    menuInGame[i]->setColor(sf::Color::White);
                                }   
                            }
                            if(opcionMenuInGame==1){
                                //salgo de la sopcion guardar y vuelvo al emnu en pausa
                                opcionMenuInGame=5;
                                guardando=false;
                                sobreescrito=false;
                            }else{
                                if(opcionMenuInGame==2){
                                    //salgo de controles
                                    enControles=false;
                                }
                                if(opcionMenuInGame==3 && pausaopciones){
                                    //salgo de opciones para ir al menuInGame
                                    enOpciones=false;
                                    pausaopciones=false;
                                    enPausa=true;
                                    
                                }
                                else{
                                    enPausa=false;
                                    std::cout<<"Ya no estoy en pausa"<<std::endl;
                                }
                               
                            }
                            
                        }else{
                            //me meto en pausa
                            /*std::cout<<"Estoy en pausa, claro, donde voy a estar sino"<<std::endl;
                            std::cout<<enPartida<<std::endl;
                            std::cout<<enCargar<<std::endl;
                            std::cout<<enOpciones<<std::endl;
                            std::cout<<enCreditos<<std::endl;
                            std::cout<<enControles<<std::endl;
                            std::cout<<enPausa<<std::endl;
                            std::cout<<guardando<<std::endl;
                            std::cout<<sobreescrito<<std::endl;
                            std::cout<<enSonido<<std::endl;
                            std::cout<<enMusica<<std::endl;
                            std::cout<<pausaopciones<<std::endl;
                            std::cout<<"impresas todas las variables booleanas"<<std::endl;*/
                            enPausa=true;
                           
                        }  
                    }  
                    if(enControles){
                        if(enPausa){
                            enControles=false;
                        }else{
                            mostrarMenuppal=true;
                            enControles=false;
                            opcionMenuppal=6;
                            
                        }
                    }
                    if(enOpciones && !pausaopciones){
                        enOpciones=false;
                        opcionMenuppal=6;
                        mostrarMenuppal=true;
                        selectedItemIndexOpciones=0;
                    }
                    if(enCreditos){
                        enCreditos=false;
                        opcionMenuppal=6;
                        mostrarMenuppal=true;
                    }
                    if(pausaopciones){
                        pausaopciones=false;
                        std::cout<<"acabo de pulsar ESC en las opciones"<<std::endl;
                        enOpciones=false;
                        std::cout<<enOpciones<<std::endl;
                        std::cout<<opcionMenuppal<<std::endl;
                        int i=0;
                            for(i=0; i<menuInGame.size(); i++){
                                if(GetPressedItem()==i){
                                    menuInGame[i]->setColor(sf::Color::Red);
                                }else{
                                    menuInGame[i]->setColor(sf::Color::White);
                                }   
                            }
                    }

                break;

                //Cualquier tecla desconocida se imprime por pantalla su código
                default:
                    std::cout << event.key.code << std::endl;
                break;

            }

    }
    
}

void EMenu::moveUp(std::vector<sf::Text*> menu, int &iterator){
    
    //con este metodo me desplazo hacia arriba en las opciones, 3, 2, 1
    if(iterator-1>=0){
        menu[iterator]->setColor(sf::Color::White);
        iterator--;
        menu[iterator]->setColor(sf::Color::Red);
    }    
}

void EMenu::moveDown(std::vector<sf::Text*> menu, int &iterator){
    
    //con este metodo me desplazo hacia abajo en el menu de opciones, 1, 2, 3
    if(iterator+1<menu.size()){
        menu[iterator]->setColor(sf::Color::White);
        iterator++;
        menu[iterator]->setColor(sf::Color::Red);
    }
}

void EMenu::nuevaPartida(sf::RenderWindow &window){
    
    //Aqui cargo el fondo para poder lanzar el juego. Metodo: nuevaPartida
    window.draw(*background);

}

void EMenu::submenu(sf::RenderWindow& window){
    
    //imprime el recuadro de pausa y el menu
    window.draw(*fondo);//para poder una transparencia
    window.draw(*FondomenuInPausa);
    draw(window, menuInGame);
    //std::cout<<"estoy aqui, en el metodo submenu"<<std::endl;

}

void cargartextura(sf::Texture textura, sf::Sprite &sprite){
    //metodo que no he de usar porque cargo la textura en el contructor
}

void EMenu::guardar(sf::RenderWindow &window){
 
    //pregunta si queremos guardar la partida
    window.draw(*FondomenuInPausa);
    window.draw(*desea);
    window.draw(*guardarsino[0]);
    window.draw(*guardarsino[1]);
    
}

void EMenu::sobreescribir(sf::RenderWindow& window){
   
    //pregunta si queremos sobreescribir la partida
    window.draw(*sobreescribirText);
    window.draw(*sobreescribir2Text);
    window.draw(*sobreescribirsino[0]);
    window.draw(*sobreescribirsino[1]);
    
}

void EMenu::sobreescritocorrectamente(sf::RenderWindow &window){
    
    //metodo que muestra que la partida se ha guardado correctamente
    window.draw(*sobrescrita);

}

void EMenu::controles(sf::RenderWindow& window){

    //mostramos los controles, la proxima vez se mostrara una imagen
    window.clear();
    window.draw(*izquierda);
    window.draw(*derecha);
    window.draw(*saltar);
    window.draw(*golpear);
    window.draw(*personaje1);
    window.draw(*personaje2);
    window.draw(*personaje3);
    
}

void EMenu::opciones(sf::RenderWindow& window){
    
    

    if(pausaopciones){
        window.draw(*fondo);
        window.draw(*FondomenuInPausa);
    }
    draw(window, opcionesMenu);
    window.draw(*valorsonido);
    window.draw(*valormusica);
    window.draw(*barrasonido);
    window.draw(*barramusica);
    window.draw(*tiradorsonido);
    window.draw(*tiradormusica);
 
    
}

void EMenu::creditos(sf::RenderWindow& window){
   
    //mostramos los creditos
    window.draw(*textocreditos);    
    
}

void EMenu::cargarPartida(sf::RenderWindow &window){

    //cargamos la partida guardada
    window.clear();
    window.draw(*textoCargarPartida);
 
}

void EMenu::reinicio(){
 
    //reiniciamos las variables booleanas
    enPartida = false;
    enCargar = false;
    enOpciones = false;
    enCreditos = false;
    enControles = false;
    enPausa=false;
    guardando=false;
    sobreescrito=false;
    enSonido=false;
    enMusica=false;
    pausaopciones=false;
}