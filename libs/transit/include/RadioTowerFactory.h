#ifndef RADIO_TOWER_FACTORY_H_
#define RADIO_TOWER_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "RadioTower.h"

/**
 * @brief Radio tower factory to produce radio tower class.
 **/
class RadioTowerFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for RadioTowerFactory class.
   **/
  virtual ~RadioTowerFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
