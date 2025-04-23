#ifndef SNAKE_H
#define SNAKE_H

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct {
    int row;
    int col;
} SnakeCell;

typedef struct {
    SnakeCell* cells;
    int num_cells;
    Direction dir;
} Snake;

typedef struct {
    int num_rows;
    int num_cols;
    char** board;
    int num_snakes;
    Snake** snakes;
} GameState;

GameState* initialize_snake_game(int num_rows, int num_cols, SnakeCell snake_loc);
void generate_food(GameState* game);
void print_board(GameState* game);
void change_direction(Snake* snake, Direction dir);
void move_snake(GameState* game);
int check_collision(GameState* game);
void grow_snake(Snake* snake);
void free_game(GameState* game);

#endif 
