/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --device=gba --mode=0 --bpp=8 --transparent=ff31de backgrounds route102.png southern_island.png 
 * Time-stamp: Thursday 01/31/2019, 19:10:04
 * 
 * Image Information
 * -----------------
 * route102.png 256@256
 * southern_island.png 256@256
 * Transparent color: (255, 49, 222)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

extern const unsigned short backgrounds_palette[35];
#define BACKGROUNDS_PALETTE_SIZE 70
#define BACKGROUNDS_PALETTE_LENGTH 35

#define BACKGROUNDS_PALETTE_TYPE (1 << 7)

extern const unsigned short backgrounds_tiles[9504];
#define BACKGROUNDS_TILES 297
#define BACKGROUNDS_TILES_SIZE 19008
#define BACKGROUNDS_TILES_LENGTH 9504

extern const unsigned short route102[1024];
#define ROUTE102_MAP_WIDTH 32
#define ROUTE102_MAP_HEIGHT 32
#define ROUTE102_MAP_SIZE 2048
#define ROUTE102_MAP_LENGTH 1024
#define ROUTE102_MAP_TYPE (0 << 14)

extern const unsigned short southern_island[1024];
#define SOUTHERN_ISLAND_MAP_WIDTH 32
#define SOUTHERN_ISLAND_MAP_HEIGHT 32
#define SOUTHERN_ISLAND_MAP_SIZE 2048
#define SOUTHERN_ISLAND_MAP_LENGTH 1024
#define SOUTHERN_ISLAND_MAP_TYPE (0 << 14)

#endif

