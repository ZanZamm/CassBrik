#include "game.hpp"
#include "TextureManager.hpp"

int main(int argc, char** argv)
{
    Game game;

    game.start(1);
    game.start(2);

    return 0;
}