#ifndef NOMA_SCREEN_MANAGER_HPP_
#define NOMA_SCREEN_MANAGER_HPP_

#include <string>
#include <map>
#include "Screen.hpp"
#include "IScreenManager.hpp"

namespace noma
{

    class ScreenManager : public IScreenManager
    {
    public:
        ScreenManager();

        virtual Screen* find_screen(const std::string& name) override;
        Screen* register_screen(Screen* screen, const std::string& name);
        void initialize();
        void update(double dt);
        void render();


    private:
        std::map<std::string, Screen*> screens_;
    };
} // namespace noma

#endif // NOMA_SCREEN_MANAGER_HPP_

