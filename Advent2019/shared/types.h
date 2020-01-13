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