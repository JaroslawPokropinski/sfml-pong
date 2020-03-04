#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

sf::CircleShape ball;
sf::RectangleShape players[2];
sf::Vector2f velocity_normal;
float speed;

void reset()
{
    ball.setPosition(400-4,300-4);
    speed=4.0f;
    velocity_normal=sf::Vector2f(1,0);
    for (unsigned int i=0; i<2; i++)
    {
        players[i].setPosition(140+i*512,300-15);
    }

}
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    app.setVerticalSyncEnabled(true);

    for(unsigned int i = 0;i<2;i++)
    {
        players[i].setFillColor(sf::Color::White);
        players[i].setSize(sf::Vector2f(8,30));
        players[i].setPosition(140+i*512,300-15);
    }


    ball.setFillColor(sf::Color::White);
    ball.setRadius(4);
    ball.setPosition(400-4,300-4);

    int dir = -1;

    int points[2];
    points[0] = 0;
    points[1] = 0;
    reset();
    velocity_normal.x *= (-1);


    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        ball.move(velocity_normal*speed);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            players[0].move(0,-1*speed/1.0f);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            players[0].move(0,1*speed/1.0f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            players[1].move(0,-1*speed/1.0f);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            players[1].move(0,1*speed/1.0f);


        for(int i = 0; i < 2; i++)
            if((ball.getPosition().x<148)*abs(i-1) || (ball.getPosition().x > 648)*i)
            {
                ball.setPosition(148.0f*abs(i-1) + 648*i,ball.getPosition().y);
                float da = ball.getPosition().y - players[i].getPosition().y + ball.getRadius();
                int db = da/4.25;

                if(db < 0 || db > 7)
                {
                    points[i]++;
                    reset();
                    velocity_normal.x *= dir;
                }
                else
                {
                    float alpha;
                    dir *= (-1);
                    if(db<4)
                        alpha = (db-3.0f)/12.0f*M_PI;
                    else 
                        alpha = (db-4.0f)/12.0f*M_PI;

                    velocity_normal.x = cos(alpha)*dir;
                    velocity_normal.y = sin(alpha);
                }
            }
        if(ball.getPosition().y < 0 || ball.getPosition().y > 600)
            velocity_normal.y *= (-1);

        // Clear screen
        app.clear();
        for(unsigned int i = 0; i < 2; i++)
            app.draw(players[i]);
        app.draw(ball);
        app.display();
    }

    return EXIT_SUCCESS;
}
