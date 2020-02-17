#include "fsm.h"
#include "changeDispenser.h"
#include "coinAcceptor.h"
#include "colaDispenser.h"
#include "display.h"


typedef enum {
   S_NO,
   S_START,
   S_INITIALISED,
   S_WAIT_FOR_COINS,
   S_DETECTED_10C,
   S_DETECTED_20C,
   S_DISPENSE,
   S_WAIT_FOR_UPDATE_CHANGE
} state_e;

state_e currentState = S_START;
event_e event = E_NO;
int insertedMoney = 0;
int priceCola = 0;
int change = 0;
int availableChange = 0;

/// Because we do not buffer events in an event queue, we send in the
/// current state, #currentState, only events that can be handled.
/// Implementing buffering using a queue and multi-threading is outside
/// the scope of this introduction to C programming.
/// \return Generated event for the #eventHandler function.
event_e generateEvent(void)
{
   event_e evnt = E_NO;
   switch (currentState)
   {
      case S_NO:
         DSPshowSystemError("current state is not initialised");
         break;
      case S_START:
         break;
      case S_INITIALISED:
         evnt = E_CONTINUE;
         break;
      case S_WAIT_FOR_COINS:
         DSPclearLine(5);
         DSPshow("Enter your coins please", 3);
         evnt = CNAcheckCoins();
         break;
      case S_DETECTED_10C:
         evnt = CVMcheckCents(10);
         DSPshow("     10C", 5);
         break;
      case S_DETECTED_20C:
         evnt = CVMcheckCents(20);
         DSPshow("     20C", 5);
         break;
      case S_DISPENSE:
         evnt = CVMcheckChange();
         break;
      case S_WAIT_FOR_UPDATE_CHANGE:
         break;
   }

   return evnt;
}

/// Uses the global variable #currentState to determine how to process the
/// received #event.
/// If an #event is received that should not be in handled in the
/// currentState this is considered as a system error.
/// The switch statements use the default case to show an appropriate
/// message to the display. It is necessary to give in all default cases
/// the nextState an appropriate value to avoid undefined behaviour. \post
/// Updated #currentState by nextSate.
void eventHandler(event_e event)
{
   state_e nextState = S_NO;

   switch (currentState)
   {
      case S_START:
         event = CVMinitialise();
         nextState = S_INITIALISED;
         break;

      case S_INITIALISED:
         insertedMoney = 0;
         priceCola = 125;
         change = 0;
         availableChange = 20;
         event = E_CONTINUE;
         nextState = S_WAIT_FOR_COINS;
         break;

      case S_WAIT_FOR_COINS:
         switch (event)
         {
            case E_10C:
               nextState = S_DETECTED_10C;
               break;
            case E_20C:
               nextState = S_DETECTED_20C;
               break;
            default:
               DSPshowSystemError(
                  "State S_WAIT_FOR_COINS received unknown event");
               nextState = S_WAIT_FOR_COINS;
         }
         break;

      case S_DETECTED_10C:
         switch (event)
         {
            case E_NOT_ENOUGH:
               nextState = S_WAIT_FOR_COINS;
               break;
            case E_ENOUGH:
               nextState = S_DISPENSE;
               break;
            default:
               DSPshowSystemError(
                  "State S_DETECTED_10C received unknown event");
               nextState = S_WAIT_FOR_COINS;
               break;
         }
         break;

      case S_DETECTED_20C:
         switch (event)
         {
            case E_NOT_ENOUGH:
               nextState = S_WAIT_FOR_COINS;
               break;
            case E_ENOUGH:
               nextState = S_DISPENSE;
               break;
            default:
               DSPshowSystemError(
                  "State S_DETECTED_20C received unkown event");
               nextState = S_WAIT_FOR_COINS;
               break;
         }
         break;

      case S_DISPENSE:
         switch (event)
         {
            case E_NO_CHANGE_DISPENSE:
               DSPshowDelete("Sorry, no change available", 3);
               CHDdispenseChange(insertedMoney);
               insertedMoney = 0;
               nextState = S_WAIT_FOR_UPDATE_CHANGE;
               break;
            case E_CHANGE_DISPENSE:
               DSPshowDelete("Please take your cola", 3);
               CLDdispenseCola();
               CHDdispenseChange(change);
               insertedMoney = 0;
               nextState = S_WAIT_FOR_COINS;
               break;
            default:
               DSPshowSystemError(
                  "State S_DISPENSE received unknown event");
               nextState = S_WAIT_FOR_COINS;
               break;
         }
         break;

      case S_WAIT_FOR_UPDATE_CHANGE:
         DSPshow("Ask administrator to fill change storage ... done", 3);
         availableChange = 20;
         nextState = S_WAIT_FOR_COINS;
         break;

      default:
         DSPshowSystemError("CVM in unknown current state");
         nextState = S_INITIALISED;
         break;
   }
   currentState = nextState;
}

//------------------------------------------------ CVM functions executed
//in FSM

/// Initialises all subsystems (devices) and puts an initial text to the
/// display.
/// Error conditions of initialised subsystems are ignored.
/// For that reason #E_NO is returned.
/// \todo Handle error conditions generated by the initialisation of every
/// subsystem in an error handling state. All subsystem initialisation
/// functions should return an event about the initialisation result (error
/// condition).
event_e CVMinitialise(void)
{
   DSPinitialise();
   CNAinitialise();
   CLDinitialise();
   CHDinitialise();

   return E_NO;
}

event_e CVMcheckCents(int coinValue)
{
   insertedMoney += coinValue;
   if (insertedMoney >= priceCola)
   {
      return E_ENOUGH;
   }
   return E_NOT_ENOUGH;
}

event_e CVMcheckChange(void)
{
   change = insertedMoney - priceCola;
   if (availableChange >= change)
   {
      availableChange -= change;
      return E_CHANGE_DISPENSE;
   }
   return E_NO_CHANGE_DISPENSE;
}
