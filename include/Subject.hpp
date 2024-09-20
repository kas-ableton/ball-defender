#include <functional>
#include <list>


namespace bd
{
class Subject {
public:
  using Observer = void(*)();
  void addObserver(Observer);
  void removeObserver(Observer);
private:
  void notifyObservers();
  std::list<Observer> mObservers;
};
}
