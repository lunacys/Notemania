#ifndef NOMA_BEATMAP_READER_HPP_
#define NOMA_BEATMAP_READER_HPP_

#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>
#include "TimingPoint.hpp"
#include "Beatmap.hpp"
#include <iomanip>
#include <algorithm>
#include <iterator>

namespace noma
{
    class BeatmapReader
    {
    public:
        static Beatmap* load_beatmap_from_file(std::string filename);
        static void save_beatmap_to_file(Beatmap* beatmap, std::string filename);

    private:
    };
} // namespace noma

#endif // NOMA_BEATMAP_READER_HPP_
