#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <stdio.h>

#define M_PI 3.14159265358979323846
#define EPSILON 1e-16
/*
        utility.cpp
*/
double uniformDistributionGetNumber();
double standardDistributionFunction(double x);
double standardDistributionDensity(double x);

/*
        �������� (������������� �������)
        Huber_dist.cpp
*/

double HuberDistributionGetNumber(double form_factor, double shift_factor = 0,
                                  double scale_factor = 1);
int HuberDistributionGetSet(int counts, std::vector<double> *dest,
                            double form_factor, double shift_factor = 0,
                            double scale_factor = 1);

double HuberDistributionDensity(double x, double form_factor,
                                double shift_factor = 0,
                                double scale_factor = 1);
double HuberDistributionMathExpectation(double form_factor,
                                        double shift_factor = 0,
                                        double scale_factor = 1);
double HuberDistributionVariation(double form_factor, double shift_factor = 0,
                                  double scale_factor = 1);
double HuberDistributionSkewness(double form_factor, double shift_factor = 0,
                                 double scale_factor = 1);
double HuberDistributionKurtosis(double form_factor, double shift_factor = 0,
                                 double scale_factor = 1);

/*
        ����� ������������� �������
        mixtures.cpp
*/

double HuberMixtureGetNum(double mixt_param, double form_factor_1,
                          double form_factor_2, double shift_factor_1,
                          double shift_factor_2, double scale_factor_1,
                          double scale_factor_2);
int HuberMixtureGetSet(int size, std::vector<double> *dest, double mixt_param,
                       double form_factor_1, double form_factor_2,
                       double shift_factor_1, double shift_factor_2,
                       double scale_factor_1, double scale_factor_2);

double HuberMixtureDencity(double x, double mixt_param, double form_factor_1,
                           double form_factor_2, double shift_factor_1,
                           double shift_factor_2, double scale_factor_1,
                           double scale_factor_2);
double HuberMixtureMathExpectation(double mixt_param, double form_factor_1,
                                   double form_factor_2, double shift_factor_1,
                                   double shift_factor_2, double scale_factor_1,
                                   double scale_factor_2);
double HuberMixtureVariation(double mixt_param, double form_factor_1,
                             double form_factor_2, double shift_factor_1,
                             double shift_factor_2, double scale_factor_1,
                             double scale_factor_2);
double HuberMixtureSkewness(double mixt_param, double form_factor_1,
                            double form_factor_2, double shift_factor_1,
                            double shift_factor_2, double scale_factor_1,
                            double scale_factor_2);
double HuberMixtureKurtosis(double mixt_param, double form_factor_1,
                            double form_factor_2, double shift_factor_1,
                            double shift_factor_2, double scale_factor_1,
                            double scale_factor_2);
/*
        �������������� �������������� �� �������
*/

double statisticDensity(double x, const std::vector<double> *values);
int statisticDensityBuild(const std::vector<double> *values,
                          std::vector<double> *frequences);
double statisticGetNum(const std::vector<double> *values);
int statisticGetSet(const std::vector<double> *values, int size,
                    std::vector<double> *dest);

double statisticMathExpectation(const std::vector<double> *values);
double statisticVariation(const std::vector<double> *values);
double statisticSkewness(const std::vector<double> *values);
double statisticKurtosis(const std::vector<double> *values);