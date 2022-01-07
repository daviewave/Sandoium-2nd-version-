#include "player.h"

int errno;

int main() 
{
  builder AI, player;
  
  char gameboard[LENGTH][WIDTH] =
  { 
    {0, 1, 2, 3, 4, 5, 6},
    {1, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2},
    {3, 2, 2, 2, 2, 2, 2},
    {4, 2, 2, 2, 2, 2, 2},
    {5, 2, 2, 2, 2, 2, 2},
    {6, 2, 2, 2, 2, 2, 2}
  };
  player = add_player(gameboard);
  AI = add_AI(gameboard);
  move_player(gameboard, player);


}