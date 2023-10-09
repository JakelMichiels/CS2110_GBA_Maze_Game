#include "gameController.h"
#include "gba.h"
#include "images/tresureChest.h"

#include <stdio.h>
#include <stdlib.h>

CHARACTER player;
CHARACTER oldPlayer;
WALL walls[5];
GOAL goal;
int wallCounter = 0;

//builds and draws the goal
void buildGoal(void) {
	goal.row = 120;
	goal.col = 120;
	goal.length = TRESURECHEST_HEIGHT;
	goal.width = TRESURECHEST_WIDTH;
	drawGoal();
}

void drawGoal(void) {
	drawImageDMA(goal.row, goal.col, 42, 34, tresureChest);

}

// checks if the player and the goal are overlapping
int atGoal(void) {
	if ((player.xpos + player.width < goal.col) || (player.xpos > goal.col + goal.width) || player.ypos + player.height < goal.row || player.ypos > goal.row + goal.width ) {
		return 0;
	}
	return 1;

}


void updateTimer(int offset) {
	char str[20];
	sprintf(str, "%d", vBlankCounter - offset);
	drawRectDMA(3, 199, 30, 10, BLUE);
	drawString(5, 200, str ,BLACK);

}

//builds and draws a rectangular character
void buildCharacter(void) {
	player.width = 10;
	player.height = 10;
	player.color = BLACK;
	player.xpos = 5;
	player.ypos = 5;
	drawRectDMA(player.ypos, player.xpos, player.width, player.height, player.color);

}

//adds walls to the walls array and draws them
void buildMaze (void) {
	addWall(20, 80,220 , 0);
	addWall(0, 30, 140, 0);
	addWall(100, 80, 140, 1);
	addWall(0, 195, 15, 0);
	addWall(15, 195, 45, 1);
	drawWalls();
}

//checks for keyboard input used for moving the character around
void updateCharacterState(u32 currentButtons, u32 previousButtons) {
	oldPlayer.xpos = player.xpos;
	oldPlayer.ypos = player.ypos;
	UNUSED(previousButtons);

	
	if KEY_DOWN(BUTTON_UP,currentButtons) {
		if (legalMove(player.xpos, player.ypos - 1)){
			player.ypos += -1;
		}
	}

	if KEY_DOWN(BUTTON_DOWN,currentButtons) {
		if (legalMove(player.xpos, player.ypos + 1)){
			player.ypos += 1;
		}
	}
	if KEY_DOWN(BUTTON_LEFT, currentButtons) {
		if (legalMove(player.xpos - 1, player.ypos)) {
			player.xpos += -1;
		}
	} 
	if KEY_DOWN(BUTTON_RIGHT, currentButtons) {
		if (legalMove(player.xpos + 1, player.ypos)) {
			player.xpos += 1;
		}
	}

	//colors over the old character and draws a new one in the corret position
	drawRectDMA(oldPlayer.ypos, oldPlayer.xpos, player.width, player.height, BLUE);
	drawRectDMA(player.ypos, player.xpos, player.width, player.height, player.color);
}

//checks to see if the character collides with the screen boarder or a wall
int legalMove(int xpos, int ypos) {
	if (xpos <= 0) {
		return 0;
	} else if (xpos >= WIDTH - player.width) {
		return 0;
	} else if (ypos <= 0) {
		return 0;
	} else if (ypos >= HEIGHT - player.height) {
		return 0;
	} else {
		//checks if the player ovelaps with any of the walls
		for (int i = 0; i < wallCounter; i++) {
			if (overlap(xpos, ypos, walls[i])) {
				return 0;
			}
		}
	}
	return 1;

}

//helper method for adding walls to the maze
void addWall(int row, int col, int length, int horizontal) {
	walls[wallCounter].row = row;
	walls[wallCounter].col = col;
	walls[wallCounter].length = length;
	walls[wallCounter].horizontal = horizontal;

	walls[wallCounter].width = WALL_WIDTH;
	walls[wallCounter].color = RED;
	wallCounter++;
}


void drawWalls(void) {
	for (int i = 0; i < wallCounter; i++) {

		if (walls[i].horizontal) {
			drawRectDMA(walls[i].row, walls[i].col, walls[i].length, walls[i].width, walls[i].color);
		} else {
			drawRectDMA(walls[i].row, walls[i].col, walls[i].width, walls[i].length, walls[i].color);
		}
	}
}

// checks to see if the characters current position overlaps with a wall
int overlap(int xpos, int ypos, WALL wall) {
	if (wall.horizontal) {
		if ((xpos + player.width < wall.col) || (xpos > wall.col + wall.length) || ypos + player.height < wall.row || ypos > wall.row + wall.width ) {
			return 0;
		}
	} else {
		if ((xpos + player.width < wall.col)|| (xpos  > wall.col + wall.width) || ypos + player.height < wall.row || ypos > wall.row + wall.length ) {
			return 0;
		}
	}

	return 1;
}


void resetApp(void){
	vBlankCounter = 0;
	wallCounter = 0;

}