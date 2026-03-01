#include "SignalBorder.h"

SignalBorder::SignalBorder(JsonObject& obj) : IEntity(obj) {}

SignalBorder::~SignalBorder() {}

void SignalBorder::update(double dt) {
    this->rotate(.05 * this->getSpeed());
}
