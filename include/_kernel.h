/* pocl/_kernel.h - OpenCL types and runtime library
   functions declarations.

   Copyright (c) 2011 Universidad Rey Juan Carlos
   
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/



/* Enable double precision. This should really only be done when
   building the run-time library; when building application code, we
   should instead check a macro to see whether the application has
   enabled this. At the moment, always enable this seems fine, since
   all our target devices will support double precision anyway.
*/
#pragma OPENCL EXTENSION cl_khr_fp64: enable



//#define __kernel __attribute__ ((noinline))
#define __global __attribute__ ((address_space(3)))
#define __local __attribute__ ((address_space(4)))
#define __constant __attribute__ ((address_space(5)))

#define global __attribute__ ((address_space(3)))
#define local __attribute__ ((address_space(4)))
#define constant __attribute__ ((address_space(5)))



typedef enum {
  CLK_LOCAL_MEM_FENCE = 0x1,
  CLK_GLOBAL_MEM_FENCE = 0x2
} cl_mem_fence_flags;



/* Data types */

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/* Ensure the data types have the right sizes */
#define _cl_static_assert(_t, _x) typedef int ai##_t[(_x) ? 1 : -1]
_cl_static_assert(char  , sizeof(char  ) == 1);
_cl_static_assert(uchar , sizeof(uchar ) == 1);
_cl_static_assert(short , sizeof(short ) == 2);
_cl_static_assert(ushort, sizeof(ushort) == 2);
_cl_static_assert(int   , sizeof(int   ) == 4);
_cl_static_assert(uint  , sizeof(uint  ) == 4);
_cl_static_assert(long  , sizeof(long  ) == 8);
_cl_static_assert(ulong , sizeof(ulong ) == 8);
_cl_static_assert(float , sizeof(float ) == 4);
_cl_static_assert(double, sizeof(double) == 8);

typedef char char2  __attribute__((ext_vector_type(2)));
typedef char char3  __attribute__((ext_vector_type(3)));
typedef char char4  __attribute__((ext_vector_type(4)));
typedef char char8  __attribute__((ext_vector_type(8)));
typedef char char16 __attribute__((ext_vector_type(16)));

typedef uchar uchar2  __attribute__((ext_vector_type(2)));
typedef uchar uchar3  __attribute__((ext_vector_type(3)));
typedef uchar uchar4  __attribute__((ext_vector_type(4)));
typedef uchar uchar8  __attribute__((ext_vector_type(8)));
typedef uchar uchar16 __attribute__((ext_vector_type(16)));

typedef short short2  __attribute__((ext_vector_type(2)));
typedef short short3  __attribute__((ext_vector_type(3)));
typedef short short4  __attribute__((ext_vector_type(4)));
typedef short short8  __attribute__((ext_vector_type(8)));
typedef short short16 __attribute__((ext_vector_type(16)));

typedef ushort ushort2  __attribute__((ext_vector_type(2)));
typedef ushort ushort3  __attribute__((ext_vector_type(3)));
typedef ushort ushort4  __attribute__((ext_vector_type(4)));
typedef ushort ushort8  __attribute__((ext_vector_type(8)));
typedef ushort ushort16 __attribute__((ext_vector_type(16)));

typedef int int2  __attribute__((ext_vector_type(2)));
typedef int int3  __attribute__((ext_vector_type(3)));
typedef int int4  __attribute__((ext_vector_type(4)));
typedef int int8  __attribute__((ext_vector_type(8)));
typedef int int16 __attribute__((ext_vector_type(16)));

typedef uint uint2  __attribute__((ext_vector_type(2)));
typedef uint uint3  __attribute__((ext_vector_type(3)));
typedef uint uint4  __attribute__((ext_vector_type(4)));
typedef uint uint8  __attribute__((ext_vector_type(8)));
typedef uint uint16 __attribute__((ext_vector_type(16)));

typedef long long2  __attribute__((ext_vector_type(2)));
typedef long long3  __attribute__((ext_vector_type(3)));
typedef long long4  __attribute__((ext_vector_type(4)));
typedef long long8  __attribute__((ext_vector_type(8)));
typedef long long16 __attribute__((ext_vector_type(16)));

typedef ulong ulong2  __attribute__((ext_vector_type(2)));
typedef ulong ulong3  __attribute__((ext_vector_type(3)));
typedef ulong ulong4  __attribute__((ext_vector_type(4)));
typedef ulong ulong8  __attribute__((ext_vector_type(8)));
typedef ulong ulong16 __attribute__((ext_vector_type(16)));

typedef float float2  __attribute__((ext_vector_type(2)));
typedef float float3  __attribute__((ext_vector_type(3)));
typedef float float4  __attribute__((ext_vector_type(4)));
typedef float float8  __attribute__((ext_vector_type(8)));
typedef float float16 __attribute__((ext_vector_type(16)));

typedef double double2  __attribute__((ext_vector_type(2)));
typedef double double3  __attribute__((ext_vector_type(3)));
typedef double double4  __attribute__((ext_vector_type(4)));
typedef double double8  __attribute__((ext_vector_type(8)));
typedef double double16 __attribute__((ext_vector_type(16)));



/* Conversion functions */

#define _CL_DECLARE_AS_TYPE(SRC, DST)                    \
  DST __attribute__ ((overloadable)) as_##DST(SRC a);

/* 1 byte */
#define _CL_DECLARE_AS_TYPE_1(DST)                  \
  _CL_DECLARE_AS_TYPE(DST, char)                    \
  _CL_DECLARE_AS_TYPE(DST, uchar)
_CL_DECLARE_AS_TYPE_1(char)
_CL_DECLARE_AS_TYPE_1(uchar)

/* 2 bytes */
#define _CL_DECLARE_AS_TYPE_2(DST)                  \
  _CL_DECLARE_AS_TYPE(DST, char2)                   \
  _CL_DECLARE_AS_TYPE(DST, uchar2)                  \
  _CL_DECLARE_AS_TYPE(DST, short)                   \
  _CL_DECLARE_AS_TYPE(DST, ushort)
_CL_DECLARE_AS_TYPE_2(char2)
_CL_DECLARE_AS_TYPE_2(uchar2)
_CL_DECLARE_AS_TYPE_2(short)
_CL_DECLARE_AS_TYPE_2(ushort)

