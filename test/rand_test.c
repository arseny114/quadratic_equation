/*-------------------------------------------------------------
 *
 * This file contains the implementation of tests (5000 times)
 * with the generation of random parameters `a`, `b`, `c` for
 * the solve_equation function.
 *
 * In addition, the file contains the check_equation_val
 * function, which checks that the root satisfies the equation,
 * the select_parameters function, which generates random
 * input parameters. And the print_error function, which is
 * used to print errors.
 *
-------------------------------------------------------------*/

#include "quadratic_equation.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The function substitutes the parameters `a`, `b`, `c` and
 * the root `x` into the equation. In this case, the function
 * checks that the resulting value does not differ from 0
 * by more than the accuracy specified in the quadratic_equation.h file.
 * If the resulting root satisfies the equation, the function
 * returns true. Otherwise, false.
 */
static int check_equation_val(double a, double b, double c, double x);

/*
 * The function generates random parameters `a`,
 * `b`, `c` of the double type.
 */
static void select_parameters(double *a, double *b, double *c);

/*
 * The function is used to output an error
 * (in case the check_equation_val function returned false).
 */
static void print_error(double a, double b, double c, double res1, double res2,
                        int msg_id);

/*
 * The main function is being tested. The for loop calls the
 * select_parameters function 5000 times, which generates random
 * parameters. After that, the quadratic equation with such parameters
 * is solved using the solve_equation function and the answer is
 * checked using the check_equation_val function.
 */
int main(void) {

  /* The variables that will be used to solve the equation. */
  double a, b, c;
  double res1, res2;
  int msg_id;

  for (int i = 1; i <= 5000; i++) {
    printf("RANDOM TEST_%d: ", i);

    /* Generation of random parameters. */
    select_parameters(&a, &b, &c);

    /* Solving the equation with the parameters that were generated. */
    msg_id = solve_equation(a, b, c, &res1, &res2);

    /*
     * Checking for overflow. In case of overflow, an error is
     * returned, because overflow cannot occur due to the fact
     * that the select_parameters function cannot generate parameters
     * that could cause an overflow in these calculations.
     */
    if (msg_id == QE_ERR_OVERFLOW) {
      printf("[ERROR]: %s\n", get_solve_equation_msg(msg_id));
      exit(1);

      /*
       * Checking that the equation has no roots. In this case,
       * the standard values of QE_STD_VAL_RES should be written
       * to res1 and res2. If this is not the case, an error is returned.
       */
    } else if (msg_id == QE_OK_NO_RES) {
      if ((res1 != QE_STD_VAL_RES) || (res2 != QE_STD_VAL_RES)) {
        printf("[ERROR]: %s\n", get_solve_equation_msg(msg_id));
        exit(1);
      }

      /* Checking res1 for correctness. */
    } else if (!check_equation_val(a, b, c, res1)) {
      print_error(a, b, c, res1, res2, msg_id);
      exit(1);

      /* Checking res2 for correctness. */
    } else if (!check_equation_val(a, b, c, res2)) {
      print_error(a, b, c, res1, res2, msg_id);
      exit(1);
    }

    /*
     * If none of the conditions are met,
     * the test is considered passed.
     */
    printf("[OK].\n");
  }
  return 0;
}

/*
 * The function substitutes the parameters `a`, `b`, `c` and
 * the root `x` into the equation. In this case, the function
 * checks that the resulting value does not differ from 0
 * by more than the accuracy specified in the quadratic_equation.h file.
 * If the resulting root satisfies the equation, the function
 * returns true. Otherwise, false.
 */
static int check_equation_val(double a, double b, double c, double x) {

  /*
   * Variables used for testing. The long double type is needed
   * so that an overflow of the double type does not occur
   * during calculations.
   */
  long double _a, _b, _c, _x, equation_val;

  _a = a;
  _b = b;
  _c = c;
  _x = x;

  /*
   * Substituting parameters into the
   * equation and calculating the result.
   */
  equation_val = _a * (_x * _x) + _b * _x + _c;

  /*
   * Checking that the result differs from 0 by
   * no more than the specified accuracy.
   */
  if (fabsl(equation_val) <= QE_RES_ACCUR)
    return true;
  else
    return false;
}

/*
 * The function generates random parameters `a`,
 * `b`, `c` of the double type.
 */
static void select_parameters(double *a, double *b, double *c) {

  /*
   * Dividing by 100 is necessary in order for the generated
   * number to be smaller. This does not affect the test results.
   */
  *a = ((double)rand()) / 100.0;
  *b = ((double)rand()) / 100.0;
  *c = ((double)rand()) / 100.0;
}

/*
 * The function is used to output an error
 * (in case the check_equation_val function returned false).
 */
static void print_error(double a, double b, double c, double res1, double res2,
                        int msg_id) {

  /*
   * Variables used for testing. The long double type is needed
   * so that an overflow of the double type does not occur
   * during calculations.
   */
  long double _a, _b, _c, _res1, _res2, equation_val1, equation_val2;

  _a = a;
  _b = b;
  _c = c;
  _res1 = res1;
  _res2 = res2;

  /*
   * Substituting parameters into the
   * equation and calculating the result.
   */
  equation_val1 = _a * (_res1 * _res1) + _b * _res1 + _c;
  equation_val2 = _a * (_res2 * _res2) + _b * _res2 + _c;

  /* Output a detailed message describing the error. */
  printf("[ERROR]:\n");
  printf("\tParameters passed: a = %E   b = %E   c = %E\n", a, b, c);
  printf("\tReceived answer: res1 = %E   res2 = %E\n", res1, res2);
  printf("\tReceived msg[%d]: %s\n", msg_id, get_solve_equation_msg(msg_id));
  printf("\tThe value of the equation[res1]: a * res1^2 + b * res1 + c = %LE\n",
         equation_val1);
  printf("\tThe value of the equation[res2]: a * res2^2 + b * res2 + c = %LE\n",
         equation_val2);
}
