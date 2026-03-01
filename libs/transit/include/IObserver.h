#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include "IEntity.h"
/**
 * @class IObserver
 * @brief This class inherits from IEntity and is the base class for all Observing objects
 * An IObserver object has a message that can be sent to the system front-end
 * using the notify() method and set to contain specific text using the 
 * setMessage() method
 */
class IObserver : public IEntity {
 public:
  /**
   * @brief Constructor with JsonObject details to define the entity
   */
  IObserver(JsonObject& obj);

  /**
   * @brief Virtual destructor for IObserver.
   */
  virtual ~IObserver();

  /**
   * @brief Sends the Observer's notification message to the front end
   */
  virtual void notify() = 0;

  /**
   * @brief Sets the Observer's message attribute 
   * @param message A string indicating what the message attribute 
   * should be set to
   */
  virtual void setMessage(std::string message) = 0;

 protected:
  std::string message;
};

#endif
