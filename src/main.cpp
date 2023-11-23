#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

namespace constants {
inline constexpr int screenWidth = 1920;
inline constexpr int screenHeight = 1080;
inline constexpr int gap = 10;
inline constexpr int vecLength = screenWidth;
inline constexpr int rectWidth = screenWidth / vecLength;
} // namespace constants

std::vector<int> generatevector(int size) {
  std::vector<int> retvec(size);
  std::mt19937 gen;
  std::uniform_int_distribution<int> get(
      constants::gap, constants::screenHeight - constants::gap);

  for (auto &i : retvec) {
    i = get(gen);
  }

  return retvec;
}

int partition(std::vector<int> &vec, int left, int right,
              std::vector<sf::RectangleShape *> &vecRects,
              sf::RenderWindow &window) {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(10ms);
  sf::RectangleShape *rect;
  int pivot = right;
  int i = left;
  for (int j = left; j < right; j++) {
    if (vec[j] < vec[pivot]) {
      std::swap(vec[i], vec[j]);
      ++i;
    }
  }
  std::swap(vec[i], vec[pivot]);

  for (int i = 0; i < vec.size(); ++i) {
    int value = vec[i];
    rect = new sf::RectangleShape;
    rect->setSize(sf::Vector2f(constants::rectWidth, value));
    rect->setPosition(constants::rectWidth * i,
                      constants::screenHeight - value);
    if (i == pivot) {
      rect->setFillColor(sf::Color::Red);
    } else if (i == left) {
      rect->setFillColor(sf::Color::Blue);
    } else {
      rect->setFillColor(sf::Color::White);
    }

    vecRects[i] = rect;
  }

  window.clear();
  for (sf::RectangleShape *rect : vecRects) {
    window.draw(*rect);
    delete rect;
  }
  window.display();

  return i;
}

void quickSort(std::vector<int> &vec, int left, int right,
               std::vector<sf::RectangleShape *> &vecRects,
               sf::RenderWindow &window) {
  if (left >= right)
    return;

  int middle = partition(vec, left, right, vecRects, window);
  quickSort(vec, left, middle - 1, vecRects, window);
  quickSort(vec, middle + 1, right, vecRects, window);
}

int main() {
  sf::RenderWindow window{
      sf::VideoMode(constants::screenWidth, constants::screenHeight), "Satris"};
  sf::Event event;
  std::vector<int> vecToSort = generatevector(constants::vecLength);
  std::vector<sf::RectangleShape *> vecRects(constants::vecLength);

  while (window.isOpen()) {

    quickSort(vecToSort, 0, vecToSort.size() - 1, vecRects, window);
    window.close();
  }

  // window.clear();
  // for (auto rect : vecRects) {
  //   window.draw(*rect);
  // }
  // window.display();

  return 0;
}
