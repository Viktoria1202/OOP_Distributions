#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#ifdef linux
#include <check.h>
#endif  // linux
#include <stdio.h>
#include <stdlib.h>

#include "../distribution.h"

#define RESET "\x1b[0m"
#define YELLOW_BG "\x1b[103m"
#define BLACK "\x1b[30m"
#define WHITE "\x1b[97m"

#define RED_BG "\x1b[41m"
#define GREEN_BG "\x1b[42m"
#define WHITE_BG "\x1b[47m"
#define GRAY_BG "\x1b[100m"

#ifdef linux
Suite *suite_Huber_Destr();
#endif  // linux

void run();

#endif  // SRC_TESTS_TESTS_H_
