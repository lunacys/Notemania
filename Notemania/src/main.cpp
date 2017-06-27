#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const double TargetFps = 300.0;
const double MsPerUpdate = 1 / TargetFps;


int main()
{
    bool fullscreen = false;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::None);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock totalClock;

    sf::Clock clock;
    double previous = totalClock.getElapsedTime().asSeconds();
    double lastTimeLocked = previous;
    double lag = 0.0;
    int framesLocked = 0;

    sf::VideoMode screenRes = sf::VideoMode::getDesktopMode();
    int screenWidth = screenRes.width;
    int screenHeight = screenRes.height;

    while (window.isOpen())
    {
        // ..:: HANDLE INPUT ::..
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                else if (event.key.code == sf::Keyboard::F)
                {
                    fullscreen = !fullscreen;
                    window.create(sf::VideoMode(1920, 1080),
                                  "SFML works!",
                                  (fullscreen ? sf::Style::Fullscreen :
                                   (screenWidth == 1920 && screenHeight == 1080
                                    ? sf::Style::None : sf::Style::Close)));
                }
            }
        }

        // ..:: UPDATE ::..
        double currentTime = totalClock.getElapsedTime().asSeconds();
        double elapsed = clock.restart().asSeconds();
        previous = currentTime;
        //std::cout << elapsed << std::endl;
        lag += elapsed;

        while (lag >= MsPerUpdate)
        {
            framesLocked++;
            if (currentTime - lastTimeLocked >= 1.0)
            {
                std::cout << 1000.0 / double(framesLocked) << " ms/frame" << std::endl;
                framesLocked = 0;
                lastTimeLocked += 1.0;
            }
            // update(elapsed);

            lag -= MsPerUpdate;
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

