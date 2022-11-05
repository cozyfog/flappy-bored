#ifndef BASE_TYPES_H_
#define BASE_TYPES_H_

#include <stdint.h>

typedef int8_t    i8    ;
typedef int16_t   i16   ;
typedef int32_t   i32   ;
typedef int64_t   i64   ;
typedef uint8_t   ui8   ;
typedef uint16_t  u16   ;
typedef uint32_t  u32   ;
typedef uint64_t  ui64  ;
typedef i8        b8    ;
typedef i16       b16   ;
typedef float     f32   ;
typedef double    f64   ;
typedef const char *    string;
typedef void      fn    ;

#define true    1
#define false   0
#define __bool_true_false_are_defined true

#define local static

#define EXIT_SUCCESS  0
#define EXIT_FAILURE  1

typedef struct V2 V2;
typedef struct V3 V3;
typedef struct V4 V4;

struct V2
{
  f32 x;
  f32 y;
};

struct V3
{
  f32 x;
  f32 y;
  f32 z;
};

struct V4
{
  f32 x;
  f32 y;
  f32 z;
  f32 w;
};

#endif // BASE_TYPES_H_
