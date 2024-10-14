#include "Constants.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <filesystem>
#include <iostream>
#include <optional>

constexpr const char* kTitle = "Ball Defender";

std::optional<std::filesystem::path> parseArgs(int argc, char* argv[]) {
  if (argc < 2) {
    return std::nullopt;
  }
  auto resourcesPath = std::filesystem::path{argv[1]};
  return resourcesPath.empty() ? std::nullopt
                               : std::make_optional(resourcesPath);
}

int main(int argc, char* argv[]) {
  auto resourcesPath = parseArgs(argc, argv);
  if (!resourcesPath.has_value()) {
    std::cerr << "Missing path to resources\n";
    std::exit(1);
  }

  auto window = sf::RenderWindow{{bd::kWindowSizeX, bd::kWindowSizeY},
                                 kTitle,
                                 sf::Style::Titlebar | sf::Style::Close};
  window.setFramerateLimit(144);

  bd::Game gameInstance(&window, *resourcesPath);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      gameInstance.handleEvent(event);
    }
    window.clear();

    gameInstance.run();

    window.display();
  }

  return 0;
}
