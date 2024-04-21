/*-------------------------------------------------------------
 *
 * This file contains the implementation of
 * the solve_equation function.
 *
 * The function solves a quadratic equation
 * and returns the msg_id characterizing the execution
 * of the function. The msg_id definitions are in
 * the quadratic_equation.h file.
 *
 * In addition, the file contains overflow checking
 * function (check_overflow) and a function for decrypting
 * msg_id (get_solve_equation_msg).
 *
-------------------------------------------------------------*/

#include "quadratic_equation.h"
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * The function check whether the res value
 * is outside the double range.
 */
static int check_overflow(long double res);

/*
 * The function returns a pointer to a string
 * that decrypts the passed msg_id.
 */
char *get_solve_equation_msg(int msg_id);

/*
 * Implementation of the solve_equation function that solves
 * the quadratic equation.
 *
 * If the equation has two different roots, then it will be written
 * in res1 and res2. If the equation has one root, then it will be
 * written to both res1 and res2.
 *
 * If there are no roots, or the roots are infinite,
 * or an overflow has occurred, the standard value is written to
 * res1 and res2, which is set in the quadratic_equation.h file.
 */
int solve_equation(double a, double b, double c, double *res1, double *res2) {

  /*
   * Variables to be used in calculations. The long double data type
   * is selected in order to eliminate double type overflow. At the
   * time of writing the response to res1 and res2,
   * an overflow check will be performed.
   */
  long double discriminant, _a, _b, _c;
  long double _res1, _res2;

  /* Checking pointers for a non-NULL value. */
  if ((res1 == NULL) || (res2 == NULL))
    return QE_ERR_NULLPTR;

  /*
   * The function writes the standard values to res1 and res2.
   * Under some conditions described above, these values will
   * not be changed.
   */
  *res1 = *res2 = QE_STD_VAL_RES;

  /* Checking for the infinity of roots. */
  if ((a == 0) && (b == 0) && (c == 0)) {
    return QE_OK_INF_RES;

    /* If only `c` is not zero, the equation has no roots. */
  } else if ((a == 0) && (b == 0) && (c != 0)) {
    return QE_OK_NO_RES;

    /* If only `b` is not zero, the equation has one root, res = 0. */
  } else if ((a == 0) && (b != 0) && (c == 0)) {
    *res1 = *res2 = 0;
    return QE_OK_ONE_RES;

    /* If only `a` is not zero, the equation has one root, res = 0. */
  } else if ((a != 0) && (b == 0) && (c == 0)) {
    *res1 = *res2 = 0;
    return QE_OK_ONE_RES;

    /*
     * If only `a` is zero, then the equation will
     * be solved using the simple formula given below.
     */
  } else if ((a == 0) && (b != 0) && (c != 0)) {
    _b = b;
    _c = c;

    _res1 = -_c / _b;

    /*
     * Before writing the root to res1 and res2, an overflow
     * check is performed. In case of overflow, the function
     * returns the msg_id characterizing the overflow.
     */
    if (check_overflow(_res1)) {
      *res1 = *res2 = _res1;
      return QE_OK_ONE_RES;
    } else
      return QE_ERR_OVERFLOW;

    /*
     * In all other cases, the equation is solved
     * through the discriminant.
     */
  } else {

    _a = a;
    _b = b;
    _c = c;

    discriminant = _b * _b - 4.0 * _a * _c;

    /*
     * Solving the equation if the discriminant
     * is greater than zero.
     */
    if (discriminant > 0) {
      _res1 = (-_b + sqrt(discriminant)) / (2.0 * _a);
      _res2 = (-_b - sqrt(discriminant)) / (2.0 * _a);

      /*
       * Before writing the root to res1 and res2, an overflow
       * check is performed. In case of overflow, the function
       * returns the msg_id characterizing the overflow.
       */
      if (check_overflow(_res1) && check_overflow(_res2)) {
        *res1 = _res1;
        *res2 = _res2;
        return QE_OK_TWO_RES;
      } else
        return QE_ERR_OVERFLOW;

      /* Solving the equation if the discriminant is zero. */
    } else if (discriminant == 0) {
      _res1 = (-_b) / (2.0 * _a);
      _res2 = _res1;

      /*
       * Before writing the root to res1 and res2, an overflow
       * check is performed. In case of overflow, the function
       * returns the msg_id characterizing the overflow.
       */
      if (check_overflow(_res1)) {
        *res1 = _res1;
        *res2 = *res1;
        return QE_OK_ONE_RES;
      } else
        return QE_ERR_OVERFLOW;

      /*
       * If the discriminant is less than zero,
       * the equation has no roots.
       *
       * In future versions, it is possible to
       * expand the library's capabilities and calculate
       * roots on the complex plane with a negative discriminant.
       */
    } else
      return QE_OK_NO_RES;
  }
}

/*
 * The function returns a pointer to a string
 * that decrypts the passed msg_id.
 */
char *get_solve_equation_msg(int msg_id) {
  switch (msg_id) {

  case QE_OK_INF_RES:
    return "The equation is solved. An infinite number of solutions have been "
           "found.";

  case QE_OK_ONE_RES:
    return "The equation is solved. One solution found.";

  case QE_OK_TWO_RES:
    return "The equation is solved. Two solutions found.";

  case QE_OK_NO_RES:
    return "The equation is solved. No solutions found.";

  case QE_ERR_OVERFLOW:
    return "The equation is not solved. An overflow has occurred.";

  case QE_ERR_NULLPTR:
    return "The null pointers *res1 and *res2 were passed to the function.";

  default:
    return "Empty message.";
  }
}

/*
 * The function check whether the res value
 * is outside the double range.
 */
static int check_overflow(long double res) {

  if ((res > DBL_MAX) || (res < -DBL_MAX))
    return false;
  else
    return true;
}
