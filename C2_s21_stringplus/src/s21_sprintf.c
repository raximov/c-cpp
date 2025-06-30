#include "s21_string.h"

#define MAX_BUFFER 1024

// Вспомогательные функции

void reverse(char *buf, int start, int end) {
  while (start < end) {
    char temp = buf[start];
    buf[start] = buf[end];
    buf[end] = temp;
    start++;
    end--;
  }
}

int itos(long long int num, char *buf, int base, int flags) {
  int i = 0;
  int isNegative = 0;

  if (num == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return i;
  }

  if (num < 0 && base == 10) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int rem = num % base;
    buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  if (isNegative)
    buf[i++] = '-';
  else if (flags & 1)
    buf[i++] = '+';
  else if (flags & 4)
    buf[i++] = ' ';

  buf[i] = '\0';
  reverse(buf, 0, i - 1);

  return i;
}
int ftos(long double x, char *buf, int precision, int flags) {
  int i = 0;
  long long int intPart = (long long int)x;
  long double fracPart = fabsl(x - intPart);

  if (x < 0 || (flags & 1) || (flags & 4)) {
    buf[i++] = (x < 0) ? '-' : ((flags & 1) ? '+' : ' ');
  }

  if (intPart == 0) {
    buf[i++] = '0';
  } else {
    i += itos(llabs(intPart), buf + i, 10, 0);
  }

  if (precision > 0 || (flags & 8)) {
    buf[i++] = '.';
    for (int j = 0; j < precision; j++) {
      fracPart *= 10;
      int digit = (int)fracPart;
      buf[i++] = digit + '0';
      fracPart -= digit;
    }
  }

  // Округление
  if (precision > 0) {
    fracPart *= 10;
    if ((int)fracPart >= 5) {
      int j = i - 1;
      while (j >= 0 && buf[j] == '9') {
        buf[j--] = '0';
      }
      if (j >= 0) {
        if (buf[j] == '.') {
          j--;
        }
        if (j >= 0) {
          buf[j]++;
        }
      }
    }
  }

  buf[i] = '\0';
  return i;
}

int etos(long double x, char *buf, int precision, int flags, int uppercase) {
  int i = 0;
  int exp = 0;

  if (x == 0.0) {
    buf[i++] = '0';
    if (precision > 0 || (flags & 8)) {
      buf[i++] = '.';
      for (int j = 0; j < precision; j++) {
        buf[i++] = '0';
      }
    }
    buf[i++] = uppercase ? 'E' : 'e';
    buf[i++] = '+';
    buf[i++] = '0';
    buf[i++] = '0';
    buf[i] = '\0';
    return i;
  }

  if (x < 0 || (flags & 1) || (flags & 4)) {
    buf[i++] = (x < 0) ? '-' : ((flags & 1) ? '+' : ' ');
    x = fabsl(x);
  }

  while (x >= 10.0) {
    x /= 10.0;
    exp++;
  }
  while (x < 1.0 && x != 0.0) {
    x *= 10.0;
    exp--;
  }

  i += ftos(x, buf + i, precision, flags);

  buf[i++] = uppercase ? 'E' : 'e';
  buf[i++] = (exp >= 0) ? '+' : '-';
  exp = abs(exp);
  if (exp < 10) {
    buf[i++] = '0';
  }
  i += itos(exp, buf + i, 10, 0);

  buf[i] = '\0';
  return i;
}

