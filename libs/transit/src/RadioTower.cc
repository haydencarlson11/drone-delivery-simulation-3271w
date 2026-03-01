#include "RadioTower.h"

RadioTower::RadioTower(JsonObject& obj) : IObserver(obj) {
    this->radius = obj["radius"];
    this->controller = nullptr;
}
RadioTower::~RadioTower() {}

void RadioTower::linkController(IController* controller) {
  this->controller = controller;
}

void RadioTower::update(double dt) {}

void RadioTower::setMessage(std::string message) {
    this->message = message;
}

void RadioTower::notify() {
    if (this->message != "") {
        JsonObject data;
        data["message"] = this->message;
        this->controller->sendEventToView("AddNotification", data);
        this->setMessage("");     // reset message attribute to an empty string
    }
}

double RadioTower::getRadius() const {
    return this->radius;
}
