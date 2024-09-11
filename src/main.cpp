#include "Constants.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <tuple>

constexpr const char* kTitle = "Ball Defender";

int main() {
  auto window = sf::RenderWindow{{bd::kWindowSizeX, bd::kWindowSizeY},
                                 kTitle,
                                 sf::Style::Titlebar | sf::Style::Close};
  window.setFramerateLimit(144);

  bd::Game gameInstance(&window);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      gameInstance.handleEvent(event);
    }

    gameInstance.run();
  }

  return 0;
}
