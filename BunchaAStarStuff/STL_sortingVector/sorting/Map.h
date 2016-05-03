//simple map class

#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#ifndef MAP_H
#define MAP_H

class Tile
{
public:
	int tilenum;
};

class Point
{
public:
	int x, y;
};

class PathNode
{
public:
	Point coords;
	int basecost;
	int gCost;
	int fCost;
	PathNode *next;

	PathNode(int gx, int gy)
	{
		coords.x = gx;
		coords.y = gy;
	}
	
	~PathNode()
	{
		delete next;
	}
};

class Path
{
public:
	PathNode *start;
	PathNode *goal;
};


class Map
{
public:
	int cols;
	int rows;

	std::vector<std::vector<Tile *>> *map; //our 2D map array

	bool LoadMap(std::string filename);
	bool CanMove(Point destination);
	~Map(void);
	Map(void);
	void FreeMem(void);
};

#endif