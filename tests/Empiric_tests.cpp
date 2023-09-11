#include <time.h>

#include "../distribution.h"
#include "test.h"

void emp_1();

int main() {
  std::srand(time(0));
  emp_1();
}

void emp_1() {
  std::vector<double> values, dest;

  printf("Сравнение статистических характеристик выборки с теоретическими\n");
  printf(GREEN_BG "РАСПРЕДЕЛЕНИЕ ХЬЮБЕРА\n" RESET);
  for (int i = 2; i < 7; i++) {
    HuberDistributionGetSet(pow(10, i), &values, 0.5, 0, 1);

    printf("-----------------\n");
    printf("Размер выборки: %.0f\n", pow(10, i));
    printf("%20s\n", "Теор. | Эмпир.");
    printf("%-20s", "Мат. ожидание:");
    printf("%.6f | %.6f\n", HuberDistributionMathExpectation(0.5, 0, 1),
           statisticMathExpectation(&values));
    printf("%-20s", "Дисперсия:");
    printf("%.6f | %.6f\n", HuberDistributionVariation(0.5, 0, 1),
           statisticVariation(&values));
    printf("%-20s", "Коэф. ассиметрии:");
    printf("%6f | %.6f\n", HuberDistributionSkewness(0.5, 0, 1),
           statisticSkewness(&values));
    printf("%-20s", "Коэф. эксцесса:");
    printf("%.6f | %.6f\n", HuberDistributionKurtosis(0.5, 0, 1),
           statisticKurtosis(&values));
  }

  printf(GREEN_BG "СМЕСЬ РАСПРЕДЕЛЕНИЙ ХЬБЮЕРА\n" RESET);
  for (int i = 2; i < 7; i++) {
    HuberMixtureGetSet(pow(10, i), &values, 0.5, 1, 1, 0, 0, 0, 0);

    printf("-----------------\n");
    printf("Размер выборки: %.0f\n", pow(10, i));
    printf("%20s\n", "Теор. | Эмпир.");
    printf("%-20s", "Мат. ожидание:");
    printf("%.6f | %.6f\n",
           HuberMixtureMathExpectation(0.6, 0.5, 2, 0, 2, 1, 2),
           statisticMathExpectation(&values));
    printf("%-20s", "Дисперсия:");
    printf("%.6f | %.6f\n", HuberMixtureVariation(0.6, 0.5, 2, 0, 2, 1, 2),
           statisticVariation(&values));
    printf("%-20s", "Коэф. ассиметрии:");
    printf("%6f | %.6f\n", HuberMixtureSkewness(0.6, 0.5, 2, 0, 2, 1, 2),
           statisticSkewness(&values));
    printf("%-20s", "Коэф. эксцесса:");
    printf("%.6f | %.6f\n", HuberMixtureKurtosis(0.6, 0.5, 2, 0, 2, 1, 2),
           statisticKurtosis(&values));
  }
}