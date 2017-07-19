#include "ScreenManager.hpp"

namespace noma
{
    ScreenManager::ScreenManager() { }

    Screen* ScreenManager::find_screen(const std::string& name)
    {
        auto screen = screens_.find(name);
        if (screen == screens_.end())
            return nullptr;
        else
            return screens_[name];
    }

    Screen* ScreenManager::register_screen(Screen *screen, const std::string& name)
    {
        screen->screen_manager = this;
        screens_[name] = screen;

        if (screens_.size() == 1)
            screens_[name]->show();

        return screen;
    }

    void ScreenManager::initialize()
    {
        for (auto screen : screens_)
            screen.second->initialize();
    }

    void ScreenManager::update(double dt)
    {
        for (auto screen : screens_)
            if (screen.second->is_visible)
                screen.second->update(dt);
    }

    void ScreenManager::render()
    {
        for (auto screen : screens_)
            if (screen.second->is_visible)
                screen.second->render();
    }

} // namespace noma
