struct Point
{
	s32 x;
	s32 y;
};

struct Segment
{
	union
	{
		Point start;
		struct
		{
			s32 x;
			s32 y;
		};
	};

	union
	{
		Point end;
		struct
		{
			s32 z;
			s32 w;
		};
	};
};

inline s32
absolute(s32 val)
{
	return val < 0 ? -val : val;
}

inline bool
inRange(s32 min, s32 max, s32 val)
{
	return val >= min && val <= max;
}


inline char*
ReadAllText(const char* path, s32* length)
{
	FILE* file = fopen(path, "rb");

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




void day03(const char* filepath)
{
	s32 length;
	auto text = ReadAllText(filepath, &length);

	auto segments = reinterpret_cast<Segment*>(malloc(sizeof(Segment) * 1024));
	s32 segments_length = 0;
	
	char* amount = new char[4] { 0, 0, 0, '\0' };

	Point previous { 0, 0 };

	// First wire
	auto firstLine = true;
	auto i = 0;
	for (; firstLine; ++i)
	{
		Point current = previous;
		for (auto j = i; j < length; ++j)
		{
			auto c = text[j];
			if (c == '\n' || c == '\r' || c == ',')
			{
				if (c == '\n')
				{
					firstLine = false;
					break;
				}

				auto dir = text[i];

				memset(amount, 0, 3);
				memcpy(amount, &text[i + 1], (size_t)j - i);

				auto val = atoi(amount);

				auto segment = &segments[segments_length];
				segments_length++;

				switch (dir)
				{
					case 'L': 
						current.x = previous.x - val;

						segment->start = current;
						segment->end = previous;
						break;
					case 'R': 
						current.x = previous.x + val;

						segment->start = previous;
						segment->end = current;
						break;
					case 'U': 
						current.y = previous.y + val;

						segment->start = previous;
						segment->end = current;
						break;
					case 'D': 
						current.y = previous.y - val; 

						segment->start = current;
						segment->end = previous;
						break;
				}

				previous = current;
				i = j;
				break;
			}
		}
	}

	// Second wire
	previous = { 0, 0 };
	for (; i < length; i++)
	{
		Point current = previous;
		for (auto j = i; j < length; ++j)
		{
			auto c = text[j];
			if (j == length - 1 || c == ',')
			{
				auto dir = text[i];

				memset(amount, 0, 3);
				memcpy(amount, &text[i + 1], (size_t)j - i);

				auto val = atoi(amount);

				auto segment = &segments[segments_length];

				switch (dir)
				{
					case 'L': 
						current.x = previous.x - val; 

						segment->start = current;
						segment->end = previous;
						break;
					case 'R': 
						current.x = previous.x + val; 

						segment->start = previous;
						segment->end = current;
						break;
					case 'U': 
						current.y = previous.y + val; 

						segment->start = previous;
						segment->end = current;
						break;
					case 'D': 
						current.y = previous.y - val; 

						segment->start = current;
						segment->end = previous;
						break;
				}

				auto horizontal0 = segment->start.x == segment->end.x;

				// Compare against all other segments
				for (auto k = 0; k < segments_length; k++)
				{
					auto segment1 = &segments[k];
					auto horizontal1 = segment1->start.x == segment1->end.x;

					// if both horizontal
					if (horizontal0 && horizontal1)
					{
						// when not on the same x they are not overlapping
						if (segment->start.x != segment1->start.x)
							continue;
						
						if (inRange(segment1->start.y, segment1->end.y, segment->start.y)
							&& inRange(segment1->start.y, segment1->end.y, segment->end.y)
							&& inRange(segment->start.y, segment->end.y, segment1->start.y)
							&& inRange(segment->start.y, segment->end.y, segment1->end.y))
						{
							Point intersection;
							intersection.x = 0;
							intersection.y = 0;

							printf("intersection a: %i\n", absolute(intersection.x) + absolute(intersection.y));
							break;
						}
					}
					// if both vertical
					else if (!horizontal0 && !horizontal1)
					{
						if (segment->start.y != segment1->start.y)
							continue;

						if (inRange(segment1->start.x, segment1->end.x, segment->start.x)
							&& inRange(segment1->start.x, segment1->end.x, segment->end.x)
							&& inRange(segment->start.x, segment->end.x, segment1->start.x)
							&& inRange(segment->start.x, segment->end.x, segment1->end.x))
						{
							Point intersection;
							intersection.x = 0;
							intersection.y = 0;

							printf("intersection b: %i\n", absolute(intersection.x) + absolute(intersection.y));
							break;
						}
					}
					else
					{
						Segment* horizontal = horizontal0 ? segment : segment1;
						Segment* vertical = !horizontal0 ? segment : segment1;

						bool bool1 = inRange(vertical->start.x, vertical->end.x, horizontal->x);
						bool bool2 = inRange(horizontal->start.y, horizontal->end.y, vertical->y);

						if (absolute(horizontal->x) + absolute(vertical->y) == 375)
							printf("intersection c: %i\n", absolute(horizontal->x) + absolute(vertical->y));

						if (bool1 && bool2)
						{
							printf("intersection c: %i\n", absolute(horizontal->x) + absolute(vertical->y));
							break;
						}
					}
				}

				previous = current;
				i = j;
				break;
			}
		}
	}
	free(segments);
}