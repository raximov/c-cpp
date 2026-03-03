#include "../math_private.h"

/**
 * @brief проверяет число на NaN
 * @details реализацию взял с сайта
 * https://en.cppreference.com/w/c/numeric/math/isnan
 * @author naillora
 * @param double x
 * @return bool (true or false)
 */
bool s21_isnan(double x) { return x != x; }