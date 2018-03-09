#include "Playfield.hpp"

namespace noma
{
Playfield::Playfield(sf::RenderWindow *window, Beatmap *beatmap)
    : current_beatmap_(beatmap), window_(window)
{
    num_bad_ = num_good_ = num_great_ = num_perfect_ = num_marvelous_ = num_miss_ = 0;

    main_font_ = new sf::Font;
    main_font_->loadFromFile("data/fonts/Consolas.ttf");

    bg_texture_ = new sf::Texture;
    bg_texture_->loadFromFile("maps/NOMA - Brain Power/" + beatmap->settings->general.background_filename);
    sf::Texture *field_texture = new sf::Texture();
    note_texture_ = new sf::Texture();
    note_texture_->loadFromFile("data/images/note.png");
    note_texture_->setRepeated(true);
    field_texture->loadFromFile("data/images/field4k.png");
    field_sprite_ = new sf::Sprite(*field_texture);
    field_sprite_->setPosition(300, 0);
    sf::Texture *buttonsTexture = new sf::Texture();
    buttonsTexture->loadFromFile("data/images/buttons4k.png");
    buttons_sprite_ = new sf::Sprite(*buttonsTexture);
    buttons_sprite_->setPosition(300, 0);

    scorescreen_texture_ = new sf::Texture();
    scorescreen_texture_->loadFromFile("data/images/scorescreen.png");

    ranking_ss_ = new sf::Texture();
    ranking_ss_->loadFromFile("data/images/ranking-X.png");
    ranking_s_ = new sf::Texture();
    ranking_s_->loadFromFile("data/images/ranking-S.png");
    ranking_a_ = new sf::Texture();
    ranking_a_->loadFromFile("data/images/ranking-A.png");
    ranking_b_ = new sf::Texture();
    ranking_b_->loadFromFile("data/images/ranking-B.png");
    ranking_c_ = new sf::Texture();
    ranking_c_->loadFromFile("data/images/ranking-C.png");
    ranking_d_ = new sf::Texture();
    ranking_d_->loadFromFile("data/images/ranking-D.png");
    //sf::SoundBuffer* hitsoundBuff = new sf::SoundBuffer();
    //hitsoundBuff->loadFromFile("data/sfx/hitsound.wav");
    //hitsound_ = new sf::Sound(*hitsoundBuff);

    //soundtrack_ = new sf::Music();
    soundtrack_.openFromFile("maps/NOMA - Brain Power/" + beatmap->settings->general.audio_filename);

    soundtrack_.setPlayingOffset(sf::milliseconds(beatmap->hit_objects[0]->get_time() - 2000));

    soundtrack_.play();

    time_.restart();
}

Playfield::~Playfield() {}

void Playfield::initialize()
{
}

void Playfield::update(double dt)
{
    if (ev_type_ == EventType::Gameplay)
    {
        int curMs = time_.getElapsedTime().asMilliseconds();
        HitObject *lastNote = current_beatmap_->hit_objects.back();

        if (lastNote->get_time() + 1000 < curMs)
        {
            ev_type_ = EventType::ScoreScreen;
            soundtrack_.stop();
        }

        auto calc_score = [&](int hitValue) -> float {
            int totalNotes = current_beatmap_->hit_objects.size();
            float baseScore = (1000000.0 / totalNotes) * (hitValue / 320.0);
            return baseScore;
        };

        auto calc_acc = [&]() -> float {
            float totalPointsOfHits = (num_bad_ * 50 + num_good_ * 100 +
                                       num_great_ * 200 + num_perfect_ * 300 +
                                       num_marvelous_ * 300);
            float totalNumberOfHits = (num_miss_ + num_bad_ + num_good_ +
                                       num_great_ + num_perfect_ + num_marvelous_);
            return totalPointsOfHits / (totalNumberOfHits * 300);
        };

        int od = (int)current_beatmap_->settings->difficulty.overall_difficulty;

        auto get_hit_value = [&](HitObject *note) -> int {
            int a = std::abs(curMs - note->get_time());
            //std::cout << "a: " << a << std::endl;
            note->press();
            if (a <= 16)
            {
                num_marvelous_++;
                combo_++;
                if (combo_ > max_combo_)
                    max_combo_ = combo_;
                return 320;
            }
            else if (a <= 64 - (3 * od))
            {
                num_perfect_++;
                combo_++;
                if (combo_ > max_combo_)
                    max_combo_ = combo_;
                return 300;
            }
            else if (a <= 97 - (3 * od))
            {
                num_great_++;
                combo_++;
                if (combo_ > max_combo_)
                    max_combo_ = combo_;
                return 200;
            }
            else if (a <= 127 - (3 * od))
            {
                num_good_++;
                combo_++;
                if (combo_ > max_combo_)
                    max_combo_ = combo_;
                return 100;
            }
            else if (a <= 151 - (3 * od))
            {
                num_bad_++;
                combo_++;
                if (combo_ > max_combo_)
                    max_combo_ = combo_;
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

        auto find_nearest_note = [&](int x) -> HitObject * {
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
            //hitsound_->play();
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
            //hitsound_->play();
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
            //hitsound_->play();
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
    else if (ev_type_ == EventType::ScoreScreen)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            reset();
    }
}

void Playfield::render()
{
    sf::Sprite bg;
    bg.setTexture(*bg_texture_);

    window_->draw(bg);
    if (ev_type_ == EventType::Gameplay)
    {
        int curMs = time_.getElapsedTime().asMilliseconds();

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
        acc.setFont(*main_font_);
        acc.setString(std::to_string((int)(accuracy_ * 100)) + '%');
        acc.setCharacterSize(54);
        acc.setFillColor(sf::Color::Blue);
        acc.setPosition(800, 20);

        combo.setFont(*main_font_);
        combo.setString(std::to_string(combo_));
        combo.setCharacterSize(28);
        combo.setPosition(500, 500);

        score.setFont(*main_font_);
        score.setString(std::to_string(score_));
        score.setCharacterSize(28);
        score.setPosition(1000, 20);

        info.setFont(*main_font_);
        std::string str("Marvelous: " + std::to_string(num_marvelous_) + "\nPerfect: " + std::to_string(num_perfect_) + "\nGreat: " + std::to_string(num_great_) + "\nGood: " + std::to_string(num_good_) + "\nBad: " + std::to_string(num_bad_) + "\nMiss: " + std::to_string(num_miss_));
        info.setString("hello");
        info.setCharacterSize(20);
        info.setPosition(20, 20);
        info.setFillColor(sf::Color::Black);

        window_->draw(acc);
        window_->draw(score);
        window_->draw(combo);
        window_->draw(info);
    }
    else if (ev_type_ == EventType::ScoreScreen)
    {
        sf::Sprite ss;
        ss.setTexture(*scorescreen_texture_);
        ss.setPosition(20, 20);
        window_->draw(ss);

        sf::Text acc, combo, score, info;
        acc.setFont(*main_font_);
        acc.setString(std::to_string((int)(accuracy_ * 100)) + '%');
        acc.setCharacterSize(42);
        acc.setFillColor(sf::Color::Blue);
        acc.setPosition(260, 120);

        combo.setFont(*main_font_);
        combo.setString(std::to_string(max_combo_));
        combo.setCharacterSize(42);
        combo.setPosition(260, 196);

        score.setFont(*main_font_);
        score.setString(std::to_string(score_));
        score.setCharacterSize(42);
        score.setPosition(260, 50);

        info.setFont(*main_font_);
        std::string str("Marvelous: " + std::to_string(num_marvelous_) + "\nPerfect: " + std::to_string(num_perfect_) + "\nGreat: " + std::to_string(num_great_) + "\nGood: " + std::to_string(num_good_) + "\nBad: " + std::to_string(num_bad_) + "\nMiss: " + std::to_string(num_miss_));
        info.setString(str);
        info.setCharacterSize(20);
        info.setPosition(40, 260);
        info.setFillColor(sf::Color::Black);

        window_->draw(acc);
        window_->draw(score);
        window_->draw(combo);
        window_->draw(info);

        sf::Sprite rank;
        if (accuracy_ == 1)
            rank.setTexture(*ranking_ss_);
        else if (accuracy_ > 0.95)
            rank.setTexture(*ranking_s_);
        else if (accuracy_ > 0.90)
            rank.setTexture(*ranking_a_);
        else if (accuracy_ > 0.80)
            rank.setTexture(*ranking_b_);
        else if (accuracy_ > 0.70)
            rank.setTexture(*ranking_c_);
        else
            rank.setTexture(*ranking_d_);

        rank.setPosition(650, 20);
        window_->draw(rank);
    }
}

void Playfield::reset()
{
    time_.restart();
    accuracy_ = 1;
    combo_ = 0;
    max_combo_ = 0;
    score_ = 0;
    num_bad_ = num_good_ = num_great_ = num_perfect_ = num_marvelous_ = num_miss_ = 0;
    ev_type_ = EventType::Gameplay;
    for (auto note : current_beatmap_->hit_objects)
        note->unpress();
    soundtrack_.play();
}
} // namespace noma
