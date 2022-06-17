
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Ball {

    public:

        Ball(int rad, int x, int y, int r, int g, int b);
        sf::CircleShape C;    //must be public so we can draw it    
        void move(float x, float y);
        void update();
        int posx, posy;
    
};

int main()
{
    Ball ball(50, 100, 30, 250, 0, 0);

    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML Test");
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                window.close();
                break;

                default:
                break;
            }

        }

        ball.update();
        window.clear(sf::Color::Black);
        window.draw(ball.C);
        window.display();
    }
    return 0;

}


Ball::Ball(int rad, int x, int y, int r, int g, int b)
{
    
    C.setRadius(rad);
    C.setFillColor(sf::Color(r,g,b));
    C.setPosition(x,y);
    posx = x;
    posy = y;
}

/*
void Ball::move(float x, float y)
{
    C.move(x,y);
}
*/
void Ball::update(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (posx>0){
            posx--;
            C.move(-1,0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {  
        if (posx<700){
            posx++;
        C.move(1,0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (posy<500){
            posy++;
            C.move(0,1);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (posy>0){
            posy--;
            C.move(0,-1);
        }
    }
}
