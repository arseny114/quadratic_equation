#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

/*
 * The return value if the solve_equation function works without
 * errors. The infinity of roots is found.
 */
#define QE_OK_INF_RES 3

/*
 * The return value if the solve_equation function works without
 * errors. Two roots have been found.
 */
#define QE_OK_TWO_RES 2

/*
 * The return value if the solve_equation function works without
 * errors. One root was found.
 */
#define QE_OK_ONE_RES 1

/*
 * The return value if the solve_equation function works without
 * errors. No roots found.
 */
#define QE_OK_NO_RES 0

/*
 * The return value if an overflow occurred while the
 * solve_equation function was running.
 */
#define QE_ERR_OVERFLOW -1

/*
 * The value that the function writes to the roots of the equation
 * according to the standard. This happens in situations where there
 * are no roots in the equation, either the roots are infinite,
 * or an overflow has occurred.
 */
#define QE_STD_VAL_RES 0

/*
 * Accuracy (the value by which the result of a quadratic equation,
 * when substituting the root into it, may differ from 0).
 * It is used in random tests. It is necessary because when using
 * floating-point numbers, there is a loss of accuracy.
 */
#define QE_RES_ACCUR 0.00001

/*
 * A function that solves a quadratic equation. Returns msg_id
 * as a result (the values are described above). The roots are
 * written to res1 and res2.
 */
extern int solve_equation(double a, double b, double c, double *res1,
                          double *res2);

/*
 * A function that allows you to get a pointer to a string
 * with a description of msg_id (the values are described above).
 * It is used in tests.
 */
extern char *get_solve_equation_msg(int msg_id);

#endif
