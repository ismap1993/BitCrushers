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

#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height) {
    
    
    
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
    opcionesMenu[0]->setPosition(sf::Vector2f(300,200));
    
    opcionesMenu[1]->setString("Control de musica");
    opcionesMenu[1]->setPosition(sf::Vector2f(300, 300));
    
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
    FondomenuInPausa = new sf::RectangleShape(sf::Vector2f(500, 400));
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
    barrasonido=new sf::RectangleShape(sf::Vector2f(200, 10));
    barrasonido->setPosition(550, 235);
    barramusica=new sf::RectangleShape(sf::Vector2f(200, 10));
    barramusica->setPosition(550, 335);
    tiradorsonido=new sf::RectangleShape(sf::Vector2f(10, 25));
    tiradorsonido->setPosition(650, 228);
    tiradorsonido->setFillColor(sf::Color::Blue);
    tiradormusica=new sf::RectangleShape(sf::Vector2f(10, 25));
    tiradormusica->setPosition(650, 328);
    tiradormusica->setFillColor(sf::Color::Blue);
    
    
}

Menu::Menu(const Menu& orig) {
}

Menu::~Menu() {
}

int Menu::run(sf::RenderWindow &window){
    
      
    while(window.isOpen()){
        
       
        sf::Event event;
        while(window.pollEvent(event)){ 
            
            teclas(window, event);
        }
        
        
        render(window);

    }
    
    
  
    return 0;
}

void Menu::render(sf::RenderWindow &window){
    window.clear();
    if(mostrarMenuppal){
        reinicio();
        
        draw(window, menu);
        if(opcionMenuppal!=6){
            //actualizamos el valor de mostrar menuppal para que no se muestre
            mostrarMenuppal=false;
        } 
    }else{
        if(opcionMenuppal==0){
            //dibujamos el juego
            enPartida=true;
            nuevaPartida(window);
            if(enPausa){
                //si estoy pausado me pinta el menuingame
                submenu(window); 
                if(opcionMenuInGame==0){
                    enPausa=false;
                    opcionMenuInGame=5;
                }if(opcionMenuInGame==1){
                    enPausa=true;
                    guardar(window);
                    if(guardando){
                        sobreescribir(window);
                        if(sobreescrito){
                            sobreescritocorrectamente(window);
                        }
                    }
                }
            }
            
        }
        if(opcionMenuppal==1){
            cargarPartida(window);
        }
        if(opcionMenuppal==2 || enControles){
            //dibujamos el juego
            enControles=true;
            controles(window);
            
        }
        if(opcionMenuppal==3 || enOpciones){
            opciones(window);
            enOpciones=true;
            /*std::cout<<"estoy o no en pausa en el if"<<std::endl;
            std::cout<<enPausa<<std::endl;*/
        }
        if(opcionMenuppal==4 || enCreditos){
            creditos(window);
            enCreditos=true;
        }
        if(opcionMenuppal==5){
            window.close();
        }   
    }
    //estoy mostrando la opcion seleccionada en el menu principal
    window.display();
}

void Menu::draw(sf::RenderWindow& window, std::vector<sf::Text*> menu){

    for(sf::Text* i : menu){
        window.draw(*i);
    }
}

