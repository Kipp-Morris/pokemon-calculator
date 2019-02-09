#include <tonc_input.h>
#include <tonc_math.h>
#include <tonc_text.h>
#include <tonc_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backgrounds.h"
#include "pokemon_sprites.h"


// Miscellaneous macros
#define SPRITE_FRAME_CHANGE_DELAY 9

#define TITLE_BACKGROUND_SCROLLING_DELAY 7
#define PRESS_START_TEXT_FLASH_RATE 30
#define TITLE_PLUSLE_MINUN_JUMP_RATE 100
#define TITLE_LATIOS_APPEAR_RATE 500

#define TITLE_BACKGROUND_HEIGHT 256
#define TITLE_BACKGROUND_WIDTH 256

#define TITLE_TEXT_Y 48
#define TITLE_TEXT_X 72

#define PRESS_START_TEXT_Y 96
#define PRESS_START_TEXT_X 76

#define TEXT_COLOR_PALETTE_LOCATION 0x4000

#define CALC_BUTTON_X 80
#define CALC_BUTTON_Y 88
#define CALC_BUTTON_SPACING 24

#define CALC_NUM_BUTTON_ROWS 3
#define CALC_NUM_BUTTON_COLS 6
#define CALC_LAST_ROW 3
#define CALC_LAST_COL 4

#define CALC_OUT_LEN 10
#define CALC_OUT_X (CALC_BUTTON_X + 5 * CALC_BUTTON_SPACING - 8 * (CALC_OUT_LEN - 1))
#define CALC_OUT_Y (CALC_BUTTON_Y - 16)

#define CALC_OUT_UPDATE_DELAY 6

#define NUM_SPRITES 4

#define PLUSLE_INITIAL_X 32
#define PLUSLE_INITIAL_Y (VID_HEIGHT / 2 - 16)

#define MINUN_INITIAL_X (VID_WIDTH - 32 * 2)
#define MINUN_INITIAL_Y (VID_HEIGHT / 2 - 16)

#define RALTS_INITIAL_X 0
#define RALTS_INITIAL_Y 0

#define LATIOS_INITIAL_X 0
#define LATIOS_INITIAL_Y 0

#define PLUSLE_CALC_X 0
#define PLUSLE_CALC_Y 32

#define MINUN_CALC_X 16
#define MINUN_CALC_Y 56

#define RALTS_CALC_X 72
#define RALTS_CALC_Y 12

#define LATIOS_CALC_X 145
#define LATIOS_CALC_Y 16


// Macros for positions of calculator buttons
#define ZERO_X (CALC_BUTTON_X + 3 * CALC_BUTTON_SPACING)
#define ZERO_Y (CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING)

#define ONE_X CALC_BUTTON_X
#define ONE_Y (CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING)

#define TWO_X (CALC_BUTTON_X + CALC_BUTTON_SPACING)
#define TWO_Y (CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING)

#define THREE_X (CALC_BUTTON_X + 2 * CALC_BUTTON_SPACING)
#define THREE_Y (CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING)

#define FOUR_X CALC_BUTTON_X
#define FOUR_Y (CALC_BUTTON_Y + CALC_BUTTON_SPACING)

#define FIVE_X (CALC_BUTTON_X + CALC_BUTTON_SPACING)
#define FIVE_Y (CALC_BUTTON_Y + CALC_BUTTON_SPACING)

#define SIX_X (CALC_BUTTON_X + 2 * CALC_BUTTON_SPACING)
#define SIX_Y (CALC_BUTTON_Y + CALC_BUTTON_SPACING)

#define SEVEN_X CALC_BUTTON_X
#define SEVEN_Y CALC_BUTTON_Y

#define EIGHT_X (CALC_BUTTON_X + CALC_BUTTON_SPACING)
#define EIGHT_Y CALC_BUTTON_Y

#define NINE_X (CALC_BUTTON_X + 2 * CALC_BUTTON_SPACING)
#define NINE_Y CALC_BUTTON_Y

#define PLUS_X (CALC_BUTTON_X + 3 * CALC_BUTTON_SPACING)
#define PLUS_Y CALC_BUTTON_Y

#define MINUS_X (CALC_BUTTON_X + 3 * CALC_BUTTON_SPACING)
#define MINUS_Y (CALC_BUTTON_Y + CALC_BUTTON_SPACING)

#define MULT_X (CALC_BUTTON_X + 4 * CALC_BUTTON_SPACING)
#define MULT_Y CALC_BUTTON_Y

