#ifndef NOMA_SCREEN_MANAGER_HPP_
#define NOMA_SCREEN_MANAGER_HPP_

#include <string>
#include <map>

namespace noma
{
    class Screen;

    class IScreenManager
    {
    public:
        virtual Screen* find_screen(const std::string& name) = 0;
    };

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

