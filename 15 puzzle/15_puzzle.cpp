#include <fstream>
#include <iostream>
#include <random>
#include <string>
#define MAX_SIZE 1000

// Структура, представляющая один квадрат в картинке
struct Square {
  char data[MAX_SIZE][MAX_SIZE];
};

// Загрузить картинку в ASCII-графике из файла
bool load_image1(const std::string &filename, char (&image)[512][512], int *x,
                 int *y) {
  int rows = 0, min_columns = 100000, columns = 0;
  char pixel;
  std::string line;
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }
  while (getline(file, line, '\n')) {
    columns = 0;
    while (line[columns] != '\0') {
      image[rows][columns] = line[columns];
      columns++;
    }
    if (columns < min_columns)
      min_columns = columns;
    rows++;
  }
  *x = rows;
  *y = min_columns;
  return true;
}

// Разбить картинку на квадраты
int divide_image(const char (&image)[512][512], Square *squares, int sx, int sy,
                 int square_count, int square_size) {
  int count_in_row = sy / square_size;
  int count_in_column = sx / square_size;
  int k = count_in_row * count_in_column;
  for (int i = 0; i < count_in_column; i++) {
    for (int j = 0; j < count_in_row; j++) {
      Square &square = squares[i * count_in_row + j];
      for (int h = 0; h < square_size; ++h) {
        for (int w = 0; w < square_size; ++w) {
          square.data[h][w] = image[i * square_size + h][j * square_size + w];
        }
      }
    }
  }
  return k;
}

int frame(int count) {
  int max = 1;
  for (int i = 1; i <= sqrt(count); i++) {
    if (count % i == 0)
      max = i;
  }
  return max;
}

void draw_squares(Square *squares, int square_count, int square_size, int x,
                  int y) {
  int count = frame(square_count);
  char c;
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < square_size; j++) {
      for (int k = 0; k < square_count / count; k++) {
        const Square &sq = squares[i * square_count / count + k];
        for (int m = 0; m < square_size; m++) {
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

int step(Square *squares, int rows, int columns, int square_size, int *x,
         int *y, int input) {
  switch (input) {
  case 0:
    if ((*x) == 0)
      return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x - 1) * columns + (*y));
      (*x)--;
      break;
    }
  case 1:
    if ((*y) == columns - 1)
      return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x) * columns + (*y + 1));
      (*y)++;
      break;
    }
  case 2:
    if ((*x) == rows - 1)
      return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x + 1) * columns + (*y));
      (*x)++;
      break;
    }
  case 3:
    if ((*y) == 0)
      return -1;
    else {
      change(squares, rows * columns, square_size, (*x) * columns + (*y),
             (*x) * columns + (*y - 1));
      (*y)--;
      break;
    }
  default:
    return -1;
  }
  return 0;
}

void game(Square *squares, int rows, int columns, int square_size, int *x,
          int *y) {
  int input;
  std::cin >> input;
  while (input != -1) {
    if (step(squares, rows, columns, square_size, x, y, input) == -1) {
      std::cout << "Введите число от 0 до 3" << std::endl;
    } else
      draw_squares(squares, rows * columns, MAX_SIZE, *x, *y);
    std::cin >> input;
  }
}

int scrumble(Square *squares, int rows, int columns, int square_size, int *x,
             int *y) {
  int rnd;
  for (int i = 0; i < 50 * rows * columns; i++) {
    rnd = rand() % 4;
    step(squares, rows, columns, square_size, x, y, rnd);
  }
  return 0;
}

int main() {
  char image[512][512];
  int square_count;
  int square_size = 0;
  int size_x = 0, size_y = 0;
  int x, y;
  Square squares[MAX_SIZE];

  if (!load_image1("image.txt", image, &size_x, &size_y)) {
    std::cout << "Failed to load image!" << std::endl;
    return 1;
  }
  std::cout << "Введите число квадратов" << std::endl;
  std::cin >> square_count;

  for (int i = 1; i < size_x; i++) {
    if ((size_x / i) * (size_y / i) < square_count) {
      square_size = i - 1;
      break;
    }
  }
  size_x -= size_x % square_size;
  size_y -= size_y % square_size;

  divide_image(image, squares, size_x, size_y, square_count, square_size);

  x = size_x / square_size - 1;
  y = size_y / square_size - 1;
  srand(time(NULL));

  scrumble(squares, size_x / square_size, size_y / square_size, square_size, &x,
           &y);
  draw_squares(squares, square_count, square_size, x, y);

  game(squares, size_x / square_size, size_y / square_size, square_size, &x,
       &y);

  return 0;
}
