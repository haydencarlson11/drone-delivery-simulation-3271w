#include "RadioTowerFactory.h"

IEntity* RadioTowerFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("radio tower") == 0) {
    std::cout << "Radio Tower Created" << std::endl;
    return new RadioTower(entity);
  }
  return nullptr;
}
