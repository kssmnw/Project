#include <iostream>
#define MAX_SIZE 50

/*
Структура, представляющая собой квадрат (кусок) картинки
*/
struct Square {
  // массив символов
  char data[MAX_SIZE][MAX_SIZE];
};

bool load_image(const std::string &filename, char (&image)[512][512], 
                 int *x, int *y);

void divide_image(const char (&image)[512][512], Square *squares, 
                  int sx, int sy, int square_count, int square_size);

int frame(int count);

void draw_squares(Square *squares, int rows, int columns, 
                  int square_size, int x, int y);

int change(Square *squares, int square_count, int square_size, 
           int a, int b);
int step(Square *squares, int rows, int columns, int square_size, 
         int *x, int *y, int input);

void game(Square *squares, int rows, int columns, int square_size, 
          int *x, int *y);

void scrumble(Square *squares, int rows, int columns, int square_size,
             int *x, int *y);

