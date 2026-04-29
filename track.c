#include "track.h"
#include "sensor.h" //nødvendigt for at få fat i count

bool running = true;

uint8_t last_count = 255; //højt tal som count aldrig er

void runTrack() {
	while (running) {
		//We make switch cases for all stages of the track

    if (count != last_count) {
      last_count = count;
      
      switch(count) {
        case 0:
          //Start
          motorSetSpeed(200);
          break;
        case 1:
          //Før bakke
          motorSetSpeed(200);
          break;
        case 2:
          //Før bakke
          motorSetSpeed(150);
          break;
        case 3:
          //Top af bakke
          motorSetSpeed(100);
          break;
        case 4:
          //Efter bakke
          motorSetSpeed(200);
          break;
        case 5:
          //gør klar til stop
          motorSetSpeed(100);
          break;
        case 6:
          //Stop, og bak
          motorSetDirection(false);
          motorSetSpeed(150);
          break;
        case 7: // sensor 5 igen
          // Stop og kør frem igen
          motorSetDirection(true);
          motorSetSpeed(250);
          break;
        case 8:
          //klar til stop snart
          motorSetSpeed(200);
          break;
        case 9:
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
}

