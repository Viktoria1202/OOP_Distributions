#include "distribution.h"

int statisticGetSet(const std::vector<double> *values, int size,
                    std::vector<double> *dest) {
  if (values == NULL || dest == NULL || size <= 0) {
    return 0;
  }
  (*dest).clear();

  double max = *(std::max_element((*values).begin(), (*values).end()));
  double min = *(std::min_element((*values).begin(), (*values).end()));
  double interval_amount = 1 + floor(log2((*values).size()));
  double interval_len = (max - min) / interval_amount;

  std::vector<double> frequences;
  statisticDensityBuild(values, &frequences);
  for (int i = 0; i < interval_amount; i++) {
    frequences[i] *= interval_len;
  }
  frequences.insert(frequences.begin(), 0.0);

  double r = 0, res = 0;
  double x_begin = 0;
  double r_lower_bound = 0, r_upper_bound = 0;

  for (int j = 0; j < size; j++) {
    r = uniformDistributionGetNumber();
    x_begin = 0;
    r_lower_bound = 0, r_upper_bound = 0;
    for (int i = 0; i < frequences.size() - 1; i++) {
      r_lower_bound += frequences[i];
      r_upper_bound += frequences[i + 1];
      if (r_lower_bound <= r && r < r_upper_bound) {
        x_begin = min + i * interval_len;
        i += frequences.size();  // выход из цикла
      }
    }

    res = uniformDistributionGetNumber();
    res = x_begin + res * interval_len;
    (*dest).push_back(res);
  }

  return 1;
}

double statisticGetNum(const std::vector<double> *values) {
  if (values == NULL) {
    return NAN;
  }
  double max = *(std::max_element((*values).begin(), (*values).end()));
  double min = *(std::min_element((*values).begin(), (*values).end()));
  double interval_amount = 1 + floor(log2((*values).size()));
  double interval_len = (max - min) / interval_amount;

  std::vector<double> frequences;
  statisticDensityBuild(values, &frequences);
  frequences.insert(frequences.begin(), 0.0);
  // ���������� ����������, �� �������� ������� �����
  double r = uniformDistributionGetNumber();
  double x_begin = 0, x_end = 0;
  double r_lower_bound = 0, r_upper_bound = 0;

  for (int i = 0; i < frequences.size() - 1; i++) {
    r_lower_bound += frequences[i];
    r_upper_bound += frequences[i + 1];
    if (r_lower_bound <= r && r < r_upper_bound) {
      x_begin = min + i * interval_len;
      x_end = x_begin + interval_len;
    }
  }

  double res = uniformDistributionGetNumber();
  res = x_begin + res * interval_len;
  return res;
}

double statisticDensity(double x, const std::vector<double> *values) {
  if (values == NULL) {
    return NAN;
  }

  double max = *(std::max_element((*values).begin(), (*values).end()));
  double min = *(std::min_element((*values).begin(), (*values).end()));

  if (x > max || x < min) {
    return 0;
  }

  double interval_amount = 1 + floor(log2((*values).size()));
  double interval_len = (max - min) / interval_amount;
  std::vector<double> frequences;
  statisticDensityBuild(values, &frequences);

  double x_begin = 0, x_end = 0;

  double res = 0;

  for (int i = 0; i < (*values).size() && !res; i++) {
    x_begin = min + i * interval_len, x_end = x_begin + interval_len;
    if (x_begin <= x && x < x_end) {
      res = frequences[i];
    } else if (x_end == max && x == max) {
      res = frequences[i];
    }
  }

  return res;
}

int statisticDensityBuild(const std::vector<double> *values,
                          std::vector<double> *frequences) {
  if (frequences == NULL) {
    return 0;
  }

  (*frequences).clear();

  double max = *(std::max_element((*values).begin(), (*values).end()));
  double min = *(std::min_element((*values).begin(), (*values).end()));

  double interval_amount = 1 + floor(log2((*values).size()));
  double interval_len = (max - min) / interval_amount;

  double x_begin = 0, x_end = 0;
  int freq_count = 0;

  for (int i = 0; i < interval_amount; i++) {
    x_begin = min + i * interval_len, x_end = x_begin + interval_len;
    freq_count = 0;
    for (int j = 0; j < (*values).size(); j++) {
      if (x_begin <= (*values)[j] && (*values)[j] < x_end) {
        freq_count++;
      } else if (fabs(x_end - max) <= EPSILON &&
                 fabs((*values)[j] - max) <= EPSILON) {
        freq_count++;
      }
    }
    (*frequences).push_back(freq_count / ((*values).size() * interval_len));
  }

  return 1;
}
double statisticMathExpectation(const std::vector<double> *values) {
  if (values == NULL) {
    return NAN;
  }

  long double res = 0;
  double size = (*values).size();

  for (auto i : *values) {
    res += i / size;
  }
  return res;
}

double statisticVariation(const std::vector<double> *values) {
  if (values == NULL) {
    return NAN;
  }

  double res = 0, M = statisticMathExpectation(values);
  double size = (*values).size();
  for (auto i : (*values)) {
    res += pow(i - M, 2) / size;
  }
  return res;
}

double statisticSkewness(const std::vector<double> *values) {
  if (values == NULL) {
    return NAN;
  }

  double res = 0, M = statisticMathExpectation(values),
         D = statisticVariation(values), size = (*values).size();
  for (auto i : (*values)) {
    res += pow(i - M, 3) / size;
  }

  res /= pow(D, 1.5);
  return res;
}

double statisticKurtosis(const std::vector<double> *values) {
  if (values == NULL) {
    return NAN;
  }

  double res = 0, M = statisticMathExpectation(values),
         D = statisticVariation(values), size = (*values).size();

  for (auto i : (*values)) {
    res += pow(i - M, 4) / size;
  }

  res = res / pow(D, 2) - 3;
  return res;
}