#define DIV_X (CALC_BUTTON_X + 4 * CALC_BUTTON_SPACING)
#define DIV_Y (CALC_BUTTON_Y + CALC_BUTTON_SPACING)

#define DECPOINT_X (CALC_BUTTON_X + 4 * CALC_BUTTON_SPACING)
#define DECPOINT_Y (CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING)

#define EQUALS_X (CALC_BUTTON_X + 5 * CALC_BUTTON_SPACING)
#define EQUALS_Y CALC_BUTTON_Y

#define CLEAR_X (CALC_BUTTON_X + 5 * CALC_BUTTON_SPACING)
#define CLEAR_Y (CALC_BUTTON_Y + CALC_BUTTON_SPACING)


// Macros for initializing sprite attributes
#define RALTS_SETUP_ATTR0 (RALTS_INITIAL_Y | ATTR0_4BPP | ATTR0_SQUARE | ATTR0_HIDE)
#define RALTS_SETUP_ATTR1 (RALTS_INITIAL_X | ATTR1_SIZE_32x32)
#define RALTS_SETUP_ATTR2 (ATTR2_PRIO(0) | RALTS0_ID | RALTS0_PALETTE_ID)

#define LATIOS_SETUP_ATTR0 (LATIOS_INITIAL_Y | ATTR0_4BPP | ATTR0_SQUARE | ATTR0_HIDE)
#define LATIOS_SETUP_ATTR1 (LATIOS_INITIAL_X | ATTR1_SIZE_32x32)
#define LATIOS_SETUP_ATTR2 (ATTR2_PRIO(0) | LATIOS0_ID | LATIOS0_PALETTE_ID)

#define PLUSLE_SETUP_ATTR0 (PLUSLE_INITIAL_Y | ATTR0_4BPP | ATTR0_SQUARE)
#define PLUSLE_SETUP_ATTR1 (PLUSLE_INITIAL_X | ATTR1_SIZE_32x32)
#define PLUSLE_SETUP_ATTR2 (ATTR2_PRIO(0) | PLUSLE0_ID | PLUSLE0_PALETTE_ID)

#define MINUN_SETUP_ATTR0 (MINUN_INITIAL_Y | ATTR0_4BPP | ATTR0_SQUARE)
#define MINUN_SETUP_ATTR1 (MINUN_INITIAL_X | ATTR1_SIZE_32x32)
#define MINUN_SETUP_ATTR2 (ATTR2_PRIO(0) | MINUN0_ID | MINUN0_PALETTE_ID)

#define CALC_CURSOR_SETUP_ATTR0 (CALC_BUTTON_Y | ATTR0_4BPP | ATTR0_SQUARE | ATTR0_HIDE)
#define CALC_CURSOR_SETUP_ATTR1 (CALC_BUTTON_X | ATTR1_SIZE_8x8)
#define CALC_CURSOR_SETUP_ATTR2 (ATTR2_PRIO(1) | CALC_CURSOR_ID | CALC_CURSOR_PALETTE_ID)


// Used to keep track of where we are in the game
typedef enum GAME_STATE {INIT_TITLE_SCREEN, TITLE_SCREEN, START_TO_CALC_TRANSITION, CALCULATOR} game_state;

// Used for scrolling backgrounds
typedef enum SCROLLING_EDGE {LEFT, BOTTOM, RIGHT, TOP} scrolling_edge;

// Used to check which Pokemon a sprite is for different purposes
typedef enum POKEMON {RALTS, LATIOS, PLUSLE, MINUN} pokemon_name;

// Used to keep track of the operation the calculator is to perform
typedef enum CALC_OP {ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, NONE} calc_op;

// Used to store the pointer to a sprite's OAM space along with other
// information used to control the sprite's appearance and position
typedef struct {
	OBJ_ATTR* obj_attr;
	int xpos;
	int ypos;
	int dy_index;
	int jumping; // Used as a boolean; only for Plusle and Minun
	int flying; // Used as a boolean; only for Latios
	int flying_right; // Used as a boolean; only for Latios
	int frame_change_delay;
	int frame;
	pokemon_name pokemon_name;
} Pokemon_Sprite;

// Used for when Plusle and Minun jump
const int jump_dy_array[] = {-7, 0, -6, 0, -5, 0, -4, 0, -3, 0, -2, 0, -1, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7};


