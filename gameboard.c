#include "gameboard.h"

//
void print_board(char arr[LENGTH][WIDTH])
{ 
  for(int i = 0; i < 7; i++)
  {
    for(int j = 0; j < 7; j++)
    {
      if(arr[i][j] == 0)
      {
        printf("");
      }
      if(arr[i][j] == 80)
      {
        printf("P ");
      }
      else if(arr[i][j] == 65)
      {
        printf("A ");
      }
      else if(arr[i][j] != 0)
      {
        printf("%i ", arr[i][j]);
      }
      else
      {
        printf("  ");
      }
    }
    printf("\n");
  } 
}