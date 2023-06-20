#include "func.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <string>

int main() {
  char image[512][512];
  int square_count;
  int square_size = 0;
  int size_x = 0;
  int size_y = 0;
  int x, y;
  if (!load_image("image.txt", image, &size_x, &size_y)) {
    std::cout << "Failed to load image!" << std::endl;
    return 1;
  }
  std::cout << "Введите число квадратов" << std::endl;
  std::cin >> square_count;
  for (int i = 1; i < size_x; i++)
  {
    if ((size_x / i) * (size_y / i) < square_count) {
      square_size = i - 1;
      break;
    }
  }
  size_x = frame(square_count) * square_size;
  size_y = (square_count / frame(square_count)) * square_size;
  Square squares[square_count];
  divide_image(image, squares, size_x, size_y, square_count, square_size);
  x = size_x / square_size - 1;
  y = size_y / square_size - 1;
  srand(time(NULL));
  scrumble(squares, size_x / square_size, size_y / square_size, square_size, 
           &x, &y); 
  draw_squares(squares, size_x / square_size, size_y / square_size,
               square_size, x, y);
  game(squares, size_x / square_size, size_y / square_size, square_size, &x,
       &y);
  return 0;
}
