// WavyPolygons.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
using namespace std;

const double M_PI = std::acos(-1.0);

class WavePolygonsApp : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserDestroy() override
	{
		return true;
	}

	bool OnUserUpdate(float elapsedTime) override
	{
		// Number of corners in the polygon
		if (GetKey(olc::Key::DOWN).bPressed)
		{
			nbPoints -= (nbPoints >= 3 ? 1 : 0);
			std::cout << "Polygonhjørner: " << nbPoints << endl;
		}
		if (GetKey(olc::Key::UP).bPressed)
		{
			nbPoints++;
			std::cout << "Polygonhjørner: " << nbPoints << endl;
		}

		// Number of polygons
		if (GetKey(olc::Key::A).bPressed)
		{
			nbForms -= (nbForms >= 2 ? 1 : 0);
			std::cout << "Polygoner: " << nbForms << endl;
		}
		if (GetKey(olc::Key::Q).bPressed)
		{
			nbForms++;
			std::cout << "Polygoner: " << nbForms << endl;
		}

		// Minimum radius
		if (GetKey(olc::Key::F).bPressed)
		{
			minRadius -= (minRadius >= 50 ? 25 : 0);
			std::cout << "Minimum radius: " << minRadius << endl;
		}
		if (GetKey(olc::Key::R).bPressed)
		{
			minRadius += 25;
			std::cout << "Minimum radius: " << minRadius << endl;
		}

		// maximum radius
		if (GetKey(olc::Key::G).bPressed)
		{
			maxRadius -= (maxRadius >= minRadius + 50 ? 25 : 0);
			std::cout << "maximum radius: " << maxRadius << endl;
		}
		if (GetKey(olc::Key::T).bPressed)
		{
			maxRadius += 25;
			std::cout << "maximum radius: " << maxRadius << endl;
		}

		// Drawing here
		Clear(olc::BLACK);

		for (int i = 1; i <= nbForms; i++)
		{
			drawPolygon(
				// x-y position
				400, 400, 
				// number of points,
				nbPoints, 
				// Radius
				linearMap(i, 0, nbForms, minRadius, maxRadius),
				// Rotation
				sinusMap(i, 0, nbForms, nWaves, -angleRotation, angleRotation),
				// Color
				olc::Pixel(
					linearMap(i, 0, nbForms, 0, 255),
					linearMap(i, 0, nbForms, 255, 0),
					linearMap(i, 0, nbForms, 64, 191)));
		}


		return !(GetKey(olc::Key::ESCAPE).bPressed);
	}

private:
	int nbForms = 5;
	int nbPoints = 5;
	double minRadius = 25;
	double maxRadius = 400;
	double angleRotation = 10*M_PI/180.0;
	int nWaves = 2;

	double linearMap(double input, double lowIn, double highIn, double lowOut, double highOut)
	{
		return ((input - lowIn) / (highIn - lowIn)) * ((highOut - lowOut)) + lowOut;
	}

	double sinusMap(double input, double lowIn, double highIn, double multiplier = 1, double lowOut = -1, double highOut = 1)
	{
		double sine = sin((input - lowIn) / (highIn - lowIn) * multiplier * 2 * M_PI);
		return linearMap(sine, -1, 1, lowOut, highOut);
	}

	void drawPolygon(double centerX, double centerY, int numPoints, double radius, double rotation = 0.0,
		olc::Pixel p = olc::WHITE)
	{
		double angle = -M_PI / 2 + rotation;
		double firstX = centerX + cos(angle) * radius;
		double firstY = centerY + sin(angle) * radius;

		double prevX = firstX;
		double prevY = firstY;


		for (int i = 1; i < numPoints; i++)
		{
			angle = -M_PI / 2 + i * 2.0 * M_PI / numPoints + rotation;

			double nextX = centerX + cos(angle) * radius;
			double nextY = centerY + sin(angle) * radius;

			DrawLine(prevX, prevY, nextX, nextY, p);

			prevX = nextX;
			prevY = nextY;
		}

		// Close shape
		DrawLine(prevX, prevY, firstX, firstY, p);

		// DrawCircle(centerX, centerY, radius, olc::DARK_GREY);
	}
};

int main()
{
	WavePolygonsApp app;
	if (app.Construct(800, 800, 1, 1, false, false))
		app.Start();
	return 0;
}