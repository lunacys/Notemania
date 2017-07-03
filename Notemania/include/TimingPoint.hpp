#ifndef NOMA_TIMING_POINT_HPP_
#define NOMA_TIMING_POINT_HPP_

namespace noma
{
    class TimingPoint
    {
    public:
        TimingPoint(int position, double msPerBeat,
                    int timeSignature, int hitSoundVolume,
                    bool resetMetronome);
        virtual ~TimingPoint();

        int get_position() const;
        double get_ms_per_beat() const;
        int get_time_signature() const;
        int get_hitsound_volume() const;
        bool should_reset_metronome() const;

        double get_bpm() const;

        static double bpm_to_ms_per_beat(double bpm);

    private:
        int position_;
        double msPerBeat_;
        int timeSignature_;
        int hitSoundVolume_;
        bool resetMetronome_;
    };
} // namespace noma

#endif // NOMA_TIMING_POINT_HPP_
