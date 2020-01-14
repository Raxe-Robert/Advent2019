struct Point
{
	s32 x;
	s32 y;

	s32 steps;
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

			s32 startSteps;
		};
	};

	union
	{
		Point end;
		struct
		{
			s32 z;
			s32 w;

			s32 endSteps;
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
	
	// Both horizontal and vertical do not occur

	Segment* hor = lHor ? l : r;
	Segment* ver = !lHor ? l : r;

	bool xInRange = inRange(hor->start.x, hor->end.x, ver->x);
	bool yInRange = inRange(ver->start.y, ver->end.y, hor->y);

	if (xInRange && yInRange)
	{
		printf("Manhattan Distance: %i\n", absolute(ver->x) + absolute(hor->y));

		auto lFirst = l->start.steps < l->end.steps ? l->start : l->end;
		auto lSteps = lFirst.steps + absolute(lFirst.y - r->y);

		auto rFirst = r->start.steps < r->end.steps ? r->start : r->end;
		auto rSteps = rFirst.steps + absolute(rFirst.x - l->x);

		printf("Total steps: %i\n\n", lSteps + rSteps);

		return true;
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
	auto steps = 0;

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
				steps += val;
				current.steps = steps;

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

	printf("---------------\n");

	// Second wire
	previous = { 0, 0 };

	steps = 0;

	for (; i < input.Length; ++i)
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
				steps += val;
				current.steps = steps;

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