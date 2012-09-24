#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "optparse.h"

int height = 0,
    width = 0;

typedef struct {
  _Bool alive;
  _Bool alive_next_round;
} cell_t;

typedef struct {
  cell_t **cells;
} world_t;

_Bool create_world(world_t *world) {
  int i;

  // allocate memory to hold all lines in the world
  world->cells = (cell_t **) malloc(sizeof (cell_t *) * height);

  // for each line in the world, assign memory to it
  for(i = 0; i<=height; i++) {
    if(!(world->cells[i] = (cell_t *) malloc(sizeof(cell_t *) * width)))
      return false;
  }

  return true;
}

// return random value
_Bool true_or_false() {
  return (rand() % 2) ? true : false;
}

void randomize_world(world_t *world) {
  int i, j;

  // initialize randomizer for later use
  srand(time(NULL));

  // assign each cell random aliveness
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      world->cells[i][j].alive = true_or_false();
    }
  }
}

void print_world(world_t *world) {
  int i, j;

  // print x-axis
  printf("  ");
  for(i = 0; i<width; i++)
    printf("%i ", i);
  printf("  → x\n");

  // print each line
  for(i = 0; i<height; i++) {
    // print y-axis
    printf("%i ", i);
    // print cells
    for(j = 0; j<width; j++) {
      printf("%s", (world->cells[i][j].alive ? "▆": "   "));
    }
    printf("\n");
  }
  printf("↓\ny\n");
}

// returns number of living neighbours for any given cell coordinate
int neighbours(world_t *world, int y, int x) {
  int count = 0;

  // ... y-1 -1<x>1
  // .*. x-1 x+1
  // ... y+1 -1<x>1
  //
  // edge cases(pun intended):
  //   y = 0, y = height
  //   x = 0, x = width

  // above
  if(y > 0) {
    if(x > 0)
      count += world->cells[y-1][x-1].alive? 1 : 0;
    count += world->cells[y-1][x].alive? 1 : 0;
    if(x < width-1)
      count += world->cells[y-1][x+1].alive? 1 : 0;
  }

  // below
  if(y < height-1) {
    if(x > 0)
      count += world->cells[y+1][x-1].alive? 1 : 0;
    count += world->cells[y+1][x].alive? 1 : 0;
    if(x < width-1)
      count += world->cells[y+1][x+1].alive? 1 : 0;
  }

  // left
  if(x > 0)
    count += world->cells[y][x-1].alive? 1 : 0;

  // right
  if(x < width-1)
    count += world->cells[y][x+1].alive? 1 : 0;

  return count;
}

// show debug information: neighbour count for all cells
void show_neighbour_count(world_t *world) {
  int i, j;
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      printf("neighbours of y(%i):x(%i) -> %i\n", i, j, neighbours(world, i, j));
    }
  }
}

// calculate whether cell will be alive in next iteration
// helper function for next_tick()
_Bool next_tick_cell(world_t *world, int i, int j) {
  cell_t cell = world->cells[i][j];

  if(!cell.alive && (neighbours(world, i, j) == 3))
    return true;
  else if(cell.alive && ((neighbours(world, i, j) < 2) || (neighbours(world, i, j) > 3)))
    return false;

  return cell.alive;
}

/*
 * evolve the world into the next iteration by the following rules:
 * 1. any live cell with fewer than two live neighbours dies, as if caused by
 *    under-population.
 * 2. any live cell with two or three live neighbours lives on to the next
 *    generation.
 * 3. any live cell with more than three live neighbours dies, as if by
 *    overcrowding.
 * 4. any dead cell with exactly three live neighbours becomes a live cell, as
 *    if by reproduction.
 */
void next_tick(world_t *world) {
  int i, j;

  // clone current population for calculations
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      world->cells[i][j].alive_next_round = world->cells[i][j].alive;
    }
  }

  // calculate next iteration for each cell
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      world->cells[i][j].alive_next_round = next_tick_cell(world, i, j);
    }
  }

  // write temporary results back into current world
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      world->cells[i][j].alive = world->cells[i][j].alive_next_round;
    }
  }
}

int main(int argc, char *argv[]) {
  world_t world;

  if(!optparse(argc, argv))
    exit(-1);

  if(!create_world(&world)) {
    printf("error creating world\n");
    abort();
  }

  // prepare world
  randomize_world(&world);
  print_world(&world);
 
  // actual GOL
  while(true) {
    sleep(1);
    next_tick(&world);
    print_world(&world);
    //show_neighbour_count(&world);
  }

  return 0;
}
