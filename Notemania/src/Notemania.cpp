#include "Notemania.hpp"
#include <iostream>

#include "BeatmapReader.hpp"

namespace noma
{
    Notemania::Notemania()
        : window_width_(800), window_height_(600), is_running_(false)
    {
        playfield_ = new Playfield(&window_, nullptr);
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
        Beatmap* test = new Beatmap();
        test->settings = new BeatmapSettings();
        test->settings->general.audio_filename = "hello there.ogg";
        test->settings->general.preview_time = 1234;
        test->settings->editor.beat_divisor = 4;
        test->settings->metadata.title = "test title";
        test->settings->metadata.artist = "test artist";
        test->settings->metadata.creator = "loonacuse";
        test->settings->metadata.version = "test version";
        test->settings->metadata.tags = "there are tags";
        test->settings->metadata.beatmap_id = 1;
        test->settings->metadata.beatmap_set_id = 1;
        test->settings->difficulty.hp_drain_rate = 4;
        test->settings->difficulty.overall_difficulty = 6;
        test->settings->difficulty.key_amount = 4;
        test->timing_points.push_back(new TimingPoint(0, 1423.34534123, 4, 100, false));
        test->hit_objects.push_back(new HitObject(1, 0, HitObjectType::Click));
        test->hit_objects.push_back(new HitObject(2, 0, HitObjectType::Click));
        test->hit_objects.push_back(new HitObject(3, 0, HitObjectType::Click));
        test->hit_objects.push_back(new HitObject(4, 0, HitObjectType::Click));
        test->hit_objects.push_back(new HitObject(2, 100, HitObjectType::Hold, 200));

        //BeatmapReader::save_beatmap_to_file(test, "test.noma");

        BeatmapReader::load_beatmap_from_file("test.noma");
    }

    void Notemania::load_content()
    {
        
    }

    void Notemania::update(double dt)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            exit();

        playfield_->update(event_, dt);
    }

    void Notemania::render()
    {
        playfield_->render();
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

