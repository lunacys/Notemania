#ifndef NOMA_SCREEN_HPP_
#define NOMA_SCREEN_HPP_

#include "IScreenManager.hpp"

namespace noma
{
    class Screen
    {
    public:
        Screen* find_screen();

        Screen* find_screen(const std::string& name);
        void show(const std::string& name, bool hideThis);
        void show();
        void hide();

        virtual void initialize();
        virtual void update(double dt);
        virtual void render();

        IScreenManager* screen_manager;
        bool is_initialized;
        bool is_visible;

    protected:
        Screen();

    private:

    };

} // namespace noma

#endif // NOMA_SCREEN_HPP_

