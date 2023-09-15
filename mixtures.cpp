#include "distribution.h"

/*
        ��� ������ mixt_param, ��� � ������� ������������ ������������
   ������������� � �������� 2, ������ 1
*/

/* Этот блок комментариев описывает функцию `HuberMixtureGetNum`, которая возвращает число из смеси распределений Хьюбера. 
    Параметры:
    - `mixt_param`: Параметр смешивания, который определяет, какая компонента смеси будет использоваться.
    - `form_factor_1` и `form_factor_2`: Факторы формы для двух компонент смеси.
    - `shift_factor_1` и `shift_factor_2`: Факторы сдвига для двух компонент смеси.*/ 

double HuberMixtureGetNum(double mixt_param, double form_factor_1,
                          double form_factor_2, double shift_factor_1,
                          double shift_factor_2, double scale_factor_1,
                          double scale_factor_2) {
  if (mixt_param < 0 || mixt_param > 1) {
    return NAN;
  }

  double res = 0;
  if (uniformDistributionGetNumber() > mixt_param) {
    res = HuberDistributionGetNumber(form_factor_1, shift_factor_1,
                                     scale_factor_1);
  } else {
    res = HuberDistributionGetNumber(form_factor_2, shift_factor_2,
                                     scale_factor_2);
  }

  return res;
}


/*
    Этот блок комментариев описывает функцию `HuberMixtureGetSet`, которая заполняет вектор случайными числами из смеси распределений Хьюбера.
    Параметры:
    - `size`: Размер вектора, который нужно заполнить.
    - `dest`: Указатель на вектор, в который будут добавлены числа из смеси.
    - Остальные параметры определяют характеристики смеси и проверки на корректность.
*/

int HuberMixtureGetSet(int size, std::vector<double> *dest, double mixt_param,
                       double form_factor_1, double form_factor_2,
                       double shift_factor_1, double shift_factor_2,
                       double scale_factor_1, double scale_factor_2) {
  if ((dest == NULL) || (form_factor_1 <= 0 || form_factor_2 <= 0) ||
      (scale_factor_1 <= 0 || scale_factor_2 <= 0) ||
      (mixt_param < 0 || mixt_param > 1)) {
    return 0;
  }
  (*dest).clear();
  for (int i = 0; i < size; i++) {
    (*dest).push_back(HuberMixtureGetNum(
        mixt_param, form_factor_1, form_factor_2, shift_factor_1,
        shift_factor_2, scale_factor_1, scale_factor_2));
  }
  return 1;
}


/*
    Этот блок комментариев описывает функцию `HuberMixtureDensity`, которая вычисляет плотность вероятности смеси распределений Хьюбера.
    Параметры:
    - `x`: Значение, для которого нужно вычислить плотность вероятности.
    - `mixt_param`: Параметр смешивания, определяющий, какая компонента смеси используется.
    - Остальные параметры определяют характеристики смеси и проверки на корректность.
*/

