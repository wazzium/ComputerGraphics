#pragma once
#include "Vertex.h"
#include <vector>
#include "GameObject.h"

#define BLUE_CUBE 0
#define RED_CUBE 1
#define WHITE_CUBE 2
#define NUMBASICOBJECTS 3

//This class stores and manipulates all the objects loaded from the text file
class Geometry
{
	Vertex * _verticesData[NUMBASICOBJECTS];
	int _numVertices[NUMBASICOBJECTS];
	std::vector <GameObject> _listOfObjects;
	

public:
	Geometry();
	~Geometry();
	void loadGameElements(char fileName[100]);
	Vertex * getData(int objectID);
	int getNumVertices(int objectID);
	int getNumGameElements();
	GameObject & getGameElement(int objectID);

};

