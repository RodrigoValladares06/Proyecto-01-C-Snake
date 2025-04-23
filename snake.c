#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

GameState* initialize_snake_game(int num_rows, int num_cols, SnakeCell snake_loc) {
    GameState* game = malloc(sizeof(GameState));

    game->num_rows = num_rows;
    game->num_cols = num_cols;

    game->board = malloc(sizeof(char*) * num_rows);
    for (int i = 0; i < num_rows; ++i) {
        game->board[i] = malloc(sizeof(char) * (num_cols + 1)); 
        for (int j = 0; j < num_cols; ++j) {
            game->board[i][j] = ' ';
        }
        game->board[i][num_cols] = '\0'; 
    }

    game->num_snakes = 1;
    game->snakes = malloc(sizeof(Snake*) * game->num_snakes);

    Snake* snake = malloc(sizeof(Snake));
    snake->num_cells = 1;
    snake->cells = malloc(sizeof(SnakeCell) * snake->num_cells);
    snake->cells[0] = snake_loc;
    snake->dir = RIGHT;
    game->snakes[0] = snake;

    game->board[snake_loc.row][snake_loc.col] = '>';

    return game;
}

void generate_food(GameState* game) {
    int row = rand() % game->num_rows;
    int col = rand() % game->num_cols;
    while (game->board[row][col] != ' ') { 
        row = rand() % game->num_rows;
        col = rand() % game->num_cols;
    }
    game->board[row][col] = '*';
}

void print_board(GameState* game) {
    for (int i = 0; i < game->num_rows; ++i) {
        for (int j = 0; j < game->num_cols; ++j) {
            printf("%c", game->board[i][j]);
        }
        printf("\n");
    }
}

void change_direction(Snake* snake, Direction dir) {
    snake->dir = dir;
}

void move_snake(GameState* game) {
    Snake* snake = game->snakes[0];
    SnakeCell new_head = snake->cells[0];

  
    switch (snake->dir) {
        case UP: new_head.row--; break;
        case DOWN: new_head.row++; break;
        case LEFT: new_head.col--; break;
        case RIGHT: new_head.col++; break;
    }

 
    for (int i = snake->num_cells - 1; i > 0; --i) {
        snake->cells[i] = snake->cells[i - 1];
    }
    snake->cells[0] = new_head;


    game->board[snake->cells[0].row][snake->cells[0].col] = '>';
    game->board[snake->cells[snake->num_cells - 1].row][snake->cells[snake->num_cells - 1].col] = ' ';
}

int check_collision(GameState* game) {
    Snake* snake = game->snakes[0];
    SnakeCell head = snake->cells[0];

    
    if (head.row < 0 || head.row >= game->num_rows || head.col < 0 || head.col >= game->num_cols) {
        return 1;
    }

   
    for (int i = 1; i < snake->num_cells; ++i) {
        if (head.row == snake->cells[i].row && head.col == snake->cells[i].col) {
            return 1;
        }
    }

    return 0;
}

void grow_snake(Snake* snake) {
    snake->num_cells++;
    snake->cells = realloc(snake->cells, sizeof(SnakeCell) * snake->num_cells);
    snake->cells[snake->num_cells - 1] = snake->cells[snake->num_cells - 2]; 
}

void free_game(GameState* game) {
    for (int i = 0; i < game->num_rows; ++i) {
        free(game->board[i]);
    }
    free(game->board);

    for (int i = 0; i < game->num_snakes; ++i) {
        free(game->snakes[i]->cells);
        free(game->snakes[i]);
    }
    free(game->snakes);
    free(game);
}
