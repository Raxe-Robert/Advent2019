s32 factorial(s32 n)
{
	for (s32 i = n - 1; i > 0; i--)
		n *= i;

	return n;
}