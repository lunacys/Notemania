#include "BeatmapReader.hpp"

namespace noma
{
    Beatmap* BeatmapReader::load_beatmap_from_file(std::string filename)
    {
        std::ifstream file(filename);

        if (file)
        {
            std::stringstream ss;

            ss << file.rdbuf();

            file.close();

            BeatmapSettingsGeneral general;
            BeatmapSettingsMetadata metadata;
            BeatmapSettingsEditor editor;
            BeatmapSettingsDifficulty diff;

            std::vector<TimingPoint*> timingPoints;
            std::vector<HitObject*> hitObjects;

            std::string tmp;

            auto get_value = [&ss, &tmp] (const std::string& key) -> std::string
                {
                    std::getline(ss, tmp);
                    if (tmp.find(key) == 0)
                    {
                        return tmp.substr(key.size());
                    }
                };

            while(std::getline(ss, tmp))
            {
                if (tmp == "[General]")
                {
                    general.audio_filename = get_value("AudioFilename:");
                    general.preview_time = std::stoi(get_value("PreviewTime:"));
                }
                std::getline(ss, tmp);
                if (tmp == "[Editor]")
                {
                    editor.beat_divisor = std::stoi(get_value("BeatDivisor:"));
                }
                std::getline(ss, tmp);
                if (tmp == "[Metadata]")
                {
                    metadata.title = get_value("Title:");
                    metadata.artist = get_value("Artist:");
                    metadata.creator = get_value("Creator:");
                    metadata.version = get_value("Version:");
                    metadata.tags = get_value("Tags:");
                    metadata.beatmap_id = std::stoi(get_value("BeatmapID:"));
                    metadata.beatmap_set_id = std::stoi(get_value("BeatmapSetID:"));
                }
                std::getline(ss, tmp);
                if (tmp == "[Difficulty]")
                {
                    diff.hp_drain_rate = std::stod(get_value("HPDrainRate:"));
                    diff.overall_difficulty = std::stod(get_value("OverallDifficulty:"));
                    diff.key_amount = std::stoi(get_value("KeyAmount:"));
                }
                std::getline(ss, tmp);
                if (tmp == "[TimingPoints]")
                {
                    std::getline(ss, tmp);
                    while(tmp != "[HitObjects]")
                    {
                        std::istringstream iss(tmp);
                        std::vector<std::string> tokens;
                        std::copy(std::istream_iterator<std::string>(iss),
                                  std::istream_iterator<std::string>(),
                                  std::back_inserter(tokens));

                        TimingPoint* tp = new TimingPoint(std::stoi(tokens[0]),
                                                          std::stod(tokens[1]),
                                                          std::stoi(tokens[2]),
                                                          std::stoi(tokens[3]),
                                                          (bool)std::stoi(tokens[4]));
                        timingPoints.push_back(tp);

                        std::getline(ss, tmp);
                    }
                }
                if (tmp == "[HitObjects]")
                {
                    while(std::getline(ss, tmp))
                    {
                        std::istringstream iss(tmp);
                        std::vector<std::string> tokens;
                        std::copy(std::istream_iterator<std::string>(iss),
                                  std::istream_iterator<std::string>(),
                                  std::back_inserter(tokens));

                        if (tokens.size() == 3)
                        {
                            HitObject* obj = new HitObject(std::stoi(tokens[0]),
                                                           std::stoi(tokens[1]),
                                                           HitObjectType::Click);
                            hitObjects.push_back(obj);
                        }
                        else if (tokens.size() == 4)
                        {
                            HitObject* obj = new HitObject(std::stoi(tokens[0]),
                                                           std::stoi(tokens[1]),
                                                           HitObjectType::Hold,
                                                           std::stoi(tokens[3]));
                            hitObjects.push_back(obj);
                        }
                    }
                }
            }
        }

        return nullptr;
    }

    void BeatmapReader::save_beatmap_to_file(Beatmap* beatmap, std::string filename)
    {
        std::ofstream outFile (filename);

        outFile << "[General]\n";
        outFile << "AudioFilename:"
                << beatmap->settings->general.audio_filename
                << std::endl;
        outFile << "PreviewTime:"
                << std::to_string(beatmap->settings->general.preview_time)
                << std::endl;

        outFile << "[Editor]\n";
        outFile << "BeatDivisor:"
                << beatmap->settings->editor.beat_divisor
                << std::endl;

        outFile << "[Metadata]\n";
        outFile << "Title:"
                << beatmap->settings->metadata.title
                << std::endl;
        outFile << "Artist:"
                << beatmap->settings->metadata.artist
                << std::endl;
        outFile << "Creator:"
                << beatmap->settings->metadata.creator
                << std::endl;
        outFile << "Version:"
                << beatmap->settings->metadata.version
                << std::endl;
        outFile << "Tags:"
                << beatmap->settings->metadata.tags
                << std::endl;
        outFile << "BeatmapID:"
                << std::to_string(beatmap->settings->metadata.beatmap_id)
                << std::endl;
        outFile << "BeatmapSetID:"
                << std::to_string(beatmap->settings->metadata.beatmap_set_id)
                << std::endl;

        outFile << "[Difficulty]\n";
        outFile << "HPDrainRate:"
                << beatmap->settings->difficulty.hp_drain_rate
                << std::endl;
        outFile << "OverallDifficulty:"
                << beatmap->settings->difficulty.overall_difficulty
                << std::endl;
        outFile << "KeyAmount:"
                << beatmap->settings->difficulty.key_amount
                << std::endl;

        outFile << "[TimingPoints]\n";
        for (auto tp : beatmap->timing_points)
        {
            outFile << tp->get_position() << " "
                    << std::fixed << std::setprecision(12) << tp->get_ms_per_beat() << " "
                    << tp->get_time_signature() << " "
                    << tp->get_hitsound_volume() << " "
                    << tp->should_reset_metronome() << std::endl;
        }

        outFile << "[HitObjects]\n";
        for (auto obj : beatmap->hit_objects)
        {
            switch (obj->get_type())
            {
            case HitObjectType::Click:
                outFile << std::to_string(obj->get_x())  << " "
                        << std::to_string(obj->get_time()) << " "
                        << std::to_string(1) << std::endl;
                break;
            case HitObjectType::Hold:
                outFile << std::to_string(obj->get_x())  << " "
                        << std::to_string(obj->get_time()) << " "
                        << std::to_string(2) << " "
                        << std::to_string(obj->get_endtime()) << std::endl;
                break;
            default: break;
            }
        }

        outFile.close();

    }
} // namespace noma
