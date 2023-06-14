#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include "func.h"

/*
Функция загружает картинку в ASCII-графике из файла

Аргументы:
const std::string &filename — имя входного файла
char (&image)[512][512] — массив картинки
int *x, int *y — размеры получившейся картинки

Возвращается значение true, если файл успешно открылся, и данные считались.
Значение false, если файл не открылся.
*/
bool load_image(const std::string &filename, char (&image)[512][512], int *x, int *y) {
  int rows = 0, min_columns = 100000, columns = 0;
  char pixel;
  std::string line;
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }
  while (getline(file, line, '\n'))
  {
    columns = 0;
    
    while (line[columns] != '\0')
    {
      image[rows][columns] = line[columns];
      columns++;
    }
    if (columns < min_columns) min_columns = columns;
    rows++;
  }
  *x = rows;
  *y = min_columns;
  return true;
}


/*
Функция разбивает картинку на квадраты

Аргументы:
char (&image)[512][512] — массив картинки
Square *squares — 
int sx, int sy — размеры картинки
int square_count — количество квадратов
int square_size — размер квадратов

Возвращается значение true, если файл успешно открылся, и данные считались.
Значение false, если файл не открылся.
*/
// Разбить картинку на квадраты
void divide_image(const char (&image)[512][512], Square *squares, int sx, int sy, int square_count, int square_size) {
  int count_in_row = sy / square_size;
  int count_in_column = sx / square_size;

  for (int i = 0; i < count_in_column; i++) 
  {
    for (int j = 0; j < count_in_row; j++) 
    {
      Square &square = squares[i * count_in_row + j];
      for (int h = 0; h < square_size; ++h) 
      {
        for (int w = 0; w < square_size; ++w) 
        {
          square.data[h][w] = image[i * square_size + h][j * square_size + w];
        }
      }
    }
  }
}

/*
Функция раскладывает число на максимально близкие 
друг к другу целые множители

Аргументы:
int count — число

Возвращает большее число из разложения
*/
int frame(int count) {
  int max = 1;
  for (int i = 1; i <= sqrt(count); i++) {
    if (count % i == 0)
      max = i;
  }
  return max;
}

void draw_squares(Square *squares, int rows, int columns, int square_size, int x, int y) {
  char c;

  for (int i = 0; i < rows; i++) 
  {
    for (int j = 0; j < square_size; j++) 
    {
      for (int k = 0; k < columns; k++) 
      {
        const Square &sq = squares[i * columns + k];
        for (int m = 0; m < square_size; m++) 
        {
          if (x == i && y == k) {
            std::cout << ' ';
            continue;
          }
          c = sq.data[j][m];
          std::cout << c;
        }
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

int change(Square *squares, int square_count, int square_size, int a, int b) {
  if (a >= square_count || b >= square_count)
    return -1;
  char c;
  Square &square1 = squares[a];
  Square &square2 = squares[b];
  for (int h = 0; h < square_size; ++h) {
    for (int w = 0; w < square_size; ++w) {
      c = square1.data[h][w];
      square1.data[h][w] = square2.data[h][w];
      square2.data[h][w] = c;
    }
  }
  return 0;
}

int step(Square *squares, int rows, int columns, int square_size, int *x, int *y, int input)
{
  switch (input) {
  case 0:
    if ((*x) == 0) return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x - 1) * columns + (*y));
      (*x)--;
      break;
    }
  case 1:
    if ((*y) == columns - 1) return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x) * columns + (*y + 1));
      (*y)++;
      break;
    }
  case 2:
    if ((*x) == rows - 1) return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x + 1) * columns + (*y));
      (*x)++;
      break;
    }
  case 3:
    if ((*y) == 0) return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x) * columns + (*y - 1));
      (*y)--;
      break;
    }
  default: return -1;
  
  }
  return 0;
}


void game(Square *squares, int rows, int columns, int square_size, int *x, int *y)
{
  int input;
  std::cin >> input;
  while (input != -1)
  {
    if (step(squares, rows, columns, square_size, x, y, input) == -1)
    {
      std::cout << "Введите число от 0 до 3" << std::endl;
    }
    else draw_squares(squares, rows, columns, square_size, *x, *y);
    std::cin >> input;
  }
}


void scrumble(Square *squares, int rows, int columns, int square_size,
                 int *x, int *y) {
  int rnd;
  for (int i = 0; i < 50 * rows * columns; i++) {
    rnd = rand() % 4;
    step(squares, rows, columns, square_size, x, y, rnd);
  }
}
