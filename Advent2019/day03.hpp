union Point
{
	struct
	{
		s32 x;
		s32 y;

		bool wire1Visited;
		bool wire2Visited;
	};
};

Point* findPoint(Point* arr, s32 arr_size, s32 x, s32 y)
{
	for (auto i = 0; i < arr_size; i++)
	{
		auto ref = &arr[i];
		if (ref->x == x && ref->y == y)
			return ref;
	}

	return 0;
}

void day03(const char* filepath)
{
	auto file = fopen(filepath, "rb");

	char direction;
	char* amount = new char[4]{ 0, 0, 0, '\0' };
	s32 amount_length = 0;
	
	int wireId = 1;
	s32 x = 0, y = 0;

	Point* points;
	points = reinterpret_cast<Point*>(malloc(sizeof(Point) * 1024 * 1024));
	memset(points, 0, sizeof(Point) * 1024 * 1024);
	s32 points_length = 0;

	while (1)
	{
		s32 c = fgetc(file);

		if (c >= 48 && c <= 57)
		{
			amount[amount_length] = (char)c;
			amount_length++;
		}
		else if (c >= 'A' && c <= 'Z')
		{
			direction = (char)c;
		}
		else if (c == COMMA || c == EOF || c == '\n')
		{
			s32 num = atoi(amount);

			s32 startX = x;
			s32 startY = y;
			
			s32 xTranslationAbs = 0;
			s32 yTranslationAbs = 0;

			switch (direction)
			{
				case 'L': 
					x -= num;
					xTranslationAbs = num;
					break;
				case 'R': 
					x += num;
					xTranslationAbs = num;
					break;
				case 'U': 
					y += num;
					yTranslationAbs = num;
					break;
				case 'D': 
					y -= num; 
					yTranslationAbs = num;
					break;
			}


			for (auto col = 0; col <= xTranslationAbs; col++)
			for (auto row = 0; row <= yTranslationAbs; row++)
			{
				auto moveX = startX;
				if (startX < x)
					moveX += col;
				else
					moveX -= col;

				auto moveY = startY;
				if (startY < y)
					moveY += row;
				else
					moveY -= row;

				auto point = findPoint(points, points_length, moveX, moveY);

				if (point != 0)
				{
					if (wireId == 1)
						point->wire1Visited = true;
					else if (wireId == 2)
						point->wire2Visited = true;
				}
				else
				{
					auto ref = &points[points_length];
					points_length++;

					ref->x = moveX;
					ref->y = moveY;

					if (wireId == 1)
						ref->wire1Visited = true;
					else if (wireId == 2)
						ref->wire2Visited = true;
				}
			}

			memset(amount, 0, amount_length);
			amount_length = 0;

			direction = 0;

			if (c == '\n')
			{
				wireId++;
				x = 0;
				y = 0;
			}

			if (c == EOF)
				break;
		}
	}

	for (auto i = 0; i < points_length; i++)
	{
		auto ref = &points[i];
		if (ref->wire1Visited && ref->wire2Visited)
		{
			s32 xBit31 = ref->x >> 31;
			s32 xAbs = (ref->x ^ xBit31) - xBit31;

			s32 yBit31 = ref->y >> 31;
			s32 yAbs = (ref->y ^ yBit31) - yBit31;

			auto distance = xAbs + yAbs;
			printf("yes, distance: %i \n", distance);
		}
	}

	delete amount;
	delete points;
}