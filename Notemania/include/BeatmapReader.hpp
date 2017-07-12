#ifndef NOMA_BEATMAP_READER_HPP_
#define NOMA_BEATMAP_READER_HPP_

#include <string>
#include <memory>
#include "Utils.hpp"
#include "Note.hpp"
#include "TimingPoint.hpp"
#include "BeatmapSettings.hpp"
#include "Beatmap.hpp"

namespace noma
{
    class BeatmapReader
    {
    public:
        static std::unique_ptr<Beatmap> load_beatmap_from_file(std::string filename);
        static void save_beatmap_to_file(std::unique_ptr<Beatmap> beatmap, std::string filename); 

    private:
    };
} // namespace noma

#endif // NOMA_BEATMAP_READER_HPP_
