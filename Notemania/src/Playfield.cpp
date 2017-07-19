#include "Playfield.hpp"

namespace noma
{
    Playfield::Playfield(sf::RenderWindow* window, Beatmap* beatmap)
        : current_beatmap_(beatmap), window_(window)
    {
        sf::Texture* single_field_texture = new sf::Texture();
        //single_field_texture.create(100, 100);
        single_field_texture->loadFromFile("data/images/single_field.png");
        single_field_sprite_ = new sf::Sprite(*single_field_texture);
        //single_field_sprite_->setTexture(single_field_texture);
    }

    Playfield::~Playfield() { }

    void Playfield::initialize()
    {
        
    }

    void Playfield::update(const sf::Event& ev, double dt)
    {
        
    }

    void Playfield::render()
    {
        window_->draw(*single_field_sprite_);
    }
} // namespace noma

