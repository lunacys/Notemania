#ifndef NOMA_ISCREEN_MANAGER_HPP_
#define NOMA_ISCREEN_MANAGER_HPP_

#include <string>

namespace noma
{
    class Screen;

    class IScreenManager
    {
    public:
        virtual Screen* find_screen(const std::string& name) = 0;
    };
} // namespace noma

#endif // NOMA_ISCREEN_MANAGER_HPP_

