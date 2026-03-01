#ifndef RADIO_TOWER_H_
#define RADIO_TOWER_H_

#include "IEntity.h"
#include "IObserver.h"
#include "IController.h"

/**
 * @class RadioTower
 * @brief This class inherits from IObserver. 
 * It represents a Radio Tower in a physical system. 
 * Radio towers have a radius and a link to the simulation controller. 
 * All Drones within the radius are subscribed to by the given radio tower
 */
class RadioTower : public IObserver {
 public:
  /**
   * @brief RadioTowers are created with a name
   * @param obj JSON object containing the RadioTower's information
   */
  RadioTower(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~RadioTower();

  /**
   * @brief link a radio tower to a controller
   * @param obj IController object 
   */
  void linkController(IController* controller);

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update
   */
  void update(double dt);

  /**
   * @brief Gets the radius for the given radio tower
   * @return the radius of the given radio tower
   */
  double getRadius() const;

  /**
   * @brief Sets the ratio tower's message attribute 
   * @param message A string indicating what the message attribute 
   * should be set to
   */
  void setMessage(std::string message);


  /**
   * @brief Sends the radio tower's notification message to the front end
   */
  void notify();

 protected:
    double radius;
    IController* controller;
};

#endif
