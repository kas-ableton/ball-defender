#include "Constants.hpp"
#include "GameView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace bd {

GameView::GameView(sf::RenderWindow* window) : mpWindow(window) {}

void GameView::addDrawObject(sf::Drawable* object) {
  mDrawObjects.push_back(object);
}

void GameView::draw() {
  mpWindow->clear();

  for (const auto& obj : mDrawObjects) {
    mpWindow->draw(*obj);
  }

  mpWindow->display();
}

void GameView::setup() {
  mpPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));
  mpPlayArea->setFillColor(sf::Color(100, 250, 50));
  mpPlayArea->setPosition(bd::kWindowPadding, bd::kWindowPadding);

  addDrawObject(mpPlayArea.get());

  mpBall = std::make_unique<sf::CircleShape>(kBallRadius);
  mpBall->setFillColor(sf::Color(250, 250, 250));
  mpBall->setPosition(bd::kWindowPadding + mpPlayArea->getSize().x / 2,
                      mpPlayArea->getSize().y);

  addDrawObject(mpBall.get());
}

}
