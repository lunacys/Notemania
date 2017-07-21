#ifndef NOMA_UTILS_HPP_
#define NOMA_UTILS_HPP_

#include <memory>

namespace noma
{
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique( Args&& ...args )
    {
        return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }
} // namespace noma

#endif // NOMA_UTILS_HPP_
