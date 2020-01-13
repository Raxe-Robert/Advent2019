inline bool
Equals(const void* l, const void* r, s32 length)
{
	const uchar* L = reinterpret_cast<const uchar*>(l);
	const uchar* R = reinterpret_cast<const uchar*>(r);

	while (length >= 4)
	{
		if (*reinterpret_cast<const u32*>(L) != *reinterpret_cast<const u32*>(R))
			return false;

		L += 4;
		R += 4;
		length -= 4;
	}

	switch (length)
	{
		case 3: if (L[2] != R[2]) return false;
		case 2: if (L[1] != R[1]) return false;
		case 1: if (L[0] != R[0]) return false;
			
	}

	return true;
}