#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace sf;

class Ufo {

    public:
        Ufo(const RenderWindow& W, int rad, int x, int y, int r, int g, int b);
        CircleShape C;    //must be public so we can draw it    
        void move(float x, float y);
        void update();
        Sprite sprite;
        Vector2f pos;
        float rad;
        float winwidth; 
		float winheight ;
        
    private:
        sf::Texture texture;
		
};

class Meteor {
    public:
		Meteor(const RenderWindow& W, int rad, int x, int y, int r, int g, int b);
		void move(float x, float y);
		void update();
        int randx, randy;
		Sprite sprite; //must be public so we can draw it	
	
	private:
		RenderWindow* W;
		Vector2f pos;	
		float rad;
		float winwidth; //assigned in ctor method below
		float winheight ;
		//float winwidth( window.getSize().x); //fails as no window object in Ball class
		//float winheight( window.getSize().y);
		Texture texture; //static so we don't have a texture for each instance
};

int main()
{
    //Ball ball(50, 100, 30, 250, 0, 0);
	Event event;
    RenderWindow window(VideoMode(800,600), "SFML Test");
    Ufo ufo(window, 50, 100, 30, 250, 0, 0);
    Meteor ball(window, 50, 100, 30, 250, 0, 0);
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                window.close();
                break;

                default:
                break;
            }

        }

        ufo.update();
        ball.move(8,20);
        ball.update();
		window.setFramerateLimit(60);
        window.clear(Color::White);
        window.draw(ball.sprite);
        window.draw(ufo.sprite);
        window.display();
    }
    return 0;

}


Meteor::Meteor(const RenderWindow& W, int rad, int x, int y, int r, int g, int b)
{
    srand(time(0));
    randx = (rand()%20)-10;
    randy = (rand()%20)-10;
    std::cout<<randx;
	winheight= W.getSize().y;
	winwidth= W.getSize().x;
    //texture.loadFromFile("meteor-small.png");
    texture.loadFromFile("meteor3.png");
    Vector2u v= texture.getSize();
    float xs= 100./v.x; //make sprite 100 pixels wide and high
    float ys= 100./v.y;
    sprite.setTexture(texture);
    sprite.setOrigin(v.x/2,v.y/2); 
    // must setOrigin to center *before* scaling 
    sprite.setScale(xs,ys);
	sprite.setPosition(x,y);
	//collided = false;
}

Ufo::Ufo(const RenderWindow& W, int rad, int x, int y, int r, int g, int b)
{
	winheight= W.getSize().y;
	winwidth= W.getSize().x;
    texture.loadFromFile("ufo.png");
    Vector2u v= texture.getSize();
    float xs= 100./v.x; //make sprite 100 pixels wide and high
    float ys= 100./v.y;
    sprite.setTexture(texture);
    sprite.setOrigin(v.x/2,v.y/2); 
    // must setOrigin to center *before* scaling 
    sprite.setScale(xs,ys);
	sprite.setPosition(x,y);
	//collided = false;
    
    
}


void Ufo::move(float x, float y)
{
	sprite.move(x,y);
}

void Meteor::move(float x, float y)
{
	sprite.move(x,y);
}


void Ufo::update(){
	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
		sprite.move(-10,0.);
	}
	if(Keyboard::isKeyPressed(Keyboard::Right))
	{
		sprite.move(10,0);
	}
	if(Keyboard::isKeyPressed(Keyboard::Down))
	{
		sprite.move(0,10);
	}
	if(Keyboard::isKeyPressed(Keyboard::Up))
	{
		sprite.move(0,-10);
	}
	pos = sprite.getPosition();
	float rad = 50.;
	if ( pos.x - rad > winwidth) //beyond right side
    {   
        pos.x = 0;
    }   
    if ( pos.y - rad > winheight) //beyond bottom
    {   
        pos.y = 0;
    }   
    
    if( pos.x + rad < 0) //beyond left side
    {   
        pos.x = winwidth;
    }   
    if( pos.y + rad < 0) //beyond top
    {   
        pos.y = winheight;
    }
	sprite.setPosition(pos.x, pos.y);
}

void Meteor::update(){
	pos = sprite.getPosition();
	if ( pos.x - rad > winwidth) //beyond right side
    {   
        pos.x = 0;
    }   
    if ( pos.y - rad > winheight) //beyond bottom
    {   
        pos.y = 0;
    }   
    
    if( pos.x + rad < 0) //beyond left side
    {   
        pos.x = winwidth;
    }   
    if( pos.y + rad < 0) //beyond top
    {   
        pos.y = winheight;
    }
    sprite.rotate(4);
	sprite.setPosition(pos.x, pos.y);
}
