#include <iostream>

#include "Game.h"

int main(int argc, char** argv)
{
    try
    {
        /*Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();*/

        Game::Instance().initApp();
        Game::Instance().getRoot()->startRendering();
        Game::Instance().closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

//! [fullsource]
