#ifndef S21_STRING
#define S21_STRING

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define s21_NULL (void *)0
typedef unsigned long s21_size_t;
#define MAX_OLEN 23
typedef struct {
  int c;
  int d;
  int i;
  int e;
  int E;
  int f;
  int g;
  int G;
  int o;
  int s;
  int u;
  int x;
  int X;
  int p;
  int n;
} specifiers;

typedef struct {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int width;
  int precision;
  int len_h;
  int len_l;
  int len_L;
  int emp;
} flags;

typedef struct {
  int flagEr;
  int stopFl;
  char *x;
  int size;
  int countStar;
  int countNumber;
  int countPoint;
} numFlags;

typedef struct {
  int c;
  int d;
  int i;
  int e;
  int E;
  int f;
  int g;
  int G;
  int o;
  int s;
  int u;
  int x;
  int X;
  int p;
  int n;
} specf_scan;
typedef struct {
  int star;
  int width;
  int len_h;
  int len_l;
  int len_L;
} flags_scan;
void *s21_memchr(const void *arr, int c, s21_size_t n);
int s21_memcmp(const void *arr, const void *arr2, s21_size_t n);
void *s21_memcpy(void *destination, const void *source, s21_size_t n);
void *s21_memset(void *destination, int c, s21_size_t n);
void *s21_strncat(char *destination, const char *source, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *destptr, const char *srcptr, s21_size_t num);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errcode);
s21_size_t s21_strlen(const char *str);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strpbrk(const char *str, const char *sym);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *orig, const char *match);
char *s21_strpbrk(const char *str, const char *sym);
char *s21_strtok(char *str, const char *del);
int s21_sprintf(char *buf, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);
/*-----------------SCAN------------------*/
char *s21_strcpy(char *dest, const char *src);
void body(const char *format, const char *src, int *result, va_list *args);
int s21_isspace(char c);
int pasrer_scan(const char *format, int *index, specf_scan *spec,
                flags_scan *fl, int *stop);
void scan_i(char **src, specf_scan *spec);
void scan_d(char **src, flags_scan *flag, va_list *args, int *count,
            int *stop_scan, int *for_n);
void scan_s(char **str, va_list *args, flags_scan *flag, int *count,
            specf_scan *s, int *stop_scan, int *skip, int *for_n);
void scan_u(char **src, flags_scan *flag, va_list *args, int *count,
            int *stop_scan, int *for_n);
void scan_s(char **str, va_list *args, flags_scan *flag, int *count,
            specf_scan *s, int *stop_scan, int *skip, int *for_n);
void scan_f(char **src, va_list *args, flags_scan *flag, int *count,
            int *stop_scan, int *for_n);
void scan_n(va_list *args, flags_scan *flag, int *stop_scan, int *for_n);
void scan_hex(char **src, flags_scan *f, va_list *args, specf_scan *spec,
              int *result, int *stop_scan, int *for_n);
void skip_space(char **src);
int is_num(char c);
void get_char(char **src, char **buf, char **temp, int *len, flags_scan *f);
void conv_ubsigned(va_list *args, char *temp, flags_scan *flag);
long long int s21_con_ch_int(const char *str);
void only_hex_o(char **src, char *buf, specf_scan *spec, int *len, int *sdvig);
long long unsigned int atoi_hex(char *str, specf_scan *spec, int *sign);
void conv_hex(flags_scan *f, va_list *args, long long unsigned int *num,
              specf_scan *spec);
int is_float(char *str);
long double atoi_f(char *str);
void convert_float(long double num, void *ptr, flags_scan *f);
int s21_ischar(char *str);
void copy_string(va_list *args, flags_scan *flag, char *t1, specf_scan *s);
void convert_int(long long int num, void *ptr, flags_scan *f);
int searchwght_sc(int *begin, const char *format, flags_scan *fl);
int searchLen_scan(int *begin, const char *format, flags_scan *fl);
void swSpecif_sc(specf_scan *spec, char ch);
int searchSpecif_sc(int *index, const char *format, specf_scan *spec);
void swflags_scan(flags_scan *fl, const char *ch, int i);
int search_nomatch(const char *str, specf_scan *spec);
void divide_16_8(char *str, long long unsigned int *num, int *i, int *powd,
                 specf_scan *spec);
void elseif_16(char *str, long long unsigned int *num, int *i, int *powd);
#endif