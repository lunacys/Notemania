#include "Note.hpp"
#include <stdexcept>

namespace noma
{
    Note::Note(int x, int time, NoteType type, int endTime)
    {
        if (x < 1 || x > 9) throw std::runtime_error("x cannot be less than 1 and greater than 9");
        if (endTime < time) throw std::runtime_error("endTime cannot be less than time");
        x_ = x;
        time_ = time;
        type_ = type;
        endTime_ = (endTime == 0 ? time : endTime);
    }

    Note::~Note() { }

    int Note::get_x() const
    {
        return x_;
    }

    int Note::get_time() const
    {
        return time_;
    }

    int Note::get_endtime() const
    {
        return endTime_;
    }

    NoteType Note::get_type() const
    {
        return type_;
    }

    bool Note::is_hold_note() const
    {
        return type_ == NoteType::Hold;
    }
}