/* 4 bytes */
#define _CL_DECLARE_AS_TYPE_4(DST)                  \
  _CL_DECLARE_AS_TYPE(DST, char4)                   \
  _CL_DECLARE_AS_TYPE(DST, uchar4)                  \
  _CL_DECLARE_AS_TYPE(DST, short2)                  \
  _CL_DECLARE_AS_TYPE(DST, ushort2)                 \
  _CL_DECLARE_AS_TYPE(DST, int)                     \
  _CL_DECLARE_AS_TYPE(DST, uint)                    \
  _CL_DECLARE_AS_TYPE(DST, float)
_CL_DECLARE_AS_TYPE_4(char4)
_CL_DECLARE_AS_TYPE_4(uchar4)
_CL_DECLARE_AS_TYPE_4(short2)
_CL_DECLARE_AS_TYPE_4(ushort2)
_CL_DECLARE_AS_TYPE_4(int)
_CL_DECLARE_AS_TYPE_4(uint)
_CL_DECLARE_AS_TYPE_4(float)

/* 8 bytes */
#define _CL_DECLARE_AS_TYPE_8(DST)                  \
  _CL_DECLARE_AS_TYPE(DST, char8)                   \
  _CL_DECLARE_AS_TYPE(DST, uchar8)                  \
  _CL_DECLARE_AS_TYPE(DST, short4)                  \
  _CL_DECLARE_AS_TYPE(DST, ushort4)                 \
  _CL_DECLARE_AS_TYPE(DST, int2)                    \
  _CL_DECLARE_AS_TYPE(DST, uint2)                   \
  _CL_DECLARE_AS_TYPE(DST, long)                    \
  _CL_DECLARE_AS_TYPE(DST, ulong)                   \
  _CL_DECLARE_AS_TYPE(DST, float2)                  \
  _CL_DECLARE_AS_TYPE(DST, double)
_CL_DECLARE_AS_TYPE_8(char8)
_CL_DECLARE_AS_TYPE_8(uchar8)
_CL_DECLARE_AS_TYPE_8(short4)
_CL_DECLARE_AS_TYPE_8(ushort4)
_CL_DECLARE_AS_TYPE_8(int2)
_CL_DECLARE_AS_TYPE_8(uint2)
_CL_DECLARE_AS_TYPE_8(long)
_CL_DECLARE_AS_TYPE_8(ulong)
_CL_DECLARE_AS_TYPE_8(float2)
_CL_DECLARE_AS_TYPE_8(double)

/* 16 bytes */
#define _CL_DECLARE_AS_TYPE_16(DST)                 \
  _CL_DECLARE_AS_TYPE(DST, char16)                  \
  _CL_DECLARE_AS_TYPE(DST, uchar16)                 \
  _CL_DECLARE_AS_TYPE(DST, short8)                  \
  _CL_DECLARE_AS_TYPE(DST, ushort8)                 \
  _CL_DECLARE_AS_TYPE(DST, int4)                    \
  _CL_DECLARE_AS_TYPE(DST, uint4)                   \
  _CL_DECLARE_AS_TYPE(DST, long2)                   \
  _CL_DECLARE_AS_TYPE(DST, ulong2)                  \
  _CL_DECLARE_AS_TYPE(DST, float4)                  \
  _CL_DECLARE_AS_TYPE(DST, double2)
_CL_DECLARE_AS_TYPE_16(char16)
_CL_DECLARE_AS_TYPE_16(uchar16)
_CL_DECLARE_AS_TYPE_16(short8)
_CL_DECLARE_AS_TYPE_16(ushort8)
_CL_DECLARE_AS_TYPE_16(int4)
_CL_DECLARE_AS_TYPE_16(uint4)
_CL_DECLARE_AS_TYPE_16(long2)
_CL_DECLARE_AS_TYPE_16(ulong2)
_CL_DECLARE_AS_TYPE_16(float4)
_CL_DECLARE_AS_TYPE_16(double2)

/* 32 bytes */
#define _CL_DECLARE_AS_TYPE_32(DST)                 \
  _CL_DECLARE_AS_TYPE(DST, short16)                 \
  _CL_DECLARE_AS_TYPE(DST, ushort16)                \
  _CL_DECLARE_AS_TYPE(DST, int8)                    \
  _CL_DECLARE_AS_TYPE(DST, uint8)                   \
  _CL_DECLARE_AS_TYPE(DST, long4)                   \
  _CL_DECLARE_AS_TYPE(DST, ulong4)                  \
  _CL_DECLARE_AS_TYPE(DST, float8)                  \
  _CL_DECLARE_AS_TYPE(DST, double4)
_CL_DECLARE_AS_TYPE_32(short16)
_CL_DECLARE_AS_TYPE_32(ushort16)
_CL_DECLARE_AS_TYPE_32(int8)
_CL_DECLARE_AS_TYPE_32(uint8)
_CL_DECLARE_AS_TYPE_32(long4)
_CL_DECLARE_AS_TYPE_32(ulong4)
_CL_DECLARE_AS_TYPE_32(float8)
_CL_DECLARE_AS_TYPE_32(double4)

/* 64 bytes */
#define _CL_DECLARE_AS_TYPE_64(DST)                 \
  _CL_DECLARE_AS_TYPE(DST, int16)                   \
  _CL_DECLARE_AS_TYPE(DST, uint16)                  \
  _CL_DECLARE_AS_TYPE(DST, long8)                   \
  _CL_DECLARE_AS_TYPE(DST, ulong8)                  \
  _CL_DECLARE_AS_TYPE(DST, float16)                 \
  _CL_DECLARE_AS_TYPE(DST, double8)
_CL_DECLARE_AS_TYPE_64(int16)
_CL_DECLARE_AS_TYPE_64(uint16)
_CL_DECLARE_AS_TYPE_64(long8)
_CL_DECLARE_AS_TYPE_64(ulong8)
_CL_DECLARE_AS_TYPE_64(float16)
_CL_DECLARE_AS_TYPE_64(double8)

/* 128 bytes */
#define _CL_DECLARE_AS_TYPE_128(DST)                \
  _CL_DECLARE_AS_TYPE(DST, long16)                  \
  _CL_DECLARE_AS_TYPE(DST, ulong16)                 \
  _CL_DECLARE_AS_TYPE(DST, double16)
_CL_DECLARE_AS_TYPE_128(long16)
_CL_DECLARE_AS_TYPE_128(ulong16)
_CL_DECLARE_AS_TYPE_128(double16)



