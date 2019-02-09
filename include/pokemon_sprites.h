/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --tileset_image=images/calc_cursor.png --device=gba --bpp=4 --mode=sprites --transparent=f331de pokemon_sprites images/calc_cursor.png images/ralts.gif images/latios.gif images/plusle.gif images/minun.gif 
 * Time-stamp: Saturday 02/02/2019, 13:27:54
 * 
 * Image Information
 * -----------------
 * images/calc_cursor.png 8@8
 * images/ralts.gif (frame 0) 32@32
 * images/ralts.gif (frame 1) 32@32
 * images/latios.gif (frame 0) 32@32
 * images/latios.gif (frame 1) 32@32
 * images/plusle.gif (frame 0) 32@32
 * images/plusle.gif (frame 1) 32@32
 * images/minun.gif (frame 0) 32@32
 * images/minun.gif (frame 1) 32@32
 * 
 * Using tilesets
 * --------------
 * images/calc_cursor.png
 * Transparent color: (243, 49, 222)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef POKEMON_SPRITES_H
#define POKEMON_SPRITES_H

#define POKEMON_SPRITES_PALETTE_TYPE (0 << 13)
#define POKEMON_SPRITES_DIMENSION_TYPE (1 << 6)

extern const unsigned short pokemon_sprites_palette[256];
#define POKEMON_SPRITES_PALETTE_SIZE 512
#define POKEMON_SPRITES_PALETTE_LENGTH 256

extern const unsigned short pokemon_sprites[2064];
#define POKEMON_SPRITES_SIZE 4128
#define POKEMON_SPRITES_LENGTH 2064

#define RALTS0_PALETTE_ID (0 << 12)
#define RALTS0_ID 0

#define RALTS1_PALETTE_ID (0 << 12)
#define RALTS1_ID 16

#define LATIOS0_PALETTE_ID (0 << 12)
#define LATIOS0_ID 32

#define LATIOS1_PALETTE_ID (0 << 12)
#define LATIOS1_ID 48

#define MINUN0_PALETTE_ID (1 << 12)
#define MINUN0_ID 64

#define PLUSLE0_PALETTE_ID (1 << 12)
#define PLUSLE0_ID 80

#define MINUN1_PALETTE_ID (1 << 12)
#define MINUN1_ID 96

#define PLUSLE1_PALETTE_ID (1 << 12)
#define PLUSLE1_ID 112

#define CALC_CURSOR_PALETTE_ID (0 << 12)
#define CALC_CURSOR_SPRITE_SHAPE (0 << 14)
#define CALC_CURSOR_SPRITE_SIZE (0 << 14)
#define CALC_CURSOR_ID 128

extern const unsigned short ralts_frames[2];
#define RALTS_FRAMES 2

#define RALTS_SPRITE_SHAPE (0 << 14)
#define RALTS_SPRITE_SIZE (2 << 14)

extern const unsigned short latios_frames[2];
#define LATIOS_FRAMES 2

#define LATIOS_SPRITE_SHAPE (0 << 14)
#define LATIOS_SPRITE_SIZE (2 << 14)

extern const unsigned short plusle_frames[2];
#define PLUSLE_FRAMES 2

#define PLUSLE_SPRITE_SHAPE (0 << 14)
#define PLUSLE_SPRITE_SIZE (2 << 14)

extern const unsigned short minun_frames[2];
#define MINUN_FRAMES 2

#define MINUN_SPRITE_SHAPE (0 << 14)
#define MINUN_SPRITE_SIZE (2 << 14)

#endif

