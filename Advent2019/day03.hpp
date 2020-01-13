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

inline bool
compareSegment(Segment* l, Segment* r)
{
	auto lHor = l->start.y == l->end.y;
	auto rHor = r->start.y == r->end.y;
	
	if (lHor && rHor)
	{
		// when not on the same x they are not overlapping
		if (l->start.x != r->start.x)
			return false;

		if (inRange(r->start.y, r->end.y, l->start.y)
			&& inRange(r->start.y, r->end.y, l->end.y)
			&& inRange(l->start.y, l->end.y, r->start.y)
			&& inRange(l->start.y, l->end.y, r->end.y))
		{
			Point intersection;
			intersection.x = 0;
			intersection.y = 0;

			printf("intersection a: %i\n", absolute(intersection.x) + absolute(intersection.y));
			return true;
		}
	}
	else if (!lHor && !rHor)
	{
		if (l->start.y != r->start.y)
			return false;

		if (inRange(r->start.x, r->end.x, l->start.x)
			&& inRange(r->start.x, r->end.x, l->end.x)
			&& inRange(l->start.x, l->end.x, r->start.x)
			&& inRange(l->start.x, l->end.x, r->end.x))
		{
			Point intersection;
			intersection.x = 0;
			intersection.y = 0;

			printf("intersection b: %i\n", absolute(intersection.x) + absolute(intersection.y));
			return true;
		}
	}
	else
	{
		Segment* hor = lHor ? l : r;
		Segment* ver = !lHor ? l : r;

		bool xInRange = inRange(hor->start.x, hor->end.x, ver->x);
		bool yInRange = inRange(ver->start.y, ver->end.y, hor->y);

		if (xInRange && yInRange)
		{
			printf("intersection c: %i\n", absolute(ver->x) + absolute(hor->y));
			return true;
		}
	}

	return false;
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

				auto* segment = &segments[segments_length];
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

				// Compare against all other segments
				for (auto k = 0; k < segments_length; k++)
					compareSegment(segment, &segments[k]);
				
				previous = current;
				i = j;
				break;
				
			}
		}
	}
	free(segments);
}