/* Work-Item Functions */

// uint get_work_dim();
uint get_global_size(uint);     // should return size_t
uint get_global_id(uint);       // should return size_t
// size_t get_local_size(uint);
uint get_local_id(uint);        // should return size_t
uint get_num_groups(uint);      // should return size_t
uint get_group_id(uint);        // should return size_t
// size_t get_global_offset(uint);

int mad24(int x, int y, int z);

__attribute__ ((noinline)) void barrier (cl_mem_fence_flags flags);



/* Math Constants */

#define MAXFLOAT  FLT_MAX
#define HUGE_VALF __builtin_huge_valf()
#define INFINITY  (1.0f / 0.0f)
#define NAN       (0.0f / 0.0f)

#define FLT_DIG        6
#define FLT_MANT_DIG   24
#define FLT_MAX_10_EXP +38
#define FLT_MAX_EXP    +128
#define FLT_MIN_10_EXP -37
#define FLT_MIN_EXP    -125
#define FLT_RADIX      2
#define FLT_MAX        0x1.fffffep127f
#define FLT_MIN        0x1.0p-126f
#define FLT_EPSILON    0x1.0p-23f

#define M_E_F        2.71828182845904523536028747135f
#define M_LOG2E_F    1.44269504088896340735992468100f
#define M_LOG10E_F   0.434294481903251827651128918917f
#define M_LN2_F      0.693147180559945309417232121458f
#define M_LN10_F     2.30258509299404568401799145468f
#define M_PI_F       3.14159265358979323846264338328f
#define M_PI_2_F     1.57079632679489661923132169164f
#define M_PI_4_F     0.785398163397448309615660845820f
#define M_1_PI_F     0.318309886183790671537767526745f
#define M_2_PI_F     0.636619772367581343075535053490f
#define M_2_SQRTPI_F 1.12837916709551257389615890312f
#define M_SQRT2_F    1.41421356237309504880168872421f
#define M_SQRT1_2_F  0.707106781186547524400844362105f

#define HUGE_VAL __builtin_huge_val()

#define DBL_DIG        15
#define DBL_MANT_DIG   53
#define DBL_MAX_10_EXP +308
#define DBL_MAX_EXP    +1024
#define DBL_MIN_10_EXP -307
#define DBL_MIN_EXP    -1021
#define DBL_MAX        0x1.fffffffffffffp1023
#define DBL_MIN        0x1.0p-1022
#define DBL_EPSILON    0x1.0p-52

#define M_E        2.71828182845904523536028747135
#define M_LOG2E    1.44269504088896340735992468100
#define M_LOG10E   0.434294481903251827651128918917
#define M_LN2      0.693147180559945309417232121458
#define M_LN10     2.30258509299404568401799145468
#define M_PI       3.14159265358979323846264338328
#define M_PI_2     1.57079632679489661923132169164
#define M_PI_4     0.785398163397448309615660845820
#define M_1_PI     0.318309886183790671537767526745
#define M_2_PI     0.636619772367581343075535053490
#define M_2_SQRTPI 1.12837916709551257389615890312
#define M_SQRT2    1.41421356237309504880168872421
#define M_SQRT1_2  0.707106781186547524400844362105



/* Math Functions */

/* Naming scheme:
 *    [NAME]_[R]_[A]*
 * where [R] is the return type, and [A] are the argument types:
 *    I: int
 *    J: vector of int
 *    U: vector of uint or ulong
 *    S: scalar (float or double)
 *    V: vector of float or double
 */

#define _CL_DECLARE_FUNC_V_V(NAME)                              \
  float    __attribute__ ((overloadable)) NAME(float   );       \
  float2   __attribute__ ((overloadable)) NAME(float2  );       \
  float3   __attribute__ ((overloadable)) NAME(float3  );       \
  float4   __attribute__ ((overloadable)) NAME(float4  );       \
  float8   __attribute__ ((overloadable)) NAME(float8  );       \
  float16  __attribute__ ((overloadable)) NAME(float16 );       \
  double   __attribute__ ((overloadable)) NAME(double  );       \
  double2  __attribute__ ((overloadable)) NAME(double2 );       \
  double3  __attribute__ ((overloadable)) NAME(double3 );       \
  double4  __attribute__ ((overloadable)) NAME(double4 );       \
  double8  __attribute__ ((overloadable)) NAME(double8 );       \
  double16 __attribute__ ((overloadable)) NAME(double16);
#define _CL_DECLARE_FUNC_V_VV(NAME)                                     \
  float    __attribute__ ((overloadable)) NAME(float   , float   );     \
  float2   __attribute__ ((overloadable)) NAME(float2  , float2  );     \
  float3   __attribute__ ((overloadable)) NAME(float3  , float3  );     \
  float4   __attribute__ ((overloadable)) NAME(float4  , float4  );     \
  float8   __attribute__ ((overloadable)) NAME(float8  , float8  );     \
  float16  __attribute__ ((overloadable)) NAME(float16 , float16 );     \
  double   __attribute__ ((overloadable)) NAME(double  , double  );     \
  double2  __attribute__ ((overloadable)) NAME(double2 , double2 );     \
  double3  __attribute__ ((overloadable)) NAME(double3 , double3 );     \
  double4  __attribute__ ((overloadable)) NAME(double4 , double4 );     \
  double8  __attribute__ ((overloadable)) NAME(double8 , double8 );     \
  double16 __attribute__ ((overloadable)) NAME(double16, double16);
#define _CL_DECLARE_FUNC_V_VVV(NAME)                                    \
  float    __attribute__ ((overloadable)) NAME(float   , float   , float   ); \
  float2   __attribute__ ((overloadable)) NAME(float2  , float2  , float2  ); \
  float3   __attribute__ ((overloadable)) NAME(float3  , float3  , float3  ); \
  float4   __attribute__ ((overloadable)) NAME(float4  , float4  , float4  ); \
  float8   __attribute__ ((overloadable)) NAME(float8  , float8  , float8  ); \
  float16  __attribute__ ((overloadable)) NAME(float16 , float16 , float16 ); \
  double   __attribute__ ((overloadable)) NAME(double  , double  , double  ); \
  double2  __attribute__ ((overloadable)) NAME(double2 , double2 , double2 ); \
  double3  __attribute__ ((overloadable)) NAME(double3 , double3 , double3 ); \
  double4  __attribute__ ((overloadable)) NAME(double4 , double4 , double4 ); \
  double8  __attribute__ ((overloadable)) NAME(double8 , double8 , double8 ); \
  double16 __attribute__ ((overloadable)) NAME(double16, double16, double16);
