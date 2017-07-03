#ifndef NOMA_BEATMAP_SETTINGS_HPP_
#define NOMA_BEATMAP_SETTINGS_HPP_
#include <memory>
#include <string>
#include <vector>

#include "TimingPoint.hpp"
#include "Note.hpp"

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

        std::vector<std::unique_ptr<TimingPoint>> timing_points;
        std::vector<std::unique_ptr<Note>> hit_objects;
    };
} // namespace noma

#endif // NOMA_BEATMAP_SETTINGS_HPP_
