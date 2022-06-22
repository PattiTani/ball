#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

class Ball {

    public:

		Ball(const RenderWindow& W, int rad, int x, int y, int r, int g, int b);
		void move(float x, float y);
		void update();
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
		//bool collided;
		
		
};


int main()
{
    //Ball ball(50, 100, 30, 250, 0, 0);

	Event event;
    RenderWindow window(VideoMode(800,600), "SFML Test");
    Ball ball(window, 50, 100, 30, 250, 0, 0);
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

        ball.update();
		window.setFramerateLimit(60);
        window.clear(Color::White);
        window.draw(ball.sprite);
        window.display();
    }
    return 0;

}


Ball::Ball(const RenderWindow& W, int rad, int x, int y, int r, int g, int b)
{
	//W.setTitle("aoiresntoiaen"); //fails cause W is passed as const ref
	//W.setSize(Vector2u(500.,500.));
	winheight= W.getSize().y;
	winwidth= W.getSize().x;
    //texture.loadFromFile("meteor-small.png");
    texture.loadFromFile("meteor3.png");
    Vector2u v= texture.getSize();
    float xs= 100./v.x; //make sprite 100 pixels wide and high
    float ys= 100./v.y;
    std::cout<<xs<<std::endl;
    sprite.setTexture(texture);
    sprite.setOrigin(v.x/2,v.y/2); 
    // must setOrigin to center *before* scaling 
    sprite.setScale(xs,ys);
	sprite.setPosition(x,y);
	//collided = false;
    
    
}


void Ball::move(float x, float y)
{
	sprite.move(x,y);
}

void Ball::update(){
	
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
	sprite.rotate(4);
}
