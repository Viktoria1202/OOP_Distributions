#include "distribution.h"

int main() {
  std::vector<double> values = {1, 2, 3, 4, 5, 6}, dest;
  statisticGetSet(&values, 20, &dest);
}