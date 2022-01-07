#include "player.h"

builder add_player(char arr[LENGTH][WIDTH])
{
  int errnum;
  builder player;

  printf("Welcome to Santorium!\n");
  printf("Goal: Get more points than the other player by building more towers\n\n");
  
  printf("Choose the row you would like to start at\n");
  scanf("%i", &player.row);
  if(player.row > 6 || player.row < 1)
  {
    errnum = errno;
    fprintf(stderr, "LOCATION NOT ON BOARD, CHOOSE AGAIN:\n\n");
    add_player(arr);
  }

  printf("Choose the column you would like to start at\n");
  scanf("%i", &player.column);
  if(player.column > 6 || player.column < 1)
  {
    errnum = errno;
    fprintf(stderr, "LOCATION NOT ON BOARD, CHOOSE AGAIN:\n\n");
    add_player(arr);
  }

  player.score = 0;
  player.curr_tower_height = 2;
  arr[player.row][player.column] = 80;
  print_board(arr);

  return player;
} 

builder add_AI(char arr[LENGTH][WIDTH])
{
  int row, column;
  builder AI;
  
  srand((unsigned) time(NULL));
  AI.row = (rand() % 6) + 1;
  AI.column = (rand() % 6) + 1;
  if(arr[AI.row][AI.column] == 'P')
  {
    add_AI(arr);
  }
  else
  {
    arr[AI.row][AI.column] = 65;
    AI.score = 0;
    AI.curr_tower_height = 2;
  }

  printf("\n\n\nThe other builder will start here: \n");
  print_board(arr);
  return AI;
}

int is_valid_move(char arr[LENGTH][WIDTH], builder player, int next_row, int next_col)
{
  //1. Check if the other player is there
  if(arr[next_row][next_col] == 'A')
  {
    printf("The other builder is already in this spot, choose a different location:\n\n");
  }

  //2. Check if move is in a straight line 
  int is_row_straight = next_row - player.row;
  int is_col_straight = next_col - player.column;
  
  while(1)
  {
    if(is_row_straight == 0 && is_col_straight == 0)
    {
      printf("You chose the spot you are already in, choose again:\n");
      move_player(arr, player);
    }
    else if(is_row_straight == 0 && is_col_straight != 0)
    {
      if(is_col_straight > 0) //moving to the right/east
      {
        while(player.column < next_col)
        {
          player.column++;
          if(arr[player.row][player.column] == 'A')
          {
            printf("Path obstructed. Choose a different spot.\n");
            move_player(arr, player);
          }
        }
      }
      else //moving to the left/west
      {
        while(player.column > next_col)
        {
          player.column--;
          if(arr[player.row][player.column] == 'A')
          {
            printf("Path obstructed. Choose a different spot.\n");
            move_player(arr, player);
          }
        }
      }
      break;
    }
    else if(is_row_straight != 0 && is_col_straight == 0)
    {
      if(is_row_straight > 0) //moving upwards/north
      {
        while(player.row < next_row)
        {
          player.row++;
          if(arr[player.row][player.column] == 'A')
          {
            printf("Path obstructed. Choose a different spot.\n");
            move_player(arr, player);
          }
        }
      }
      else //moving downwards/south
      {
        while(player.row > next_row)
        {
          player.row--;
          if(arr[player.row][player.column] == 'A')
          {
            printf("Path obstructed. Choose a different spot.\n");
            move_player(arr, player);
          }
        }
      }
      break;
    }
    else
    {
      int is_straight = is_row_straight / is_col_straight;
      if(is_straight == 1 || is_straight == -1)
      {
        if(is_straight == 1 && is_row_straight < 0) //moving to the northwest
        {
          printf("\n\nNORTHWEST\n\n");
          while(player.row != next_row && player.column != next_col)
          {
            player.row--;
            player.column--;
            if(arr[player.row][player.column] == 'A')
            {
              printf("Path obstructed. Choose a different spot.\n");
              return -1;
            }
          }
        }
        else if(is_straight == 1 && is_row_straight < 0) //moving to the southeast
        {
           printf("\n\nSOUTHEAST\n\n");
          while(player.row != next_row && player.column != next_col)
          {
            player.row++;
            player.column++;
            if(arr[player.row][player.column] == 'A')
            {
              printf("Path obstructed. Choose a different spot.\n");
              return -1;
            }
          }
        }
        else if(is_straight == -1 && is_row_straight < 0) //moving to the northeast
        {
           printf("\n\nNORTHEAST\n\n");
          while(player.row - next_row != 0 && player.column - next_col != 0)
          {
            player.row--;
            player.column++;
            if(arr[player.row][player.column] == 'A')
            {
              printf("Path obstructed. Choose a different spot.\n");
              return -1;
            }
          }
        }
        else if(is_straight == -1 && is_row_straight > 0) //moving to the southwest
        {
           printf("\n\nSOUTHWEST\n\n");
          while(player.row != next_row && player.column != next_col)
          {
            player.row++;
            player.column--;
            printf("Player 1: %i\nPlayer 2: %i\n", player.row, player.column);
            if(arr[player.row][player.column] == 'A')
            {
              printf("Path obstructed. Choose a different spot.\n");
              return -1;
            }
          }
        }
        break;
      }
      else
      {
        printf("Illegal move. Choose a different spot: ");
        return -1;
      }
    }
  }

  arr[player.row][player.column] = player.curr_tower_height + 1;
  player.row = next_row;
  player.column = next_col;
  arr[player.row][player.column] = 80; 
  print_board(arr);
}

void move_player(char arr[LENGTH][WIDTH], builder player)
{
  int next_row, next_col;
  printf("Its your turn to move.\n"); 
  printf("Choose the row and column you'd like to move to: \n");
  printf("Row: ");
  scanf("%i", &next_row);
  printf("Column: ");
  scanf("%i", &next_col);

  if(is_valid_move(arr, player, next_row, next_col) == -1)
  {
    printf("ERROR: INVALID MOVE: CHOOSE A DIFFERENT SPOT");
    move_player(arr, player);
  }
  else
  {
    arr[player.row][player.column] = player.curr_tower_height + 1;
    player.row = next_row;
    player.column = next_col;
    arr[player.row][player.column] = 80; 
    print_board(arr);
  }



}
