//Base types
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t b32;
typedef float r32;
typedef double r64;
typedef intptr_t intptr;
typedef uintptr_t uintptr;
typedef unsigned char uchar;

// Constants
#define PI 3.141592653589793f
#define TAU 6.283185307179586f
#define DEG2RAD 0.017453292519943295f
#define RAD2DEG 57.29577951308232f
#define EPSILON 0.00001f
#define S8MIN  -128
#define S16MIN -32768
#define S32MIN -2147483648
#define S64MIN -9223372036854775808L
#define S8MAX  127
#define S16MAX 32767
#define S32MAX 2147483647
#define S64MAX 9223372036854775807L
#define U8MAX  255
#define U16MAX 65535
#define U32MAX 4294967295U
#define U64MAX 18446744073709551615UL

constexpr s32 COMMA = 44;

struct string
{
	union
	{
		char* Data;
		u8* UData;
		void* VData;
	};

	s32 Length;
	s32 Capacity;

	inline char& operator [] (s32 i)
	{
		if (i < 0 || i > this->Capacity)
			throw std::invalid_argument("Index out of range");

		return this->Data[i];
	}
};

struct s32_array
{
	s32* Data;
	s32 Length;
	s32 Capacity;

	inline s32& operator [] (s32 i)
	{
		if (i < 0 || i > this->Length)
			throw std::invalid_argument("Index out of range");

		return this->Data[i];
	}
};