// Основная функция s21_sprintf

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int written = 0;
  char buffer[MAX_BUFFER];

  while (*format) {
    if (*format != '%') {
      str[written++] = *format++;
      continue;
    }

    format++;

    int flags = 0;
    int width = 0;
    int precision = -1;
    int length = 0;

    // Парсинг флагов
    while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '#' || *format == '0') {
      switch (*format) {
        case '-':
          flags |= 2;
          break;
        case '+':
          flags |= 1;
          break;
        case ' ':
          flags |= 4;
          break;
        case '#':
          flags |= 8;
          break;
        case '0':
          flags |= 16;
          break;
      }
      format++;
    }

    // Парсинг ширины
    if (*format == '*') {
      width = va_arg(args, int);
      format++;
    } else {
      while (*format >= '0' && *format <= '9') {
        width = width * 10 + (*format - '0');
        format++;
      }
    }

    // Парсинг точности
    if (*format == '.') {
      format++;
      if (*format == '*') {
        precision = va_arg(args, int);
        format++;
      } else {
        precision = 0;
        while (*format >= '0' && *format <= '9') {
          precision = precision * 10 + (*format - '0');
          format++;
        }
      }
    }

    // Парсинг длины
    switch (*format) {
      case 'h':
        length = 1;
        format++;
        break;
      case 'l':
        length = 2;
        format++;
        break;
      case 'L':
        length = 3;
        format++;
        break;
    }

    // Обработка спецификаторов
    switch (*format) {
      case 'c': {
        char c = (char)va_arg(args, int);
        if (!(flags & 2) && width > 1)
          while (--width > 0) str[written++] = (flags & 16) ? '0' : ' ';
        str[written++] = c;
        if (flags & 2)
          while (--width > 0) str[written++] = ' ';
        break;
      }
      case 'd':
      case 'i': {
        long long int num;
        if (length == 1)
          num = (short)va_arg(args, int);
        else if (length == 2)
          num = va_arg(args, long int);
        else
          num = va_arg(args, int);

        int len = itos(num, buffer, 10, flags);
        int padding = (width > len) ? width - len : 0;

        if (!(flags & 2)) {
          char pad_char = (flags & 16) ? '0' : ' ';
          if ((flags & 1) || (flags & 4) || num < 0) {
            str[written++] = buffer[0];
            while (padding--) str[written++] = pad_char;
            for (int i = 1; i < len; i++) str[written++] = buffer[i];
          } else {
            while (padding--) str[written++] = pad_char;
            for (int i = 0; i < len; i++) str[written++] = buffer[i];
          }
        } else {
          for (int i = 0; i < len; i++) str[written++] = buffer[i];
          while (padding--) str[written++] = ' ';
        }
        break;
      }
      case 'f':
      case 'g':
      case 'G':
      case 'e':
      case 'E': {
        long double num =
            (length == 3) ? va_arg(args, long double) : va_arg(args, double);
        if (precision < 0) precision = 6;
        int len;
        if (*format == 'f') {
          len = ftos(num, buffer, precision, flags);
        } else if (*format == 'g' || *format == 'G') {
          int exp = 0;
          long double abs_num = fabsl(num);
          if (abs_num != 0) {
            while (abs_num >= 10.0) {
              abs_num /= 10.0;
              exp++;
            }
            while (abs_num < 1.0) {
              abs_num *= 10.0;
              exp--;
            }
          }
          if (exp < -4 || exp >= precision) {
            len = etos(num, buffer, precision - 1, flags, *format == 'G');
          } else {
            len = ftos(num, buffer, precision - (exp + 1), flags);
          }
        } else {
          len = etos(num, buffer, precision, flags, *format == 'E');
        }
        int padding = (width > len) ? width - len : 0;

        if (!(flags & 2)) {
          while (padding--) str[written++] = (flags & 16) ? '0' : ' ';
        }
        for (int i = 0; i < len; i++) str[written++] = buffer[i];
        if (flags & 2) {
          while (padding--) str[written++] = ' ';
        }
        break;
      }
      case 's': {
        char *s = va_arg(args, char *);
        int len = s21_strlen(s);
        if (precision >= 0 && precision < len) len = precision;
        int padding = (width > len) ? width - len : 0;

        if (!(flags & 2)) {
          while (padding--) str[written++] = ' ';
        }
        for (int i = 0; i < len; i++) str[written++] = s[i];
        if (flags & 2) {
          while (padding--) str[written++] = ' ';
        }
        break;
      }
      case 'u': {
        unsigned long long int num;
        if (length == 1)
          num = (unsigned short)va_arg(args, unsigned int);
        else if (length == 2)
          num = va_arg(args, unsigned long int);
        else
          num = va_arg(args, unsigned int);

        int len = itos(num, buffer, 10, flags);
        int padding = (width > len) ? width - len : 0;

        if (!(flags & 2)) {
          while (padding--) str[written++] = (flags & 16) ? '0' : ' ';
        }
        for (int i = 0; i < len; i++) str[written++] = buffer[i];
        if (flags & 2) {
          while (padding--) str[written++] = ' ';
        }
        break;
      }
      case 'x':
      case 'X': {
        unsigned long long int num;
        if (length == 1)
          num = (unsigned short)va_arg(args, unsigned int);
        else if (length == 2)
          num = va_arg(args, unsigned long int);
        else
          num = va_arg(args, unsigned int);

        int len = itos(num, buffer, 16, flags);
        if (*format == 'X') {
          for (int i = 0; i < len; i++)
            if (buffer[i] >= 'a' && buffer[i] <= 'f')
              buffer[i] = buffer[i] - 'a' + 'A';
        }

        int padding = (width > len) ? width - len : 0;
        if (flags & 8 && num != 0) {
          padding -= 2;
        }

        if (!(flags & 2)) {
          if (flags & 16) {
            if (flags & 8 && num != 0) {
              str[written++] = '0';
              str[written++] = *format;
            }
            while (padding-- > 0) str[written++] = '0';
          } else {
            while (padding-- > 0) str[written++] = ' ';
            if (flags & 8 && num != 0) {
              str[written++] = '0';
              str[written++] = *format;
            }
          }
        } else if (flags & 8 && num != 0) {
          str[written++] = '0';
          str[written++] = *format;
        }

        for (int i = 0; i < len; i++) str[written++] = buffer[i];

        if (flags & 2) {
          while (padding-- > 0) str[written++] = ' ';
        }
        break;
      }
      case 'o': {
        unsigned long long int num;
        if (length == 1)
          num = (unsigned short)va_arg(args, unsigned int);
        else if (length == 2)
          num = va_arg(args, unsigned long int);
        else
          num = va_arg(args, unsigned int);

        int len = itos(num, buffer, 8, flags);
        int padding = (width > len) ? width - len : 0;
        if (flags & 8) {
          str[written++] = '0';
          padding--;
        }

        if (!(flags & 2)) {
          while (padding--) str[written++] = (flags & 16) ? '0' : ' ';
        }
        for (int i = 0; i < len; i++) str[written++] = buffer[i];
        if (flags & 2) {
          while (padding--) str[written++] = ' ';
        }
        break;
      }
      case 'p': {
        void *ptr = va_arg(args, void *);
        if (ptr == NULL) {
          const char *null_str = "(nil)";
          int null_len = s21_strlen(null_str);
          s21_memcpy(str + written, null_str, null_len);
          written += null_len;
        } else {
          unsigned long num = (unsigned long)ptr;
          char temp[16];  // Достаточно для 64-битного указателя
          int len = 0;

          // Преобразуем указатель в шестнадцатеричную строку
          do {
            int digit = num % 16;
            temp[len++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
            num /= 16;
          } while (num > 0);

          // Добавляем префикс "0x"
          str[written++] = '0';
          str[written++] = 'x';

          // Добавляем ведущие нули до 8 символов (не считая "0x")
          while (len < 8) {
            str[written++] = '0';
            len++;
          }

          // Выводим цифры в обратном порядке
          for (int i = len - 1; i >= 0; i--) {
            str[written++] = temp[i];
          }
        }
        break;
      }
      case '%':
        str[written++] = '%';
        break;
    }
    format++;
  }

  str[written] = '\0';
  va_end(args);
  return written;
}