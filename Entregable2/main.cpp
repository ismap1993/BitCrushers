#include <SFML/Graphics.hpp>
#include <vector>

class clase1{
  
    sf::RectangleShape rectangulo;
    bool arriba, abajo, derecha, izquierda;
    float velSalto, velMovimiento;
    const float gravedad = 10.f;
    float acelMaxima; ///2
 
public:
    sf::Vector2f aceleracion;
    bool camino; ///1
    clase1(sf::Vector2f tamanyo): aceleracion(0,0)
    {
        acelMaxima = 300; ///2
        velMovimiento = 20.f;
        velSalto = 500.f;
        rectangulo.setSize(tamanyo);
    }
 
    void ent(sf::Vector2f entrada)
    {
        
    
        
        rectangulo.setPosition(entrada);
    }
 
    void actualizacion()
    {
        arriba = false; abajo = false;
        izquierda = false; derecha = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            arriba = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            abajo = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            izquierda = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            derecha = true;
    }
 
    void movimiento(sf::Vector2f v)
    {
        rectangulo.move(v);
    }
 
    sf::Vector2f moviment(sf::Time tiempo)
    {
        if(camino)
        {
            aceleracion.y = 0;
        }
 
        if(arriba){
            if(camino)
                aceleracion.y -= velSalto;
        }
 
        if(izquierda && aceleracion.x > -acelMaxima)
            aceleracion.x -= velMovimiento;
        else if(derecha && aceleracion.x < acelMaxima)
            aceleracion.x += velMovimiento;
        else{
            aceleracion.x *= 0.95;
        }
 
        aceleracion.y += gravedad;
        return aceleracion * tiempo.asSeconds();
    }
 
    sf::FloatRect colision()
    {
        return rectangulo.getGlobalBounds();
    }
 
    void dibujar(sf::RenderWindow &window)
    {
        window.draw(rectangulo);
    }
 
};
 
class Colisiones
{
public:
    static void conflicto(clase1 &g1, std::vector <clase1> V, sf::Vector2f movimiento)
    {
        sf::FloatRect X = g1.colision();
        sf::FloatRect Y = g1.colision();
        X.left += movimiento.x;
        Y.top += movimiento.y;
        bool kolX = false; bool kolY = false;
 
        for(int i = 0; i < V.size(); i++)
            if(X.intersects(V[i].colision())){
                kolX = true;
 
            }
            else if (Y.intersects(V[i].colision()))
            {
                kolY = true;
 
 
                if(((V[i].colision().top + V[i].colision().height) - Y.top) < 5){
                    g1.camino = false;
                    g1.aceleracion.y = 0;
                }
                else{
                    g1.camino = true;
                }
            }
 
        if(!kolX)
            g1.movimiento(sf::Vector2f(movimiento.x, 0));
        if(!kolY){
            g1.movimiento(sf::Vector2f(0, movimiento.y));
            g1.camino = false;
        }
 
    }
};
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Movimiento del personaje");
 
    sf::Clock reloj;
    sf::Time actual = sf::Time::Zero;
    const sf::Time tiempoPaso = sf::seconds(1.f/160.f);
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/caracol.png"))
    {
        
        exit(0);
    }
    
    sf::Sprite sprite(tex);
      
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(64/2,32/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*64, 0*32, 64, 32));
    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(100, 482);
    
    clase1 jugador(sf::Vector2f(20, 20));
    clase1 piso(sf::Vector2f(800, 20)); piso.ent(sf::Vector2f(0, 580));
    clase1 obstaculo1(sf::Vector2f(50, 20)); obstaculo1.ent(sf::Vector2f(400, 520));
    clase1 obstaculo2(sf::Vector2f(50, 20)); obstaculo2.ent(sf::Vector2f(470, 480));
    clase1 obstaculo3(sf::Vector2f(50, 20)); obstaculo3.ent(sf::Vector2f(540, 420));
    clase1 obstaculo4(sf::Vector2f(50, 20)); obstaculo4.ent(sf::Vector2f(470, 360));
    std::vector <clase1> V;
    V.push_back(piso);
    V.push_back(obstaculo1);
    V.push_back(obstaculo2);
    V.push_back(obstaculo3);
    V.push_back(obstaculo4);
    while(window.isOpen())
    {
        sf::Time tiempo = reloj.restart();
        actual += tiempo;
        jugador.actualizacion();
        while(actual > tiempoPaso)
        {
            actual -= tiempoPaso;
            sf::Event event;
            while(window.pollEvent(event))
            {
                if( event.type == sf::Event::Closed )
                     window.close();
 
            }
                Colisiones::conflicto(jugador, V, jugador.moviment(tiempoPaso));
        }
        window.clear();
        jugador.dibujar(window);
        for(int i = 0; i < V.size(); i++)
            V[i].dibujar(window);
        window.display();
 
    }
    
    
    return 0;
}