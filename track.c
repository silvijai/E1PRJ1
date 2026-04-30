#include "track.h"
#include "motor.h"
#include "sensor.h" //nødvendigt for at få fat i count

bool running = true;

volatile uint8_t count = 0;
uint8_t lastCount = 255;

void runTrack() {
	while (running) {
		//We make switch cases for all stages of the track
    
    if (count != lastCount) {
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
          motorSetSpeed(150);
          break;
        case 7:
          // bliv ved
          break;
        case 8:
          //Stop, og bak
          motorSetDirection(false);
          motorSetSpeed(150);
          break;
        case 9: // sensor 5 igen
          // Stop og kør frem igen
          motorSetDirection(true);
          motorSetSpeed(250);
          break;
        case 10:
          //klar til stop snart
          motorSetSpeed(200);
          break; 
        case 11:
          //STOP!
          _delay_ms(1500);
          motorSetSpeed(0);
          running = false;
          break;
        default:
          // kør fremad
          break;
        }

        lastCount = count;
      }
    
      // stop loopet (sikre at det hele er kørt)
      // running = false;
  }
}

