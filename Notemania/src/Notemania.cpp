#include "Notemania.hpp"
#include <iostream>

#include "BeatmapReader.hpp"

namespace noma
{
    Notemania::Notemania()
        : window_width_(1280), window_height_(720), is_running_(false)
    {
        
    }

    Notemania::~Notemania() { }

    void Notemania::run()
    {
        window_.create(sf::VideoMode(window_width_, window_height_, 32), "Notemania");
        initialize();
        load_content();
        total_clock_.restart();
        is_running_ = true;
        main_loop();
    }

    void Notemania::exit()
    {
        is_running_ = false;
    }

    void Notemania::initialize()
    {

        Beatmap* bm = BeatmapReader::load_beatmap_from_file("maps/NOMA - Brain Power/NOMA - Brain Power.noma");

        //playfield_ = new Playfield(&window_, bm);
        screen_manager_ = new ScreenManager();
        screen_manager_->register_screen(new Playfield(&window_, bm), "Playfield");
    }

    void Notemania::load_content()
    {
        
    }

    void Notemania::update(double dt)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            exit();

        screen_manager_->update(dt);
    }

    void Notemania::render()
    {
        screen_manager_->render();
    }

    void Notemania::main_loop()
    {
        double previousTime = total_clock_.getElapsedTime().asSeconds();
        double lastTimeLocked = previousTime;
        double lag = 0.0;
        int framesLocked = 0;

        while (is_running_ && window_.isOpen())
        {
            // Handling input
            sf::Event ev;
            while (window_.pollEvent(ev))
            {
                if (ev.type == sf::Event::Closed)
                {
                    window_.close();
                }
            }

            // Updating
            double currentTime = total_clock_.getElapsedTime().asSeconds();
            double elapsed = currentTime - previousTime;
            previousTime = currentTime;
            lag += elapsed;

            while (lag >= MsPerUpdate)
            {
                framesLocked++;
                if (currentTime - lastTimeLocked >= 1.0)
                {
                    // Обновляем счётчик миллисекунд, потраченных на обновление фрейма
                    // Здесь же мы можем использовать это значение для дебаггинга
                    // например std::cout << 1000.0 / double(framesLocked);
                    // Полученное значение будет являться количеством времени
                    // 16.(6) мс = 60 кадров в сенунду (1 / fps)
                    framesLocked = 0;
                    lastTimeLocked += 1.0;
                }

                update(elapsed);

                lag -= MsPerUpdate;
            }

            // Rendering
            window_.clear();
            render();
            window_.display();
        }

        is_running_ = false;
    }
} // namespace noma