// Function declarations
void animate_sprite(Pokemon_Sprite* sprite);
void jump_sprites(Pokemon_Sprite* sprites[]);
void latios_appear(Pokemon_Sprite* latios);
void latios_fly(Pokemon_Sprite* latios);
void scroll_background(scrolling_edge* background_edge, int* hscroll, int* vscroll, int* scroll_delay);
void init_calc_buttons();
void move_cursor(OBJ_ATTR* calc_cursor_obj_attr);
void update_calc_output(OBJ_ATTR* calc_cursor_obj_attr, char* output, int* output_len, int* intermediate_result, calc_op* operation);
void calculate(char* output, int* output_len, int* intermediate_result, calc_op operation);


//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	// Copy background graphics data to VRAM
	dma3_cpy(pal_bg_mem, backgrounds_palette, BACKGROUNDS_PALETTE_SIZE);
	dma3_cpy(&tile_mem[0], backgrounds_tiles, BACKGROUNDS_TILES_SIZE);
	dma3_cpy(&se_mem[30], southern_island, SOUTHERN_ISLAND_MAP_SIZE);
	dma3_cpy(&se_mem[31], route102, ROUTE102_MAP_SIZE);


	// Copy sprite graphics data to VRAM
	dma3_cpy(pal_obj_mem, pokemon_sprites_palette, POKEMON_SPRITES_PALETTE_SIZE);
	dma3_cpy(&tile_mem[4], pokemon_sprites, POKEMON_SPRITES_SIZE);


	// Initialize each of the four pokemon sprites
	OBJ_ATTR* ralts_obj_attr = (OBJ_ATTR*) oam_mem;
	Pokemon_Sprite* ralts = malloc(sizeof(Pokemon_Sprite));
	ralts->obj_attr = ralts_obj_attr;
	ralts->xpos = RALTS_INITIAL_X;
	ralts->ypos = RALTS_INITIAL_Y;
	ralts->pokemon_name = RALTS;
	obj_set_attr(ralts->obj_attr, RALTS_SETUP_ATTR0, RALTS_SETUP_ATTR1, RALTS_SETUP_ATTR2);

	OBJ_ATTR* latios_obj_attr = ((OBJ_ATTR*) oam_mem) + 1;
	Pokemon_Sprite* latios = malloc(sizeof(Pokemon_Sprite));
	latios->obj_attr = latios_obj_attr;
	latios->xpos = LATIOS_INITIAL_X;
	latios->ypos = LATIOS_INITIAL_Y;
	latios->pokemon_name = LATIOS;
	obj_set_attr(latios->obj_attr, LATIOS_SETUP_ATTR0, LATIOS_SETUP_ATTR1, LATIOS_SETUP_ATTR2);

	OBJ_ATTR* plusle_obj_attr = ((OBJ_ATTR*) oam_mem) + 2;
	Pokemon_Sprite* plusle = malloc(sizeof(Pokemon_Sprite));
	plusle->obj_attr = plusle_obj_attr;
	plusle->xpos = PLUSLE_INITIAL_X;
	plusle->ypos = PLUSLE_INITIAL_Y;
	plusle->pokemon_name = PLUSLE;
	obj_set_attr(plusle->obj_attr, PLUSLE_SETUP_ATTR0, PLUSLE_SETUP_ATTR1, PLUSLE_SETUP_ATTR2);

	OBJ_ATTR* minun_obj_attr = ((OBJ_ATTR*) oam_mem) + 3;
	Pokemon_Sprite* minun = malloc(sizeof(Pokemon_Sprite));
	minun->obj_attr = minun_obj_attr;
	minun->xpos = MINUN_INITIAL_X;
	minun->ypos = MINUN_INITIAL_Y;
	minun->pokemon_name = MINUN;
	obj_set_attr(minun->obj_attr, MINUN_SETUP_ATTR0, MINUN_SETUP_ATTR1, MINUN_SETUP_ATTR2);

	Pokemon_Sprite* sprites[] = {ralts, latios, plusle, minun};


	// Initialize the calculator's cursor (it's a sprite)
	OBJ_ATTR* calc_cursor_obj_attr = ((OBJ_ATTR*) oam_mem) + 4;
	obj_set_attr(calc_cursor_obj_attr, CALC_CURSOR_SETUP_ATTR0, CALC_CURSOR_SETUP_ATTR1, CALC_CURSOR_SETUP_ATTR2);


	// Initialize text display features
	txt_init_std();

	// Variables used for scrolling title screen
	int* hscroll = calloc(1, sizeof(int));
	int* vscroll = calloc(1, sizeof(int));
	int* scroll_delay = calloc(1, sizeof(int));

	// Used to keep track of what screen we're on
	game_state state = INIT_TITLE_SCREEN;

	// Used to keep track of the edge that the background is scrolling along
	scrolling_edge* background_edge = malloc(sizeof(background_edge));
	*(background_edge) = LEFT;

	// Is incremented each frame; modded to facilitate delays
	int frame_counter = 0;


	// ** Variables used by calculator **

    // The string output by the calulator
	char* calc_output = malloc(sizeof(char) * (CALC_OUT_LEN + 1));
	for (int i = 0; i < CALC_OUT_LEN; i++) {
		calc_output[i] = ' ';
	}
    calc_output[CALC_OUT_LEN] = '\0';

    // The length in characters of the calculator's current output
	int* calc_output_len = calloc(1, sizeof(int));

    // The intermediate result currently stored and ready to use in the next
    // calculation
	int* calc_intermediate_result = calloc(1, sizeof(int));

    // The next operation to be performed
	calc_op* calc_op = malloc(sizeof(calc_op));
	*(calc_op) = NONE;


    // Game loop
	while (1) {
		if (state == INIT_TITLE_SCREEN) {
			// Enable video mode 0 (all four backgrounds are regular tiled
            // backgrounds)
			REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;

			// Prepare background 0 (title background) for display
			// Note that backgrounds with a priority bit of 1 actually have
			// lower priority; BG0 has priority 1 so BG1 (text) can display on
			// top of it
			REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32 | BG_PRIO(1);

			// Initialize tiled text and display it over BG0 using BG1
			txt_init_se(1, BG_CBB(2) | BG_SBB(29), TEXT_COLOR_PALETTE_LOCATION, CLR_YELLOW, 0);
			se_puts(TITLE_TEXT_X, TITLE_TEXT_Y, "  Pokemon   \n\nCalculator!", TEXT_COLOR_PALETTE_LOCATION);
			se_puts(PRESS_START_TEXT_X, PRESS_START_TEXT_Y, "PRESS START", TEXT_COLOR_PALETTE_LOCATION);

			state = TITLE_SCREEN;
		} else if (state == TITLE_SCREEN) {
            // Determine which keys have been pressed
			key_poll();

			// Plusle and Minun each (independently) have a 1% chance of
			// jumping at each frame
			int random_num = rand() % TITLE_PLUSLE_MINUN_JUMP_RATE;
			if (random_num == 0) {
				plusle->jumping = 1;
			}
			random_num = rand() % TITLE_PLUSLE_MINUN_JUMP_RATE;
			if (random_num == 0) {
				minun->jumping = 1;
			}

			// Latios also has a .5% chance of appearing and flying across the
			// screen (at a random spot from a random direction)
			random_num = rand() % TITLE_LATIOS_APPEAR_RATE;
			if (random_num == 0) {
				if (!latios->flying) {
					latios_appear(latios);
				}
			}

			// Have PRESS START text flash in and out
			if (frame_counter++ == PRESS_START_TEXT_FLASH_RATE) {
				se_puts(PRESS_START_TEXT_X, PRESS_START_TEXT_Y, "           ", TEXT_COLOR_PALETTE_LOCATION);
			} else if (frame_counter >= 2 * PRESS_START_TEXT_FLASH_RATE) {
				se_puts(PRESS_START_TEXT_X, PRESS_START_TEXT_Y, "PRESS START", TEXT_COLOR_PALETTE_LOCATION);
				frame_counter = 0;
			}

			// Animate Plusle and Minun
			animate_sprite(plusle);
			animate_sprite(minun);

			// Keeps the sprites moving through their jump if they're jumping;
            // otherwise does nothing
			jump_sprites(sprites);

            // If Latios is flying, animate it and keep it moving across the
            // screen
			if (latios->flying) {
				animate_sprite(latios);
				latios_fly(latios);
			}

            // Scroll the background
			scroll_background(background_edge, hscroll, vscroll, scroll_delay);

            // Move to the calculator if the start button is pressed
			if (KEY_DOWN_NOW(KEY_START)) {
				state = START_TO_CALC_TRANSITION;
			}
		} else if (state == START_TO_CALC_TRANSITION) {
			// Stop Plusle and Minun from jumping
			plusle->dy_index = 0;
			plusle->jumping = 0;
			minun->dy_index = 0;
			minun->jumping = 0;

			// Stop Latios from flying
			latios->flying = 0;
			latios->obj_attr->attr1 = latios->obj_attr->attr1 & (~(ATTR1_HFLIP));

			// Set up the sprites around the screen
			plusle->xpos = PLUSLE_CALC_X;
			plusle->ypos = PLUSLE_CALC_Y;
			obj_set_pos(plusle->obj_attr, plusle->xpos, plusle->ypos);
			plusle->obj_attr->attr0 = plusle->obj_attr->attr0 & (~(ATTR0_HIDE));
			plusle->obj_attr->attr1 = plusle->obj_attr->attr1 | ATTR1_HFLIP;

			minun->xpos = MINUN_CALC_X;
			minun->ypos = MINUN_CALC_Y;
			obj_set_pos(minun->obj_attr, minun->xpos, minun->ypos);
			minun->obj_attr->attr0 = minun->obj_attr->attr0 & (~(ATTR0_HIDE));
			minun->obj_attr->attr1 = minun->obj_attr->attr1 | ATTR1_HFLIP;

			latios->xpos = LATIOS_CALC_X;
			latios->ypos = LATIOS_CALC_Y;
			obj_set_pos(latios->obj_attr, latios->xpos, latios->ypos);
			latios->obj_attr->attr0 = latios->obj_attr->attr0 & (~(ATTR0_HIDE));

			ralts->xpos = RALTS_CALC_X;
			ralts->ypos = RALTS_CALC_Y;
			obj_set_pos(ralts->obj_attr, ralts->xpos, ralts->ypos);
			ralts->obj_attr->attr0 = ralts->obj_attr->attr0 & (~(ATTR0_HIDE));
			ralts->obj_attr->attr1 = ralts->obj_attr->attr1 | ATTR1_HFLIP;

			// Hide the text from the title screen
			se_puts(TITLE_TEXT_X, TITLE_TEXT_Y, "            \n\n           ", TEXT_COLOR_PALETTE_LOCATION);
			se_puts(PRESS_START_TEXT_X, PRESS_START_TEXT_Y, "           ", TEXT_COLOR_PALETTE_LOCATION);

			// Switch BG0 to the route 2 background
			REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_8BPP | BG_REG_32x32 | BG_PRIO(1);

			// Display the calculator
			init_calc_buttons();

			// Have the cursor appear
			calc_cursor_obj_attr->attr0 = calc_cursor_obj_attr->attr0 & (~(ATTR0_HIDE));

			// Reset counter for delays
			frame_counter = 0;

			state = CALCULATOR;
		} else if (state == CALCULATOR) {
			// Animate sprites
			animate_sprite(plusle);
			animate_sprite(minun);
			animate_sprite(latios);
			animate_sprite(ralts);

			// Check every 6 frames for button input
			if (frame_counter++ % CALC_OUT_UPDATE_DELAY == 0) {
				key_poll();

				// Check to see if a directional pad button has been pressed
				// and move accordingly
				move_cursor(calc_cursor_obj_attr);

				// If the A button has been pressed, update the calculator's
				// based on the calculator button being pressed
				if (KEY_DOWN_NOW(KEY_A)) {
					update_calc_output(calc_cursor_obj_attr, calc_output, calc_output_len, calc_intermediate_result, calc_op);
				}
			}
		}

        // Wait for vsync
		vid_vsync();
	}
}


