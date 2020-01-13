inline string
String()
{
	string result;
	result.Length = 0;
	result.Data = reinterpret_cast<uchar*>(malloc(8));
	result.Data[0] = '\0';
	result.Capacity = 8;

	return result;
}

inline string
String(const char* s)
{
	assert(s);

	string result;
	result.Length = strlen(s);
	result.Capacity = result.Length + 1;
	result.Data = reinterpret_cast<uchar*>(malloc(result.Capacity));
	memcpy(result.Data, s, result.Capacity);

	return result;
}

inline string
String(const char* s, s32 length)
{
	assert(s);

	string result;
	result.Length = length;
	result.Capacity = result.Length + 1;
	result.Data = reinterpret_cast<uchar*>(malloc(result.Capacity));
	memcpy(result.Data, s, result.Length);
	result.Data[result.Length] = 0;
	
	return result;
}

inline bool
Equals(string l, string r)
{
	return l.Length == r.Length 
		&& Equals(l.Data, r.Data, r.Length);
}

