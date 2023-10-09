#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include "gba.h"

#define MAX_VELOCITY 10
#define WALL_WIDTH 3;

typedef struct {
	int xpos;
	int ypos;
	int width;
	int height;
	u16 color;
} CHARACTER;

typedef struct {
	int row;
	int col;
	// 1 if horizontal 0 if vertical
	int length;
	int horizontal;
	int width;
	u16 color;
} WALL;

typedef struct {
	int row;
	int col;
	int length;
	int width;
} GOAL;

void buildCharacter(void);
void drawGoal(void);
void buildGoal(void);
void updateCharacterState(u32 currentState, u32 previousState);
int legalMove(int xpos, int ypos);
void buildMaze(void);
void addWall(int row, int col, int length, int horizontal);
void drawWalls(void);
int overlap(int xpos, int ypos, WALL wall);
int atGoal(void);
void updateTimer(int offset);
void resetApp(void);

#endif