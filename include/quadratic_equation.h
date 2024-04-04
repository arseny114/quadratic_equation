#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#define QE_OK_INF_RES 3
#define QE_OK_TWO_RES 2
#define QE_OK_ONE_RES 1
#define QE_OK_NO_RES 0
#define QE_ERR_OVERFLOW -1

#define QE_STD_VAL_RES 0

// При точности 10^-6 уже падает 1512 тест
#define QE_RES_ACCUR 0.00001

extern int solve_equation(double a, double b, double c, double *res1,
                          double *res2);

extern char *get_solve_equation_msg(int msg_id);

#endif
