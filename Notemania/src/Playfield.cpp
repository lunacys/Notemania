#include "Playfield.hpp"

namespace noma
{
    Playfield::Playfield(sf::RenderWindow* window, Beatmap* beatmap)
        : current_beatmap_(beatmap), window_(window)
    {
        main_font_.loadFromFile("data/fonts/MainFont.ttf");

        bg_texture_ = new sf::Texture();
        bg_texture_->loadFromFile(beatmap->settings->general.background_filename);
        sf::Texture* field_texture = new sf::Texture();
        note_texture_ = new sf::Texture();
        note_texture_->loadFromFile("data/images/note.png");
        note_texture_->setRepeated(true);
        field_texture->loadFromFile("data/images/field4k.png");
        field_sprite_ = new sf::Sprite(*field_texture);
        field_sprite_->setPosition(300, 0);
        sf::Texture* buttonsTexture = new sf::Texture();
        buttonsTexture->loadFromFile("data/images/buttons4k.png");
        buttons_sprite_ = new sf::Sprite(*buttonsTexture);
        buttons_sprite_->setPosition(300, 0);

        time_.restart();
    }

    Playfield::~Playfield() { }

    void Playfield::initialize()
    {
        
    }

    void Playfield::update(double dt)
    {
        //time_ += 1;//current_beatmap_->timing_points[0]->get_ms_per_beat() / 60 * dt;
        int curMs = time_.getElapsedTime().asMilliseconds();

        auto calc_score = [&] (int hitValue) -> float
            {
                int totalNotes = current_beatmap_->hit_objects.size();
                float baseScore = (1000000.0 / totalNotes) * (hitValue / 320.0);
                std::cout << baseScore << std::endl;
                return baseScore;
            };

        auto calc_acc = [&] () -> float
            {
                float totalPointsOfHits = (num_bad_ * 50 + num_good_ * 100 +
                                         num_great_ * 200 + num_perfect_ * 300 +
                                         num_marvelous_ * 300);
                float totalNumberOfHits = (num_miss_ + num_bad_ + num_good_ +
                                         num_great_ + num_perfect_ + num_marvelous_);
                return totalPointsOfHits / (totalNumberOfHits * 300);
            };

        int od = (int)current_beatmap_->settings->difficulty.overall_difficulty;

        auto get_hit_value = [&] (HitObject* note) -> int
            {
                int a = std::abs(curMs - note->get_time());
                //std::cout << "a: " << a << std::endl;
                note->press();
                if (a <= 16)
                {
                    num_marvelous_++;
                    combo_++;
                    return 320;
                }
                else if (a <= 64 - (3 * od))
                {
                    num_perfect_++;
                    combo_++;
                    return 300;
                }
                else if (a <= 97 - (3 * od))
                {
                    num_great_++;
                    combo_++;
                    return 200;
                }
                else if (a <= 127 - (3 * od))
                {
                    num_good_++;
                    combo_++;
                    return 100;
                }
                else if (a <= 151 - (3 * od))
                {
                    num_bad_++;
                    combo_++;
                    return 50;
                }
                else if (a < 188 - (3 * od))
                {
                    num_miss_++;
                    combo_ = 0;
                    return 0;
                }

                return 0;
            };

        auto find_nearest_note = [&] (int x) -> HitObject*
            {
                for (auto note : current_beatmap_->hit_objects)
                {
                    if (!note->is_pressed() &&
                        note->get_x() == x &&
                        std::abs(curMs - note->get_time()) < 188 - (3 * od))
                        return note;
                }
                return nullptr;
            };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            auto note = find_nearest_note(1);
            if (note != nullptr)
            {
                int hv = get_hit_value(note);
                score_ += calc_score(hv);
                accuracy_ = calc_acc();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            auto note = find_nearest_note(2);
            if (note != nullptr)
            {
                int hv = get_hit_value(note);
                score_ += calc_score(hv);
                accuracy_ = calc_acc();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            auto note = find_nearest_note(3);
            if (note != nullptr)
            {
                int hv = get_hit_value(note);
                score_ += calc_score(hv);
                accuracy_ = calc_acc();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            auto note = find_nearest_note(4);
            if (note != nullptr)
            {
                int hv = get_hit_value(note);
                score_ += calc_score(hv);
                accuracy_ = calc_acc();
            }
        }

        for (auto note : current_beatmap_->hit_objects)
        {
            if (!note->is_pressed() && note->get_time() - curMs < -(188 - (3 * od)))
            {
                num_miss_++;
                calc_score(0);
                calc_acc();
                note->press();
            }
        }
    }

    void Playfield::render()
    {
        int curMs = time_.getElapsedTime().asMilliseconds();

        sf::Sprite bg;
        bg.setTexture(*bg_texture_);
        
        window_->draw(bg);
        window_->draw(*field_sprite_);
        window_->draw(*buttons_sprite_);
        for (auto note : current_beatmap_->hit_objects)
        {
            if (note->get_endtime() >= curMs && !note->is_pressed())
            {
                if (note->get_type() == HitObjectType::Click)
                {
                    sf::Sprite n;
                    n.setTexture(*note_texture_);
                    n.setPosition((note->get_x() + 2) * 100, note->get_time() - curMs);
                    window_->draw(n);
                }
                else if (note->get_type() == HitObjectType::Hold)
                {
                    sf::Sprite n;
                    n.setTexture(*note_texture_);
                    n.setTextureRect(sf::IntRect(0, 0, 100, note->get_endtime() - note->get_time()));
                    n.setPosition((note->get_x() + 2) * 100, note->get_time() - curMs);
                    window_->draw(n);
                }
            }
        }
        sf::Text acc, combo, score, info;
        acc.setFont(main_font_);
        acc.setString(std::to_string((int)(accuracy_ * 100)) + '%');
        acc.setCharacterSize(54);
        acc.setFillColor(sf::Color::Blue);
        acc.setPosition(800, 20);

        combo.setFont(main_font_);
        combo.setString(std::to_string(combo_));
        combo.setCharacterSize(28);
        combo.setPosition(500, 500);

        score.setFont(main_font_);
        score.setString(std::to_string(score_));
        score.setCharacterSize(28);
        score.setPosition(1000, 20);

        info.setFont(main_font_);
        std::string str("Marvelous: " + std::to_string(num_marvelous_)
                        + "\nPerfect: " + std::to_string(num_perfect_)
                        + "\nGreat: " + std::to_string(num_great_)
                        + "\nGood: " + std::to_string(num_good_)
                        + "\nBad: " + std::to_string(num_bad_)
                        + "\nMiss: " + std::to_string(num_miss_));
        info.setString(str);
        info.setCharacterSize(20);
        info.setPosition( 20, 20);
        info.setFillColor(sf::Color::Black);

        window_->draw(acc);
        window_->draw(score);
        window_->draw(combo);
        window_->draw(info);
    }
} // namespace noma