void Menu::teclas(sf::RenderWindow& window, sf::Event event){
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
                            moveDown(guardarsino, selectedItemIndexGuardar);
                        }else{
                            moveDown(sobreescribirsino, selectedItemIndexSobreescribir);
                        }
                    }
                    if(enOpciones){
                       
                        if(GetPressedItemOpciones()==0 && tiradorsonido->getPosition().x<=735){
                            tiradorsonido->move(5,0);
                        }
                        if(GetPressedItemOpciones()==1 && tiradormusica->getPosition().x<=735){
                            tiradormusica->move(5,0);
                        }
                    }
                break;

                case sf::Keyboard::Left:
                    if(opcionMenuInGame==1){
                        //estoy guardando la partida
                        if(!guardando){
                            moveUp(guardarsino, selectedItemIndexGuardar);
                        }else{
                            moveUp(sobreescribirsino, selectedItemIndexSobreescribir);
                        }
                    }
                    if(enOpciones){
                        
                        if(GetPressedItemOpciones()==0 && tiradorsonido->getPosition().x>=555){
                            tiradorsonido->move(-5,0);
                        }
                        if(GetPressedItemOpciones()==1 && tiradormusica->getPosition().x>=555){
                            tiradormusica->move(-5,0);
                        }
                    }
                break;

                case sf::Keyboard::Up:
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
                        if(opcionMenuInGame!=1){
                            if(GetPressedItemInPausa()==2){
                                enControles=true;
                                selectedItemIndexInPausa=0;
                                int i=0;
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
                                std::cout<<GetPressedItemOpciones()<<std::endl;
                                std::cout<<enPausa<<std::endl;
                                std::cout<<enOpciones<<std::endl;
                                
                                if(GetPressedItemOpciones()==2 && pausaopciones){
                                    mostrarMenuppal=false;
                                    enOpciones=false;
                                    pausaopciones=false;
                                    std::cout<<"debo salir al menu de pausa"<<std::endl;
                                }
                                
                                
                                
                            }
                            if(GetPressedItemInPausa()==4){
                                std::cout<<"he presionado salir al menu principal"<<std::endl;
                                reinicio();
                                mostrarMenuppal=true;
                                enPausa=false;
                                enPartida=false;
                                opcionMenuppal=6;
                                selectedItemIndexInPausa=0;
                                int i=0;
                                    for(i=0; i<menuInGame.size(); i++){
                                        if(GetPressedItem()==i){
                                            menuInGame[i]->setColor(sf::Color::Red);
                                        }else{
                                            menuInGame[i]->setColor(sf::Color::White);
                                        }   
                                    }
                            }
                            opcionMenuInGame=GetPressedItemInPausa();
                            selectedItemIndexInPausa=0;
                            selectedItemIndexGuardar=0;
                            selectedItemIndexSobreescribir=0;
                            guardarsino[0]->setColor(sf::Color::Red);
                            guardarsino[1]->setColor(sf::Color::White);
                            sobreescribirsino[0]->setColor(sf::Color::Red);
                            sobreescribirsino[1]->setColor(sf::Color::White);
                        }else{
                            if(guardando && GetPressedItemSobreescribir()==0 && !sobreescrito){
                                
                                sobreescrito=true;
                            }
                            if(GetPressedItemGuardar()==0){
                                guardando=true;
                            } 
                            
                        }
                    }
                    if(enOpciones){
                        if(GetPressedItemOpciones()==0){
                           enSonido=true; 
                        }
                        if(GetPressedItemOpciones()==1){
                            enMusica=true;
                        }
                        if(GetPressedItemOpciones()==2 && !pausaopciones && !enPausa){
                            mostrarMenuppal=true;
                            pausaopciones=false;
                            enOpciones=false;
                            opcionMenuppal=6;
                            //selectedItemIndexOpciones=0;
                            int i=0;
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
                        std::cout<<"a ver si ahora al darle a volver sale este exto"<<std::endl;
                        enOpciones=false;
                        enPausa=true;
                        pausaopciones=false;
                        selectedItemIndexOpciones=0;
                        int i=0;
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
                        window.close();
                    }
                    if(enPartida){
                        if(enPausa){
                            selectedItemIndexInPausa=0;
                            int i=0;
                            for(i=0; i<menuInGame.size(); i++){
                                if(GetPressedItem()==i){
                                    menuInGame[i]->setColor(sf::Color::Red);
                                }else{
                                    menuInGame[i]->setColor(sf::Color::White);
                                }   
                            }
                            if(opcionMenuInGame==1){
                                opcionMenuInGame=5;
                                std::cout<<"Saliendo de guardar"<<std::endl;
                                guardando=false;
                                sobreescrito=false;
                            }else{
                                if(opcionMenuInGame==2){
                                    enControles=false;
                                }
                                if(opcionMenuInGame==3 && pausaopciones){
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
                            std::cout<<"Estoy en pausa, claro, donde voy a estar sino"<<std::endl;
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
                            std::cout<<"impresas todas las variables booleanas"<<std::endl;
                            
                            
                            
                            
                            enPausa=true;
                            std::cout<<enPausa <<std::endl;
                           
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

void Menu::moveUp(std::vector<sf::Text*> menu, int &iterator){
    if(iterator-1>=0){
        menu[iterator]->setColor(sf::Color::White);
        iterator--;
        menu[iterator]->setColor(sf::Color::Red);
    }    
}

void Menu::moveDown(std::vector<sf::Text*> menu, int &iterator){
    
    if(iterator+1<menu.size()){
        menu[iterator]->setColor(sf::Color::White);
        iterator++;
        std::cout<<iterator<<std::endl;
        std::cout<<"acabo de imprimir le iterator"<<std::endl;
        menu[iterator]->setColor(sf::Color::Red);
    }
}

void Menu::nuevaPartida(sf::RenderWindow &window){
    //Aqui cargo el fondo para poder lanzar el juego. Metodo: nuevaPartida
        
    //std::cout<<"hasta aqui llego en la funcion nuevaPartida"<<std::endl;
    //cargartextura(texturaBackground, background);// de momento no tengo que usarlo
    window.draw(*background);
}

void Menu::submenu(sf::RenderWindow& window){
    
    
    window.draw(*fondo);//para poder una transparencia
    window.draw(*FondomenuInPausa);
    draw(window, menuInGame);
    //std::cout<<"estoy aqui, en el metodo submenu"<<std::endl;
    

}

void cargartextura(sf::Texture textura, sf::Sprite &sprite){
    //metodo que no he de usar porque cargo la textura en el contructor
}

void Menu::guardar(sf::RenderWindow &window){
 
    window.draw(*FondomenuInPausa);
    window.draw(*desea);
    window.draw(*guardarsino[0]);
    window.draw(*guardarsino[1]);
    
}

void Menu::sobreescribir(sf::RenderWindow& window){
   
    window.draw(*sobreescribirText);
    window.draw(*sobreescribir2Text);
    window.draw(*sobreescribirsino[0]);
    window.draw(*sobreescribirsino[1]);
    
}

void Menu::sobreescritocorrectamente(sf::RenderWindow &window){
    window.draw(*sobrescrita);
}

void Menu::controles(sf::RenderWindow& window){

    window.clear();
    window.draw(*izquierda);
    window.draw(*derecha);
    window.draw(*saltar);
    window.draw(*golpear);
    window.draw(*personaje1);
    window.draw(*personaje2);
    window.draw(*personaje3);
    
}

void Menu::opciones(sf::RenderWindow& window){
    
    

    if(pausaopciones){
        window.draw(*fondo);
        window.draw(*FondomenuInPausa);
    }
    draw(window, opcionesMenu);
    
    window.draw(*barrasonido);
    window.draw(*barramusica);
    window.draw(*tiradorsonido);
    window.draw(*tiradormusica);
 
    
}

void Menu::creditos(sf::RenderWindow& window){
   
    window.draw(*textocreditos);    
    
}

void Menu::cargarPartida(sf::RenderWindow &window){

    window.clear();
    window.draw(*textoCargarPartida);
 
}

void Menu::reinicio(){
 
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