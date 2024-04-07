/*-------------------------------------------------------------
 *
 * This file contains the implementation of the tests for
 * the quadratic_equation function.
 *
 * The input parameters a, b, c and the expected output data
 * are recorded in an array of structures of type test_param.
 * Each test checks whether the solutions that the
 * solve_equation function finds match the expected ones.
 *
 * In addition, the file contains the check function, which
 * performs testing on the structure selected from the array.
 * And the print_error function, which outputs an explanatory
 * message in case of an error.
 *
-------------------------------------------------------------*/

#include <assert.h>
#include <float.h>
#include <quadratic_equation.h>
#include <stdio.h>
#include <string.h>

/*
 * The function is used for testing. It receives the structure
 * number from the array as input. Using the data recorded
 * in this structure, it compares the expected values with
 * those obtained after solving the quadratic equation.
 * In case of an error, it returns 1.
 */
static int check(int test_num);

/*
 * The function is used to print a message in case of an error.
 * It prints the expected and received response, as well as
 * the parameters passed to the solve equation function.
 */
static void print_error(double a, double b, double c, double true_res1,
                        double true_res2, double false_res1, double false_res2,
                        int true_msg_id, int false_msg_id);

/*
 * A structure that contains the expected responses
 * depending on the passed parameters. It also contains
 * the name of the test.
 */
typedef struct {
  double a;    /* Transmitted parameter. */
  double b;    /* Transmitted parameter. */
  double c;    /* Transmitted parameter. */
  double res1; /* Expected response. */
  double res2; /* Expected response. */
  int msg_id;  /* Expected response. */
  char *name;  /* Name of the test. */
  char *
      test_id; /* The test ID is needed to select a structure from the array. */
} test_param;

/*
 * An array of test_param type structures with different data.
 * For the test, the structure is selected, the test_id of
 * which is passed to the main function in the parameters.
 */
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

/*
 * The main function receives one parameter as input.
 * It is needed to compare with test_id and select
 * the desired test. After selecting a test, the
 * main function performs testing using the check
 * function.
 */
int main(int argc, char *argv[]) {

  /*
   * The value returned by the main function. In case of a
   * failed test, the unchanged value of 1 will be returned.
   * If the test is successful, the function returns 0.
   */
  int res = 1;

  /* The number of elements in the test_param_arr array. */
  int size = sizeof(test_param_arr) / sizeof(test_param_arr[0]);

  /* Checking for the number of passed parameters in main. */
  assert(argc == 2);

  /*
   * Search for the desired structure by the test_id
   * parameter received by the main function.
   */
  for (int i = 0; i < size; i++)
    if (strcmp(argv[1], test_param_arr[i].test_id) == 0)
      res = check(i);

  /*
   * The value returned by the main function. In case of a
   * failed test, the unchanged value of 1 will be returned.
   * If the test is successful, the function returns 0.
   */
  return res;
}

/*
 * The function is used for testing. It receives the structure
 * number from the array as input. Using the data recorded
 * in this structure, it compares the expected values with
 * those obtained after solving the quadratic equation.
 * In case of an error, it returns 1.
 */
static int check(int test_num) {

  /*
   * Variables into which data from the selected structure
   * will be read. The result of the solve equation function will
   * be written to the variables res1 and res2.
   */
  double a, b, c, res1, res2, true_res1, true_res2;
  int msg_id, true_msg_id;

  printf("TEST_%d (%s): ", test_num, test_param_arr[test_num].name);

  a = test_param_arr[test_num].a; /* Reading the parameter `a'. */
  b = test_param_arr[test_num].b; /* Reading the parameter `b'. */
  c = test_param_arr[test_num].c; /* Reading the parameter `c'. */
  true_res1 =
      test_param_arr[test_num].res1; /* Reading the expected response. */
  true_res2 =
      test_param_arr[test_num].res2; /* Reading the expected response. */
  true_msg_id =
      test_param_arr[test_num].msg_id; /* Reading the expected response. */

  /*
   * Solving a quadratic equation with parameters
   * from the selected structure.
   */
  msg_id = solve_equation(a, b, c, &res1, &res2);

  /*
   * Checking the msg_id for correctness. If the received value
   * is not equal to the expected one, an error will be displayed
   * and the value 1 will be returned.
   */
  if (msg_id != true_msg_id) {
    print_error(a, b, c, true_res1, true_res2, res1, res2, true_msg_id, msg_id);
    return 1;

    /*
     * Checking res1 and res2 for correctness. If the received values
     * are not equal to the expected values, an error will be displayed
     * and the value 1 will be returned.
     */
  } else if ((res1 != true_res1 || res2 != true_res2) &&
             (res1 != true_res2 || res2 != true_res1)) {
    print_error(a, b, c, true_res1, true_res2, res1, res2, true_msg_id, msg_id);
    return 1;
  }

  /*
   * If there are no errors, the test is considered
   * passed and the value 0 will be returned.
   */
  printf("[OK].\n");
  return 0;
}

/*
 * The function is used to print a message in case of an error.
 * It prints the expected and received response, as well as
 * the parameters passed to the solve equation function.
 */
static void print_error(double a, double b, double c, double true_res1,
                        double true_res2, double false_res1, double false_res2,
                        int true_msg_id, int false_msg_id) {

  printf("[ERROR]:\n");

  /* Output of the transmitted parameters and the results obtained. */
  printf("\tParameters passed: a = %E   b = %E   c = %E\n", a, b, c);
  printf("\tReceived answer: res1 = %E   res2 = %E\n", false_res1, false_res2);
  printf("\tReceived msg[%d]: %s\n", false_msg_id,
         get_solve_equation_msg(false_msg_id));

  /* Output of expected results. */
  printf("\tExpected answer: res1 = %E   res2 = %E\n", true_res1, true_res2);
  printf("\tExpected msg[%d]: %s\n", true_msg_id,
         get_solve_equation_msg(true_msg_id));
}
