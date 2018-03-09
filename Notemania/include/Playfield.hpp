#ifndef NOMA_PLAYFIELD_HPP_
#define NOMA_PLAYFIELD_HPP_

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Beatmap.hpp"
#include "Screen.hpp"

namespace noma
{
enum class EventType
{
    Gameplay,
    ScoreScreen
};

class Playfield : public Screen
{
  public:
    Playfield(sf::RenderWindow *window, Beatmap *beatmap);
    virtual ~Playfield();

    virtual void initialize() override;
    virtual void update(double dt) override;
    virtual void render() override;

  private:
    bool is_d_pressed_, is_f_pressed_, is_j_pressed_, is_k_pressed_;
    Beatmap *current_beatmap_;
    sf::RenderWindow *window_;

    sf::Font *main_font_;

    sf::Clock time_;
    //double time_ = 1000;

    float accuracy_ = 1;
    int combo_ = 0, max_combo_ = 0;
    int score_ = 0;

    int num_bad_, num_good_, num_great_, num_perfect_, num_marvelous_, num_miss_;

    sf::Sprite *field_sprite_;
    sf::Sprite *buttons_sprite_;
    sf::Sprite *key_buttons_sprite_;
    sf::Texture *note_texture_;
    sf::Texture *bg_texture_;
    sf::Texture *scorescreen_texture_;
    sf::Texture *ranking_ss_, *ranking_s_, *ranking_a_, *ranking_b_, *ranking_c_, *ranking_d_;
    sf::Music soundtrack_;
    sf::Sound *hitsound_;

    EventType ev_type_ = EventType::Gameplay;

    void reset();
};
} // namespace noma

#endif // NOMA_PLAYFIELD_HPP_
