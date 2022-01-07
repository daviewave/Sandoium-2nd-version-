#include "gameboard.h"
#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
  int row;
  int column;
  int direction;
  int curr_tower_height;
  int score;
}builder;

builder add_player(char arr[LENGTH][WIDTH]);

builder add_AI(char arr[LENGTH][WIDTH]);

int is_valid_move(char arr[LENGTH][WIDTH], builder player, int next_row, int next_col);

void move_player(char arr[LENGTH][WIDTH], builder player);


#endif