#define _CL_DECLARE_FUNC_V_U(NAME)                              \
  float    __attribute__ ((overloadable)) NAME(uint   );        \
  float2   __attribute__ ((overloadable)) NAME(uint2  );        \
  float3   __attribute__ ((overloadable)) NAME(uint3  );        \
  float4   __attribute__ ((overloadable)) NAME(uint4  );        \
  float8   __attribute__ ((overloadable)) NAME(uint8  );        \
  float16  __attribute__ ((overloadable)) NAME(uint16 );        \
  double   __attribute__ ((overloadable)) NAME(ulong  );        \
  double2  __attribute__ ((overloadable)) NAME(ulong2 );        \
  double3  __attribute__ ((overloadable)) NAME(ulong3 );        \
  double4  __attribute__ ((overloadable)) NAME(ulong4 );        \
  double8  __attribute__ ((overloadable)) NAME(ulong8 );        \
  double16 __attribute__ ((overloadable)) NAME(ulong16);
#define _CL_DECLARE_FUNC_V_VS(NAME)                                     \
  float2   __attribute__ ((overloadable)) NAME(float2  , float );       \
  float3   __attribute__ ((overloadable)) NAME(float3  , float );       \
  float4   __attribute__ ((overloadable)) NAME(float4  , float );       \
  float8   __attribute__ ((overloadable)) NAME(float8  , float );       \
  float16  __attribute__ ((overloadable)) NAME(float16 , float );       \
  double2  __attribute__ ((overloadable)) NAME(double2 , double);       \
  double3  __attribute__ ((overloadable)) NAME(double3 , double);       \
  double4  __attribute__ ((overloadable)) NAME(double4 , double);       \
  double8  __attribute__ ((overloadable)) NAME(double8 , double);       \
  double16 __attribute__ ((overloadable)) NAME(double16, double);
#define _CL_DECLARE_FUNC_V_VJ(NAME)                                     \
  float    __attribute__ ((overloadable)) NAME(float   , int  );        \
  float2   __attribute__ ((overloadable)) NAME(float2  , int2 );        \
  float3   __attribute__ ((overloadable)) NAME(float3  , int3 );        \
  float4   __attribute__ ((overloadable)) NAME(float4  , int4 );        \
  float8   __attribute__ ((overloadable)) NAME(float8  , int8 );        \
  float16  __attribute__ ((overloadable)) NAME(float16 , int16);        \
  double   __attribute__ ((overloadable)) NAME(double  , int  );        \
  double2  __attribute__ ((overloadable)) NAME(double2 , int2 );        \
  double3  __attribute__ ((overloadable)) NAME(double3 , int3 );        \
  double4  __attribute__ ((overloadable)) NAME(double4 , int4 );        \
  double8  __attribute__ ((overloadable)) NAME(double8 , int8 );        \
  double16 __attribute__ ((overloadable)) NAME(double16, int16);
#define _CL_DECLARE_FUNC_V_VI(NAME)                             \
  float2   __attribute__ ((overloadable)) NAME(float2  , int);  \
  float3   __attribute__ ((overloadable)) NAME(float3  , int);  \
  float4   __attribute__ ((overloadable)) NAME(float4  , int);  \
  float8   __attribute__ ((overloadable)) NAME(float8  , int);  \
  float16  __attribute__ ((overloadable)) NAME(float16 , int);  \
  double2  __attribute__ ((overloadable)) NAME(double2 , int);  \
  double3  __attribute__ ((overloadable)) NAME(double3 , int);  \
  double4  __attribute__ ((overloadable)) NAME(double4 , int);  \
  double8  __attribute__ ((overloadable)) NAME(double8 , int);  \
  double16 __attribute__ ((overloadable)) NAME(double16, int);
#define _CL_DECLARE_FUNC_V_VPV(NAME)                                    \
  float    __attribute__ ((overloadable)) NAME(float   , __global  float   *); \
  float2   __attribute__ ((overloadable)) NAME(float2  , __global  float2  *); \
  float3   __attribute__ ((overloadable)) NAME(float3  , __global  float3  *); \
  float4   __attribute__ ((overloadable)) NAME(float4  , __global  float4  *); \
  float8   __attribute__ ((overloadable)) NAME(float8  , __global  float8  *); \
  float16  __attribute__ ((overloadable)) NAME(float16 , __global  float16 *); \
  double   __attribute__ ((overloadable)) NAME(double  , __global  double  *); \
  double2  __attribute__ ((overloadable)) NAME(double2 , __global  double2 *); \
  double3  __attribute__ ((overloadable)) NAME(double3 , __global  double3 *); \
  double4  __attribute__ ((overloadable)) NAME(double4 , __global  double4 *); \
  double8  __attribute__ ((overloadable)) NAME(double8 , __global  double8 *); \
  double16 __attribute__ ((overloadable)) NAME(double16, __global  double16*); \
  float    __attribute__ ((overloadable)) NAME(float   , __local   float   *); \
  float2   __attribute__ ((overloadable)) NAME(float2  , __local   float2  *); \
  float3   __attribute__ ((overloadable)) NAME(float3  , __local   float3  *); \
  float4   __attribute__ ((overloadable)) NAME(float4  , __local   float4  *); \
  float8   __attribute__ ((overloadable)) NAME(float8  , __local   float8  *); \
  float16  __attribute__ ((overloadable)) NAME(float16 , __local   float16 *); \
  double   __attribute__ ((overloadable)) NAME(double  , __local   double  *); \
  double2  __attribute__ ((overloadable)) NAME(double2 , __local   double2 *); \
  double3  __attribute__ ((overloadable)) NAME(double3 , __local   double3 *); \
  double4  __attribute__ ((overloadable)) NAME(double4 , __local   double4 *); \
  double8  __attribute__ ((overloadable)) NAME(double8 , __local   double8 *); \
  double16 __attribute__ ((overloadable)) NAME(double16, __local   double16*); \
  /* __private is not supported yet                                     \
  float    __attribute__ ((overloadable)) NAME(float   , __private float   *); \
  float2   __attribute__ ((overloadable)) NAME(float2  , __private float2  *); \
  float3   __attribute__ ((overloadable)) NAME(float3  , __private float3  *); \
  float4   __attribute__ ((overloadable)) NAME(float4  , __private float4  *); \
  float8   __attribute__ ((overloadable)) NAME(float8  , __private float8  *); \
  float16  __attribute__ ((overloadable)) NAME(float16 , __private float16 *); \
  double   __attribute__ ((overloadable)) NAME(double  , __private double  *); \
  double2  __attribute__ ((overloadable)) NAME(double2 , __private double2 *); \
  double3  __attribute__ ((overloadable)) NAME(double3 , __private double3 *); \
  double4  __attribute__ ((overloadable)) NAME(double4 , __private double4 *); \
  double8  __attribute__ ((overloadable)) NAME(double8 , __private double8 *); \
  double16 __attribute__ ((overloadable)) NAME(double16, __private double16*); \
  */
