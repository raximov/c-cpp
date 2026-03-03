#include "../math_private.h"

/**
 * @brief проверяет является ли число infinity
 * @details
 * @author lambertm
 * @param double x
 * @return bool (true or false)
 */
bool s21_isinf(double x) { return x == S21_INFINITY || x == -S21_INFINITY; }
