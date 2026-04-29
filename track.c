#include "track.h"
#include "motor.h"
#include "sensor.h" //nødvendigt for at få fat i count

bool running = true;

volatile uint8_t count = 0;

void runTrack() {
	while (running) {
		//We make switch cases for all stages of the track
      
    switch(count) {
      case 0:
        // vent på input
        break;
      case 1:
        //Start
        motorSetSpeed(200);
        break;
      case 2:
        //Før bakke
        motorSetSpeed(200);
        break;
      case 3:
        //Før bakke
        motorSetSpeed(150);
        break;
      case 4:
        //Top af bakke
        motorSetSpeed(100);
        break;
      case 5:
        //Efter bakke
        motorSetSpeed(200);
        break;
      case 6:
        //gør klar til stop
        motorSetSpeed(100);
        break;
      case 7:
        //Stop, og bak
        motorSetDirection(false);
        motorSetSpeed(150);
        break;
      case 8: // sensor 5 igen
        // Stop og kør frem igen
        motorSetDirection(true);
        motorSetSpeed(250);
        break;
      case 9:
        //klar til stop snart
        motorSetSpeed(200);
        break;
      case 10:
        //STOP!
        motorSetSpeed(0);
        running = false;
        break;
      default:
        // kør fremad
        break;
      }

    
      // stop loopet (sikre at det hele er kørt)
      // running = false;
  }
}

