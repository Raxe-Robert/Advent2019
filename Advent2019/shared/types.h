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

constexpr s32 COMMA = 44;

#define CRASH *(int*)0=0;

#if _DEBUG
#define assert(expr) if (!(expr)) { fprintf(stderr, "FAILED assertion [" __FILE__ ":%i] " #expr "\n", __LINE__);  CRASH; }
#else
#define assert(expr)
#endif

struct string
{
	union
	{
		uchar* Data;
		u8* UData;
		char* SData;
		void* VData;
	};

	s32 Length;
	s32 Capacity;

	inline uchar& operator [] (s32 i)
	{
		assert(i >= 0);
		assert(i < this->Capacity);
		return this->Data[i];
	}
};