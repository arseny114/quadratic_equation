#include <assert.h>
#include <float.h>
#include <math.h>
#include <quadratic_equation.h>
#include <stdbool.h>

static int check_overflow(long double res);

int solve_equation(double a, double b, double c, double *res1, double *res2) {

  long double discriminant, _a, _b, _c;
  long double _res1, _res2;
  // int msg_id;

  assert(res1);
  assert(res2);

  *res1 = *res2 = QE_STD_VAL_RES;

  if ((a == 0) && (b == 0) && (c == 0)) {
    return QE_OK_INF_RES;

  } else if ((a == 0) && (b == 0) && (c != 0)) {
    return QE_OK_NO_RES;

  } else if ((a == 0) && (b != 0) && (c == 0)) {
    *res1 = *res2 = 0;
    return QE_OK_ONE_RES;

  } else if ((a != 0) && (b == 0) && (c == 0)) {
    *res1 = *res2 = 0;
    return QE_OK_ONE_RES;

  } else if ((a == 0) && (b != 0) && (c != 0)) {
    _b = b;
    _c = c;

    _res1 = -_c / _b;

    if (check_overflow(_res1)) {
      *res1 = *res2 = _res1;
      return QE_OK_ONE_RES;
    } else
      return QE_ERR_OVERFLOW;

  } else {

    _a = a;
    _b = b;
    _c = c;

    discriminant = _b * _b - 4 * _a * _c;

    if (discriminant > 0) {
      _res1 = (-_b + sqrt(discriminant)) / (2 * _a);
      _res2 = (-_b - sqrt(discriminant)) / (2 * _a);

      if (check_overflow(_res1) && check_overflow(_res2)) {
        *res1 = _res1;
        *res2 = _res2;
        return QE_OK_TWO_RES;
      } else
        return QE_ERR_OVERFLOW;

    } else if (discriminant == 0) {
      _res1 = (-_b) / (2 * _a);
      _res2 = _res1;

      if (check_overflow(_res1)) {
        *res1 = _res1;
        *res2 = *res1;
        return QE_OK_ONE_RES;
      } else
        return QE_ERR_OVERFLOW;

    } else
      return QE_OK_NO_RES;
  }
}

// Только для мейна
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

  default:
    return "Empty message.";
  }
}

static int check_overflow(long double res) {

  if ((res > DBL_MAX) || (res < -DBL_MAX))
    return false;
  else
    return true;
}
