#pragma once
#include"head.h"

class Hand
{
private:
	pair<int, int> pos0;
	int length;

public:
	Hand(pair<int, int> p, int l);
	void drawHand(const tm& n);
};

class Plate
{
private:
    pair<int, int> pos0;
    int radius;

public:
	Plate(pair<int, int> p, int r);
	void drawPlate();
};