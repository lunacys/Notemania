#ifndef NOMA_NOTE_HPP_
#define NOMA_NOTE_HPP_

namespace noma
{
    enum class HitObjectType
    {
        Click,
        Hold
    };

    class HitObject
    {
    public:
        HitObject(int x, int time, HitObjectType type, int endTime = 0);
        virtual ~HitObject();

        int get_x() const;
        int get_time() const;
        int get_endtime() const;
        HitObjectType get_type() const;

        bool is_hold_note() const;

    private:
        HitObjectType type_;
        int x_;
        int time_;
        int endTime_;
    };
} // namespace noma

#endif // NOMA_NOTE_HPP_
