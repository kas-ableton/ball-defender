#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>
#include <tuple>

constexpr const char* KTitle = "Ball Defender";

struct Point {
  Point(int& _x, int& _y) : x(_x), y(_y) {}
  int x;
  int y;
};

int main()
{
    auto window = sf::RenderWindow{ { 1080u, 1080u }, KTitle, sf::Style::Titlebar | sf::Style::Close };
    window.setFramerateLimit(144);

    std::deque<Point> ClickPoints{};

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
              if (event.mouseButton.button == sf::Mouse::Left)
              {
                ClickPoints.emplace_back(event.mouseButton.x, event.mouseButton.y);
              }
            }
        }

        window.clear();

        for (auto it = ClickPoints.begin(); it != ClickPoints.end(); ++it)
        {
          sf::CircleShape dot(5.f);
          dot.setFillColor(sf::Color(100, 250, 50));
          dot.setPosition(it->x, it->y);
          window.draw(dot);
        }

        window.display();
    }

    return 0;
}