#define _CL_DECLARE_FUNC_V_SV(NAME)                                     \
  float2   __attribute__ ((overloadable)) NAME(float , float2  );       \
  float3   __attribute__ ((overloadable)) NAME(float , float3  );       \
  float4   __attribute__ ((overloadable)) NAME(float , float4  );       \
  float8   __attribute__ ((overloadable)) NAME(float , float8  );       \
  float16  __attribute__ ((overloadable)) NAME(float , float16 );       \
  double2  __attribute__ ((overloadable)) NAME(double, double2 );       \
  double3  __attribute__ ((overloadable)) NAME(double, double3 );       \
  double4  __attribute__ ((overloadable)) NAME(double, double4 );       \
  double8  __attribute__ ((overloadable)) NAME(double, double8 );       \
  double16 __attribute__ ((overloadable)) NAME(double, double16);
#define _CL_DECLARE_FUNC_J_V(NAME)                      \
  int   __attribute__ ((overloadable)) NAME(float   );  \
  int2  __attribute__ ((overloadable)) NAME(float2  );  \
  int3  __attribute__ ((overloadable)) NAME(float3  );  \
  int4  __attribute__ ((overloadable)) NAME(float4  );  \
  int8  __attribute__ ((overloadable)) NAME(float8  );  \
  int16 __attribute__ ((overloadable)) NAME(float16 );  \
  int   __attribute__ ((overloadable)) NAME(double  );  \
  int2  __attribute__ ((overloadable)) NAME(double2 );  \
  int3  __attribute__ ((overloadable)) NAME(double3 );  \
  int4  __attribute__ ((overloadable)) NAME(double4 );  \
  int8  __attribute__ ((overloadable)) NAME(double8 );  \
  int16 __attribute__ ((overloadable)) NAME(double16);
#define _CL_DECLARE_FUNC_S_VV(NAME)                                     \
  float  __attribute__ ((overloadable)) NAME(float   , float   );       \
  float  __attribute__ ((overloadable)) NAME(float2  , float2  );       \
  float  __attribute__ ((overloadable)) NAME(float3  , float3  );       \
  float  __attribute__ ((overloadable)) NAME(float4  , float4  );       \
  float  __attribute__ ((overloadable)) NAME(float8  , float8  );       \
  float  __attribute__ ((overloadable)) NAME(float16 , float16 );       \
  double __attribute__ ((overloadable)) NAME(double  , double  );       \
  double __attribute__ ((overloadable)) NAME(double2 , double2 );       \
  double __attribute__ ((overloadable)) NAME(double3 , double3 );       \
  double __attribute__ ((overloadable)) NAME(double4 , double4 );       \
  double __attribute__ ((overloadable)) NAME(double8 , double8 );       \
  double __attribute__ ((overloadable)) NAME(double16, double16);

/* Move built-in declarations out of the way. (There should be a
   better way of doing so.) These five functions are built-in math
   functions for all Clang languages; see Clang's "Builtin.def".
   */
#define cos _cl_cos
#define fma _cl_fma
#define pow _cl_pow
#define sin _cl_sin
#define sqrt _cl_sqrt

_CL_DECLARE_FUNC_V_V(acos)
_CL_DECLARE_FUNC_V_V(acosh)
_CL_DECLARE_FUNC_V_V(acospi)
_CL_DECLARE_FUNC_V_V(asin)
_CL_DECLARE_FUNC_V_V(asinh)
_CL_DECLARE_FUNC_V_V(asinpi)
_CL_DECLARE_FUNC_V_V(atan)
_CL_DECLARE_FUNC_V_VV(atan2)
_CL_DECLARE_FUNC_V_VV(atan2pi)
_CL_DECLARE_FUNC_V_V(atanh)
_CL_DECLARE_FUNC_V_V(atanpi)
_CL_DECLARE_FUNC_V_V(cbrt)
_CL_DECLARE_FUNC_V_V(ceil)
_CL_DECLARE_FUNC_V_VV(copysign)
_CL_DECLARE_FUNC_V_V(cos)
_CL_DECLARE_FUNC_V_V(cosh)
_CL_DECLARE_FUNC_V_V(cospi)
_CL_DECLARE_FUNC_S_VV(dot)
_CL_DECLARE_FUNC_V_V(erfc)
_CL_DECLARE_FUNC_V_V(erf)
_CL_DECLARE_FUNC_V_V(exp)
_CL_DECLARE_FUNC_V_V(exp2)
_CL_DECLARE_FUNC_V_V(exp10)
_CL_DECLARE_FUNC_V_V(expm1)
_CL_DECLARE_FUNC_V_V(fabs)
_CL_DECLARE_FUNC_V_VV(fdim)
_CL_DECLARE_FUNC_V_V(floor)
_CL_DECLARE_FUNC_V_VVV(fma)
_CL_DECLARE_FUNC_V_VV(fmax)
_CL_DECLARE_FUNC_V_VS(fmax)
_CL_DECLARE_FUNC_V_VV(fmin)
_CL_DECLARE_FUNC_V_VS(fmin)
_CL_DECLARE_FUNC_V_VV(fmod)
_CL_DECLARE_FUNC_V_VPV(fract)
// frexp
_CL_DECLARE_FUNC_V_VV(hypot)
_CL_DECLARE_FUNC_J_V(ilogb)
_CL_DECLARE_FUNC_V_VJ(ldexp)
_CL_DECLARE_FUNC_V_VI(ldexp)
_CL_DECLARE_FUNC_V_V(lgamma)
// lgamma_r
_CL_DECLARE_FUNC_V_V(log)
_CL_DECLARE_FUNC_V_V(log2)
_CL_DECLARE_FUNC_V_V(log10)
_CL_DECLARE_FUNC_V_V(log1p)
_CL_DECLARE_FUNC_V_V(logb)
_CL_DECLARE_FUNC_V_VVV(mad)
_CL_DECLARE_FUNC_V_VV(maxmag)
_CL_DECLARE_FUNC_V_VV(minmag)
// modf
_CL_DECLARE_FUNC_V_U(nan)
_CL_DECLARE_FUNC_V_VV(nextafter)
_CL_DECLARE_FUNC_V_VV(pow)
_CL_DECLARE_FUNC_V_VJ(pown)
_CL_DECLARE_FUNC_V_VI(pown)
_CL_DECLARE_FUNC_V_VV(powr)
_CL_DECLARE_FUNC_V_VV(remainder)
// remquo
_CL_DECLARE_FUNC_V_V(rint)
_CL_DECLARE_FUNC_V_VJ(rootn)
_CL_DECLARE_FUNC_V_VI(rootn)
_CL_DECLARE_FUNC_V_V(round)
_CL_DECLARE_FUNC_V_V(rsqrt)
_CL_DECLARE_FUNC_V_V(sin)
// sincos
_CL_DECLARE_FUNC_V_V(sinh)
_CL_DECLARE_FUNC_V_V(sinpi)
_CL_DECLARE_FUNC_V_V(sqrt)
_CL_DECLARE_FUNC_V_V(tan)
_CL_DECLARE_FUNC_V_V(tanh)
_CL_DECLARE_FUNC_V_V(tanpi)
_CL_DECLARE_FUNC_V_V(tgamma)
_CL_DECLARE_FUNC_V_V(trunc)