// Called each iteration of the game loop while there are Pokemon on the
// screen; every SPRITE_FRAME_CHANGE_DELAY passes through the game loop,
// change each sprite's frame.
void animate_sprite(Pokemon_Sprite* sprite) {
	if (++sprite->frame_change_delay == SPRITE_FRAME_CHANGE_DELAY) {
		sprite->frame_change_delay = 0;

		if (sprite->frame == 0) {
			sprite->frame = 1;

			if (sprite->pokemon_name == RALTS) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | RALTS1_ID | RALTS1_PALETTE_ID;
			} else if (sprite->pokemon_name == LATIOS) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | LATIOS1_ID | LATIOS1_PALETTE_ID;
			} else if (sprite->pokemon_name == PLUSLE) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | PLUSLE1_ID | PLUSLE1_PALETTE_ID;
			} else if (sprite->pokemon_name == MINUN) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | MINUN1_ID | MINUN1_PALETTE_ID;
			}
		} else {
			sprite->frame = 0;

			if (sprite->pokemon_name == RALTS) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | RALTS0_ID | RALTS0_PALETTE_ID;
			} else if (sprite->pokemon_name == LATIOS) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | LATIOS0_ID | LATIOS0_PALETTE_ID;
			} else if (sprite->pokemon_name == PLUSLE) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | PLUSLE0_ID | PLUSLE0_PALETTE_ID;
			} else if (sprite->pokemon_name == MINUN) {
				sprite->obj_attr->attr2 = ATTR2_PRIO(0) | MINUN0_ID | MINUN0_PALETTE_ID;
			}
		}
	}
}


