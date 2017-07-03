#ifndef NOMA_NOTE_HPP_
#define NOMA_NOTE_HPP_

namespace noma
{
    enum class NoteType
    {
        Click,
        Hold
    };

    class Note
    {
    public:
        Note(int x, int time, NoteType type, int endTime = 0);
        virtual ~Note();

        int get_x() const;
        int get_time() const;
        int get_endtime() const;
        NoteType get_type() const;

        bool is_hold_note() const;

    private:
        NoteType type_;
        int x_;
        int time_;
        int endTime_;
    };
} // namespace noma

#endif // NOMA_NOTE_HPP_