/* Integer Constants */

#define CHAR_BIT  8
#define CHAR_MAX  SCHAR_MAX
#define CHAR_MIN  SCHAR_MIN
#define INT_MAX   2147483647
#define INT_MIN   (-2147483647 - 1)
#define LONG_MAX  0x7fffffffffffffffL
#define LONG_MIN  (-0x7fffffffffffffffL - 1)
#define SCHAR_MAX 127
#define SCHAR_MIN (-127 - 1)
#define SHRT_MAX  32767
#define SHRT_MIN  (-32767 - 1)
#define UCHAR_MAX 255
#define USHRT_MAX 65535
#define UINT_MAX  0xffffffff
#define ULONG_MAX 0xffffffffffffffffUL



/* Integer Functions */

#define _CL_DECLARE_FUNC_G_G(NAME)                              \
  char     __attribute__ ((overloadable)) NAME(char    );       \
  char2    __attribute__ ((overloadable)) NAME(char2   );       \
  char3    __attribute__ ((overloadable)) NAME(char3   );       \
  char4    __attribute__ ((overloadable)) NAME(char4   );       \
  char8    __attribute__ ((overloadable)) NAME(char8   );       \
  char16   __attribute__ ((overloadable)) NAME(char16  );       \
  short    __attribute__ ((overloadable)) NAME(short   );       \
  short2   __attribute__ ((overloadable)) NAME(short2  );       \
  short3   __attribute__ ((overloadable)) NAME(short3  );       \
  short4   __attribute__ ((overloadable)) NAME(short4  );       \
  short8   __attribute__ ((overloadable)) NAME(short8  );       \
  short16  __attribute__ ((overloadable)) NAME(short16 );       \
  int      __attribute__ ((overloadable)) NAME(int     );       \
  int2     __attribute__ ((overloadable)) NAME(int2    );       \
  int3     __attribute__ ((overloadable)) NAME(int3    );       \
  int4     __attribute__ ((overloadable)) NAME(int4    );       \
  int8     __attribute__ ((overloadable)) NAME(int8    );       \
  int16    __attribute__ ((overloadable)) NAME(int16   );       \
  long     __attribute__ ((overloadable)) NAME(long    );       \
  long2    __attribute__ ((overloadable)) NAME(long2   );       \
  long3    __attribute__ ((overloadable)) NAME(long3   );       \
  long4    __attribute__ ((overloadable)) NAME(long4   );       \
  long8    __attribute__ ((overloadable)) NAME(long8   );       \
  long16   __attribute__ ((overloadable)) NAME(long16  );       \
  uchar    __attribute__ ((overloadable)) NAME(uchar   );       \
  uchar2   __attribute__ ((overloadable)) NAME(uchar2  );       \
  uchar3   __attribute__ ((overloadable)) NAME(uchar3  );       \
  uchar4   __attribute__ ((overloadable)) NAME(uchar4  );       \
  uchar8   __attribute__ ((overloadable)) NAME(uchar8  );       \
  uchar16  __attribute__ ((overloadable)) NAME(uchar16 );       \
  ushort   __attribute__ ((overloadable)) NAME(ushort  );       \
  ushort2  __attribute__ ((overloadable)) NAME(ushort2 );       \
  ushort3  __attribute__ ((overloadable)) NAME(ushort3 );       \
  ushort4  __attribute__ ((overloadable)) NAME(ushort4 );       \
  ushort8  __attribute__ ((overloadable)) NAME(ushort8 );       \
  ushort16 __attribute__ ((overloadable)) NAME(ushort16);       \
  uint     __attribute__ ((overloadable)) NAME(uint    );       \
  uint2    __attribute__ ((overloadable)) NAME(uint2   );       \
  uint3    __attribute__ ((overloadable)) NAME(uint3   );       \
  uint4    __attribute__ ((overloadable)) NAME(uint4   );       \
  uint8    __attribute__ ((overloadable)) NAME(uint8   );       \
  uint16   __attribute__ ((overloadable)) NAME(uint16  );       \
  ulong    __attribute__ ((overloadable)) NAME(ulong   );       \
  ulong2   __attribute__ ((overloadable)) NAME(ulong2  );       \
  ulong3   __attribute__ ((overloadable)) NAME(ulong3  );       \
  ulong4   __attribute__ ((overloadable)) NAME(ulong4  );       \
  ulong8   __attribute__ ((overloadable)) NAME(ulong8  );       \
  ulong16  __attribute__ ((overloadable)) NAME(ulong16 );