// Used to have sprites jump by changing their y position by different amounts
// for a number of frames
void jump_sprites(Pokemon_Sprite* sprites[]) {
	for (int i = 0; i < NUM_SPRITES; i++) {
		if (sprites[i]->jumping) {
			if (sprites[i]->dy_index < sizeof(jump_dy_array) / sizeof(int)) {
				sprites[i]->ypos = sprites[i]->ypos + jump_dy_array[(sprites[i]->dy_index)++];
				obj_set_pos(sprites[i]->obj_attr, sprites[i]->xpos, sprites[i]->ypos);
			} else {
				sprites[i]->dy_index = 0;
				sprites[i]->jumping = 0;
			}
		}
	}
}


// Called to cause Latios to appear somewhere from one of the sides of the
// screen
void latios_appear(Pokemon_Sprite* latios) {
	if (rand() % 2) {
		latios->xpos = -32;
		latios->flying_right = 1;
		latios->obj_attr->attr1 = latios->obj_attr->attr1 | ATTR1_HFLIP;
	} else {
		latios->xpos = VID_WIDTH;
		latios->flying_right = 0;
	}
	latios->ypos = rand() % (VID_HEIGHT - 32);
	latios->obj_attr->attr0 = latios->obj_attr->attr0 & (~(ATTR0_HIDE));
	obj_set_pos(latios->obj_attr, latios->xpos, latios->ypos);
	latios->flying = 1;
}


