# Assignment1 Report part1
## Yusra Rayyan - 212896534

- The code for the Bresenham’s algorith is located in computer-graphics-2023-yusra\Viewer\src
inside Renderer.ccp (the algorith is under the function Renderer::DrawLine.
The code for drawing a circle in funtion Renderer::Render.


###   Bresenham’s algorith


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





### The result after drawing the circle:
![2022-11-09.jpg](https://www.dropbox.com/s/u00tk1coozsmt1o/2022-11-09.jpg?dl=0&raw=1)

### the creative part:
 - I drew a house and tried drawing a cat.
 
![cat.png](https://www.dropbox.com/s/bprg73po82ioz68/cat.png?dl=1)
![house.png](https://www.dropbox.com/s/4yu653mb51ytcth/house.png?dl=1)
 








