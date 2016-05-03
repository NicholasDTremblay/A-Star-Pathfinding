//example program that demonstrates sorting an stl::vector

#include <cmath>
#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm> //need this to use std::sort
#include <stdlib.h> //used for rand()
#include "Map.h"

using namespace std;



class WeightedPathNode
{
public:
	float x,y; //coordinates
	float fCost;
};

//function to sort pathnodes by fCost{    return (A.fCost < B.fCost);}
bool sortByF(PathNode *A, PathNode *B) 
{
   if( A->fCost < B->fCost ) return 1;

   return 0;
}

void PrintList(std::vector<WeightedPathNode *> *theList)
{
	for(int i = 0; i < theList->size(); ++i)
	{
		cout << i+1 << " - " << "X:" << (*theList)[i]->x << ", Y:" << (*theList)[i]->y << ", fCost:" << (*theList)[i]->fCost << endl;
	}
}

void main()
{
	bool same = false;
	bool Finished = false;
	bool GSAME = false;
	int Hweight = 1;
	Map* TheMap;

	Path* ThePath;

	PathNode* CurrentNode;

	PathNode* CheckNode;

	PathNode* TempNode;

	PathNode* START;
	WeightedPathNode* WSTART;

	PathNode* GOAL;
	WeightedPathNode* WGOAL;

	TheMap = new Map();

	TheMap->LoadMap("map.txt");

	ThePath = new Path();

	GOAL = new PathNode(3,3);

	START = new PathNode(14,15);
	START->gCost = 0;
	START->basecost = (*TheMap->map)[START->coords.y][START->coords.x]->tilenum;
	START->fCost = (abs(GOAL->coords.x - START->coords.x) * Hweight) + (abs(GOAL->coords.y - START->coords.y) * Hweight) + START->gCost;

	ThePath->start = START;

	ThePath->goal = GOAL;

	std::vector<WeightedPathNode *> OList;

	std::vector<PathNode *> OpenList;

	std::vector<PathNode *> ClosedList;

	OpenList.push_back(START);

	//CurrentNode = new PathNode(0,0);

	//CheckNode = new PathNode(0,0);

	do
	{
		CurrentNode = *OpenList.begin();

		OpenList.erase(OpenList.begin());
		//CHECK RIGHT
		CheckNode = new PathNode(CurrentNode->coords.x + 1 , CurrentNode->coords.y);

		if(TheMap->CanMove(CheckNode->coords))
		{
			CheckNode->basecost = (*TheMap->map)[CheckNode->coords.y][CheckNode->coords.x]->tilenum;
			CheckNode->gCost = CurrentNode->gCost + CheckNode->basecost;

			CheckNode->fCost = (abs(GOAL->coords.x - CheckNode->coords.x) * Hweight) + (abs(GOAL->coords.y - CheckNode->coords.y) * Hweight) + CheckNode->gCost;

			CheckNode->next = new PathNode(0,0);
			CheckNode->next->basecost = CurrentNode->basecost;
			CheckNode->next->coords.x = CurrentNode->coords.x;
			CheckNode->next->coords.y = CurrentNode->coords.y;
			CheckNode->next->fCost = CurrentNode->fCost;
			CheckNode->next->gCost = CurrentNode->gCost;
			CheckNode->next->next = CurrentNode->next;

			if((CheckNode->coords.x == GOAL->coords.x) && (CheckNode->coords.y == GOAL->coords.y))
			{
				Finished = true;
			}

			for(int i = 0; i < OpenList.size(); i++)
			{
				if(CheckNode->coords.x == OpenList.at(i)->coords.x)
				{
					if(CheckNode->coords.y == OpenList.at(i)->coords.y)
					{
						same = true;

						if(CheckNode->gCost < OpenList.at(i)->gCost)
						{
							OpenList.erase(OpenList.begin() + i);
							break;
						}
						else
						{
							GSAME = true;
						}
					}
				}
			}
			if(same == false)
			{
				for(int j = 0; j < ClosedList.size(); j++)
				{
					if(CheckNode->coords.x == ClosedList.at(j)->coords.x)
					{
						if(CheckNode->coords.y == ClosedList.at(j)->coords.y)
						{
							if(CheckNode->gCost < ClosedList.at(j)->gCost)
							{
								ClosedList.erase(ClosedList.begin()+j);
								break;
							}
							else
							{
								GSAME = true;
							}
						}
					}
				}	
			}
			if(GSAME == false)
			{
				OpenList.push_back(CheckNode);
			}
			same = false;
			GSAME = false;
		}

		//CHECK DOWN
		CheckNode = new PathNode(CurrentNode->coords.x , CurrentNode->coords.y + 1);

		if(TheMap->CanMove(CheckNode->coords))
		{
			CheckNode->basecost = (*TheMap->map)[CheckNode->coords.y][CheckNode->coords.x]->tilenum;
			CheckNode->gCost = CurrentNode->gCost + CheckNode->basecost;

			CheckNode->fCost = (abs(GOAL->coords.x - CheckNode->coords.x) * Hweight) + (abs(GOAL->coords.y - CheckNode->coords.y) * Hweight) + CheckNode->gCost;

			CheckNode->next = new PathNode(0,0);
			CheckNode->next->basecost = CurrentNode->basecost;
			CheckNode->next->coords.x = CurrentNode->coords.x;
			CheckNode->next->coords.y = CurrentNode->coords.y;
			CheckNode->next->fCost = CurrentNode->fCost;
			CheckNode->next->gCost = CurrentNode->gCost;
			CheckNode->next->next = CurrentNode->next;

			if((CheckNode->coords.x == GOAL->coords.x) && (CheckNode->coords.y == GOAL->coords.y))
			{
				Finished = true;
			}

  			for(int i = 0; i < OpenList.size(); i++)
			{
				if(CheckNode->coords.x == OpenList.at(i)->coords.x)
				{
					if(CheckNode->coords.y == OpenList.at(i)->coords.y)
					{
						same = true;

						if(CheckNode->gCost < OpenList.at(i)->gCost)
						{
							OpenList.erase(OpenList.begin() + i);
							break;
						}
						else
						{
							GSAME = true;
						}
					}
				}
			}
			if(same == false)
			{
				for(int j = 0; j < ClosedList.size(); j++)
				{
					if(CheckNode->coords.x == ClosedList.at(j)->coords.x)
					{
						if(CheckNode->coords.y == ClosedList.at(j)->coords.y)
						{
							if(CheckNode->gCost < ClosedList.at(j)->gCost)
							{
								ClosedList.erase(ClosedList.begin()+j);
								break;
							}
							else
							{
								GSAME = true;
							}
						}
					}
				}	
			}
			if(GSAME == false)
			{
				OpenList.push_back(CheckNode);
			}
			same = false;
			GSAME = false;
		}

		//CHECK LEFT
		CheckNode = new PathNode(CurrentNode->coords.x - 1 , CurrentNode->coords.y);

		if(TheMap->CanMove(CheckNode->coords))
		{
			CheckNode->basecost = (*TheMap->map)[CheckNode->coords.y][CheckNode->coords.x]->tilenum;
			CheckNode->gCost = CurrentNode->gCost + CheckNode->basecost;

			CheckNode->fCost = (abs(GOAL->coords.x - CheckNode->coords.x) * Hweight) + (abs(GOAL->coords.y - CheckNode->coords.y) * Hweight) + CheckNode->gCost;

			CheckNode->next = new PathNode(0,0);
			CheckNode->next->basecost = CurrentNode->basecost;
			CheckNode->next->coords.x = CurrentNode->coords.x;
			CheckNode->next->coords.y = CurrentNode->coords.y;
			CheckNode->next->fCost = CurrentNode->fCost;
			CheckNode->next->gCost = CurrentNode->gCost;
			CheckNode->next->next = CurrentNode->next;

			if((CheckNode->coords.x == GOAL->coords.x) && (CheckNode->coords.y == GOAL->coords.y))
			{
				Finished = true;
			}

			for(int i = 0; i < OpenList.size(); i++)
			{
				if(CheckNode->coords.x == OpenList.at(i)->coords.x)
				{
					if(CheckNode->coords.y == OpenList.at(i)->coords.y)
					{
						same = true;

						if(CheckNode->gCost < OpenList.at(i)->gCost)
						{
							OpenList.erase(OpenList.begin() + i);
							break;
						}
						else
						{
							GSAME = true;
						}
					}
				}
			}
			if(same == false)
			{
				for(int j = 0; j < ClosedList.size(); j++)
				{
					if(CheckNode->coords.x == ClosedList.at(j)->coords.x)
					{
						if(CheckNode->coords.y == ClosedList.at(j)->coords.y)
						{
							if(CheckNode->gCost < ClosedList.at(j)->gCost)
							{
								ClosedList.erase(ClosedList.begin()+j);
								break;
							}
							else
							{
								GSAME = true;
							}
						}
					}
				}	
			}
			if(GSAME == false)
			{
				OpenList.push_back(CheckNode);
			}
			same = false;
			GSAME = false;
		}

		//CHECK UP
		CheckNode = new PathNode(CurrentNode->coords.x , CurrentNode->coords.y - 1);

		if(TheMap->CanMove(CheckNode->coords))
		{
			CheckNode->basecost = (*TheMap->map)[CheckNode->coords.y][CheckNode->coords.x]->tilenum;
			CheckNode->gCost = CurrentNode->gCost + CheckNode->basecost;

			CheckNode->fCost = (abs(GOAL->coords.x - CheckNode->coords.x) * Hweight) + (abs(GOAL->coords.y - CheckNode->coords.y) * Hweight) + CheckNode->gCost;

			CheckNode->next = new PathNode(0,0);
			CheckNode->next->basecost = CurrentNode->basecost;
			CheckNode->next->coords.x = CurrentNode->coords.x;
			CheckNode->next->coords.y = CurrentNode->coords.y;
			CheckNode->next->fCost = CurrentNode->fCost;
			CheckNode->next->gCost = CurrentNode->gCost;
			CheckNode->next->next = CurrentNode->next;

			if((CheckNode->coords.x == GOAL->coords.x) && (CheckNode->coords.y == GOAL->coords.y))
			{
				TempNode = new PathNode(0,0);
				TempNode->basecost = CurrentNode->basecost;
				TempNode->coords.x = CurrentNode->coords.x;
				TempNode->coords.y = CurrentNode->coords.y;
				TempNode->fCost = CurrentNode->fCost;
				TempNode->gCost = CurrentNode->gCost;
				TempNode->next = CurrentNode->next;
				GOAL->next = TempNode;
				Finished = true;
			}

			for(int i = 0; i < OpenList.size(); i++)
			{
				if(CheckNode->coords.x == OpenList.at(i)->coords.x)
				{
					if(CheckNode->coords.y == OpenList.at(i)->coords.y)
					{
						same = true;

						if(CheckNode->gCost < OpenList.at(i)->gCost)
						{
							OpenList.erase(OpenList.begin() + i);
							break;
						}
						else
						{
							GSAME = true;
						}
					}
				}
			}
			if(same == false)
			{
				for(int j = 0; j < ClosedList.size(); j++)
				{
					if(CheckNode->coords.x == ClosedList.at(j)->coords.x)
					{
						if(CheckNode->coords.y == ClosedList.at(j)->coords.y)
						{
							if(CheckNode->gCost < ClosedList.at(j)->gCost)
							{
								ClosedList.erase(ClosedList.begin()+j);
								break;
							}
							else
							{
								GSAME = true;
							}
						}
					}
				}	
			}
			if(GSAME == false)
			{
				OpenList.push_back(CheckNode);
			}
			same = false;
			GSAME = false;
		}
	
		ClosedList.push_back(CurrentNode);
		std::sort(OpenList.begin(), OpenList.end(), sortByF);

	}while(Finished == false && OpenList.size() > 0);

	if(Finished == false)
	{
		cout << "No path found!";
		system("pause");
		return;
	}

	for(int i = 0; i < TheMap->rows; i++)
	{
		for(int k = 0; k < TheMap->cols; k++)
		{
			cout << (*TheMap->map)[k][i]->tilenum;
		}
		cout << endl;
	}
	cout << GOAL->coords.x << " , " << GOAL->coords.y << endl;

	CurrentNode = TempNode;
	do
	{

		cout << CurrentNode->coords.x << " , " << CurrentNode->coords.y << endl;
		CurrentNode = CurrentNode->next;

	}while((CurrentNode->coords.x != START->coords.x) || (CurrentNode->coords.y != START->coords.y));

	cout << START->coords.x << " , " << START->coords.y << endl;

	srand(1); //seed the random number generator with a known seed, just for repeatability
	/*******
	//make a few nodes and add them to the list
	for(int i = 0; i < 5; ++i)
	{
		WeightedPathNode *newNode = new WeightedPathNode();
		newNode->x = rand() % 100;
		newNode->y = rand() % 100;
		//make up a randon fcost
		newNode->fCost = newNode->x + newNode->y;

		//add it to the open list
		OList.push_back(newNode);
	}

	//print the unsorted list
	cout << "Unsorted, the list looks like:" << endl;
	PrintList(&OList);

	//sort open list, using the sortByF() function
	std::sort(OList.begin(), OList.end(), sortByF); 

	//output the results
	cout << endl << "Sorted by fCost, the list looks like:" << endl;
	PrintList(&OList);
	*******/

	_getch();

	TheMap->FreeMem();

	for(int i = OpenList.size()-1; i >= 0; i--)
	{
		delete OpenList.at(i);
	}
	OpenList.clear();

	for(int i = ClosedList.size()-1; i >= 0; i--)
	{
		delete ClosedList.at(i);
	}
	ClosedList.clear();

	delete CheckNode;
	delete CurrentNode;
	delete TempNode;
	delete TheMap;
	delete ThePath;
	delete START;
	delete GOAL;
	
}