// Has Latios keep flying horizontally until it exits the screen
void latios_fly(Pokemon_Sprite* latios) {
	if (latios->flying_right) {
		if (latios->xpos < VID_WIDTH) {
			obj_set_pos(latios->obj_attr, ++(latios->xpos), latios->ypos);
		} else {
			latios->obj_attr->attr0 = latios->obj_attr->attr0 | ATTR0_HIDE;
			latios->flying = 0;
			latios->obj_attr->attr1 = latios->obj_attr->attr1 & (~(ATTR1_HFLIP));
		}
	} else {
		if (latios->xpos > -32) {
			obj_set_pos(latios->obj_attr, --(latios->xpos), latios->ypos);
		} else {
			latios->obj_attr->attr0 = latios->obj_attr->attr0 | ATTR0_HIDE;
			latios->flying = 0;
		}
	}
}


// Used to scroll around BG0 on the title screen
void scroll_background(scrolling_edge* background_edge, int* hscroll, int* vscroll, int* scroll_delay) {
	if (*(scroll_delay) % TITLE_BACKGROUND_SCROLLING_DELAY == 0) {
		if (*(background_edge) == LEFT) {
			if (*(vscroll) < TITLE_BACKGROUND_HEIGHT - VID_HEIGHT) {
				++(*(vscroll));
			} else {
				*(background_edge) = BOTTOM;
			}
		} else if (*(background_edge) == BOTTOM) {
			if (*(hscroll) < TITLE_BACKGROUND_WIDTH - VID_WIDTH) {
				++(*(hscroll));
			} else {
				*(background_edge) = RIGHT;
			}
		} else if (*(background_edge) == RIGHT) {
			if (*(vscroll) > 0) {
				(*(vscroll))--;
			} else {
				*(background_edge) = TOP;
			}
		} else if (*(background_edge) == TOP) {
			if (*(hscroll) > 0) {
				(*(hscroll))--;
			} else {
				*(background_edge) = LEFT;
			}
		}

		REG_BG0HOFS = *(hscroll);
		REG_BG0VOFS = *(vscroll);
	}

	*(scroll_delay) = *(scroll_delay) + 1;
}

