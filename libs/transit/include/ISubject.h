#ifndef ISUBJECT_H_
#define ISUBJECT_H_

#include "IObserver.h"
#include <vector>
#include "IEntity.h"

/**
 * @class ISubject
 * @brief This class inherits from IEntity and is the base class for all Subject IEntity objects
 * An ISubject object keeps track of the vector of IObserver objects
 * that are currently registered to observe it. It can register and 
 * unregister a given observer as well as notify all observers at
 * any point in time
 */
class ISubject: public IEntity {
 public:
  /**
   * @brief Constructor with JsonObject details to define the entity
  */
  ISubject(JsonObject& obj);

  /**
   * @brief Virtual destructor for ISubject.
   */
  ~ISubject();

  /**
   * @brief register an observer to the given subject
   * @param obs the observer to register
   */
  void registerObserver(IObserver& obs);

  /**
   * @brief unregister an observer to the given subject
   * @param obs the observer to unregister
   */
  void unregisterObserver(IObserver& obs);

  /**
   * @brief notify all registered observers at once
   */
  void notifyObservers() const;

 protected:
  std::vector<IObserver*> reg_observers;
};

#endif
