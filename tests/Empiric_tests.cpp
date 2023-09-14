#include <time.h>

#include "../distribution.h"
#include "test.h"

void emp_1();
void emp_2();

int main() {
  std::srand(time(NULL));
  emp_1();
  emp_2();
}

void emp_1() {
  std::vector<double> values, dest;

  double y_1, y_2, mu_1, mu_2, lambda_1, lambda_2;

  y_1 = 0.5;
  y_2 = 1;
  mu_1 = 0;
  mu_2 = 2;
  lambda_1 = 1;
  lambda_2 = 1;

  printf("Сравнение статистических характеристик выборки с теоретическими\n");
  printf(GREEN_BG "РАСПРЕДЕЛЕНИЕ ХЬЮБЕРА" RESET "\n");
  for (int i = 2; i < 7; i++) {
    HuberDistributionGetSet(pow(10, i), &values, y_1, mu_1, lambda_1);

    //--

    printf("-----------------\n");
    printf("Размер выборки: %.0f\n", pow(10, i));
    printf("                      Теор. | Эмпир. \n");
    printf("Мат. ожидание:     %.6f | %.6f \n",
           HuberDistributionMathExpectation(y_1, mu_1, lambda_1),
           statisticMathExpectation(&values));
    printf("Дисперсия:         %.6f | %.6f \n",
           HuberDistributionVariation(y_1, mu_1, lambda_1),
           statisticVariation(&values));
    printf("Коэф ассиметрии:   %.6f | %.6f \n",
           HuberDistributionSkewness(y_1, mu_1, lambda_1),
           statisticSkewness(&values));
    printf("Коэф. эксцесса:    %.6f | %.6f \n",
           HuberDistributionKurtosis(y_1, mu_1, lambda_1),
           statisticKurtosis(&values));
    printf("Плотность в x = 0: %.6f | %.6f \n",
           HuberDistributionDensity(0, y_1, mu_1, lambda_1),
           statisticDensity(0, &values));
  }

  printf("\n" GREEN_BG "СМЕСЬ РАСПРЕДЕЛЕНИЙ ХЬБЮЕРА" RESET "\n");

  double p = 0.6;

  for (int i = 2; i < 7; i++) {
    HuberMixtureGetSet(pow(10, i), &values, p, y_1, y_2, mu_1, mu_2, lambda_1,
                       lambda_2);

    printf("-----------------\n");
    printf("Размер выборки: %.0f\n", pow(10, i));
    printf("                      Теор. | Эмпир. \n");
    printf("Мат. ожидание:     %.6f | %.6f \n",
           HuberMixtureMathExpectation(p, y_1, y_2, mu_1, mu_2, lambda_1,
                                       lambda_2),
           statisticMathExpectation(&values));
    printf("Дисперсия:         %.6f | %.6f \n",
           HuberMixtureVariation(p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticVariation(&values));
    printf("Коэф. ассиметрии: %.6f | %.6f \n",
           HuberMixtureSkewness(p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticSkewness(&values));
    printf("Коэф. эксцесса:    %.6f | %.6f \n",
           HuberMixtureKurtosis(p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticKurtosis(&values));
    printf("Плотность в х = 0: %.6f | %.6f \n",
           HuberMixtureDencity(0, p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticDensity(0, &values));
  }

  for (int i = 1; i < 5; i++) {
    HuberMixtureGetSet(i * 1000000, &values, p, y_1, y_2, mu_1, mu_2, lambda_1,
                       lambda_2);

    printf("-----------------\n");
    printf("Размер выборки: %d\n", i * 1000000);
    printf("                      Теор. | Эмпир. \n");
    printf("Мат. ожидание:     %.6f | %.6f \n",
           HuberMixtureMathExpectation(p, y_1, y_2, mu_1, mu_2, lambda_1,
                                       lambda_2),
           statisticMathExpectation(&values));
    printf("Дисперсия:         %.6f | %.6f \n",
           HuberMixtureVariation(p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticVariation(&values));
    printf("Коэф. ассиметрии: %.6f | %.6f \n",
           HuberMixtureSkewness(p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticSkewness(&values));
    printf("Коэф. эксцесса:    %.6f | %.6f \n",
           HuberMixtureKurtosis(p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticKurtosis(&values));
    printf("Плотность в х = 0: %.6f | %.6f \n",
           HuberMixtureDencity(0, p, y_1, y_2, mu_1, mu_2, lambda_1, lambda_2),
           statisticDensity(0, &values));
  }
}

void emp_2() {
  double y_1, mu_1, lambda_1;

  y_1 = 1;
  mu_1 = 0;
  lambda_1 = 2;

  std::vector<double> values, other_values;

  printf("\n" GREEN_BG "ВЫБОРКА ПО ВЫБОРКЕ" RESET "\n");

  for (int i = 2; i < 7; i++) {
    int size = pow(10, i);
    HuberDistributionGetSet(size, &values, y_1, mu_1, lambda_1);
    statisticGetSet(&values, size, &other_values);

    printf("-----------------\n");
    printf("Размер выборки: %.0f\n", pow(10, i));
    printf("           Нач. выборка | Вторичная выборка | Теор. \n");
    printf("Мат. ожидание:     % .6f | % .6f | % .6f \n",
           statisticMathExpectation(&values),
           statisticMathExpectation(&other_values),
           HuberDistributionMathExpectation(y_1, mu_1, lambda_1));
    printf("Дисперсия:         % .6f | % .6f | % .6f \n",
           statisticVariation(&values), statisticVariation(&other_values),
           HuberDistributionVariation(y_1, mu_1, lambda_1));
    printf("Коэф ассиметрии:   % .6f | % .6f | % .6f \n",
           statisticSkewness(&values), statisticSkewness(&other_values),
           HuberDistributionSkewness(y_1, mu_1, lambda_1));

    printf("Коэф. эксцесса:    % .6f | % .6f | % .6f \n",
           statisticKurtosis(&values), statisticKurtosis(&other_values),
           HuberDistributionKurtosis(y_1, mu_1, lambda_1));
  }
}