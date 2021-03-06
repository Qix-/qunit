/*
 * QUnit
 *   the stupidly simple (yet stunningly gorgeous) unit testing framework
 *
 * https://github.com/AERO-ff/qunit
 * Released to the Public Domain by JD Ballard
 *
 * Usage:
 *
 *   #include "qunit.h"
 *
 *   const char *some_test(void) {
 *     if (true)
 *       return 0; // success
 *     else
 *       return "there was some sort of error"; // error
 *   }
 *
 *   q_start();
 *   q_test(some_test);
 *   q_end();
 *
 * Yes, really. That simple.
 * Built for the AERO File Format for the Kleos Foundation.
 *
 * Want TAP output? (testanything.org)
 *
 *   #define QUNIT_TAP
 */
#ifndef QUNIT__
#define QUNIT__

#ifdef _WIN32
# pragma warning( disable : 4127 4710 4711 )
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# define _Q_SUC "*"
#else
# define _Q_SUC "✓"
#endif

#ifdef QUNIT_TAP
# define TAP(x) x
# define NOTAP(x)
#else
# define TAP(x)
# define NOTAP(x) x
#endif

#define q_test(_name)                                                           \
  do {                                                                          \
    extern const char * _name(void);                                            \
    const char *res = _name();                                                  \
    if (res) {                                                                  \
      NOTAP(printf("  \x1b[31m! " #_name ":\x1b[0m %s\n", res));                \
      TAP(printf("not ok %d %s\n", *count + 1, #_name));                        \
      failed = 1;                                                               \
    } else {                                                                    \
      NOTAP(printf("  \x1b[32m" _Q_SUC "\x1b[0m " #_name "\n"));                \
      TAP(printf("ok %d %s\n", *count + 1, #_name));                            \
      ++*passed;                                                                \
    }                                                                           \
    ++*count;                                                                   \
  } while(0)

#define q_start()                                                               \
  static char unused;                                                           \
  int q_do_test(int *count, int *passed) {                                      \
    int failed = 0

#define q_end()                                                                 \
    return failed;                                                              \
  }                                                                             \
                                                                                \
  int main(void) {                                                              \
    (void) unused;                                                              \
    NOTAP(printf("\n"));                                                        \
    int total = 0;                                                              \
    int passed = 0;                                                             \
    int result = q_do_test(&total, &passed);                                    \
    NOTAP(printf("\n\x1b[1m%s\x1b[0m with \x1b[1m%d/%d\x1b[0m passing "         \
        "(\x1b[1m%d%%\x1b[0m)\n\n",                                             \
        (result ? "FAILED" : "OK"),                                             \
        passed, total,                                                          \
        total ? (int)(((float)passed / (float)total) * 100.0f) : 100));         \
    TAP(printf("1..%d\n", total));                                              \
    return result;                                                              \
  }                                                                             \
                                                                                \
  static char unused = 0                                                        \

#ifndef Q_ASSERT_BUFFER_SIZE
#define Q_ASSERT_BUFFER_SIZE 4096
#endif
#ifndef Q_MAGIC
#define Q_MAGIC "\xAE\x40\xAE\x40"
#endif

#define _q_to_string(fmt1, fmt2, ...)                                           \
  char _Q__buf[Q_ASSERT_BUFFER_SIZE];                                           \
  char *_Q__second;                                                             \
  char *_Q__first;                                                              \
  sprintf(&_Q__buf[0], fmt1 Q_MAGIC fmt2, __VA_ARGS__);                         \
  _Q__second = strstr(&_Q__buf[0], Q_MAGIC);                                    \
  *_Q__second = 0;                                                              \
  _Q__second += 4;                                                              \
  _Q__first = &_Q__buf[0]

#ifdef _WIN32
# define _Q__ANSI_DIM "\x1b[30;1m"
#else
# define _Q__ANSI_DIM "\x1b[2m"
#endif

#define q_throw(fmt, ...)                                                       \
  do {                                                                          \
    char *_Q__errbuf = malloc(Q_ASSERT_BUFFER_SIZE);                            \
    sprintf(_Q__errbuf, fmt _Q__ANSI_DIM "\n\tat %s:%d\x1b[0m", __VA_ARGS__,    \
      __FILE__, __LINE__);                                                      \
    return _Q__errbuf;                                                          \
  } while (0)

#define q_assert(cond)                                                          \
  do {                                                                          \
    if (!(cond)) return ("assertion failed: " #cond);                           \
  } while (0)

#define q_assert_eq(fmt1, fmt2, ...)                                            \
  do {                                                                          \
    _q_to_string(fmt1, fmt2, __VA_ARGS__);                                      \
    if (strcmp(_Q__first, _Q__second) != 0) {                                   \
      q_throw("\x1b[31;7m%s\x1b[39;27m should equal \x1b[31;7m%s\x1b[39;27m",   \
        _Q__first, _Q__second);                                                 \
    }                                                                           \
  } while (0)

#define q_assert_not_eq(fmt1, fmt2, ...)                                        \
  do {                                                                          \
    _q_to_string(fmt1, fmt2, __VA_ARGS__);                                      \
    if (strcmp(_Q__first, _Q__second) == 0) {                                   \
      q_throw("\x1b[31;7m%s\x1b[3927m should not equal \x1b[31;7m%s\x1b[39;27m",\
        _Q__first, _Q__second);                                                 \
    }                                                                           \
  } while (0)

#endif
