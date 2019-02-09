# pokemon-calculator
A four-operation calculator for the Nintendo GameBoy Advance written in C.

![alt text](https://github.com/Kipp-Morris/pokemon-calculator/blob/master/readme_images/title_screen.png)

In my Intro to Computer Systems and Organization class we did an assignment where we created a small GBA game and used it as a way to learn some of the basics of having to think about hardware while programming. It was also meant to help us become more used to programming in C, since GBA games are written in either C or C++. Since that assignment was small in terms of the amount of time we spent on it and I honestly did a lot of it without totally understanding how the underlying hardware of the GBA worked, this calculator project that I took on on my own was a way for me to practice C programming while also learning more about the GBA.

To that end, I'll use this space to explain some of what I learned about GBA graphics and how I would extend this project if I were to put more time into it.

# Bitmap Graphics vs Tiled Graphics
Seeing as games are all about displaying different things on the screen for players to interact with, learning about displaying graphics was the most important and time-consuming portion of the project. There are two main graphics display modes available for displaying backgrounds and sprites (small graphics used for characters, etc.) on the GBA: *bitmap graphics and tiled graphics*.

For **bitmap graphics**, a graphic is stored in memory as an array of pixels, where each pixel is a color value. Bitmap graphics are easier to understand and work with than tiled graphics, but in the case of the GBA, they don't take full advantage of the available hardware that can make graphics display much faster. I used bitmap graphics in the aforementioned class project, but this time I used tiled graphics to make the project more meaningful and educational.

---

For **tiled graphics**, a graphic is broken up into three different components: a color palette, a tile map, and the actual graphic, broken up into 8x8 tiles, hence the name "tiled graphics".

---

![alt text](https://github.com/Kipp-Morris/pokemon-calculator/blob/master/readme_images/palette_mem.png)

The *color palette* is pretty self-explanatory; it goes in an area of memory set aside for color palettes and contains all of the colors used in the graphic. There are separate palettes for backgrounds and sprites.

---

The *tile map*, not shown because it's an array of relatively uninteresting hex values, is an array of references to tiles. It is used by the hardware to determine what tiles to display on the screen.

---

<img src="https://github.com/Kipp-Morris/pokemon-calculator/blob/master/readme_images/background_tiles.png" height="200%" width="200%">

**Background tiles**


<img src="https://github.com/Kipp-Morris/pokemon-calculator/blob/master/readme_images/sprite_tiles.png" height="200%" width="200%">

**Sprite tiles**

Last are the *tiles* themselves, shown above in screenshots taken from my GBA emulator's memory viewer. The memory viewer isn't perfect and some of the colors are off, but the way the tiles are stored should be clear from the picture. Each element of the tile is an index into that graphic's color palette, which is how the memory viewer knows what the tiles look like even though the way they are shown isn't how they are literally stored.

Note: The empty space not used by the graphics is filled with hot pink because the GBA hardware requires that one color be designated as the transparent color, and I chose hot pink because it's easy to tell apart from the colors that my backgrounds or sprites use.

---

I converted my graphics, which I found at [The Spriter's Resource](https://www.spriters-resource.com), directly from images to .c and .h files containing these three components using [nin10kit](https://github.com/TricksterGuy/nin10kit), an awesome tool for homebrew game development made by Brandon, a former computer science teaching assistant at Georgia Tech! So getting the graphics ready to use was just a matter of copying the palettes, tile maps, and tiles into their appropriate areas of memory before doing anything else.

From there, actually displaying the graphics is a matter of setting certain bits in the background and sprite control registers, and for sprites, an area of memory called object attribute memory.

# OAM (Object Attribute Memory)

Object attribute memory is where information about sprites is stored. It is an array of struct obj_attrs, with each obj_attr essentially being a reference to a sprite. Each struct obj_attr contains three 16-bit attributes, which store a variety of information such as:

* Whether or not the sprite is visible
* The locations the sprite's palette and tile map (so the hardware knows what graphics to use for what sprite)
* The x and y coordinates of the sprite on the screen
* Whether or not the sprite is horizontally or vertically flip

As long as these attributes are set appropriately, the hardware handles everything.

![alt text](https://github.com/Kipp-Morris/pokemon-calculator/blob/master/readme_images/oam_view.png)

The emulator's OAM viewer, shown above, was very useful while I was first trying to get the sprites to appear on the screen because it will show you what sprites' info is stored where.

# Project Extension

![alt text](https://github.com/Kipp-Morris/pokemon-calculator/blob/master/readme_images/calculator_screen.png)

The calculator as of right now doesn't handle negative numbers or decimal numbers. My main goal was to learn about the GBA graphics and just make something fun, but I decided that at least for right now, adding negative and decimal numbers is a time investment that wouldn't really add much to what I learned from the project. My main goal was to learn about the GBA graphics so I could spend less time learning them and potentially do a more complex GBA project later on. But it would be a more functional calculator with those additions (if someone were to actually use it for math?).

Decimal numbers in particular would be interesting because it would require a technique called fixed-point arithmetic, which is essentially using integer variables to perform decimal number calculations. It isn't terribly complicated, and [tonc](https://www.coranac.com/tonc/text/toc.htm), the GBA library and guide I used, has functions that would do most of the work, but it still wouldn't teach me much about the GBA graphics. I read about it a little bit and thought it was very interesting though, so I may add it in sometime just to learn about it.

# Libraries and Tools I Used

[devkitPro](https://github.com/devkitPro), a compiler toolchain for GBA and DS development

[tonc](https://www.coranac.com/tonc/text/toc.htm), a "textbook" of sorts that does a great job of explaining GBA programming

[tonclib](http://www.coranac.com/projects/tonc/), a library for GBA devlopment made by the writer of tonc; I used version 1.3 because I found I had some issues with displaying text using the newest version

[nin10kit](https://github.com/TricksterGuy/nin10kit), a graphics and sound conversion tool for homebrew game devlopment
