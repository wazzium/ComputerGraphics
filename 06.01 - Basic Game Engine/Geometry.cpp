#include "Geometry.h"
#include "ErrorManagement.h"
#include <iostream>
#include <fstream>

using namespace std;


/*
* Constructor 
*/
Geometry::Geometry(){
	_numVertices[BLUE_CUBE] = 36;
	_verticesData[BLUE_CUBE] = new Vertex[36];
	


	for (int i = 0; i < _numVertices[BLUE_CUBE]; i++) 
	{
			GLfloat x = 0.0;
			GLfloat y = 0.0;
			GLfloat z = 0.0;

		if (i <= 4 && i>=0) {
			_verticesData[BLUE_CUBE][i].setPosition(x, y, z - 1);
		}
		if (i <= 8 && i >= 4) {
			_verticesData[BLUE_CUBE][i].setPosition(x, y, z + 1);
		}
		if (i <= 12 && i >= 8) {
			_verticesData[BLUE_CUBE][i].setPosition(x - 1, y, z);
		}
		if (i <= 16 && i >= 12) {
			_verticesData[BLUE_CUBE][i].setPosition(x + 1, y, z);
		}
		if (i <= 20 && i >= 16) {
			_verticesData[BLUE_CUBE][i].setPosition(x, y - 1, z);
		}
		if (i <= 24 && i >= 20) {
			_verticesData[BLUE_CUBE][i].setPosition(x, y + 1, z);
		}
		if (i <= 28 && i >= 24) {
			_verticesData[BLUE_CUBE][i].setPosition(x + 1, y + 1, z + 1);
		}
		if (i <= 32 && i >= 28) {
			_verticesData[BLUE_CUBE][i].setPosition(x + 1, y, z + 1);
		}
		if (i <= 35 && i >= 32) {
			_verticesData[BLUE_CUBE][i].setPosition(x - 1, y - 1, z - 1);
		}
	}
	

}


Geometry::~Geometry(){
	
}

/*
* Load the game elements from a text file
*/
void Geometry::loadGameElements(char fileName[100]){	
	/* Text format
	<number of game elements>
	<type of game element> <vec3 position> <angle> <vec3 rotation> <vec3 scale>	
	*/
	int numGameElements=0;
	GameObject tempObject;
	glm::vec3 vector3fElements;
	ifstream file;
	file.open(fileName);

	if (file.is_open()){
		//TODO: Read the content and add it into the data structure
		file >> numGameElements;

		for (int i=0; i < numGameElements; i++) {
			 
			file >> tempObject._objectType >> tempObject._translate.x >> tempObject._translate.y >> tempObject._translate.z >>
				tempObject._angle >>
				tempObject._rotation.x >> tempObject._rotation.y >> tempObject._rotation.z >>
				tempObject._scale.x >> tempObject._scale.y >> tempObject._scale.z;
		
			_listOfObjects.push_back(tempObject);

		}
			file.close();

	}
	else{
		string message = "The file "+ string(fileName)+" doesn't exists";
		ErrorManagement::errorRunTime(message);
	}

}



/*
* Get the vertices data for an specific object
* @param objectID is the identifier of the requested object
* @return Vertex * is an array with all the vertices data
*/
Vertex * Geometry::getData(int objectID){
	return _verticesData[objectID];
}

/*
* Get the number of vertices for an specific object
* @param objectID is the identifier of the requested object
* @return int is the number of vertices
*/

int Geometry::getNumVertices(int objectID){
	return _numVertices[objectID];
}

/*
* Get the number of elements to render
*/
int Geometry::getNumGameElements() {
	return _listOfObjects.size();
}

/*
* Get the number of vertices of an specific game element
* @param objectID is the identifier of the requested object
*/
GameObject & Geometry::getGameElement(int objectID) {
	return (_listOfObjects[objectID]);
}

