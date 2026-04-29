#include "track.h"

bool running = true;
uint8_t count = 0; // needs to be connected with sensor

void runTrack() {
	while (running) {
		//We make switch cases for all stages of the track
		switch(count) {
      case 0:
        //Start
        break;
      case 1:
        //Før bakke
        break;
      case 2:
        //Før bakke
        break;
      case 3:
        //Top af bakke
        break;
      case 4:
        //Efter bakke
        break;
      case 5:
        //gør klar til stop
        break;
      case 6:
        //Stop, og bak
        break;
      case 7: // sensor 5 igen
        // Stop og kør frem igen
        break;
      case 8:
        //klar til stop snart
        break;
      case 9:
        //STOP!
        break;
      default:
        // kør fremad
        break;
      }

    
      // stop loopet (sikre at det hele er kørt)
      // running = false;
    }
}

