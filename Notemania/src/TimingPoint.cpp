#include "TimingPoint.hpp"
#include <stdexcept>

namespace noma
{
    TimingPoint::TimingPoint(int position, double msPerBeat,
                             int timeSignature, int hitSoundVolume,
                             bool resetMetronome)
        : position_(position), msPerBeat_(msPerBeat),
          timeSignature_(timeSignature), hitSoundVolume_(hitSoundVolume),
          resetMetronome_(resetMetronome)
    {
        if (hitSoundVolume < 5 || hitSoundVolume > 100)
            throw std::runtime_error("hitSoundVolume cannot be less than 5 and more than 100");
    }

    TimingPoint::~TimingPoint() { }

    int TimingPoint::get_position() const
    {
        return position_;
    }

    double TimingPoint::get_ms_per_beat() const
    {
        return msPerBeat_;
    }

    int TimingPoint::get_time_signature() const
    {
        return timeSignature_;
    }

    int TimingPoint::get_hitsound_volume() const
    {
        return hitSoundVolume_;
    }

    bool TimingPoint::should_reset_metronome() const
    {
        return resetMetronome_;
    }

    double TimingPoint::get_bpm() const
    {
        return 60000 / msPerBeat_;
    }

    double TimingPoint::bpm_to_ms_per_beat(double bpm)
    {
        return 60000 / bpm;
    }
} // namespace noma
