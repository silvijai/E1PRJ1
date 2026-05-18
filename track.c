#include "track.h"
#include "motor.h"
#include "sensor.h"
#include "sound.h"

bool running = true;

volatile uint8_t count = 0;
uint8_t lastCount = 255;

void runTrack() {
  while (running) {
  //We make switch cases for all stages of the track
    
    if (count != lastCount) {
      switch(count) {
        case 0:
          //Start
          motorSetSpeed(255);  
          break;
        case 1:
          //Før bakke
          motorSetSpeed(255);
          playSound(2);
          break;
        case 2:
          //Før bakke
          motorSetSpeed(200);
          playSound(2);
          break;
        case 3:
          //Top af bakke
          motorSetSpeed(80);
          playSound(2);
          break;
        case 4:
          //Efter bakke
          motorSetSpeed(200);
          playSound(2);
          break;
        case 5:
          //gør klar til stop
          motorSetSpeed(180);
          playSound(2);
          break;
        case 6:
          //Stop, og bak
          motorSetDirection(false);
		      motorSetSpeed(160);
          playSound(2);
          break;
        case 7:
		      motorSetSpeed(180);
          // bliv ved
          break;
        case 8: // sensor 5 igen
          // Stop og kør frem igen
          motorSetDirection(true);
          motorSetSpeed(200);
          playSound(2);
          break;
        case 9:
          //klar til stop snart
          motorSetSpeed(255);
          playSound(2);
          break; 
        case 10: 
		      break;
		    case 11:
          //STOP!
          playSound(2);
          _delay_ms(1000);
          motorSetSpeed(0);
          running = false;
          break;
        default:
          // kør fremad
          break;
        }

      lastCount = count;
   }
  }
}

