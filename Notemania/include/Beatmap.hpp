#ifndef NOMA_BEATMAP_HPP_
#define NOMA_BEATMAP_HPP_

#include <vector>
#include <string>
#include "HitObject.hpp"
#include "TimingPoint.hpp"

namespace noma
{
    struct BeatmapSettingsGeneral
    {
        std::string audio_filename;
        int preview_time;
        std::string background_filename;
    };
    struct BeatmapSettingsEditor
    {
        int beat_divisor;
    };
    struct BeatmapSettingsMetadata
    {
        std::string title;
        std::string artist;
        std::string creator;
        std::string version;
        std::string tags;
        int beatmap_id;
        int beatmap_set_id;
    };
    struct BeatmapSettingsDifficulty
    {
        float hp_drain_rate;
        float overall_difficulty;
        int key_amount;
    };
    struct BeatmapSettings
    {
        BeatmapSettingsGeneral general;
        BeatmapSettingsEditor editor;
        BeatmapSettingsMetadata metadata;
        BeatmapSettingsDifficulty difficulty;
    };
    class Beatmap
    {
    public:
        Beatmap();
        virtual ~Beatmap();

        BeatmapSettings* settings;

        std::vector<TimingPoint*> timing_points;
        std::vector<HitObject*> hit_objects;
    };
} // namespace noma

#endif // NOMA_BEATMAP_HPP_
