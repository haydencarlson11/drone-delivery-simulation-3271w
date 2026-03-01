#ifndef SIGNAL_BORDER_H_
#define SIGNAL_BORDER_H_

#include "IEntity.h"

/**
 * @class SignalBorder
 * @brief Represents a Signal Border for a Radio Tower in a physical system. 
 * Signal Borders are centered on the coordinates of their respective Radio Towers, 
 */
class SignalBorder : public IEntity {
 public:
  /**
  * @brief SignalBorders are created with a name
  * @param obj JSON object containing the SignalBorder's information
  */
  SignalBorder(JsonObject& obj);

  /**
  * @brief Destructor
  */
  ~SignalBorder();

  /**
   * @brief Updates the border, which rotates it
   * 
   * @param dt difference in time since last update
  */
  void update(double dt);
};

#endif
