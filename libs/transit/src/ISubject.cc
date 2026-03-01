#include "ISubject.h"

ISubject::ISubject(JsonObject& obj) : IEntity(obj) {}

ISubject::~ISubject() {}
void ISubject::registerObserver(IObserver& obs) {
    reg_observers.push_back(&obs);
}

void ISubject::unregisterObserver(IObserver& obs) {
    for (int i = 0; i < reg_observers.size(); i++) {
        if (&obs == reg_observers[i]) {
            reg_observers.erase(reg_observers.begin() + i);
            return;
        }
    }
}
void ISubject::notifyObservers() const {
    for (int i = 0; i < reg_observers.size(); i++) {
        reg_observers[i]->notify();
    }
}
