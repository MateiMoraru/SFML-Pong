#include <math.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

#define WIDTH 800
#define HEIGHT 600

int rand_float(float min, float max);
void create_env(RectangleShape &player, RectangleShape &AI, CircleShape &ball);
bool intersects(CircleShape &c, RectangleShape &p);
bool contains(CircleShape &c, Vector2f &p);

int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pong!");

    bool start = false;
    float speed = 10.0;
    RectangleShape player;
    RectangleShape AI;
    CircleShape ball(15);
    float ball_speed[2] = {-1 / 50.0, 1 / 50.0};

    create_env(player, AI, ball);

    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            if(event.type == Event::KeyPressed)
                switch(event.key.code)
                {
                    case Keyboard::S:
                        player.move(Vector2f(0, speed));
                        break;
                    case Keyboard::W:
                        player.move(Vector2f(0, -speed));
                        break;
                    case Keyboard::Space:
                        start = true;
                }
        }

        if(start)
        {
            ball.move(Vector2f(ball_speed[0], ball_speed[1]));
            if(ball.getPosition().x < 0 || ball.getPosition().x > WIDTH)
                ball_speed[0] *= -1;
            if(ball.getPosition().y < 0 || ball.getPosition().y > HEIGHT)
                ball_speed[1] *= -1;
            if(intersects(ball, player) || intersects(ball, AI))
                ball_speed[0] *= -1;
        }

        window.clear();

        window.draw(player);
        window.draw(AI);
        window.draw(ball);

        window.display();
    }
    return 0;
}

void create_env(RectangleShape &player, RectangleShape &AI, CircleShape &ball)
{
    player.setSize(Vector2f(20, 100));
    player.setPosition(Vector2f(40, HEIGHT / 2 - 50));
    player.setFillColor(Color(255, 255, 255));
    
    AI.setSize(Vector2f(20, 100));
    AI.setPosition(Vector2f(WIDTH - 40, HEIGHT / 2 - 50));
    AI.setFillColor(Color(255, 255, 255));

    ball.setFillColor(Color(255, 255, 255));
    ball.setPosition(Vector2f(WIDTH / 2 - 15, HEIGHT / 2 - 15));
}


int rand_float(float min, float max)
{
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max-min)));
}
bool intersects(CircleShape &c, RectangleShape &r){
    FloatRect fr = r.getGlobalBounds();
    Vector2f topLeft(fr.left, fr.top);
    Vector2f topRight(fr.left + fr.width, fr.top);
    Vector2f botLeft(fr.left, fr.top + fr.height);
    Vector2f botRight(fr.left + fr.width, fr.top + fr.height);

    return contains(c, topLeft) || 
        contains(c, topRight) || 
        contains(c, botLeft) || 
        contains(c, botRight);
}

bool contains(CircleShape &c, Vector2f &p){
    Vector2f center = c.getPosition();
    float a = (p.x - center.x);
    float b = (p.y - center.y);
    a *= a;
    b *= b;
    float r = c.getRadius() * c.getRadius();

    return (( a + b ) < r);
}
