# Assignment1 Report part1
## Yusra Rayyan - 212896534

- The code for the Bresenham’s algorith is located in computer-graphics-2023-yusra\Viewer\src
inside Renderer.ccp (the algorith is under the function Renderer::DrawLine.
The code for drawing a circle in funtion Renderer::Render.


###   Bresenham’s algorith

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	
	double x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	int dx = x1 - x0, dy = y1 - y0, D = 2 * dy - dx, x = x0, y = y0, yi = 1, xi = 1, m;
	if (dx == 0) m = 200; // so we wont have something undefined
	else { m = dy / dx; }; // calcutaleing the Incline
	if (m < 1 && m > -1) // the cases is -1 < Incline < 1
	{
		//plotLineLow
		if (dy < 0) {
			yi = -1;
			dy = -dy;
		}
		D = (2 * dy) - dx;
		y = y0;
		for (int x = x0; x <= x1; x++)
		{
			PutPixel(x, y, color);
			if (D > 0)
			{
				y = y + yi;
				D = D + (2 * (dy - dx));
			}
			else
				D = D + 2 * dy;
		}
		// plotLineHigh
		if (dx < 0)
		{
			xi = -1;
			dx = -dx;
		}
		D = (2 * dx) - dy;
		x = x0;
		for (int y = y0; y <= y1; y++)
		{
			PutPixel(x, y, color);
			if (D > 0)
			{
				x = x + xi;
				D = D + (2 * (dx - dy));
			}
			else
				D = D + 2 * dx;
		}
		if (dy > 0)
		{

			if (x0 > x1) //plotLineLow(x1, y1, x0, y0)
			{
				dx = x0 - x1;
				dy = y0 - y1;
				yi = 1;
				if (dy < 0) {
					yi = -1;
					dy = -dy;
				}
				D = (2 * dy) - dx;
				y = y1;
				cnt3++;
				for (int x = x1; x <= x0; x++)
				{
					PutPixel(x, y, color);
					if (D > 0)
					{
						y = y + yi;
						D = D + (2 * (dy - dx));
					}
					else
						D = D + 2 * dy;
				}
			}
			else // plotLineLow(x0, y0, x1, y1)
			{
				dx = x1 - x0;
				dy = y1 - y0;
				yi = 1;
				if (dy < 0) {
					yi = -1;
					dy = -dy;
				}
				D = (2 * dy) - dx;
				y = y0;
				for (int x = x0; x <= x1; x++)
				{
					PutPixel(x, y, color);
					if (D > 0)
					{
						y = y + yi;
						D = D + (2 * (dy - dx));
					}
					else
						D = D + 2 * dy;
				}
			}
		}
	}
	else if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1) //plotLineLow(x1, y1, x0, y0)
		{
			dx = x0 - x1;
			dy = y0 - y1;
			yi = 1;
			if (dy < 0) {
				yi = -1;
				dy = -dy;
			}
			D = (2 * dy) - dx;
			y = y1;
			cnt3++;
			for (int x = x1; x <= x0; x++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					y = y + yi;
					D = D + (2 * (dy - dx));
				}
				else
					D = D + 2 * dy;
			}
		}
		else // plotLineLow(x0, y0, x1, y1)
		{
			dx = x1 - x0;
			dy = y1 - y0;
			yi = 1;
			if (dy < 0) {
				yi = -1;
				dy = -dy;
			}
			D = (2 * dy) - dx;
			y = y0;
			for (int x = x0; x <= x1; x++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					y = y + yi;
					D = D + (2 * (dy - dx));
				}
				else
					D = D + 2 * dy;
			}
		}
	}
	else {
		if (y0 > y1) // plotLineHigh(x1, y1, x0, y0)
		{
			dx = x0 - x1;
			dy = y0 - y1;
			xi = 1;
			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			D = (2 * dx) - dy;
			x = x1;
			for (int y = y1; y <= y0; y++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					x = x + xi;
					D = D + (2 * (dx - dy));
				}
				else
					D = D + 2 * dx;
			}
		}
		else // plotLineHigh(x0, y0, x1, y1)
		{
			dx = x1 - x0;
			dy = y1 - y0;
			xi = 1;
			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			D = (2 * dx) - dy;
			x = x0;
			for (int y = y0; y <= y1; y++)
			{
				PutPixel(x, y, color);
				if (D > 0)
				{
					x = x + xi;
					D = D + (2 * (dx - dy));
				}
				else
					D = D + 2 * dx;
			}
		}
	}


	// algorethem from the enternet with some changes
	/*double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
	int dx = x2 - x1,
		dy = y2 - y1,
		p = 2 * dy - dx,
		x = x1,
		y = y1;
	while (x <= x2)
	{
		if (p >= 0)
		{
			PutPixel(x, y, color);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			PutPixel(x, y, color);
			p = p + 2 * dy;
		}
		x = x + 1;
	}*/
	
	// algorethem from the slides
	/*double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
	int x = x1, y = y1, e = -1 * (x2 - x1), dx = x2 - x1,dy = y2 - y1;
	while (x <= x2)
	{
		e = 2 * dy * x + 2 * dx * y - 1;
		if (e > 0)
		{
			y = y + 1; e = e - 2 * dx;
		}
		PutPixel(x, y, color);
		x = x + 1; e = e + 2 * dy;
	}*/

}


### The result after drawing the circle:






