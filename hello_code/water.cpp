
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransform.h>
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
	HWND myWindow = SoWin::init("Water molecule"); // pass the app name
	if (myWindow == NULL) exit(1);
	// Make a scene containing a red cone
	SoGroup *waterMolecule = new SoGroup; // water molecule
	SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
	SoGroup *oxygen = new SoGroup; // oxygen atom
	SoMaterial *redPlastic = new SoMaterial;
	SoSphere *sphere1 = new SoSphere;
	SoGroup *hydrogen1 = new SoGroup; // hydrogen atoms
	SoGroup *hydrogen2 = new SoGroup;
	SoTransform *hydrogenXform1 = new SoTransform;
	SoTransform *hydrogenXform2 = new SoTransform;
	SoMaterial *whitePlastic = new SoMaterial;
	SoSphere *sphere2 = new SoSphere;
	SoSphere *sphere3 = new SoSphere;
	// Set all field values for the oxygen atom
	redPlastic->ambientColor.setValue(1.0, 0.0, 0.0);
	redPlastic->diffuseColor.setValue(1.0, 0.0, 0.0);
	redPlastic->specularColor.setValue(0.5, 0.5, 0.5);
	redPlastic->shininess = 0.5;
	// Set all field values for the hydrogen atoms
	hydrogenXform1->scaleFactor.setValue(0.75, 0.75, 0.75);
	hydrogenXform1->translation.setValue(0.1, 1.2, 1.0);
	hydrogenXform2->translation.setValue(0.0, -3.2, 0.0);
	whitePlastic->ambientColor.setValue(1.0, 1.0, 1.0);
	whitePlastic->diffuseColor.setValue(1.0, 1.0, 1.0);
	whitePlastic->specularColor.setValue(0.5, 0.5, 0.5);
	whitePlastic->shininess = 0.5;
	// Create a hierarchy
	waterMolecule->ref();
	waterMolecule->addChild(oxygen);
	waterMolecule->addChild(hydrogen1);
	waterMolecule->addChild(hydrogen2);
	oxygen->addChild(redPlastic);
	oxygen->addChild(sphere1);
	hydrogen1->addChild(hydrogenXform1);
	hydrogen1->addChild(whitePlastic);
	hydrogen1->addChild(sphere2);
	hydrogen2->addChild(hydrogenXform2);
	hydrogen2->addChild(sphere3);
	SoWinExaminerViewer *myRenderArea = new SoWinExaminerViewer(myWindow);
	// Make myCamera see everything.
	myCamera->viewAll(waterMolecule, myRenderArea->getViewportRegion());
	// Put our scene in myRenderArea, change the title
	myRenderArea->setSceneGraph(waterMolecule);
	myRenderArea->setTitle("Water molecule");
	myRenderArea->show();
	SoWin::show(myWindow); // Display main window
	SoWin::mainLoop(); // Main Inventor event loop
	delete myRenderArea;
	waterMolecule->unref();
	return 0;
}