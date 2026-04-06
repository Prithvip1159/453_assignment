#include "Game.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(0));

    Game game;
    game.start();

    return 0;
}