// Used to initialize the calculator buttons; it is assumed that txt_init_se()
// has already been called
void init_calc_buttons() {
	// First row of buttons
	se_puts(CALC_BUTTON_X, CALC_BUTTON_Y, "7", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + CALC_BUTTON_SPACING, CALC_BUTTON_Y, "8", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 2 * CALC_BUTTON_SPACING, CALC_BUTTON_Y, "9", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 3 * CALC_BUTTON_SPACING, CALC_BUTTON_Y, "+", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 4 * CALC_BUTTON_SPACING, CALC_BUTTON_Y, "x", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 5 * CALC_BUTTON_SPACING, CALC_BUTTON_Y, "=", TEXT_COLOR_PALETTE_LOCATION);

	// Second row of buttons
	se_puts(CALC_BUTTON_X, CALC_BUTTON_Y + CALC_BUTTON_SPACING, "4", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + CALC_BUTTON_SPACING, CALC_BUTTON_Y + CALC_BUTTON_SPACING, "5", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 2 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + CALC_BUTTON_SPACING, "6", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 3 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + CALC_BUTTON_SPACING, "-", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 4 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + CALC_BUTTON_SPACING, "/", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 5 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + CALC_BUTTON_SPACING, "c", TEXT_COLOR_PALETTE_LOCATION);

	// Third row of buttons
	se_puts(CALC_BUTTON_X, CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING, "1", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + CALC_BUTTON_SPACING, CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING, "2", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 2 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING, "3", TEXT_COLOR_PALETTE_LOCATION);
	se_puts(CALC_BUTTON_X + 3 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING, "0", TEXT_COLOR_PALETTE_LOCATION);

    // Add this back in later for calculations that include decimal
    // numbers?
	// se_puts(CALC_BUTTON_X + 4 * CALC_BUTTON_SPACING, CALC_BUTTON_Y + 2 * CALC_BUTTON_SPACING, ".", TEXT_COLOR_PALETTE_LOCATION);
}


// Uses the current directional pad input to move the calculator's cursor
void move_cursor(OBJ_ATTR* calc_cursor_obj_attr) {
	int curr_xpos = calc_cursor_obj_attr->attr1 & 0x1FF;
	int curr_ypos = calc_cursor_obj_attr->attr0 & 0xFF;
	if (KEY_DOWN_NOW(KEY_LEFT)) {
		if (curr_xpos > CALC_BUTTON_X) {
			obj_set_pos(calc_cursor_obj_attr, curr_xpos - CALC_BUTTON_SPACING, curr_ypos);
		}
	} else if (KEY_DOWN_NOW(KEY_RIGHT)) {
		if (curr_xpos < CALC_BUTTON_X + (CALC_NUM_BUTTON_COLS - 1) * CALC_BUTTON_SPACING && !(curr_ypos >= CALC_BUTTON_Y + (CALC_NUM_BUTTON_ROWS - 1) * CALC_BUTTON_SPACING && curr_xpos >= CALC_BUTTON_X + CALC_LAST_ROW * CALC_BUTTON_SPACING)) {
			obj_set_pos(calc_cursor_obj_attr, curr_xpos + CALC_BUTTON_SPACING, curr_ypos);
		}
	} else if (KEY_DOWN_NOW(KEY_UP)) {
		if (curr_ypos > CALC_BUTTON_Y) {
			obj_set_pos(calc_cursor_obj_attr, curr_xpos, curr_ypos - CALC_BUTTON_SPACING);
		}
	} else if (KEY_DOWN_NOW(KEY_DOWN)) {
		if (curr_ypos < CALC_BUTTON_Y + (CALC_NUM_BUTTON_ROWS - 1) * CALC_BUTTON_SPACING && !(curr_xpos >= CALC_BUTTON_X + CALC_LAST_COL * CALC_BUTTON_SPACING && curr_ypos >= CALC_BUTTON_Y + CALC_BUTTON_SPACING)) {
			obj_set_pos(calc_cursor_obj_attr, curr_xpos, curr_ypos + CALC_BUTTON_SPACING);
		}
	}
}


