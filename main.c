#include "main.h"
#include "gameController.h"
#include "images/trophy.h"
#include "images/maze.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  WIN
};

u32 previousButtons;
u32 currentButtons;

int offset;

enum gba_state state;

int main(void) {
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  previousButtons = BUTTONS;
  currentButtons = BUTTONS;

  // Load initial application state
  state = START;
  buildStart();

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    waitForVBlank();
    if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
      resetApp();
      state = START;
      buildStart();
    }    

    switch (state) {
      case START:
        start();
        break;

      case PLAY:
        play();
        break;

      case WIN:
        win();
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }
    
  return 0;
}

//initializes start state
void buildStart(void) {
      //drawFullScreenImageDMA(startScreen);
      drawFullScreenImageDMA(maze);
      drawCenteredString(30, 105, 15, 15, "Maze Game", RED);
      drawCenteredString(80, 110, 8, 8, "press start", RED);

    }

    void start(void) {
      if KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons) {
        buildPlay();
      }
    }

    //switches to play state, updates background, and builds assets
    void buildPlay(void) {
      offset = vBlankCounter;
      state = PLAY;
      fillScreenDMA(BLUE);
      buildMaze();
      buildGoal();
      buildCharacter();

    }

    //checks for character state changes and checks for win condition
    void play(void) {
      updateCharacterState(currentButtons, previousButtons);
      updateTimer(offset);
      if (atGoal()) {
        buildWin();
      }

    }

    //switches to win state and displays score
    void buildWin(void) {
      state = WIN;
      int score = vBlankCounter;
      char str[10];

      sprintf(str, "%d", score);
      drawFullScreenImageDMA(trophy);
      drawCenteredString(30, 105, 15, 15, "You Win!", RED);
      drawCenteredString(50, 110, 8, 8, "Score:", RED);
      drawCenteredString(50, 140, 8, 8, str, RED);

      drawCenteredString(80, 110, 8, 8, "press start", RED);
      drawCenteredString(90, 110, 8, 8, "to play again", RED);
    }


    void win(void) {
      if KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons) {
        resetApp();
        buildPlay();
      } 
    }

