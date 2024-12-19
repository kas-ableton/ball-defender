#include "Constants.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <filesystem>
#include <iostream>
#include <optional>

constexpr const char* kTitle = "Ball Defender";
constexpr int kTitleBarHeightHeuristic = 50;

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

  auto desktop = sf::VideoMode::getDesktopMode();
  auto window = sf::RenderWindow{
      {desktop.width, desktop.height - kTitleBarHeightHeuristic},
      kTitle,
      sf::Style::Titlebar | sf::Style::Close};

  window.setVerticalSyncEnabled(true);

  bd::Game gameInstance(&window, *resourcesPath);

  // this loop is run once per frame
  // frame rate is how many frames per second
  auto time = std::chrono::steady_clock::now();
  while (window.isOpen()) {
    const auto current = std::chrono::steady_clock::now();
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      gameInstance.handleEvent(event);
    }
    window.clear();

    // time passed since last frame
    const std::chrono::duration<double> deltaTime = current - time;

    gameInstance.run(static_cast<float>(deltaTime.count()));

    window.display();

    time = current;
  }

  return 0;
}
