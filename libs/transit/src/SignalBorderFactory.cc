#include "SignalBorderFactory.h"

IEntity* SignalBorderFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("signal border") == 0) {
    std::cout << "Signal Border Created" << std::endl;
    return new SignalBorder(entity);
  }
  return nullptr;
}
