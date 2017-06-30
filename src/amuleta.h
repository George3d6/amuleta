
/*
 *  amuleta.h
 *  Part of Amuleta, a traditional roguelike - https://deveah.github.io/amuleta
 *  (c) Vlad Dumitru, <dalv.urtimud@gmail.com>
 *  Licensed under the terms and conditions of the MIT License. Please consult
 *  the LICENSE file included with this project.
 */

#pragma once

#include <termbox.h>

/*  terminal minimum size requirements */
#define MINIMUM_TERMINAL_WIDTH  80
#define MINIMUM_TERMINAL_HEIGHT 25

/*
 *  a tile represents a terrain/environment type
 */
struct tile {
  /*  appearance of the tile */
  struct tb_cell *cell;

  /*  tile flags */
  #define TILE_FLAG_SOLID  (1<<0)
  #define TILE_FLAG_OPAQUE (1<<1)
  int flags;
};

/*  basic tiles defined in tile.c */
extern struct tile
  void_tile,
  floor_tile,
  wall_tile;

/*
 *  a map represents a level
 */
struct map {
  /*  the level layout (terrain) */
  #define MAP_WIDTH  80
  #define MAP_HEIGHT 20
  struct tile *tile[MAP_WIDTH][MAP_HEIGHT];
};

/*
 *  nothing to explain here
 */
struct dungeon {
  #define DUNGEON_DEPTH 10
  struct map *map[DUNGEON_DEPTH];
};

/*
 *  an actor is a living entity which can be either controlled by the user, or
 *  by the computer
 */
struct actor {
  /*  name of the actor */
  char *name;

  /*  apperance of the actor */
  struct tb_cell *cell;

  /*  position in the dungeon */
  int x, y, z;

  /*  hit points and maximum hit points */
  int hp, max_hp;

  /*  link to the next actor in a linked list */
  struct actor *next;

  #define ACTOR_FLAG_PLAYER (1<<0)
  int flags;
};

/*
 *  a game structure holds all the state regarding a play session
 */
struct game {
  /*  whether or not the game is running */
  int running;

  /*  the random seed used to generate the game */
  unsigned int random_seed;

  /*  the dungeon layout */
  struct dungeon *dungeon;

  /*  the player actor -- note that this is here for convenience, as all actors
   *  live inside the `actors' list */
  struct actor *player;

  /*  linked list containing all the actors currently in the game */
  struct actor *actors;
};

/*  dungeon.c */
struct dungeon *generate_dungeon(void);
void free_dungeon(struct dungeon *d);
struct map *generate_map(void);

/*  game.c */
struct game *initialize_game(unsigned int random_seed);
void destroy_game(struct game *g);
struct actor *create_player(void);
void run_game(struct game *g);

/*  ui.c */
void draw_map(struct game *g, int z);
