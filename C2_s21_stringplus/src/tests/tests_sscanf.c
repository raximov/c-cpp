
#include "s21_test.h"

START_TEST(sscanf_test_e_1) {
  float e1 = 0, e2 = 0;
  int orig_result = 0, our_result = 0;

  orig_result = sscanf("42e21", "%e", &e1);
  our_result = s21_sscanf("42e21", "%e", &e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("12e21", "%e", &e1);
  our_result = s21_sscanf("12e21", "%e", &e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42.215e-21", "%9e", &e1);
  our_result = s21_sscanf("42.215e-21", "%9e", &e2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "not equal");

  orig_result = sscanf("42.215e21", "%8e", &e1);
  our_result = s21_sscanf("42.215e21", "%8e", &e2);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("1.423422423", "%e", &e1);
  our_result = s21_sscanf("1.423422423", "%e", &e2);
  ck_assert_float_eq(e1, e2);
  ck_assert_msg(e1 == e2, "not equal");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_l_1) {
  int orig_result = 0, our_result = 0;
  unsigned long lu1 = 0, lu2 = 0;
  long ld1 = 0, ld2 = 0;
  wchar_t lc1, lc2;
  wchar_t lsuite[100], ls2[100];

  orig_result = sscanf("a", "%lc", &lc1);
  our_result = s21_sscanf("a", "%lc", &lc2);
  ck_assert_int_eq(lc1, lc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4245", "%lu", &lu1);
  our_result = s21_sscanf("4245", "%lu", &lu2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4245", "%ld", &ld1);
  our_result = s21_sscanf("4245", "%ld", &ld2);
  ck_assert_int_eq(ld1, ld2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("amazing", "%9ls", lsuite);
  our_result = s21_sscanf("amazing", "%9ls", ls2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_int_eq(wcscmp(ls2, lsuite), 0);

  orig_result = sscanf("amazing", "%2ls", lsuite);
  our_result = s21_sscanf("amazing", "%2ls", ls2);
  ck_assert_int_eq(wcscmp(lsuite, ls2), 0);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_L_1) {
  int orig_result = 0, our_result = 0;
  long double Lf1 = 0, Lf2 = 0;

  orig_result = sscanf("42.45", "%Lf", &Lf1);
  our_result = s21_sscanf("42.45", "%Lf", &Lf2);
  ck_assert_msg((int)Lf1 == (int)Lf2, "not equal");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_u_1) {
  int orig_result = 0, our_result = 0;
  unsigned u1 = 0, u2 = 0;

  orig_result = sscanf("", "%u", &u1);
  our_result = s21_sscanf("", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("481516", "%u", &u1);
  our_result = s21_sscanf("481516", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-48", "%u", &u1);
  our_result = s21_sscanf("-48", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("48.1516", "%u", &u1);
  our_result = s21_sscanf("48.1516", "%u", &u2);
  ck_assert_msg(u1 == u2, "not equal");
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_h_1) {
  int orig_result = 0, our_result = 0;
  unsigned short hu1 = 0, hu2 = 0;

  orig_result = sscanf("1", "%hu", &hu1);
  our_result = s21_sscanf("1", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("48151623", "%hu", &hu1);
  our_result = s21_sscanf("48151623", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-5", "%hu", &hu1);
  our_result = s21_sscanf("-5", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_s_1) {
  int orig_result = 0, our_result = 0;
  char suite[100], s2[100];

  orig_result = sscanf("Ricasso 21 SaMaRkAnD1", "%*s%s", suite);
  our_result = s21_sscanf("Ricasso 21 SaMaRkAnD1", "%*s%s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("", "%s", suite);
  our_result = s21_sscanf("", "%s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("PROGRAMMER", "%8s", suite);
  our_result = s21_sscanf("PROGRAMMER", "%8s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("PROGRAMMER", "%18s", suite);
  our_result = s21_sscanf("PROGRAMMER", "%18s", s2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_f_1) {
  int orig_result = 0, our_result = 0;
  float f_1 = 0, f2 = 0;

  orig_result = sscanf("42e-3", "%f", &f_1);
  our_result = s21_sscanf("42e-3", "%f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-42.21", "%f", &f_1);
  our_result = s21_sscanf("-42.21", "%f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-21.42", "%5f", &f_1);
  our_result = s21_sscanf("-21.42", "%5f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("21.42", "%5f", &f_1);
  our_result = s21_sscanf("21.42", "%5f", &f2);
  ck_assert_int_eq(f_1, f2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_x_1) {
  int orig_result = 0, our_result = 0;
  unsigned x1 = 0, x2 = 0;

  orig_result = sscanf("0X481516", "%x", &x1);
  our_result = s21_sscanf("0X481516", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0x481516", "%2x", &x1);
  our_result = s21_sscanf("0x481516", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("fffff", "%2x", &x1);
  our_result = s21_sscanf("fffff", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("BBBBBB", "%2x", &x1);
  our_result = s21_sscanf("BBBBBB", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("ABCDEFGH", "%x", &x1);
  our_result = s21_sscanf("ABCDEFGH", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("abcdefg", "%x", &x1);
  our_result = s21_sscanf("abcdefg", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0x42456789042456789", "%x", &x1);
  our_result = s21_sscanf("0x42456789042456789", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0", "%x", &x1);
  our_result = s21_sscanf("0", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-42", "%x", &x1);
  our_result = s21_sscanf("-42", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_i_1) {
  int orig_result = 0, our_result = 0;
  int i1 = 0, i2 = 0;

  orig_result = sscanf("9878645", "%i", &i1);
  our_result = s21_sscanf("9878645", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0x42AB", "%i", &i1);
  our_result = s21_sscanf("0x42AB", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("177777777", "%i", &i1);
  our_result = s21_sscanf("177777777", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-481516", "%i", &i1);
  our_result = s21_sscanf("-481516", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_proc_1) {
  int orig_result = 0, our_result = 0;
  char proc1[100] = {0}, proc2[100] = {0};

  orig_result = sscanf("48151642342", "%s%%", proc1);
  our_result = s21_sscanf("48151642342", "%s%%", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("Hello", "%%%s", proc1);
  our_result = s21_sscanf("Hello", "%%%s", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_p_1) {
  int orig_result = 0, our_result = 0;
  void *p1 = 0, *p2 = 0;

  orig_result = sscanf("0x42", "%8p", &p1);
  our_result = s21_sscanf("0x42", "%8p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0X4245", "%p", &p1);
  our_result = s21_sscanf("0X4245", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0X4245AB", "%p", &p1);
  our_result = s21_sscanf("0X4245AB", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42.456", "%p", &p1);
  our_result = s21_sscanf("42.456", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-5", "%8p", &p1);
  our_result = s21_sscanf("-5", "%8p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("0", "%p", &p1);
  our_result = s21_sscanf("0", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_n_1) {
  int n_1 = 0, n_2 = 0, d_1 = 0, d_2 = 0, orig_result = 0, our_result = 0;

  orig_result = sscanf("42.456", "%n", &n_1);
  our_result = s21_sscanf("42.456", "%n", &n_2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42456", "%d%n", &d_1, &n_1);
  our_result = s21_sscanf("42456", "%d%n", &d_2, &n_2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_d_1) {
  int orig_result = 0, our_result = 0, d1 = 0, d2 = 0;

  orig_result = sscanf("42", "%d", &d1);
  our_result = s21_sscanf("42", "%d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("-42 l", "%10d", &d1);
  our_result = s21_sscanf("-42 l", "%10d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_all) {
  int d1 = 0, d2 = 0, i1 = 0, i2 = 0, n_1 = 0, n_2 = 0, orig_result = 0,
      our_result = 0;
  float e1 = 0, e2 = 0, E1 = 0, E2 = 0, f_1 = 0, f2 = 0, g1 = 0, g2 = 0, G1 = 0,
        G2 = 0;
  unsigned o1 = 0, o2 = 0, u1 = 0, u2 = 0, x1 = 0, x2 = 0, X1 = 0, X2 = 0;
  void *p1 = 0, *p2 = 0;
  char suite[100], s2[100], c1, c2, proc1[100] = {0}, proc2[100] = {0};
  short hi1 = 0, hi2 = 0, hd1 = 0, hd2 = 0;
  unsigned long lo1 = 0, lo2 = 0, lu1 = 0, lu2 = 0;
  long double Le1 = 0, Le2 = 0, LE1 = 0, LE2 = 0, Lg1 = 0, Lg2 = 0, LG1 = 0,
              LG2 = 0;

  orig_result = sscanf("42", "%d", &d1);
  our_result = s21_sscanf("42", "%d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42 amazing", "%d%9s", &d1, suite);
  our_result = s21_sscanf("42 amazing", "%d%9s", &d2, s2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("42 amazing q", "%d%9s%c", &d1, suite, &c1);
  our_result = s21_sscanf("42 amazing q", "%d%9s%c", &d2, s2, &c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q", "%i%d%9s%c", &i1, &d1, suite, &c1);
  our_result = s21_sscanf("4 42 amazing q", "%i%d%9s%c", &i2, &d2, s2, &c2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21", "%i%d%9s%c%e", &i1, &d1, suite, &c1, &e1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21", "%i%d%9s%c%e", &i2, &d2, s2, &c2, &e2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12 43e21", "%i%d%9s%c%e%E", &i1, &d1,
                       suite, &c1, &e1, &E1);
  our_result = s21_sscanf("4 42 amazing q 12 43e21", "%i%d%9s%c%e%E", &i2, &d2,
                          s2, &c2, &e2, &E2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37", "%i%d%9s%c%e%E%f",
                       &i1, &d1, suite, &c1, &e1, &E1, &f_1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13,37", "%i%d%9s%c%e%E%f",
                          &i2, &d2, s2, &c2, &e2, &E2, &f2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21 43e21 13.37 2.28", "%i%d%9s%c%e%E%f%g", &i1,
             &d1, suite, &c1, &e1, &E1, &f_1, &g1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28", "%i%d%9s%c%e%E%f%g",
                 &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                       "%i%d%9s%c%e%E%f%g%G", &i1, &d1, suite, &c1, &e1, &E1,
                       &f_1, &g1, &G1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                          "%i%d%9s%c%e%E%f%g%G", &i2, &d2, s2, &c2, &e2, &E2,
                          &f2, &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                       "%i%d%9s%c%e%E%f%g%G", &i1, &d1, suite, &c1, &e1, &E1,
                       &f_1, &g1, &G1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228",
                          "%i%d%9s%c%e%E%f%g%G", &i2, &d2, s2, &c2, &e2, &E2,
                          &f2, &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101",
                       "%i%d%9s%c%e%E%f%g%G%o", &i1, &d1, suite, &c1, &e1, &E1,
                       &f_1, &g1, &G1, &o1);
  our_result = s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101",
                          "%i%d%9s%c%e%E%f%g%G%o", &i2, &d2, s2, &c2, &e2, &E2,
                          &f2, &g2, &G2, &o2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854",
             "%i%d%9s%c%e%E%f%g%G%o%u", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
             &g1, &G1, &o1, &u1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854",
                 "%i%d%9s%c%e%E%f%g%G%o%u", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                 &g2, &G2, &o2, &u2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result =
      sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab",
             "%i%d%9s%c%e%E%f%g%G%o%u%x", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
             &g1, &G1, &o1, &u1, &x1);
  our_result =
      s21_sscanf("4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab",
                 "%i%d%9s%c%e%E%f%g%G%o%u%x", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                 &g2, &G2, &o2, &u2, &x2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X", &i1, &d1, suite, &c1, &e1, &E1, &f_1, &g1,
      &G1, &o1, &u1, &x1, &X1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X", &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2, &G2,
      &o2, &u2, &x2, &X2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p1", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
      &g1, &G1, &o1, &u1, &x1, &X1, &p1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p2", &i2, &d2, s2, &c2, &e2, &E2, &f2, &g2,
      &G2, &o2, &u2, &x2, &X2, &p2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab "
      "BA21 shrek & amazing is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%%", &i1, &d1, suite, &c1, &e1, &E1, &f_1,
      &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%%", &i2, &d2, s2, &c2, &e2, &E2, &f2,
      &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_int_eq(orig_result, our_result);
  orig_result = sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab "
      "BA21 shrek & amazing is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%9s%%", &i1, &d1, suite, &c1, &e1, &E1,
      &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1, proc1);
  our_result = s21_sscanf(
      "4 42 amazing q 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab "
      "BA21 shrek & amazing is sus?",
      "%i%d%9s%c%e%E%f%g%G%o%u%x%X%p%n%9s%%", &i2, &d2, s2, &c2, &e2, &E2, &f2,
      &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2, proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = s21_sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%12i%4d%20s%c%3e%7E%1f%9g%5G%6o%12u%11x%2X%10p%n%21s%%", &i1, &d1, suite,
      &c1, &e1, &E1, &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1, proc1);
  our_result = s21_sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%12i%4d%20s%c%3e%7E%1f%9g%5G%6o%12u%11x%2X%10p%n%21s%%", &i2, &d2, s2,
      &c2, &e2, &E2, &f2, &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2, proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg((int)E1 == (int)E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 "
      "shrek & amazing is sus?",
      "%*i%12i%4d%20s%c%3e%7E%*i%1f%9g%5G%6o%12u%*x%11x%2X%10p%n%21s%%", &i1,
      &d1, suite, &c1, &e1, &E1, &f_1, &g1, &G1, &o1, &u1, &x1, &X1, &p1, &n_1,
      proc1);
  our_result = s21_sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%*i%12i%4d%20s%c%3e%7E%*i%1f%9g%5G%6o%12u%*x%11x%2X%10p%n%21s%%", &i2,
      &d2, s2, &c2, &e2, &E2, &f2, &g2, &G2, &o2, &u2, &x2, &X2, &p2, &n_2,
      proc2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(
      "4 42 amazingq 12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%*i%12hi%4hd%20s%c%3Le%7LE%*i%1f%9Lg%5LG%6lo%12lu%*x%11x%2X%10p%n%21s%%",
      &hi1, &hd1, suite, &c1, &Le1, &LE1, &f_1, &Lg1, &LG1, &lo1, &lu1, &x1,
      &X1, &p1, &n_1, proc1);
  our_result = s21_sscanf(
      "4 42 amazingq f12e21 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 shrek "
      "& amazing is sus?",
      "%*i%12hi%4hd%20s%c%3Le%7LE%*i%1f%9Lg%5LG%6lo%12lu%*x%11x%2X%10p%n%21s%%",
      &hi2, &hd2, s2, &c2, &Le2, &LE2, &f2, &Lg2, &LG2, &lo2, &lu2, &x2, &X2,
      &p2, &n_2, proc2);
  ck_assert_int_eq(hi1, hi2);
  ck_assert_int_eq(hd1, hd2);
  ck_assert_str_eq(suite, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f_1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(lo1, lo2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n_1, n_2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_c_1) {
  char *empty_str = "";
  char c1, c2;
  int orig_result, our_result;
  char *storig_result = " abc ";

  orig_result = sscanf(storig_result, "%*c%*c%c", &c1);
  our_result = s21_sscanf(storig_result, "%*c%*c%c", &c2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_int_eq(c1, c2);

  orig_result = sscanf(empty_str, "%c", &c1);
  our_result = s21_sscanf(empty_str, "%c", &c2);
  ck_assert_int_eq(orig_result, our_result);
  ck_assert_int_eq(c1, c2);

  char fstr[] = "%c %c %c %c";
  char str[] = " c    a  d b";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, z1 = 0, z2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &z1, &d1);

  int res2 = sscanf(str, fstr, &a2, &b2, &z2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(d1, d2);

  char fstr1[] = "%c%c%c%c";
  char str1[] = "cadb";
  a1 = 0, a2 = 2, b1 = 0, b2 = 2, z1 = 0, z2 = 1, d1 = 0, d2 = 3;

  res1 = s21_sscanf(str1, fstr1, &a1, &b1, &z1, &d1);

  res2 = sscanf(str1, fstr1, &a2, &b2, &z2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(d1, d2);

  char fstr3[] = "%c %c %c %c";
  char str3[] = "   0 000    ";
  a1 = 0, a2 = 2, b1 = 0, b2 = 2, z1 = 0, z2 = 1, d1 = 0, d2 = 3;

  res1 = s21_sscanf(str3, fstr3, &a1, &b1, &z1, &d1);

  res2 = sscanf(str3, fstr3, &a2, &b2, &z2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(z1, z2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_test_d_2) {
  char *empty_str = "";
  int nmb1 = 111, nmb2 = 111;
  int orig_result, our_result;
  char *stour_result = "  42   -42   567  32368  ";
  char wrong_stour_result[] = " abc 324 ";
  orig_result = sscanf(stour_result, "%*d%d%*d%*d", &nmb1);
  our_result = s21_sscanf(stour_result, "%*d%d%*d%*d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(orig_result, our_result);

  nmb1 = 1, nmb2 = 1;
  orig_result = sscanf(empty_str, "%d", &nmb1);
  our_result = s21_sscanf(empty_str, "%d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(orig_result, our_result);

  nmb1 = 0, nmb2 = 0;
  orig_result = sscanf(wrong_stour_result, "%d", &nmb1);
  our_result = s21_sscanf(wrong_stour_result, "%d", &nmb2);
  ck_assert_int_eq(nmb1, nmb2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_i_2) {
  char *empty_str = "";
  int nmbX1 = 1, nmbX2 = 1;
  int nmbO1 = 1, nmbO2 = 1;
  int nmbD1 = 1, nmbD2 = 1;
  int orig_result, our_result;
  char *str3 = "  0x3F5  0600 -4245 987";
  char *wrong_str3 = "  0000xFF5  ";

  orig_result = sscanf(str3, "%i%i%i%*i", &nmbX1, &nmbO1, &nmbD1);
  our_result = s21_sscanf(str3, "%i%i%i%*i", &nmbX2, &nmbO2, &nmbD2);
  ck_assert_int_eq(nmbX1, nmbX2);
  ck_assert_int_eq(nmbO1, nmbO2);
  ck_assert_int_eq(nmbD1, nmbD2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%i", &nmbD1);
  our_result = s21_sscanf(empty_str, "%i", &nmbD2);
  ck_assert_int_eq(nmbD1, nmbD2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str3, "%i", &nmbX1);
  our_result = s21_sscanf(wrong_str3, "%i", &nmbX2);
  ck_assert_uint_eq(nmbX1, nmbX2);
  ck_assert_int_eq(orig_result, our_result);

  unsigned int octnmb1 = 1, octnmb2 = 2;

  orig_result = sscanf(str3, "%*x%o", &octnmb1);
  our_result = s21_sscanf(str3, "%*x%o", &octnmb2);
  ck_assert_uint_eq(octnmb1, octnmb2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_u_2) {
  char *empty_str = "";
  unsigned u1 = 1, u2 = 2, orig_result, our_result;
  char *str4 = " 0    3513187186";
  char *wrong_str4 = "  Ricasso21";

  orig_result = sscanf(str4, "%*u%u", &u1);
  our_result = s21_sscanf(str4, "%*u%u", &u2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%u", &u1);
  our_result = s21_sscanf(empty_str, "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str4, "%u", &u1);
  our_result = s21_sscanf(wrong_str4, "%u", &u2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_x_2) {
  unsigned u1 = 1, u2 = 2, u3 = 3, u4 = 4, orig_result, our_result;
  char *str4 = " 4242  322662 42 42";

  orig_result = sscanf(str4, "%*x%x%X%*X", &u1, &u3);
  our_result = s21_sscanf(str4, "%*x%x%X%*X", &u2, &u4);
  ck_assert_uint_eq(u1, u2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_EeGg) {
  char *empty_str = "";
  int orig_result, our_result;
  double e1, e2, g1, g2;
  char *str6_u = "  0.08762147E+03  1446567457.024E-11 0E+02";
  char *wrong_str6 = "  Ricasso21+02";

  orig_result = sscanf(str6_u, "%lE%lG%*e", &e1, &g1);
  our_result = s21_sscanf(str6_u, "%lE%lG%*e", &e2, &g2);
  ck_assert_int_eq(e1, e2);
  ck_assert_int_eq(g1, g2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%le", &e1);
  our_result = s21_sscanf(empty_str, "%le", &e2);
  ck_assert_int_eq(e1, e2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str6, "%lg", &g1);
  our_result = s21_sscanf(wrong_str6, "%lg", &g2);
  ck_assert_int_eq(g1, g2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_s_2) {
  int orig_result, our_result;
  char str_vaorig_result[30] = "", str_vaour_result[30] = "";

  orig_result =
      sscanf(" this is random string", "%*s%*s%10s%*s", str_vaorig_result);
  our_result =
      s21_sscanf(" this is random string", "%*s%*s%10s%*s", str_vaour_result);
  ck_assert_str_eq(str_vaorig_result, str_vaour_result);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf("\0", "%10s", str_vaorig_result);
  our_result = s21_sscanf("\0", "%10s", str_vaour_result);
  ck_assert_str_eq(str_vaorig_result, str_vaour_result);
  ck_assert_int_eq(orig_result, our_result);
}

START_TEST(sscanf_test_ld) {
  char *empty_str = "";
  int orig_result, our_result;
  long nm1 = 111, nm2 = 111;
  char *str5 = "  42   -5424242   567  588  ";
  char wrong_str5[] = " abc 42 ";

  orig_result = sscanf(str5, "%*d%ld%*d%*d", &nm1);
  our_result = s21_sscanf(str5, "%*d%ld%*d%*d", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%ld", &nm1);
  our_result = s21_sscanf(empty_str, "%ld", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str5, "%ld", &nm1);
  our_result = s21_sscanf(wrong_str5, "%ld", &nm2);
  ck_assert_int_eq(nm1, nm2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_hd) {
  char *empty_str = "";
  int orig_result, our_result;
  short nh1 = 111, nh2 = 111;
  char *str6 = "  42   -5424242   567  588  ";
  char wrong_str6[] = " abc 42 ";

  orig_result = sscanf(str6, "%*d%hd%*d%*d", &nh1);
  our_result = s21_sscanf(str6, "%*d%hd%*d%*d", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%hd", &nh1);
  our_result = s21_sscanf(empty_str, "%hd", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str6, "%hd", &nh1);
  our_result = s21_sscanf(wrong_str6, "%hd", &nh2);
  ck_assert_int_eq(nh1, nh2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_lu) {
  char *empty_str = "";
  int orig_result, our_result;
  unsigned long nu1 = 111, nu2 = 111;
  char *str7 = "  42   5424242   567  588  ";
  char wrong_str7[] = " abc 42 ";

  orig_result = sscanf(str7, "%*d%lu%*d%*d", &nu1);
  our_result = s21_sscanf(str7, "%*d%lu%*d%*d", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%lu", &nu1);
  our_result = s21_sscanf(empty_str, "%lu", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str7, "%lu", &nu1);
  our_result = s21_sscanf(wrong_str7, "%lu", &nu2);
  ck_assert_int_eq(nu1, nu2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_hu) {
  char *empty_str = "";
  int orig_result, our_result;
  unsigned short nuh1 = 111, nuh2 = 111;
  char *str5 = "  42   15000   567  588  ";
  char wrong_str5[] = " abc 42 ";

  orig_result = sscanf(str5, "%*d%hu%*d%*d", &nuh1);
  our_result = s21_sscanf(str5, "%*d%hu%*d%*d", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%hu", &nuh1);
  our_result = s21_sscanf(empty_str, "%hu", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str5, "%hu", &nuh1);
  our_result = s21_sscanf(wrong_str5, "%hu", &nuh2);
  ck_assert_int_eq(nuh1, nuh2);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

START_TEST(sscanf_test_ptr) {
  char *empty_str = "";
  int orig_result, our_result;
  unsigned long p1 = 111, p2 = 111;
  unsigned long *ptorig_result = &p1;
  unsigned long *ptorig_result1 = &p1;
  unsigned long *ptour_result = &p2;
  unsigned long *ptour_result2 = &p2;
  char *str8 = "  42   5424242   0x567  588  ";
  char wrong_str8[] = " abc 42 ";

  orig_result = sscanf(str8, "%*d%p%p%*p", &ptorig_result, &ptorig_result1);
  our_result = s21_sscanf(str8, "%*d%p%p%*p", &ptour_result, &ptour_result2);
  ck_assert_ptr_eq(ptorig_result, ptour_result);
  ck_assert_ptr_eq(ptorig_result1, ptour_result2);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(empty_str, "%p", &ptorig_result);
  our_result = s21_sscanf(empty_str, "%p", &ptour_result);
  ck_assert_ptr_eq(ptorig_result, ptour_result);
  ck_assert_int_eq(orig_result, our_result);

  orig_result = sscanf(wrong_str8, "%p", &ptorig_result);
  our_result = s21_sscanf(wrong_str8, "%p", &ptour_result);
  ck_assert_ptr_eq(ptorig_result, ptour_result);
  ck_assert_int_eq(orig_result, our_result);
}
END_TEST

Suite *test_sscanf() {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc = tcase_create("s21_sscanf");

  tcase_add_test(tc, sscanf_test_e_1);
  tcase_add_test(tc, sscanf_test_EeGg);
  tcase_add_test(tc, sscanf_test_l_1);
  tcase_add_test(tc, sscanf_test_L_1);
  tcase_add_test(tc, sscanf_test_ld);
  tcase_add_test(tc, sscanf_test_hd);
  tcase_add_test(tc, sscanf_test_lu);
  tcase_add_test(tc, sscanf_test_hu);
  tcase_add_test(tc, sscanf_test_h_1);
  tcase_add_test(tc, sscanf_test_d_1);
  tcase_add_test(tc, sscanf_test_d_2);
  tcase_add_test(tc, sscanf_test_u_1);
  tcase_add_test(tc, sscanf_test_u_2);
  tcase_add_test(tc, sscanf_test_ptr);
  tcase_add_test(tc, sscanf_test_proc_1);
  tcase_add_test(tc, sscanf_test_p_1);
  tcase_add_test(tc, sscanf_test_s_1);
  tcase_add_test(tc, sscanf_test_s_2);
  tcase_add_test(tc, sscanf_test_f_1);
  tcase_add_test(tc, sscanf_test_x_1);
  tcase_add_test(tc, sscanf_test_x_2);
  tcase_add_test(tc, sscanf_test_i_1);
  tcase_add_test(tc, sscanf_test_i_2);
  tcase_add_test(tc, sscanf_test_c_1);
  tcase_add_test(tc, sscanf_test_n_1);
  tcase_add_test(tc, sscanf_test_all);

  suite_add_tcase(s, tc);
  return s;
}
