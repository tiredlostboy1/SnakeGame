#include <iostream>
#include <algorithm>
#include <ncurses.h>
#include <stdio.h>
#include <random>
#include <ctime>
#include <list>

class game{
private:
  int i = 1, j = 1;
  int di = 0, dj = 1;
  int key = 0;
  char xndzor = 'a';
  int xndzor_i, xndzor_j;
  std::list<std::pair<int, int>> snake;
  int size = 3;

public:
 //default
  game(int i = 1, int j = 1): i{i}, j{j}{
    set_up();
    snake.push_back({i,j});
  }

void set_up(){
      initscr();
      clear();
      noecho();
      cbreak();
      curs_set(0);
      keypad(stdscr, TRUE);
      timeout(200);
      border(0, 0, 0, 0, 0, 0, 0, 0);
      xndzor_gen();
  }

  void uptade_speed(){
    if (key == KEY_RIGHT) {
          dj = 1;
          di = 0;
        }
        else if (key == KEY_LEFT) {
          dj = -1;
          di = 0;
        }
        else if (key == KEY_DOWN) {
          di = 1;
          dj = 0;
        }
        else if (key == KEY_UP) {
          di = -1;
          dj = 0;
        }
  }

  void xndzor_gen(){
      srand(time(0));
      xndzor_i = (rand()%(LINES-2))+1;
      xndzor_j = (rand()%(COLS-2))+1;
    }

  void update_coords(){
      i += di;
      j += dj;
    
    //xndzory kerala
    if(i == xndzor_i && j == xndzor_j){
      size++;      
      xndzor_gen();
    }
    

    
    //borders
    if(i < 1 || i >= LINES-2 ||  j < 1 || j >= COLS-2){
      key = 'q';
      clear();
      endwin();
      std::cout<< "GAME OVER"<<std::endl;
    }

  }

  void update(){  
      move(snake.front().first, snake.front().second);
      addch(' ');
  
      move(xndzor_i, xndzor_j);
      addch(xndzor);
    
      uptade_speed();
      update_coords();
    
      if(snake.size()-1 == size){
        snake.pop_front(); 
      }

      for (auto it : snake) {
          if(it.first == i && it.second == j)
        {
          key = 'q';
          clear();
          endwin();
          std::cout<<"GAME OVER"<<std::endl;
        }
      }
      
      snake.push_back({i,j});
    
      move(snake.back().first, snake.back().second);
      addch('@');
      refresh();
  }

void run(){
  set_up();
  update();
  while (key != 'q') {
    key = getch();
    update();
  }
    endwin();
}
};

int main() {
  game a{};
  a.run();
  
  return 0;
}
