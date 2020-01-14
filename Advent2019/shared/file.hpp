inline string
ReadAllText(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
		return string();

	s32 size;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	auto buffer = malloc(size + 1);
	fread(buffer, 1, size, file);
	fclose(file);

	string result;
	result.VData = buffer;
	result.Data[size] = 0;
	result.Length = size;
	result.Capacity = size + 1;

	return result;
}