double HuberMixtureDencity(double x, double mixt_param, double form_factor_1,
                           double form_factor_2, double shift_factor_1,
                           double shift_factor_2, double scale_factor_1,
                           double scale_factor_2) {
  if (mixt_param < 0 || mixt_param > 1) {
    return NAN;
  }

  return (1 - mixt_param) * HuberDistributionDensity(x, form_factor_1,
                                                     shift_factor_1,
                                                     scale_factor_1) +
         mixt_param * HuberDistributionDensity(x, form_factor_2, shift_factor_2,
                                               scale_factor_2);
}
/*
    Этот блок комментариев описывает функцию `HuberMixtureMathExpectation`, которая вычисляет математическое ожидание смеси распределений Хьюбера.
    Параметры:
    - `mixt_param`: Параметр смешивания, который определяет, какая компонента смеси используется.
    - Остальные параметры определяют характеристики смеси и проверки на корректность.
*/
double HuberMixtureMathExpectation(double mixt_param, double form_factor_1,
                                   double form_factor_2, double shift_factor_1,
                                   double shift_factor_2, double scale_factor_1,
                                   double scale_factor_2) {
  if (mixt_param < 0 || mixt_param > 1) {
    return NAN;
  }

  return (1 - mixt_param) * HuberDistributionMathExpectation(
                                form_factor_1, shift_factor_1, scale_factor_1) +
         mixt_param * HuberDistributionMathExpectation(
                          form_factor_2, shift_factor_2, scale_factor_2);
}
/*
    Этот блок комментариев описывает функцию `HuberMixtureVariation`, которая вычисляет дисперсию смеси распределений Хьюбера.
    Параметры:
    - `mixt_param`: Параметр смешивания, который определяет, какая компонента смеси используется.
    - Остальные параметры определяют характеристики смеси и проверки на корректность.
*/
double HuberMixtureVariation(double mixt_param, double form_factor_1,
                             double form_factor_2, double shift_factor_1,
                             double shift_factor_2, double scale_factor_1,
                             double scale_factor_2) {
  if (mixt_param < 0 || mixt_param > 1) {
    return NAN;
  }

  double m_1 = HuberDistributionMathExpectation(form_factor_1, shift_factor_1,
                                                scale_factor_1),
         m_2 = HuberDistributionMathExpectation(form_factor_2, shift_factor_2,
                                                scale_factor_2);
  double v_1 = HuberDistributionVariation(form_factor_1, shift_factor_1,
                                          scale_factor_1),
         v_2 = HuberDistributionVariation(form_factor_2, shift_factor_2,
                                          scale_factor_2);
  double m_mix = HuberMixtureMathExpectation(
      mixt_param, form_factor_1, form_factor_2, shift_factor_1, shift_factor_2,
      scale_factor_1, scale_factor_2);

  double res =
      (1 - mixt_param) * (pow(m_1, 2) + v_1) + mixt_param * (pow(m_2, 2) + v_2);
  res -= pow(m_mix, 2);
  return res;
}
/*
    Этот блок комментариев описывает функцию `HuberMixtureSkewness`, которая вычисляет коэффициент асимметрии смеси распределений Хьюбера.
    Параметры:
    - `mixt_param`: Параметр смешивания, который определяет, какая компонента смеси используется.
    - Остальные параметры определяют характеристики смеси и проверки на корректность.
*/
double HuberMixtureSkewness(double mixt_param, double form_factor_1,
                            double form_factor_2, double shift_factor_1,
                            double shift_factor_2, double scale_factor_1,
                            double scale_factor_2) {
  if (mixt_param < 0 || mixt_param > 1) {
    return NAN;
  }

  double m_1 = HuberDistributionMathExpectation(form_factor_1, shift_factor_1,
                                                scale_factor_1),
         m_2 = HuberDistributionMathExpectation(form_factor_2, shift_factor_2,
                                                scale_factor_2);
  double v_1 = HuberDistributionVariation(form_factor_1, shift_factor_1,
                                          scale_factor_1),
         v_2 = HuberDistributionVariation(form_factor_2, shift_factor_2,
                                          scale_factor_2);
  double m_mix = HuberMixtureMathExpectation(
      mixt_param, form_factor_1, form_factor_2, shift_factor_1, shift_factor_2,
      scale_factor_1, scale_factor_2);
  double v_mix = HuberMixtureVariation(mixt_param, form_factor_1, form_factor_2,
                                       shift_factor_1, shift_factor_2,
                                       scale_factor_1, scale_factor_2);
  double skew_1 = HuberDistributionSkewness(form_factor_1, shift_factor_1,
                                            scale_factor_1),
         skew_2 = HuberDistributionSkewness(form_factor_2, shift_factor_2,
                                            scale_factor_2);

  double tmp_1 =
      (1 - mixt_param) *
      (pow(m_1 - m_mix, 3) + 3 * (m_1 - m_mix) * v_1 + pow(v_1, 1.5) * skew_1);
  double tmp_2 = mixt_param * (pow(m_2 - m_mix, 3) + 3 * (m_2 - m_mix) * v_2 +
                               pow(v_2, 1.5) * skew_2);
  double res = (tmp_1 + tmp_2) / pow(v_mix, 1.5);

  return res;
}
/*
    Этот блок комментариев описывает функцию `HuberMixtureKurtosis`, которая вычисляет эксцесс смеси распределений Хьюбера.
    Параметры:
    - `mixt_param`: Параметр смешивания, который определяет, какая компонента смеси используется.
    - Остальные параметры определяют характеристики смеси и проверки на корректность.
*/
double HuberMixtureKurtosis(double mixt_param, double form_factor_1,
                            double form_factor_2, double shift_factor_1,
                            double shift_factor_2, double scale_factor_1,
                            double scale_factor_2) {
  if (mixt_param < 0 || mixt_param > 1) {
    return NAN;
  }

  double m_1 = HuberDistributionMathExpectation(form_factor_1, shift_factor_1,
                                                scale_factor_1),
         m_2 = HuberDistributionMathExpectation(form_factor_2, shift_factor_2,
                                                scale_factor_2);
  double v_1 = HuberDistributionVariation(form_factor_1, shift_factor_1,
                                          scale_factor_1),
         v_2 = HuberDistributionVariation(form_factor_2, shift_factor_2,
                                          scale_factor_2);
  double m_mix = HuberMixtureMathExpectation(
      mixt_param, form_factor_1, form_factor_2, shift_factor_1, shift_factor_2,
      scale_factor_1, scale_factor_2);
  double v_mix = HuberMixtureVariation(mixt_param, form_factor_1, form_factor_2,
                                       shift_factor_1, shift_factor_2,
                                       scale_factor_1, scale_factor_2);
  double skew_1 = HuberDistributionSkewness(form_factor_1, shift_factor_1,
                                            scale_factor_1),
         skew_2 = HuberDistributionSkewness(form_factor_2, shift_factor_2,
                                            scale_factor_2);
  double kurt_1 = HuberDistributionKurtosis(form_factor_1, shift_factor_1,
                                            scale_factor_1),
         kurt_2 = HuberDistributionKurtosis(form_factor_2, shift_factor_2,
                                            scale_factor_2);

  double tmp_1 =
      (1 - mixt_param) *
      (pow(m_1 - m_mix, 4) + 6 * pow(m_1 - m_mix, 2) * v_1 +
       4 * (m_1 - m_mix) * pow(v_1, 1.5) * skew_1 + v_1 * v_1 * (kurt_1 + 3));
  double tmp_2 =
      mixt_param *
      (pow(m_2 - m_mix, 4) + 6 * pow(m_2 - m_mix, 2) * v_2 +
       4 * (m_2 - m_mix) * pow(v_2, 1.5) * skew_2 + v_2 * v_2 * (kurt_2 + 3));
  double res = (tmp_1 + tmp_2) / pow(v_mix, 2) - 3;

  return res;
}
