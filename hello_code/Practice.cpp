
#include<windows.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include<Inventor/nodes/SoTransform.h>
#include<Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
int
main(int, char ** argv)
{

	HWND window = SoWin::init(argv[0]);
	if (window == NULL) exit(1);
	SoWinExaminerViewer * viewer = new SoWinExaminerViewer(window);
	viewer->setDecoration(false);
	// Robot with legs
		// Construct parts for legs (thigh, calf and foot)
	SoCube *thigh = new SoCube;
	thigh->width = 1.2;
	thigh->height = 2.2;
	thigh->depth = 1.1;
	SoTransform *calfTransform = new SoTransform;
	calfTransform->translation.setValue(0, 2.25, 0.0);
	SoCube *calf = new SoCube;
	calf->width = 1;
	calf->height = 2.2;
	calf->depth = 1;
	SoTransform *footTransform = new SoTransform;
	footTransform->translation.setValue(0, 2, .5);
	SoCube *foot = new SoCube;
	foot->width = 0.8;
	foot->height = 0.8;
	foot->depth = 2;
	// Put leg parts together
	SoGroup *leg = new SoGroup;
	leg->addChild(thigh);
	leg->addChild(calfTransform);
	leg->addChild(calf);
	leg->addChild(footTransform);
	leg->addChild(foot);
	SoTransform *leftTransform = new SoTransform;
	leftTransform->translation = SbVec3f(1, -4.25, 0);
	// Left leg
	SoSeparator *leftLeg = new SoSeparator;
	leftLeg->addChild(leftTransform);
	leftLeg->addChild(leg);
	SoTransform *rightTransform = new SoTransform;
	rightTransform->translation.setValue(4, -4.25, 0);
	// Right leg
	SoSeparator *rightLeg = new SoSeparator;
	rightLeg->addChild(rightTransform);
	rightLeg->addChild(leg);
	// Parts for body
	SoTransform *bodyTransform = new SoTransform;
	bodyTransform->translation.setValue(0.0, 3.0, 0.0);
	SoMaterial *bronze = new SoMaterial;
	bronze->ambientColor.setValue(.33, .22, .27);
	bronze->diffuseColor.setValue(.78, .57, .11);
	bronze->specularColor.setValue(.99, .94, .81);
	bronze->shininess = .28;
	SoCylinder *bodyCylinder = new SoCylinder;
	bodyCylinder->radius = 2.5;
	bodyCylinder->height = 6;
	// Construct body out of parts
	SoSeparator *body = new SoSeparator;
	body->addChild(bodyTransform);
	body->addChild(bronze);
	body->addChild(bodyCylinder);
	body->addChild(leftLeg);
	body->addChild(rightLeg);
	// Head parts
	SoTransform *headTransform = new SoTransform;
	headTransform->translation.setValue(0, 7.5, 0);
	headTransform->scaleFactor.setValue(1.5, 1.5, 1.5);
	SoMaterial *silver = new SoMaterial;
	silver->ambientColor.setValue(.2, .2, .2);
	silver->diffuseColor.setValue(.6, .6, .6);
	silver->specularColor.setValue(.5, .5, .5);
	silver->shininess = .5;
	SoSphere *headSphere = new SoSphere;
	// Construct head
	SoSeparator *head = new SoSeparator;
	head->addChild(headTransform);
	head->addChild(silver);
	head->addChild(headSphere);
	// Robot is just head and body
	SoSeparator *robot = new SoSeparator;
	robot->ref();
	robot->addChild(body);
	robot->addChild(head);

	viewer->setSceneGraph(robot);
	viewer->show();
	SoWin::show(window);
	SoWin::mainLoop();
	delete viewer;
	robot->unref();
	return 0;
}