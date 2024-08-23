#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace bd
{

Game::Game(sf::RenderWindow* window) : mWindow(window) {}

void Game::Start() {
  mWindow->clear();

  mWindow->display();
}

enum Game::State Game::State() const {
    return mState;
}

}
