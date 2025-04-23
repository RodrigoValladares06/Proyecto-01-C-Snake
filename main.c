#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"


#include <termios.h>
#include <fcntl.h>

int _kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); 
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main() {
    SnakeCell initial_pos = {5, 5};
    GameState* game = initialize_snake_game(20, 20, initial_pos);
    
    generate_food(game);  

    while (1) {
        print_board(game);
        
        if (_kbhit()) {  
            char key = getchar();
            switch (key) {
                case 'w': change_direction(game->snakes[0], UP); break;
                case 's': change_direction(game->snakes[0], DOWN); break;
                case 'a': change_direction(game->snakes[0], LEFT); break;
                case 'd': change_direction(game->snakes[0], RIGHT); break;
            }
        }
        
        move_snake(game);
        
        if (check_collision(game)) {
            printf("Game Over!\n");
            break;
        }

        Snake* snake = game->snakes[0];
        SnakeCell head = snake->cells[0];
        if (game->board[head.row][head.col] == '*') {
            grow_snake(snake);
            generate_food(game); 
        }

        usleep(100000);  
    }

    free_game(game);
    return 0;
}
