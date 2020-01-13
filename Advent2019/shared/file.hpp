inline char*
ReadAllText(const char* path, s32* length)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
		return NULL;

	s32 size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	auto buffer = malloc(size + 1);
	fread(buffer, 1, size, file);
	fclose(file);

	auto result = reinterpret_cast<char*>(buffer);
	result[size] = 0;
	*length = size;
	return result;
}
