#include "game.hpp"

Game::Game()
{
    oWindow = new sf::RenderWindow(sf::VideoMode(640, 480), "Le Kas Brik");

}

Game::~Game()
{
}

void Game::start(int level)
{
    setLevel(level);
    running = true;

    while (running)
    {
        event();

        update();

        display();

        frameLimiter();
    }
}

void Game::event()
{
    while (oWindow->pollEvent(oEvent))
    {
        switch (oEvent.type)
        {
        //--- CLOSE ---//
        case sf::Event::Closed:
            oWindow->close();
            break;

        //--- MOUSE CLICK ---//
        case 9:
            if (listBall.size() < 3)
                listBall.push_back(new Ball(oWindow));
            break;

        default:
            break;
        }
    }
}

void Game::update()
{
    deltaTime = clock.restart();

    //--- CANON ---//
    canon.update(deltaTime, oWindow);


    for (auto itBall = listBall.begin(); itBall != listBall.end();)
    {
    //--- BALLS Collision ---//
        for (auto itBallColision = listBall.begin(); itBallColision != listBall.end(); ++itBallColision)
        {
            if (itBall == itBallColision)
                continue;

            (*itBall)->checkBounce(*itBallColision);
        }

        for (auto itTile = listTiles.begin(); itTile != listTiles.end();)
        {
            (*itBall)->checkBounce(*itTile);

    //--- TILES ---//
            if ((*itTile)->update(deltaTime, oWindow) == 1)
            {
                delete* itTile;
                itTile = listTiles.erase(itTile);
            }
            else
            {
                ++itTile;
            }
        }


    //--- BALLS ---//
        if ((*itBall)->update(deltaTime, oWindow) == 1)
        {
            delete* itBall;
            itBall = listBall.erase(itBall);
        }
        else
        {
            ++itBall;
        }
    }

    if (listTiles.empty())
    {
        running = false;

        for (auto itBall = listBall.begin(); itBall != listBall.end();)
        {
            delete* itBall;
            itBall = listBall.erase(itBall);
        }
    }
}

void Game::display()
{
    //--- CLEAR ---//
    oWindow->clear();

    //--- DRAW ---//
    // Balls
    for (int i = 0; i < listBall.size(); i++)
    {
        oWindow->draw(*listBall[i]->getHitbox());
        oWindow->draw(*listBall[i]->getShape());
    }
    // Tiles
    for (int i = 0; i < listTiles.size(); i++)
    {
        oWindow->draw(*listTiles[i]->getShape());
    }
    // Canon
    oWindow->draw(*canon.getShape());

    //--- DISPLAY ---//
    oWindow->display();
}

void Game::frameLimiter()
{
    timeElapsed = clock.getElapsedTime();
    if (timeElapsed < timePerFrame)
    {
        sf::sleep(timePerFrame - timeElapsed);
    }
}

void Game::setLevel(int level)
{
    std::string path = "level/" + std::to_string(level) + ".txt";

    std::ifstream levelTxt(path);
    std::string row;
    int i = 0;

    while (std::getline(levelTxt, row))
    {
        for (int j = 0; j < 10; j++)
        {
            if (row[j] != '0')
            {
                listTiles.push_back(new Tiles(j, i, row[j] - 48));
            }
        }
        i++;
    }
}
