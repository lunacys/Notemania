#include "Notemania.hpp"

int main(int argc, char** argv)
{
    noma::Notemania* game = new noma::Notemania();
    game->run();
    delete game;

    return 0;
}

