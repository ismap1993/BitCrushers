#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include <algorithm>
using namespace std;

#define kVel 25
#define friction kVel/3



string toString(int integer){ 
    char numstr[10]; // enough to hold all numbers up to 32-bits
    sprintf(numstr, "%i", integer);
    return numstr;
}
 

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Prueba interpolacion");
    //window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(true);
    sf::RectangleShape rectangulo;
    rectangulo.setPosition(100, 100);
    rectangulo.setSize(sf::Vector2f(150,50));
    rectangulo.setFillColor(sf::Color::Black);
    
    //sf::Clock clock;
    sf::Clock updateClock;
    sf::Clock accelMainClock;
    sf::Clock accelClock;
    sf::Time accelTime;
    sf::Time countDown;
   
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool accelOn = false;
    bool countDowning = false;
    
    int UPDATE_TICK_TIME = 1000/15;
    sf::Vector2i lastPosVec; //Posicion anterior
    sf::Vector2i newPosVec;  //Posicion actual
    sf::Vector2i velVector;  //Vector de velocidad
    sf::Vector2i accVector;  //Vector de aceleración
    
    bool first = true;
    
    float percentTick;
    
    bool inter = false;
    
    while (window.isOpen()){  
        
        if(first){
            
            lastPosVec.x = newPosVec.x = rectangulo.getPosition().x;
            lastPosVec.y = newPosVec.y = rectangulo.getPosition().y;
                
        }
        
        if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME){
        //lastx = rectangulo.getPosition().x;
             updateClock.restart();
             
            lastPosVec.x = newPosVec.x;
            lastPosVec.y = newPosVec.y;
        //UPDATE
         
             
             //percentTick=0;
            
             
             
            //Bucle de obtención de eventos
            sf::Event event;
            while (window.pollEvent(event)){
                
                {
                
		switch (event.type){
			
                    case sf::Event::KeyPressed: {
                        
                        if(event.key.code == sf::Keyboard::X )
                            if(!inter)
                                inter = true;
                            else
                                inter = false;
                        
                        if(event.key.code == sf::Keyboard::Right)
                            isMovingRight = true;
                        if(event.key.code == sf::Keyboard::Left)
                            isMovingLeft = true;
                        if(event.key.code == sf::Keyboard::Up)
                            isMovingUp = true;
                        if(event.key.code == sf::Keyboard::Down)
                            isMovingDown = true;
                        
                        break;
                    }        
                    
                    case sf::Event::KeyReleased:{
                        
                       if(event.key.code == sf::Keyboard::Right)
                            isMovingRight = false;
                        if(event.key.code == sf::Keyboard::Left)
                            isMovingLeft = false;
                        if(event.key.code == sf::Keyboard::Up)
                            isMovingUp = false;
                        if(event.key.code == sf::Keyboard::Down)
                            isMovingDown = false;
                        
                        break;
                    }
                    
                    
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                        
                   
                       
                    default:
                                //std::cout << event.key.code << std::endl;
                        break;

                    }
                
                    
                
                }

            }    
            
       
                //if your speed is close to 0, stop
                if (abs(velVector.x) <= friction){
                   velVector.x = 0;
                }
                else{
                   //decrease the speed
                     if(velVector.x>0)
                         velVector.x -= friction;
                     else
                         velVector.x += friction;
                }
            
                if (abs(velVector.y) <= friction){
                       velVector.y = 0;
                    }
                    else{
                       //decrease the speed
                         if(velVector.y>0)
                             velVector.y -= friction;
                         else
                             velVector.y += friction;
                    }
         
            
         
            if(isMovingRight){
                //lastx = rectangulo.getPosition().x;
                //rectangulo.move(kVel,0);
                //newx = rectangulo.getPosition().x;
                velVector.x += kVel;
                //accVector.x = 


            }
            
               
            if(isMovingLeft){
                //lastx = rectangulo.getPosition().x;
                //rectangulo.move(-kVel,0);
                //newx = rectangulo.getPosition().x;
                velVector.x += -kVel;
            }
            
            if(isMovingUp){
                //lasty = rectangulo.getPosition().y;
                //rectangulo.move(0,-kVel);
                //newy = rectangulo.getPosition().y;
                velVector.y += -kVel;

            }
            
            
            if(isMovingDown){
                //lasty = rectangulo.getPosition().y;
                //rectangulo.move(0, kVel);
                //newy = rectangulo.getPosition().y;
                velVector.y += kVel;

            }
            
            
            
            //LAST STATE = NEW STATE
            
            newPosVec.x += velVector.x;
            newPosVec.y += velVector.y;
            
            std::cout<<velVector.x<<std::endl;
            
        }
        
            //updateClock.restart();
           //std::cout<<newPosVec.x<<" "<<newPosVec.y<<std::endl;
        
        //std::cout<<"New positions: "<<rectangulo.getPosition().x<<" "<<rectangulo.getPosition().y<<std::endl;

        percentTick = std::min(1.f, (float)updateClock.getElapsedTime().asMilliseconds()/UPDATE_TICK_TIME);
        //percentTick = std::min(1.f, (float)(updateClock.getElapsedTime().asMilliseconds()*(UPDATE_FRAMERATE*UPDATE_FRAMERATE))/UPDATE_TICK_TIME);
       // percentTick*=(UPDATE_FRAMERATE*UPDATE_FRAMERATE);
        //std::cout<<percentTick<<std::endl;
        if(!first){
            if(inter)
                rectangulo.setPosition(lastPosVec.x * (1-percentTick) + newPosVec.x * percentTick, lastPosVec.y * (1-percentTick) + newPosVec.y * percentTick);
            else
                rectangulo.setPosition(newPosVec.x, newPosVec.y);
        }
       
        
          
         
                //lastx = rectangulo.getPosition().x;
                //lasty = rectangulo.getPosition().y;
         //std::cout<<inter<<std::endl;
     
       // newx = lastx * (1-percentTick) + newx * percentTick;
        //newy = lasty * (1-percentTick) + newy * percentTick;
        //std::cout<<percentTick<<std::endl;
       
      
        //std::cout<<"drawing.."<<std::endl;
        //std::cout<<percentTick<<std::endl;
       //std::cout<<(float)(updateClock.getElapsedTime().asMilliseconds()*(UPDATE_FRAMERATE*UPDATE_FRAMERATE))/UPDATE_TICK_TIME<<std::endl;
        //std::cout<<(float)updateClock.getElapsedTime().asMilliseconds()<<" / "<<timePerFrame.asMilliseconds()<<" = "<< (float)updateClock.getElapsedTime().asMilliseconds()/500<<std::endl;
        //std::cout<<lastx * (1-percentTick) + newx * percentTick<<" "<<lasty * (1-percentTick) + newy * percentTick<<std::endl;
       

        //RENDER
        window.clear(sf::Color::White); //COLOR DE FONDO BLANCO   
        window.draw(rectangulo);
        window.display();
        
        first = false;
        
    }
    
    return 0;
}