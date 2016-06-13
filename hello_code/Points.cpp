#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include<windows.h>
#include<fstream>
#include<string>
#include<iostream>
#include<Inventor\nodes\SoPointSet.h>
#include <Inventor/Win/SoWin.h>
#include<Inventor/nodes/SoTransform.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include<CoinPipes.h>
#include<Inventor\nodes\SoSphere.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
SoSeparator* getsphere(SbVec3f position)
{
	SoSeparator *root = new SoSeparator;
	SoTransform *trans = new SoTransform;
	trans->translation.setValue(position);
	SoSphere *sphere = new SoSphere;
	
	sphere->radius.setValue(7);
	root->addChild(trans);
	root->addChild(sphere);
	return root;
}
SoSeparator *getDiag(char* filename,float &big)
{
	std::ifstream file;
	file.open(filename);
	std::string word;
	SoSeparator *diag = new SoSeparator;
	SbVec3f pointarray[2500];
	int point_index = 0, i = 0;
	float temp[3];
	while (file >> word)
	{
		float cord = std::stof(word, nullptr);
		if (cord > big) big = cord;
		if (i == 3)
		{
			pointarray[point_index] = SbVec3f(temp);
			diag->addChild(getsphere(temp));
			i = 0;
			point_index++;
		}
		temp[i++] = cord;
	}
	pointarray[point_index] = SbVec3f(temp);
	SoCoordinate3 *coord = new SoCoordinate3();
	SoPointSet *points = new SoPointSet;
	SoMaterial *color = new SoMaterial;
	SoDrawStyle *pointdraw = new SoDrawStyle;
	pointdraw->pointSize = 4;
	color->diffuseColor.setValue(0, 0, 0);
	coord->point.setValues(0, point_index, pointarray);
	points->numPoints.setValue(point_index);
	diag->addChild(pointdraw);
	diag->addChild(color);
	/*diag->addChild(coord);
	diag->addChild(points);*/
	return diag;
}
int main(int, char **argv)
{
	// Initialize Inventor. This returns a main window to use.
	// If unsuccessful, exit.
	HWND myWindow = SoWin::init("Points"); // pass the app name
	if (myWindow == NULL) exit(1);
	SoSeparator *root = new SoSeparator;
	root->ref();
	float big = 0;
	root->addChild(getDiag("coordinates.txt",big));
	root->addChild(getCompass(big+10));
	SoWinExaminerViewer *myRenderArea = new SoWinExaminerViewer(myWindow);
	myRenderArea->setBackgroundColor(SbColor(1,1,1));
	myRenderArea->setSceneGraph(root);
	myRenderArea->setTitle("Points");
	myRenderArea->show();
	SoWin::show(myWindow); // Display main window
	SoWin::mainLoop(); // Main Inventor event loop
	delete myRenderArea;
	root->unref();
	return 0;
}