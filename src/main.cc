#include "sudoku.hpp"
#include "glob_rand.hpp"
#include <string>
#include <random>
#include <chrono>

std::mt19937 GlobRand::RNG;

int main() {
  // set default value of the random engine
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  GlobRand::RNG = std::mt19937{ seed };

  auto s = Sudoku( 3 );
  std::cout << s;
}
