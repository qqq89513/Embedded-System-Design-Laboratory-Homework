/*
 * Coordinates.h
 *
 *  Created on: Oct 29, 2020
 *      Author: QM
 */

#ifndef INC_COORDINATES_C_
#define INC_COORDINATES_C_

// Defines ---------------------------------------------------------------
// BSP_LCD_DisplayStringAt(POS_SETTING_X, POS_SETTING_Y, str, LEFT_MODE)
#define POS_SETTING_X 88
#define POS_SETTING_Y 137

#define PX_MAX_X 480          // pixels of X of LCD
#define PX_MAX_Y 272          // pixels of Y of LCD

#define PX_BAR_WIDTH      5   // pixels of width of bar
#define PX_BAR_LENGTH    60   // pixels of length of bar
#define PX_BAR_PADDING_X 30   // pixels of distance from a bar to edge
#define PX_BALL_RADIUS    5   // pixels of radius of ball
#define PX_BORDER_Y       7   // pixels of border, distance that graphs should stay away from edges
#define PX_BORDER_X       2   // pixels of border, distance that graphs should stay away from edges
#define PX_SCORE_WIDTH   60   // for determining if ball is overlapped with the score display. change this doesn't change the size of score
#define PX_SCORE_HEIGHT  30   // for determining if ball is overlapped with the score display. change this doesn't change the size of score

#define TK_REFRESH_TS     30  // interval of refreshing touch screen data in milli second
#define TK_REFRESH_GRAPH  30  // interval of refreshing graph in play mode
#define TK_CH_MODE        10  // interval of checking change of Mode
#define TK_DB_SETTING    100  // debounce of setting: increase or decrease Speed
#define TK_REFRESH_BALL_BASE   1 // (11-Speed)*TK_REFRESH_BALL_BASE+TK_REFRESH_BALL_BASE_OFFSET
#define TK_REFRESH_BALL_OFFSET 5 // Ball move interval: (11-Speed)*TK_REFRESH_BALL_BASE+TK_REFRESH_BALL_BASE_OFFSET

// 0: enter settting mode as a game pause, exit setting mode to resume
// 1: enter setting mode and exit setting mode to restart game
#define GAME_RESTAR_AFTER_SETTING 0

#define MODE_PLAY 0
#define MODE_SETTING 1


// Struct Defines --------------------------------------------------------

// rectangle: From (RectTypeDef.coord.X, RectTypeDef.coord.Y) to (RectTypeDef.coord.X + .len.X, RectTypeDef.coord.Y + .len.Y)
typedef struct {
    int16_t x1, y1;   // start coordinate, left up corner
    int16_t x2, y2;   // end coordinate, right bottom corner
} RectTypeDef;
RectTypeDef BarL_default = {
    .x1 = 0 + PX_BAR_PADDING_X,
    .x2 = 0 + PX_BAR_PADDING_X + PX_BAR_WIDTH,
    .y1 = PX_MAX_Y/2 - PX_BAR_LENGTH/2,
    .y2 = PX_MAX_Y/2 + PX_BAR_LENGTH/2,
};
RectTypeDef BarR_default = {
    .x1 = PX_MAX_X - PX_BAR_PADDING_X - PX_BAR_WIDTH,
    .x2 = PX_MAX_X - PX_BAR_PADDING_X,
    .y1 = PX_MAX_Y/2 - PX_BAR_LENGTH/2,
    .y2 = PX_MAX_Y/2 + PX_BAR_LENGTH/2,
};

typedef struct {
    int16_t x, y;  // coordinates of ball
    uint8_t dx, dy; // direction
} BallTypeDef;
BallTypeDef Ball_default = {
    .x = PX_MAX_X/2,
    .y = PX_MAX_Y/2,
    .dx = 0,
    .dy = 0
};

#endif /* INC_COORDINATES_C_ */
