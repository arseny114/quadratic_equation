#include "quadratic_equation.h"
#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <string.h>

static int check(int test_num);
static void print_error(double a, double b, double c, double true_res1,
                        double true_res2, double false_res1, double false_res2,
                        int true_msg_id, int false_msg_id);

typedef struct {
  double a;
  double b;
  double c;
  double res1;
  double res2;
  int msg_id;
  char *name;
  char *test_id;
} test_param;

test_param test_param_arr[] = {
    {.a = 0,
     .b = 0,
     .c = 0,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_OK_INF_RES,
     .name = "All parameters are equal to 0.",
     .test_id = "test1"},

    {.a = 0,
     .b = 0,
     .c = 1,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_OK_NO_RES,
     .name = "Only `c` is not equal to 0.",
     .test_id = "test2"},

    {.a = 0,
     .b = 1,
     .c = 0,
     .res1 = 0,
     .res2 = 0,
     .msg_id = QE_OK_ONE_RES,
     .name = "Only `b` is not equal to 0.",
     .test_id = "test3"},

    {.a = 1,
     .b = 0,
     .c = 0,
     .res1 = 0,
     .res2 = 0,
     .msg_id = QE_OK_ONE_RES,
     .name = "Only `a` is not equal to 0.",
     .test_id = "test4"},

    {.a = 0,
     .b = 5,
     .c = 3,
     .res1 = -0.6,
     .res2 = -0.6,
     .msg_id = QE_OK_ONE_RES,
     .name = "An incomplete quadratic equation with `a` equal to 0.",
     .test_id = "test5"},

    {.a = 0,
     .b = 0.01,
     .c = DBL_MAX - 1,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_ERR_OVERFLOW,
     .name = "An incomplete quadratic equation with `a` equal to 0. Overflow.",
     .test_id = "test6"},

    {.a = 1,
     .b = 0,
     .c = 1,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_OK_NO_RES,
     .name = "An incomplete quadratic equation with `b` equal to 0, D < 0.",
     .test_id = "test7"},

    {.a = 1,
     .b = 0,
     .c = -16,
     .res1 = -4,
     .res2 = 4,
     .msg_id = QE_OK_TWO_RES,
     .name = "An incomplete quadratic equation with `b` equal to 0, D > 0.",
     .test_id = "test8"},

    {.a = -DBL_MAX + 1,
     .b = 0,
     .c = DBL_MAX - 1,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_ERR_OVERFLOW,
     .name = "An incomplete quadratic equation with `b` equal to 0. D > 0. "
             "Overflow.",
     .test_id = "test9"},

    {.a = 10,
     .b = 5,
     .c = 0,
     .res1 = 0,
     .res2 = -0.5,
     .msg_id = QE_OK_TWO_RES,
     .name = "An incomplete quadratic equation with `c` equal to 0.",
     .test_id = "test10"},

    {.a = 10,
     .b = DBL_MAX - 1,
     .c = 0,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_ERR_OVERFLOW,
     .name = "An incomplete quadratic equation with `c` equal to 0. Overflow",
     .test_id = "test11"},

    {.a = 1,
     .b = 3,
     .c = -70,
     .res1 = -10,
     .res2 = 7,
     .msg_id = QE_OK_TWO_RES,
     .name = "The complete quadratic equation. D > 0.",
     .test_id = "test12"},

    {.a = -1.5625,
     .b = 5,
     .c = -4,
     .res1 = 1.6,
     .res2 = 1.6,
     .msg_id = QE_OK_ONE_RES,
     .name = "The complete quadratic equation. D = 0.",
     .test_id = "test13"},

    {.a = 5,
     .b = 10,
     .c = 100,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_OK_NO_RES,
     .name = "The complete quadratic equation. D < 0.",
     .test_id = "test14"},

    {.a = 1,
     .b = DBL_MAX - 1,
     .c = 1,
     .res1 = QE_STD_VAL_RES,
     .res2 = QE_STD_VAL_RES,
     .msg_id = QE_ERR_OVERFLOW,
     .name = "The complete quadratic equation. Overflow.",
     .test_id = "test15"}};

int main(int argc, char *argv[]) {
  int res = 1;

  int size = sizeof(test_param_arr) / sizeof(test_param_arr[0]);

  assert(argc == 2);

  for (int i = 0; i < size; i++)
    if (strcmp(argv[1], test_param_arr[i].test_id) == 0)
      res = check(i);

  return res;
}

static int check(int test_num) {
  double a, b, c, res1, res2, true_res1, true_res2;
  int msg_id, true_msg_id;

  printf("TEST_%d (%s): ", test_num, test_param_arr[test_num].name);

  a = test_param_arr[test_num].a;
  b = test_param_arr[test_num].b;
  c = test_param_arr[test_num].c;
  true_res1 = test_param_arr[test_num].res1;
  true_res2 = test_param_arr[test_num].res2;
  true_msg_id = test_param_arr[test_num].msg_id;

  msg_id = solve_equation(a, b, c, &res1, &res2);

  if (msg_id != true_msg_id) {
    print_error(a, b, c, true_res1, true_res2, res1, res2, true_msg_id, msg_id);
    return 1;

  } else if ((res1 != true_res1 || res2 != true_res2) &&
             (res1 != true_res2 || res2 != true_res1)) {
    print_error(a, b, c, true_res1, true_res2, res1, res2, true_msg_id, msg_id);
    return 1;
  }
  printf("[OK].\n");
  return 0;
}

static void print_error(double a, double b, double c, double true_res1,
                        double true_res2, double false_res1, double false_res2,
                        int true_msg_id, int false_msg_id) {

  printf("[ERROR]:\n");
  printf("\tParameters passed: a = %E   b = %E   c = %E\n", a, b, c);
  printf("\tReceived answer: res1 = %E   res2 = %E\n", false_res1, false_res2);
  printf("\tReceived msg[%d]: %s\n", false_msg_id,
         get_solve_equation_msg(false_msg_id));

  printf("\tExpected answer: res1 = %E   res2 = %E\n", true_res1, true_res2);
  printf("\tExpected msg[%d]: %s\n", true_msg_id,
         get_solve_equation_msg(true_msg_id));
}
