#ifndef NOMA_PLAYFIELD_HPP_
#define NOMA_PLAYFIELD_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Beatmap.hpp"

namespace noma
{
    class Playfield
    {
    public:
        Playfield(sf::RenderWindow* window, Beatmap* beatmap);
        virtual ~Playfield();

        void initialize();
        void update(const sf::Event& ev, double dt);
        void render();

    private:
        bool pressed_keys_[256];
        Beatmap* current_beatmap_;
        sf::RenderWindow* window_;

        sf::Sprite* single_field_sprite_;
        sf::Sprite* key_buttons_sprite_;
    };
} // namespace noma

#endif // NOMA_PLAYFIELD_HPP_

