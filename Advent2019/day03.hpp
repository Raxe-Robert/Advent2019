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

void day03(string input)
{
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
		for (auto j = i; j < input.Length; ++j)
		{
			auto c = input[j];
			if (c == '\n' || c == '\r' || c == ',')
			{
				if (c == '\n')
				{
					firstLine = false;
					break;
				}

				auto dir = input[i];

				memset(amount, 0, 3);
				memcpy(amount, &input[i + 1], (size_t)j - i);

				auto val = atoi(amount);

				auto segment = &segments[segments_length];
				segments_length++;

				printf("%i, %i\n", previous.x, previous.y);

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

	printf("---------------\n\n\n");

	// Second wire
	previous = { 0, 0 };
	for (; i < input.Length; i++)
	{
		Point current = previous;
		for (auto j = i; j < input.Length; ++j)
		{
			auto c = input[j];
			if (j == input.Length - 1 || c == ',')
			{
				auto dir = input[i];

				memset(amount, 0, 3);
				memcpy(amount, &input[i + 1], (size_t)j - i);



				auto val = atoi(amount);

				auto segment0 = &segments[segments_length];

				switch (dir)
				{
					case 'L': 
						current.x = previous.x - val; 

						segment0->start = current;
						segment0->end = previous;
						break;
					case 'R': 
						current.x = previous.x + val; 

						segment0->start = previous;
						segment0->end = current;
						break;
					case 'U': 
						current.y = previous.y + val; 

						segment0->start = previous;
						segment0->end = current;
						break;
					case 'D': 
						current.y = previous.y - val; 

						segment0->start = current;
						segment0->end = previous;
						break;
				}
				//printf("\naction: %c%i\n", dir, val);
				printf("%i, %i\n", previous.x, previous.y);

				auto horizontal0 = segment0->start.x == segment0->end.x;

				// Compare against all other segments
				for (auto k = 0; k < segments_length; k++)
				{
					auto segment1 = &segments[k];
					auto horizontal1 = segment1->start.x == segment1->end.x;

					// if both horizontal
					if (horizontal0 && horizontal1)
					{
						// when not on the same x they are not overlapping
						if (segment0->start.x != segment1->start.x)
							continue;
						
						if (inRange(segment1->start.y, segment1->end.y, segment0->start.y)
							&& inRange(segment1->start.y, segment1->end.y, segment0->end.y)
							&& inRange(segment0->start.y, segment0->end.y, segment1->start.y)
							&& inRange(segment0->start.y, segment0->end.y, segment1->end.y))
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
						if (segment0->start.y != segment1->start.y)
							continue;

						if (inRange(segment1->start.x, segment1->end.x, segment0->start.x)
							&& inRange(segment1->start.x, segment1->end.x, segment0->end.x)
							&& inRange(segment0->start.x, segment0->end.x, segment1->start.x)
							&& inRange(segment0->start.x, segment0->end.x, segment1->end.x))
						{
							Point intersection;
							intersection.x = 0;
							intersection.y = 0;

							//printf("intersection b: %i\n", absolute(intersection.x) + absolute(intersection.y));
							break;
						}
					}
					else
					{
						Segment* horizontal = horizontal0 ? segment0 : segment1;
						Segment* vertical = !horizontal0 ? segment0 : segment1;

						bool xInRange = inRange(vertical->start.x, vertical->end.x, horizontal->x);
						bool yInRange = inRange(horizontal->start.y, horizontal->end.y, vertical->y);

						//if (absolute(horizontal->x) + absolute(vertical->y) == 375)
						//	printf("intersection c: %i\n", absolute(horizontal->x) + absolute(vertical->y));

						if (xInRange && yInRange)
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