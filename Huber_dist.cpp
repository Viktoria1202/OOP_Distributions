#include "distribution.h"

double HuberDistributionGetNumber(double form_factor, double shift_factor,
                                  double scale_factor) {
  if (form_factor <= 0 || scale_factor <= 0) {
    return NAN; // Если хотя бы один из них меньше или равен нулю, функция возвращает значение NAN (Not-a-Number), что может означать ошибку или некорректные входные данные.
  }
  double res = 0.0;
  double K_coefficient =
      2.0 * standardDistributionDensity(form_factor) / form_factor +
      2 * standardDistributionFunction(form_factor) - 1;
  double P_coefficient =
      (2.0 * standardDistributionFunction(form_factor) - 1) / K_coefficient; // центральный интервал

  double first_rand = uniformDistributionGetNumber(); //  Вероятно, это случайное число, полученное из равномерного распределения.

  if (first_rand <= P_coefficient) {
    res = form_factor + 1;
    while (!(-form_factor <= res && res <= form_factor)) {
      double r1 = uniformDistributionGetNumber(),
             r2 = uniformDistributionGetNumber();
      res = sqrt(-2.0 * log(r1)) * cos(2.0 * M_PI * r2); // реализация нормальной случайной величины
    }
  } else {
    double r1 = 0;
    while (fabs(r1) <= EPSILON || fabs(r1 - 1) <= EPSILON) {
      r1 = uniformDistributionGetNumber();
    }
    res = form_factor - log(r1) / form_factor;
    if (first_rand >= 0.5 * (1 + P_coefficient)) res = -res;
  }

  return res * scale_factor + shift_factor;
}

int HuberDistributionGetSet(int counts, std::vector<double> *dest,
                            double form_factor, double shift_factor,
                            double scale_factor) {
  if (counts < 1 || scale_factor <= 0 || form_factor <= 0 || dest == NULL) {
    return 0;
  }
  (*dest).clear();
  std::vector<double> result;
  for (int i = 0; i < counts; i++) {
    (*dest).push_back(
        HuberDistributionGetNumber(form_factor, shift_factor, scale_factor));
  }

  return 1;
}

double HuberDistributionDensity(double x, double form_factor,
                                double shift_factor, double scale_factor) {
  if (form_factor <= 0 || scale_factor <= 0) {
    return NAN;
  }
  double K_coefficient =
      2.0 * standardDistributionDensity(form_factor) / form_factor +
      2 * standardDistributionFunction(form_factor) - 1;
  double res = 1.0 / (sqrt(2 * M_PI) * K_coefficient);
  x = (x - shift_factor) / scale_factor;
  if (fabs(x) <= form_factor) {
    res *= exp(-x * x / 2.0);
  } else {
    res *= exp(form_factor * form_factor / 2.0 - form_factor * fabs(x));
  }

  return res / scale_factor;
}

double HuberDistributionMathExpectation(double form_factor, double shift_factor,
                                        double scale_factor) {
  if (form_factor <= 0 || scale_factor <= 0) {
    return NAN;
  }
  return shift_factor;
}

double HuberDistributionVariation(double form_factor, double shift_factor,
                                  double scale_factor) {
  if (form_factor <= 0 || scale_factor <= 0) {
    return NAN;
  }
  double K_coefficient =
      2.0 * standardDistributionDensity(form_factor) / form_factor +
      2 * standardDistributionFunction(form_factor) - 1;
  double res = 1 + (2 * standardDistributionDensity(form_factor) *
                    (pow(form_factor, 2) + 2)) /
                       (pow(form_factor, 3) * K_coefficient);
  return res * pow(scale_factor, 2);
}

double HuberDistributionSkewness(double form_factor, double shift_factor,
                                 double scale_factor) {
  if (form_factor <= 0 || scale_factor <= 0) {
    return NAN;
  }

  return 0;
}

double HuberDistributionKurtosis(double form_factor, double shift_factor,
                                 double scale_factor) {
  if (form_factor <= 0 || scale_factor <= 0) {
    return NAN;
  }
  double K_coefficient =
      2.0 * standardDistributionDensity(form_factor) / form_factor +
      2 * standardDistributionFunction(form_factor) - 1;
  double variation =
      HuberDistributionVariation(form_factor, shift_factor, scale_factor);
  double res = 3 * (2 * standardDistributionFunction(form_factor) - 1);
  res += 2 * standardDistributionDensity(form_factor) *
         (24 * pow(form_factor, -5) + 24 * pow(form_factor, -3) +
          12 / form_factor + form_factor);
  res /= (pow(variation, 2) * K_coefficient);
  res -= 3;
  return res;
}
