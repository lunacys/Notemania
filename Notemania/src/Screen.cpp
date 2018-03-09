#include "Screen.hpp"
#include "ScreenManager.hpp"

namespace noma
{
Screen::Screen() {}

Screen *Screen::find_screen(const std::string &name)
{
    if (screen_manager != nullptr)
        return screen_manager->find_screen(name);

    return nullptr;
}

void Screen::show(const std::string &name, bool hideThis)
{
    auto screen = find_screen(name);
    screen->show();

    if (hideThis)
        hide();
}

void Screen::show()
{
    if (!is_initialized)
        initialize();

    is_visible = true;
}

void Screen::hide()
{
    is_visible = false;
}

void Screen::initialize()
{
    is_initialized = true;
}

void Screen::update(double dt) {}

void Screen::render() {}

} // namespace noma
