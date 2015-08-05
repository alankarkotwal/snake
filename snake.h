//
//  snake.h
//  
//
//  Created by Alankar Kotwal on 06/08/15.
//
//

#ifndef ____snake__
#define ____snake__

#include <iostream>
#include <queue>
#include <vector>

#define SNAKE_INIT_LEN 5

typedef enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
} snake_dir;

class vertex {
    
    public:
        int x, y;
        vertex(int _x, int _y) {
            x = _x; y = _y;
        }
};

class snake_t {
    
    private:
        std::queue<vertex> snake;
        snake_dir dir;
    
    public:
        snake_t();
        ~snake_t();
        void updateSnake();
        void setDir(snake_dir);
        snake_dir getDir();
        std::queue<vertex> getSnake();
    
};

#endif /* defined(____snake__) */
