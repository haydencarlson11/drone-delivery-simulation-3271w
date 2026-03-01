#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

#include "Package.h"
#include "SimulationModel.h"

#include "RadioTower.h"

Drone::Drone(JsonObject& obj) : ISubject(obj) {
  available = true;
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination =
          new JumpDecorator(
            new AstarStrategy(
              packagePosition,
              finalDestination,
              model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new DijkstraStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else {
        toFinalDestination = new BeelineStrategy(
          packagePosition,
          finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  // initialize inRange array for a given drone
  // only occurs during the first update of the Drone
  std::string message;
  if (inRange.size() == 0) {
    for (int i = 0; i < model->towers.size(); i++) {
        inRange.push_back(false);
    }
  }

  if (available) {
    getNextDelivery();
    // when new delivery orders are recieved, but not yet picked up
    if (!available && !pickedUp) {
    for (int i = 0; i < model->towers.size(); i++) {
        if (inRange[i]) {
          message = (getName() + " is on the way to pick up "
                  + package->getName() + ".");
          (model->towers[i])->setMessage(message);
        }
      }
    }
  }

  if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;

      // when package is successfully picked up
      for (int i = 0; i < model->towers.size(); i++) {
        if (inRange[i]) {
          message = (getName() + " picked up " + package->getName()
                  + " and is in transit.");
          (model->towers[i])->setMessage(message);
        }
      }
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      
      // when package is successfully delivered
      for (int i = 0; i < model->towers.size(); i++) {
        if (inRange[i]) {
          message = (getName() + " delivered " + package->getName() + ".");
          (model->towers[i])->setMessage(message);
        }
      }
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }

// we have finished moving
// now check if the drone is outside any of its observers' radius
// update the array of True/False values to indicate which
// towers are still in range to recieve notifications

  double dist;
  Vector3 towerPos;
  RadioTower* tower;
  IObserver* obs;
  for (int i = 0; i < model->towers.size(); i++) {
    tower = (model->towers)[i];
    towerPos = tower->getPosition();
    dist = std::sqrt(std::pow(position[0] - towerPos[0], 2)
          + std::pow(position[2] - towerPos[2], 2));
    obs = dynamic_cast<IObserver*> (tower);

    // if we were within the radius and are now out of observing range
    if (inRange[i] && (dist > tower->getRadius())) {
      message = (tower->getName() + " lost " + getName()
                + "'s signal - notifications will stop.");
      (model->towers[i])->setMessage(message);
      // the tower will be unregisterd, so call its notify method individually
      tower->notify();
      unregisterObserver(*obs);
      inRange[i] = false;

    // if we were outside the radius, but are now back in observing range
    } else if (!inRange[i] && dist < tower->getRadius()) {
      inRange[i] = true;
      registerObserver(*obs);
      message = (getName() + " has entered signal range for "
                + tower->getName() + " - now receiving notifications.");

      // if the newly recovered Drone has a package and is in transit
      if (!available && pickedUp) {
        message += ("\n" + getName() + " is in transit with "
                + package->getName() + ".");

      // if the newly recovered Drone is on the way to pick up a package
      } else if (!available && !pickedUp) {
        message += ("\n" + getName() + " is on the way to pick up "
                  + package->getName() + ".");
      }
      (model->towers[i])->setMessage(message);
    }
  }
  // notify all registered obervers for a given drone at the end of each update.
  notifyObservers();
}
