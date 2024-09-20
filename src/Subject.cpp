
namespace bd
{
void Subject::addObserver(Subject::Observer observer) {
  mObservers.insert(observer);
}

void Subject::removeObserver(Subject::Observer observer) {
  mObservers.remove(observer);
}

void Subject::notifyObservers() {
  for (auto observer : mObservers)
  {
    observer();
  }
}
}
