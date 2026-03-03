#ifndef C4_S21_MATH_S21_MATH_H_
#define C4_S21_MATH_S21_MATH_H_

#define S21_INFINITY 1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define S21_EXP 2.7182818284
#define S21_EPSILON 1e-16
#define S21_M_PI 3.1415926535897932
#define S21_M_PI_2 1.57079632679489661923
#define MAX_ITERATIONS 1000000
#define S21_STEP 1000
#define S21_FLT_MAX 10000000000000000L
#define TAYLOR_ROW_LOG 300

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif  // C4_S21_MATH_S21_MATH_H_