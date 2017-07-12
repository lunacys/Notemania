#ifndef NOMA_BEATMAP_HPP_
#define NOMA_BEATMAP_HPP_

#include <memory>
#include <vector>
#include <string>
#include "HitObject.hpp"
#include "TimingPoint.hpp"

namespace noma
{
    typedef struct
    {
        std::string audio_filename;
        int preview_time;
    } BeatmapSettingsGeneral;
    typedef struct
    {
        int beat_divisor;
    } BeatmapSettingsEditor;
    typedef struct
    {
        std::string title;
        std::string artist;
        std::string creator;
        std::string version;
        std::string tags;
        int beatmap_id;
        int beatmap_set_id;
    } BeatmapSettingsMetadata;
    typedef struct
    {
        float hp_drain_rate;
        float overall_difficulty;
        int key_amount;
    } BeatmapSettingsDifficulty;
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
        

    private:
        std::vector<std::unique_ptr<HitObject>> hitObjects_;
        std::vecotr<std::unique_ptr<TimingPoint>> timingPoints_;
    };
} // namespace noma

#endif // NOMA_BEATMAP_HPP_