#define _CL_DECLARE_FUNC_G_GG(NAME)                                     \
  char     __attribute__ ((overloadable)) NAME(char    , char    );     \
  char2    __attribute__ ((overloadable)) NAME(char2   , char2   );     \
  char3    __attribute__ ((overloadable)) NAME(char3   , char3   );     \
  char4    __attribute__ ((overloadable)) NAME(char4   , char4   );     \
  char8    __attribute__ ((overloadable)) NAME(char8   , char8   );     \
  char16   __attribute__ ((overloadable)) NAME(char16  , char16  );     \
  short    __attribute__ ((overloadable)) NAME(short   , short   );     \
  short2   __attribute__ ((overloadable)) NAME(short2  , short2  );     \
  short3   __attribute__ ((overloadable)) NAME(short3  , short3  );     \
  short4   __attribute__ ((overloadable)) NAME(short4  , short4  );     \
  short8   __attribute__ ((overloadable)) NAME(short8  , short8  );     \
  short16  __attribute__ ((overloadable)) NAME(short16 , short16 );     \
  int      __attribute__ ((overloadable)) NAME(int     , int     );     \
  int2     __attribute__ ((overloadable)) NAME(int2    , int2    );     \
  int3     __attribute__ ((overloadable)) NAME(int3    , int3    );     \
  int4     __attribute__ ((overloadable)) NAME(int4    , int4    );     \
  int8     __attribute__ ((overloadable)) NAME(int8    , int8    );     \
  int16    __attribute__ ((overloadable)) NAME(int16   , int16   );     \
  long     __attribute__ ((overloadable)) NAME(long    , long    );     \
  long2    __attribute__ ((overloadable)) NAME(long2   , long2   );     \
  long3    __attribute__ ((overloadable)) NAME(long3   , long3   );     \
  long4    __attribute__ ((overloadable)) NAME(long4   , long4   );     \
  long8    __attribute__ ((overloadable)) NAME(long8   , long8   );     \
  long16   __attribute__ ((overloadable)) NAME(long16  , long16  );     \
  uchar    __attribute__ ((overloadable)) NAME(uchar   , uchar   );     \
  uchar2   __attribute__ ((overloadable)) NAME(uchar2  , uchar2  );     \
  uchar3   __attribute__ ((overloadable)) NAME(uchar3  , uchar3  );     \
  uchar4   __attribute__ ((overloadable)) NAME(uchar4  , uchar4  );     \
  uchar8   __attribute__ ((overloadable)) NAME(uchar8  , uchar8  );     \
  uchar16  __attribute__ ((overloadable)) NAME(uchar16 , uchar16 );     \
  ushort   __attribute__ ((overloadable)) NAME(ushort  , ushort  );     \
  ushort2  __attribute__ ((overloadable)) NAME(ushort2 , ushort2 );     \
  ushort3  __attribute__ ((overloadable)) NAME(ushort3 , ushort3 );     \
  ushort4  __attribute__ ((overloadable)) NAME(ushort4 , ushort4 );     \
  ushort8  __attribute__ ((overloadable)) NAME(ushort8 , ushort8 );     \
  ushort16 __attribute__ ((overloadable)) NAME(ushort16, ushort16);     \
  uint     __attribute__ ((overloadable)) NAME(uint    , uint    );     \
  uint2    __attribute__ ((overloadable)) NAME(uint2   , uint2   );     \
  uint3    __attribute__ ((overloadable)) NAME(uint3   , uint3   );     \
  uint4    __attribute__ ((overloadable)) NAME(uint4   , uint4   );     \
  uint8    __attribute__ ((overloadable)) NAME(uint8   , uint8   );     \
  uint16   __attribute__ ((overloadable)) NAME(uint16  , uint16  );     \
  ulong    __attribute__ ((overloadable)) NAME(ulong   , ulong   );     \
  ulong2   __attribute__ ((overloadable)) NAME(ulong2  , ulong2  );     \
  ulong3   __attribute__ ((overloadable)) NAME(ulong3  , ulong3  );     \
  ulong4   __attribute__ ((overloadable)) NAME(ulong4  , ulong4  );     \
  ulong8   __attribute__ ((overloadable)) NAME(ulong8  , ulong8  );     \
  ulong16  __attribute__ ((overloadable)) NAME(ulong16 , ulong16 );
#define _CL_DECLARE_FUNC_U_G(NAME)                              \
  uchar    __attribute__ ((overloadable)) NAME(char    );       \
  uchar2   __attribute__ ((overloadable)) NAME(char2   );       \
  uchar3   __attribute__ ((overloadable)) NAME(char3   );       \
  uchar4   __attribute__ ((overloadable)) NAME(char4   );       \
  uchar8   __attribute__ ((overloadable)) NAME(char8   );       \
  uchar16  __attribute__ ((overloadable)) NAME(char16  );       \
  ushort   __attribute__ ((overloadable)) NAME(short   );       \
  ushort2  __attribute__ ((overloadable)) NAME(short2  );       \
  ushort3  __attribute__ ((overloadable)) NAME(short3  );       \
  ushort4  __attribute__ ((overloadable)) NAME(short4  );       \
  ushort8  __attribute__ ((overloadable)) NAME(short8  );       \
  ushort16 __attribute__ ((overloadable)) NAME(short16 );       \
  uint     __attribute__ ((overloadable)) NAME(int     );       \
  uint2    __attribute__ ((overloadable)) NAME(int2    );       \
  uint3    __attribute__ ((overloadable)) NAME(int3    );       \
  uint4    __attribute__ ((overloadable)) NAME(int4    );       \
  uint8    __attribute__ ((overloadable)) NAME(int8    );       \
  uint16   __attribute__ ((overloadable)) NAME(int16   );       \
  ulong    __attribute__ ((overloadable)) NAME(long    );       \
  ulong2   __attribute__ ((overloadable)) NAME(long2   );       \
  ulong3   __attribute__ ((overloadable)) NAME(long3   );       \
  ulong4   __attribute__ ((overloadable)) NAME(long4   );       \
  ulong8   __attribute__ ((overloadable)) NAME(long8   );       \
  ulong16  __attribute__ ((overloadable)) NAME(long16  );       \
  uchar    __attribute__ ((overloadable)) NAME(uchar   );       \
  uchar2   __attribute__ ((overloadable)) NAME(uchar2  );       \
  uchar3   __attribute__ ((overloadable)) NAME(uchar3  );       \
  uchar4   __attribute__ ((overloadable)) NAME(uchar4  );       \
  uchar8   __attribute__ ((overloadable)) NAME(uchar8  );       \
  uchar16  __attribute__ ((overloadable)) NAME(uchar16 );       \
  ushort   __attribute__ ((overloadable)) NAME(ushort  );       \
  ushort2  __attribute__ ((overloadable)) NAME(ushort2 );       \
  ushort3  __attribute__ ((overloadable)) NAME(ushort3 );       \
  ushort4  __attribute__ ((overloadable)) NAME(ushort4 );       \
  ushort8  __attribute__ ((overloadable)) NAME(ushort8 );       \
  ushort16 __attribute__ ((overloadable)) NAME(ushort16);       \
  uint     __attribute__ ((overloadable)) NAME(uint    );       \
  uint2    __attribute__ ((overloadable)) NAME(uint2   );       \
  uint3    __attribute__ ((overloadable)) NAME(uint3   );       \
  uint4    __attribute__ ((overloadable)) NAME(uint4   );       \
  uint8    __attribute__ ((overloadable)) NAME(uint8   );       \
  uint16   __attribute__ ((overloadable)) NAME(uint16  );       \
  ulong    __attribute__ ((overloadable)) NAME(ulong   );       \
  ulong2   __attribute__ ((overloadable)) NAME(ulong2  );       \
  ulong3   __attribute__ ((overloadable)) NAME(ulong3  );       \
  ulong4   __attribute__ ((overloadable)) NAME(ulong4  );       \
  ulong8   __attribute__ ((overloadable)) NAME(ulong8  );       \
  ulong16  __attribute__ ((overloadable)) NAME(ulong16 );
