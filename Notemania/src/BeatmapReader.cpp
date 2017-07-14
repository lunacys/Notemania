#include "BeatmapReader.hpp"

namespace noma
{
    std::unique_ptr<Beatmap> BeatmapReader::load_beatmap_from_file(std::string filename)
    {
        
        return noma::make_unique<Beatmap>();
    }

    void BeatmapReader::save_beatmap_to_file(std::unique_ptr<Beatmap> beatmap, std::string filename)
    {
        
    }
} // namespace noma
