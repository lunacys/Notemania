#ifndef NOMA_TEST_SCREEN_HPP_
#define NOMA_TEST_SCREEN_HPP_

#include "Screen.hpp"

namespace noma 
{
    class TestScreen : public Screen 
    {
    public: 
        TestScreen() {}
        virtual ~TestScreen() {}
        virtual void initialize() override {}
        virtual void update(double dt) override {}
        virtual void render() override {}

    private:

    };
}

#endif // !NOMA_TEST_SCREEN_HPP_
