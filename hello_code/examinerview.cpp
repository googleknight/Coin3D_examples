
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include<windows.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>


int main(int, char **argv)
{
	// Initialize Inventor. This returns a main window to use.
	// If unsuccessful, exit.
	HWND myWindow = SoWin::init("A red cone."); // pass the app name
	if (myWindow == NULL) exit(1);
	// Make a scene containing a red cone
	SoSeparator *root = new SoSeparator;
	root->ref();
	SoMaterial *myMaterial = new SoMaterial;
	myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);
	root->addChild(myMaterial);
	root->addChild(new SoCone);
	// Set up viewer:
	SoWinExaminerViewer *myViewer =new SoWinExaminerViewer(myWindow);
	myViewer->setSceneGraph(root);
	myViewer->setTitle("Examiner Viewer");
	myViewer->show(); 
	
	SoWin::show(myWindow); // Display main window
	SoWin::mainLoop(); // Main Inventor event loop
	
	root->unref();
	return 0;
}