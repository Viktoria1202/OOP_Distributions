#include "distribution.h"

double uniformDistributionGetNumber() {
  double res = (double)std::rand() / RAND_MAX;
  return res;
}

double standardDistributionFunction(double x) {
  return 0.5 * (1 + std::erf(x / std::sqrt(2)));
}

double standardDistributionDensity(double x) {
  return std::exp(-0.5 * pow(x, 2.0)) / std::sqrt(2 * M_PI);
}