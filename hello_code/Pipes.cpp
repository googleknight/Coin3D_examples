#include<windows.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include<Inventor/nodes/SoTransform.h>
#include<Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include<Inventor\actions\SoWriteAction.h>
#include<Inventor\nodes\SoText2.h>
#include<Inventor\actions\SoGetBoundingBoxAction.h>
#include<string>
#include<CoinPipes.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
SoSeparator* makepipe(float pipeRadius, float position)
{
	SoSeparator *pipe = new SoSeparator;
	SoTransform *pipetransform = new SoTransform;
	pipetransform->translation.setValue(0, position, 0);
	SoCylinder *pipeCylinder = new SoCylinder;
	pipeCylinder->radius = pipeRadius;
	pipeCylinder->height = 10;
	pipe->addChild(pipetransform);
	pipe->addChild(pipeCylinder);
	return pipe;
}


int main(int, char ** argv)
{
	float piperadius = 2.5, yposition = 0.0;
	HWND window = SoWin::init("Oil Well");
	if (window == NULL) exit(1);
	SoWinExaminerViewer * viewer = new SoWinExaminerViewer(window);
	
	viewer->setDecoration(false);
	viewer->setSize(SbVec2s(800,600));	
	SoSeparator *root = new SoSeparator;
	root->ref();

	//Definig color
	SoMaterial *bronze = new SoMaterial;
	bronze->ambientColor.setValue(.33, .22, .27);
	bronze->diffuseColor.setValue(.78, .57, .11);
	bronze->specularColor.setValue(.99, .94, .81);
	bronze->shininess = .28;
	root->addChild(bronze);
	
	/*SbViewportRegion myViewport;
	SoGetBoundingBoxAction bboxAction(myViewport);
	bboxAction.apply(root);
	*/
	//Making pipes
	for (int index = 0; index < 6; index++)
	{
		root->addChild(makepipe(piperadius, yposition));
		piperadius -= 0.3;
		yposition-=10.1;
	}

	//Compass
	SoTransform *compassTransform = new SoTransform;
	compassTransform->translation.setValue(-20,-20,-10);
	root->addChild(compassTransform);
	root->addChild(getCompass());
	viewer->setSceneGraph(root);
	SoWriteAction myAction;
	myAction.getOutput()->openFile("myFile.iv");
	myAction.getOutput()->setBinary(FALSE);
	myAction.apply(root);
	myAction.getOutput()->closeFile();
	viewer->setTitle("Oil Well");
	viewer->show();
	SoWin::show(window);
	SoWin::mainLoop();
	delete viewer;
	root->unref();
	return 0;
}