
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include<windows.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


int main(int, char **argv)
{
	// Initialize Inventor. This returns a main window to use.
	// If unsuccessful, exit.
	HWND myWindow = SoWin::init("A red cone."); // pass the app name
	if (myWindow == NULL) exit(1);
	// Make a scene containing a red cone
	SoSeparator *root = new SoSeparator;
	SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
	SoMaterial *myMaterial = new SoMaterial;
	root->ref();
	root->addChild(myCamera);
	root->addChild(new SoDirectionalLight);
	myMaterial->diffuseColor.setValue(1.0, 1.0, 0.0); // Red
	root->addChild(myMaterial);

	root->addChild(new SoCone);
	// Create a renderArea in which to see our scene graph.
	// The render area will appear within the main window.
	SoWinExaminerViewer *myRenderArea = new SoWinExaminerViewer(myWindow);
	// Make myCamera see everything.
	myCamera->viewAll(root, myRenderArea->getViewportRegion());
	// Put our scene in myRenderArea, change the title
	myRenderArea->setSceneGraph(root);
	myRenderArea->setTitle("A red cone");
	myRenderArea->show();
	SoWin::show(myWindow); // Display main window
	SoWin::mainLoop(); // Main Inventor event loop
	delete myRenderArea;
	root->unref();
	return 0;
}