#ifndef SIGNAL_BORDER_FACTORY_H_
#define SIGNAL_BORDER_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "SignalBorder.h"

/**
 * @brief Signal Border factory to produce SignalBorder class.
 **/
class SignalBorderFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for SignalBorderFactory class.
   **/
  virtual ~SignalBorderFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
