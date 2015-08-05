//
//  snake.cpp
//  
//
//  Created by Alankar Kotwal on 06/08/15.
//
//

#include "snake.h"

snake_t::snake_t() {
    
    std::cout << "Hey!" << std::endl;
    
    for(int i=0; i<SNAKE_INIT_LEN; i++) {
        this->snake.push(vertex(i-SNAKE_INIT_LEN+1, 0));
    }
    this->dir = SNAKE_RIGHT;
}

snake_t::~snake_t() {
    
    std::cout << "Bye." << std::endl;
    exit(0);
}

void snake_t::updateSnake() {
    
    this->snake.pop();
    vertex last = this->snake.back();
    int x_head = last.x;
    int y_head = last.y;
    
    switch (this->dir) {
        case SNAKE_UP:
            this->snake.push(vertex(x_head, y_head+1));
            break;
        case SNAKE_DOWN:
            this->snake.push(vertex(x_head, y_head-1));
            break;
        case SNAKE_LEFT:
            this->snake.push(vertex(x_head-1, y_head));
            break;
        case SNAKE_RIGHT:
            this->snake.push(vertex(x_head+1, y_head));
            break;
        default:
            std::cerr << "This should never happen" << std::endl;
            break;
    }
}

void snake_t::setDir(snake_dir _dir) {
    
    switch (_dir) {
        case SNAKE_UP:
            if(this->dir != SNAKE_DOWN) dir = _dir;
            break;
        case SNAKE_DOWN:
            if(this->dir != SNAKE_UP) dir = _dir;
            break;
        case SNAKE_LEFT:
            if(this->dir != SNAKE_RIGHT) dir = _dir;
            break;
        case SNAKE_RIGHT:
            if(this->dir != SNAKE_LEFT) dir = _dir;
            break;
        default:
            break;
    }
}

snake_dir snake_t::getDir() {
    
    return dir;
}

std::queue<vertex> snake_t::getSnake() {
    return this->snake;
}