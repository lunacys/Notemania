#include "Playfield.hpp"

namespace noma
{
    Playfield::Playfield(sf::RenderWindow* window, Beatmap* beatmap)
        : current_beatmap_(beatmap), window_(window), time_(0)
    {
        sf::Texture* field_texture = new sf::Texture();
        note_texture_ = new sf::Texture();
        note_texture_->loadFromFile("data/images/note.png");
        //single_field_texture.create(100, 100);
        std::string filename = "field4k.png";
        switch (beatmap->settings->difficulty.key_amount)
        {
        case 4: filename = "field4k.png"; break;
        case 5: filename = "field5k.png"; break;
        case 6: filename = "field6k.png"; break;
        case 7: filename = "field7k.png"; break;
        default: break;
        }
        field_texture->loadFromFile("data/images/field4k.png");
        field_sprite_ = new sf::Sprite(*field_texture);
        field_sprite_->setPosition(100, 0);
        //single_field_sprite_->setTexture(single_field_texture);
    }

    Playfield::~Playfield() { }

    void Playfield::initialize()
    {
        
    }

    void Playfield::update(const sf::Event& ev, double dt)
    {
        time_++;
    }

    void Playfield::render()
    {
        window_->draw(*field_sprite_);
        for (auto note : current_beatmap_->hit_objects)
        {
            sf::Sprite n;
            n.setTexture(*note_texture_);
            n.setPosition(note->get_x() * 100, note->get_time() - time_);
            window_->draw(n);
        }
    }
} // namespace noma

