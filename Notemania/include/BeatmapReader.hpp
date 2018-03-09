#ifndef NOMA_BEATMAP_READER_HPP_ 
#define NOMA_BEATMAP_READER_HPP_

#include <string>

namespace noma
{
    class Beatmap;

    class BeatmapReader
    {
    public:
        static Beatmap* load_beatmap_from_file(std::string filename);
        static void save_beatmap_to_file(Beatmap* beatmap, std::string filename);

    private:
        static std::istream& sgetline(std::istream& is, std::string& t);
    };
} // namespace noma

#endif // NOMA_BEATMAP_READER_HPP_
