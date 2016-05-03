#include "Map.h"

void Map::FreeMem()
{
	if(map != NULL)
	{
		//free memory of the 2d vector
		for(int i = 0; i < rows; ++i)
		{
			for(int x =0; x < cols; ++x)
				delete (*map)[i][x];

			(*map)[i].clear();
		}

		map->clear();
		
		rows = cols = 0;
		delete map;
		map = NULL;
	}
}

Map::Map(void)
{
	rows = cols = 0;
	map = NULL;
}

Map::~Map(void)
{
	FreeMem();
}

bool Map::LoadMap(std::string fname)
{
	std::ifstream ifile;
	ifile.open(fname.c_str());
	if(!ifile.is_open()) return false;

	if(map != NULL)
	{
		//we had a map already loaded, so free it first
		FreeMem();
	}

	ifile >> cols;
	ifile >> rows;

	//allocate our 2D array
	map = new std::vector<std::vector<Tile *> > (cols, std::vector<Tile *>(rows));

	//load the map data into the array
	for(int j = 0; j < rows; ++j)	
	{
		for(int i = 0; i < cols; ++i)
		{
			(*map)[i][j] = new Tile;
			ifile >> (*map)[i][j]->tilenum;
		}
	}
	
	ifile.close();

	return true;
}

bool Map::CanMove(Point destination)
{
	if(destination.x < 0) return false;
	if(destination.x > cols - 1) return false;

	if(destination.y < 0) return false;
	if(destination.y > rows - 1) return false;

	return true;
}