#include "HitObject.hpp"
#include <stdexcept>

namespace noma
{
    HitObject::HitObject(int x, int time, HitObjectType type, int endTime)
    {
        if (x < 1 || x > 9) throw std::runtime_error("x cannot be less than 1 and greater than 9");
        if (endTime < time) throw std::runtime_error("endTime cannot be less than time");
        x_ = x;
        time_ = time;
        type_ = type;
        endTime_ = (endTime == 0 ? time : endTime);
    }

    HitObject::~HitObject() { }

    int HitObject::get_x() const
    {
        return x_;
    }

    int HitObject::get_time() const
    {
        return time_;
    }

    int HitObject::get_endtime() const
    {
        return endTime_;
    }

    HitObjectType HitObject::get_type() const
    {
        return type_;
    }

    bool HitObject::is_hold_note() const
    {
        return type_ == HitObjectType::Hold;
    }
}