#define _CL_DECLARE_FUNC_U_GG(NAME)                                     \
  uchar    __attribute__ ((overloadable)) NAME(char    , char    );     \
  uchar2   __attribute__ ((overloadable)) NAME(char2   , char2   );     \
  uchar3   __attribute__ ((overloadable)) NAME(char3   , char3   );     \
  uchar4   __attribute__ ((overloadable)) NAME(char4   , char4   );     \
  uchar8   __attribute__ ((overloadable)) NAME(char8   , char8   );     \
  uchar16  __attribute__ ((overloadable)) NAME(char16  , char16  );     \
  ushort   __attribute__ ((overloadable)) NAME(short   , short   );     \
  ushort2  __attribute__ ((overloadable)) NAME(short2  , short2  );     \
  ushort3  __attribute__ ((overloadable)) NAME(short3  , short3  );     \
  ushort4  __attribute__ ((overloadable)) NAME(short4  , short4  );     \
  ushort8  __attribute__ ((overloadable)) NAME(short8  , short8  );     \
  ushort16 __attribute__ ((overloadable)) NAME(short16 , short16 );     \
  uint     __attribute__ ((overloadable)) NAME(int     , int     );     \
  uint2    __attribute__ ((overloadable)) NAME(int2    , int2    );     \
  uint3    __attribute__ ((overloadable)) NAME(int3    , int3    );     \
  uint4    __attribute__ ((overloadable)) NAME(int4    , int4    );     \
  uint8    __attribute__ ((overloadable)) NAME(int8    , int8    );     \
  uint16   __attribute__ ((overloadable)) NAME(int16   , int16   );     \
  ulong    __attribute__ ((overloadable)) NAME(long    , long    );     \
  ulong2   __attribute__ ((overloadable)) NAME(long2   , long2   );     \
  ulong3   __attribute__ ((overloadable)) NAME(long3   , long3   );     \
  ulong4   __attribute__ ((overloadable)) NAME(long4   , long4   );     \
  ulong8   __attribute__ ((overloadable)) NAME(long8   , long8   );     \
  ulong16  __attribute__ ((overloadable)) NAME(long16  , long16  );     \
  uchar    __attribute__ ((overloadable)) NAME(uchar   , uchar   );     \
  uchar2   __attribute__ ((overloadable)) NAME(uchar2  , uchar2  );     \
  uchar3   __attribute__ ((overloadable)) NAME(uchar3  , uchar3  );     \
  uchar4   __attribute__ ((overloadable)) NAME(uchar4  , uchar4  );     \
  uchar8   __attribute__ ((overloadable)) NAME(uchar8  , uchar8  );     \
  uchar16  __attribute__ ((overloadable)) NAME(uchar16 , uchar16 );     \
  ushort   __attribute__ ((overloadable)) NAME(ushort  , ushort  );     \
  ushort2  __attribute__ ((overloadable)) NAME(ushort2 , ushort2 );     \
  ushort3  __attribute__ ((overloadable)) NAME(ushort3 , ushort3 );     \
  ushort4  __attribute__ ((overloadable)) NAME(ushort4 , ushort4 );     \
  ushort8  __attribute__ ((overloadable)) NAME(ushort8 , ushort8 );     \
  ushort16 __attribute__ ((overloadable)) NAME(ushort16, ushort16);     \
  uint     __attribute__ ((overloadable)) NAME(uint    , uint    );     \
  uint2    __attribute__ ((overloadable)) NAME(uint2   , uint2   );     \
  uint3    __attribute__ ((overloadable)) NAME(uint3   , uint3   );     \
  uint4    __attribute__ ((overloadable)) NAME(uint4   , uint4   );     \
  uint8    __attribute__ ((overloadable)) NAME(uint8   , uint8   );     \
  uint16   __attribute__ ((overloadable)) NAME(uint16  , uint16  );     \
  ulong    __attribute__ ((overloadable)) NAME(ulong   , ulong   );     \
  ulong2   __attribute__ ((overloadable)) NAME(ulong2  , ulong2  );     \
  ulong3   __attribute__ ((overloadable)) NAME(ulong3  , ulong3  );     \
  ulong4   __attribute__ ((overloadable)) NAME(ulong4  , ulong4  );     \
  ulong8   __attribute__ ((overloadable)) NAME(ulong8  , ulong8  );     \
  ulong16  __attribute__ ((overloadable)) NAME(ulong16 , ulong16 );

_CL_DECLARE_FUNC_U_G(abs)
_CL_DECLARE_FUNC_U_GG(abs_diff)
_CL_DECLARE_FUNC_G_GG(add_sat)
_CL_DECLARE_FUNC_G_GG(hadd)