// Called every 
void update_calc_output(OBJ_ATTR* calc_cursor_obj_attr, char* output, int* output_len, int* intermediate_result, calc_op* operation) {
	int xpos = calc_cursor_obj_attr->attr1 & 0x1FF;
	int ypos = calc_cursor_obj_attr->attr0 & 0xFF;
	int adding_digit = 0; // Used as boolean
	char new_digit = '0';
	if (xpos == ZERO_X && ypos == ZERO_Y) {
		new_digit = '0';
		adding_digit = 1;
	} else if (xpos == ONE_X && ypos == ONE_Y) {
		new_digit = '1';
		adding_digit = 1;
	} else if (xpos == TWO_X && ypos == TWO_Y) {
		new_digit = '2';
		adding_digit = 1;
	} else if (xpos == THREE_X && ypos == THREE_Y) {
		new_digit = '3';
		adding_digit = 1;
	} else if (xpos == FOUR_X && ypos == FOUR_Y) {
		new_digit = '4';
		adding_digit = 1;
	} else if (xpos == FIVE_X && ypos == FIVE_Y) {
		new_digit = '5';
		adding_digit = 1;
	} else if (xpos == SIX_X && ypos == SIX_Y) {
		new_digit = '6';
		adding_digit = 1;
	} else if (xpos == SEVEN_X && ypos == SEVEN_Y) {
		new_digit = '7';
		adding_digit = 1;
	} else if (xpos == EIGHT_X && ypos == EIGHT_Y) {
		new_digit = '8';
		adding_digit = 1;
	} else if (xpos == NINE_X && ypos == NINE_Y) {
		new_digit = '9';
		adding_digit = 1;
	} else if (xpos == PLUS_X && ypos == PLUS_Y) {
		calculate(output, output_len, intermediate_result, *(operation));

		*(operation) = ADDITION;

        for (int i = 0; i < CALC_OUT_LEN; i++) {
            output[i] = ' ';
        }
	} else if (xpos == MINUS_X && ypos == MINUS_Y) {
		calculate(output, output_len, intermediate_result, *(operation));

        *(operation) = SUBTRACTION;

        for (int i = 0; i < CALC_OUT_LEN; i++) {
            output[i] = ' ';
        }
	} else if (xpos == MULT_X && ypos == MULT_Y) {
		calculate(output, output_len, intermediate_result, *(operation));

        *(operation) = MULTIPLICATION;

        for (int i = 0; i < CALC_OUT_LEN; i++) {
            output[i] = ' ';
        }
	} else if (xpos == DIV_X && ypos == DIV_Y) {
		calculate(output, output_len, intermediate_result, *(operation));

        *(operation) = DIVISION;

        for (int i = 0; i < CALC_OUT_LEN; i++) {
            output[i] = ' ';
        }
	} else if (xpos == EQUALS_X && ypos == EQUALS_Y) {
		calculate(output, output_len, intermediate_result, *(operation));

        *(operation) = NONE;

        int out_num_temp = *(intermediate_result);
        int result_length = 0;
        
        if (out_num_temp % 10 != 0) {
            ++result_length;
        }

        while ((out_num_temp = out_num_temp / 10) > 0) {
            ++result_length;
        }

        // If the result being displayed is 0, the result is 1 digit long
        if (*(intermediate_result) <= 0) {
            result_length = 1;
        }

        // Don't want to deal with negative numbers (for now?)
        if (*(intermediate_result) < 0) {
            *(intermediate_result) = 0;
        }

        for (int i = 0; i < CALC_OUT_LEN - *(output_len); i++) {
            output[i] = ' ';
        }

        itoa(*(intermediate_result), output + CALC_OUT_LEN - result_length, 10);

        *(intermediate_result) = 0;
	} else if (xpos == DECPOINT_X && ypos == DECPOINT_Y) {

	} else if (xpos == CLEAR_X && ypos == CLEAR_Y) {
		for (int i = 0; i < CALC_OUT_LEN; i++) {
			output[i] = ' ';
		}
        output[CALC_OUT_LEN] = '\0';
		*(output_len) = 0;
	}
	if (*(output_len) > CALC_OUT_LEN) {
		*(output_len) = CALC_OUT_LEN;
	}
	if (adding_digit && *(output_len) < CALC_OUT_LEN) {
		for (int i = CALC_OUT_LEN - 1 - (*(output_len))++; i < CALC_OUT_LEN - 1; i++) {
			output[i] = output[i + 1];
		}
		output[CALC_OUT_LEN - 1] = new_digit;
	}
	se_puts(CALC_OUT_X, CALC_OUT_Y, output, TEXT_COLOR_PALETTE_LOCATION);
}


// Called when an operation button is pressed; performs the calculation
// from the *last* time an operation button was pressed and updates the
// intermediate result appropriately
void calculate(char* output, int* output_len, int* intermediate_result, calc_op operation) {
	char* output_trimmed = calloc(1, sizeof(char) * (*(output_len) + 1));
	output_trimmed[*(output_len)] = '\0';
	for (int i = 0; i < *(output_len); i++) {
		output_trimmed[i] = output[i + CALC_OUT_LEN - *(output_len)];
	}
	int out_num = atoi(output_trimmed);
	if (operation == ADDITION) {
		out_num = *(intermediate_result) + out_num;
	} else if (operation == SUBTRACTION) {
		out_num = *(intermediate_result) - out_num;
	} else if (operation == MULTIPLICATION) {
		out_num = *(intermediate_result) * out_num;
	} else if (operation == DIVISION) {
		out_num = *(intermediate_result) / out_num;
	}
	*(output_len) = 0;
	*(intermediate_result) = out_num;
}
