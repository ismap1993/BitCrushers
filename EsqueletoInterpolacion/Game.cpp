#include "Game.h"


/************ VARIABLES GLOBALES ************/
const sf::Time Game::timePerFrame = sf::seconds(1.f/15.f);
const int ancho = 640, alto = 480;
const float segStatistics = 0.5f; //segundos de refresco de las estadisticas




/************ CONSTRUCTOR **************/
Game::Game()
: window(sf::VideoMode(ancho, alto, 24), "TITULO APLICACION", sf::Style::Close)
, contFonts()
, contTextures()
, mStatisticsText()
, player()
, isMovingUp(false)
, isMovingDown(false)
, isMovingRight(false)
, isMovingLeft(false)
, mIsRotatingLeft(false)
, mIsRotatingRight(false)
, firstTime(true)
, isInterpolating(false)
{
	window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
	window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
	

   // Cargamos RECURSOS. Utilizamos los contenedores genericos
        if(!contTextures.loadFromFile("resources/Eagle.png")){
            std::cout<<"Error"<<std::endl;
        }
                
		
		contFonts.loadFromFile("resources/OpenSans-Regular.ttf");

    
	
   //Configuramos Items
	player.Init(contTextures,200.f, 250.f);
	
	mStatisticsText.setFont(contFonts);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(13);
	mStatisticsText.setColor(sf::Color::Black);
	mStatisticsText.setString("Interpolacion Desactivada (X)");
}



/**************  METODOS PRINCIPALES **************/

void Game::run()    //Metodo principal
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;  //Tiempo desde el ultimo cambio de frame
	
	
	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();     //Actualizamos variables de tiempo
		timeSinceLastUpdate += elapsedTime;
        
		processEvents();
		
		
        //Llevamos control en las actualizaciones por frame
		while (timeSinceLastUpdate > timePerFrame)   // 15 veces/segundo
		{
			timeSinceLastUpdate -= timePerFrame;
            
            //Realizamos actualizaciones
			update(timePerFrame);       
			
		}
		
		interpolation = (float)std::min(1.f, timeSinceLastUpdate.asSeconds() / timePerFrame.asSeconds());

        render(interpolation);
	}
}



/***************  METODOS DE FISICA Y DISPLAY  *************/

void Game::update(sf::Time elapsedTime)     //Actualiza la fisica
{
	float horiz = 0.f, vertic=0.f;
	if(!firstTime)
	{
		sf::Vector2f vel;
		
		
		if(isMovingDown)
			vertic = 300.f;
		if(isMovingUp)
			vertic = -300.f;
		if(isMovingLeft)
			horiz = -300.f;
		if(isMovingRight)
			horiz = 300.f;
			
		vel = sf::Vector2f(horiz,vertic);
			
		player.Update(vel, elapsedTime);
	}
	
	firstTime=false;
}

void Game::render(float interpolation)     //Dibuja
{
	window.clear(sf::Color::White);
	//window.draw(sprite);
	
	//LLAMAR AL DRAW DEL PLAYER
	if(isInterpolating)
		player.DrawWithInterpolation(window, interpolation);
	else
		player.Draw(window);
	
	window.draw(mStatisticsText);
	window.display();
}





/************** EVENTOS ****************/

void Game::processEvents()   //Captura y procesa eventos
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
                
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
                
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

// Realiza las operaciones correspondientes a cada Evento
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)            //Traslaciones
		isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		isMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		isMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		isMovingRight = isPressed;
	
	else if (key == sf::Keyboard::X && isPressed){
		isInterpolating = !isInterpolating;
		
		if(isInterpolating)
			mStatisticsText.setString("Interpolacion Activada (X)");
		else
			mStatisticsText.setString("Interpolacion Desactivada (X)");
	}
}
