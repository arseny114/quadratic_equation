#include <math.h>
#include <quadratic_equation.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int check_equation_val(double a, double b, double c, double x);
static void select_parameters(double *a, double *b, double *c);
static void print_error(double a, double b, double c, double res1, double res2,
                        int msg_id);
int main(void) {
  double a, b, c;
  double res1, res2;
  int msg_id;

  for (int i = 1; i <= 5000; i++) {
    printf("RANDOM TEST_%d: ", i);

    select_parameters(&a, &b, &c);

    msg_id = solve_equation(a, b, c, &res1, &res2);

    if (msg_id == QE_ERR_OVERFLOW) {
      printf("[ERROR]: %s\n", get_solve_equation_msg(msg_id));
      exit(1);

    } else if (msg_id == QE_OK_NO_RES) {
      if ((res1 != QE_STD_VAL_RES) || (res2 != QE_STD_VAL_RES)) {
        printf("[ERROR]: %s\n", get_solve_equation_msg(msg_id));
        exit(1);
      }

    } else if (!check_equation_val(a, b, c, res1)) {
      print_error(a, b, c, res1, res2, msg_id);
      exit(1);

    } else if (!check_equation_val(a, b, c, res2)) {
      print_error(a, b, c, res1, res2, msg_id);
      exit(1);
    }
    printf("[OK].\n");
  }
  return 0;
}

static int check_equation_val(double a, double b, double c, double x) {
  long double _a, _b, _c, _x, equation_val;

  _a = a;
  _b = b;
  _c = c;
  _x = x;

  equation_val = _a * (_x * _x) + _b * _x + _c;

  if (fabsl(equation_val) <= QE_RES_ACCUR)
    return true;
  else
    return false;
}

static void select_parameters(double *a, double *b, double *c) {
  *a = ((double)rand()) / 100.0;
  *b = ((double)rand()) / 100.0;
  *c = ((double)rand()) / 100.0;
}

static void print_error(double a, double b, double c, double res1, double res2,
                        int msg_id) {
  long double _a, _b, _c, _res1, _res2, equation_val1, equation_val2;

  _a = a;
  _b = b;
  _c = c;
  _res1 = res1;
  _res2 = res2;

  equation_val1 = _a * (_res1 * _res1) + _b * _res1 + _c;
  equation_val2 = _a * (_res2 * _res2) + _b * _res2 + _c;

  printf("[ERROR]:\n");
  printf("\tParameters passed: a = %E   b = %E   c = %E\n", a, b, c);
  printf("\tReceived answer: res1 = %E   res2 = %E\n", res1, res2);
  printf("\tReceived msg[%d]: %s\n", msg_id, get_solve_equation_msg(msg_id));
  printf("\tThe value of the equation[res1]: a * res1^2 + b * res1 + c = %LE\n",
         equation_val1);
  printf("\tThe value of the equation[res2]: a * res2^2 + b * res2 + c = %LE\n",
         equation_val2);
}
