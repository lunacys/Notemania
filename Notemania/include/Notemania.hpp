#ifndef NOMA_NOTEMANIA_HPP_
#define NOMA_NOTEMANIA_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Playfield.hpp"
#include "Beatmap.hpp"

namespace noma
{
    const double TargetFps = 300.0;
    const double MsPerUpdate = 1 / TargetFps;

    class Notemania
    {
    public:
        Notemania();
        virtual ~Notemania();

        void run();
        void exit();

    protected:
        void initialize();
        void load_content();
        void update(double dt);
        void render();

    private:
        int window_width_;
        int window_height_;

        bool is_running_;

        sf::Event event_;

        sf::RenderWindow window_;
        sf::Clock total_clock_;

        Playfield* playfield_;

        void main_loop();
    };
} // namespace noma

#endif // NOMA_NOTEMANIA_HPP_
