#include "doctest.h"
#include "func.h"

TEST_CASE("File has not found") {
  char image[512][512];
  int x = 0, y = 0;
  REQUIRE(load_image("a.txt", image, &x, &y) == false);
}

TEST_CASE("File has opened successfully") {
  char image[512][512];
  int x = 0, y = 0;
  REQUIRE(load_image("image.txt", image, &x, &y) == true);
}

TEST_CASE("Frame 10") {
  REQUIRE(frame(10) == 2);
}

TEST_CASE("Frame 16") {
  REQUIRE(frame(16) == 4);
}

TEST_CASE("Correct change") {
  char image[512][512];
  int square_count = 9;
  int square_size = 8;
  int size_x, size_y;

  load_image("image.txt", image, &size_x, &size_y);

  Square squares[square_count];

  divide_image(image, squares, size_x, size_y, square_count, square_size);
  
  REQUIRE(change(squares, square_count, square_size, 0, 1) == 0);
}

TEST_CASE("Incorrect change") {
  char image[512][512];
  int square_count = 9;
  int square_size = 8;
  int size_x, size_y;

  load_image("image.txt", image, &size_x, &size_y);

  Square squares[square_count];

  divide_image(image, squares, size_x, size_y, square_count, square_size);
  
  REQUIRE(change(squares, square_count, square_size, 1, 11) == -1);
}

TEST_CASE("Correct move") {
  char image[512][512];
  int square_count = 9;
  int square_size = 8;
  int size_x, size_y;
  int x = 2, y = 2;

  load_image("image.txt", image, &size_x, &size_y);

  Square squares[square_count];

  divide_image(image, squares, size_x, size_y, square_count, square_size);
  
  REQUIRE(step(squares, 3, 3, square_size, &x, &y, 0) == 0);
  
}

TEST_CASE("Incorrect move") {
  char image[512][512];
  int square_count = 9;
  int square_size = 8;
  int size_x, size_y;
  int x = 2, y = 2;

  load_image("image.txt", image, &size_x, &size_y);

  Square squares[square_count];

  divide_image(image, squares, size_x, size_y, square_count, square_size);
  
  REQUIRE(step(squares, 3, 3, square_size, &x, &y, 2) == -1);
}
