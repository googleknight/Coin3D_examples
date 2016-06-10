#include<windows.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include<Inventor/nodes/SoTransform.h>
#include<Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoLineSet.h>
#include<Inventor\nodes\SoNormal.h>
#include<Inventor\nodes\SoFaceSet.h>
#include<Inventor\nodes\SoCoordinate3.h>


#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//Definig color
static float vertices[28][3] =
{
	{ 0, 30, 0 },{ 2,27, 2 },{ 2,27, 2 }, //front tri
	{ 0, 30, 0 },{ 2,27,2 },{ 2,27, 2 }, //left tri
	{ 0, 30, 0 },{ 2,27,2 },{ 2,27,2 }, //rear tri
	{ 0, 30, 0 },{ 2,27, 2 },{ 2,27,2 }, //right tri
	{ 2, 27, 2 },{ 4,0, 4 },{ 4,0, 4 },{ 2,27, 2 }, //front quad
	{ 2, 27,2 },{ 4,0,4 },{ 4,0, 4 },{ 2,27, 2 }, //left quad
	{ 2, 27,2 },{ 4,0,4 },{ 4,0,4 },{ 2,27,2 }, //rear quad
	{ 2, 27, 2 },{ 4,0, 4 },{ 4,0,4 },{ 2,27,2 } //right quad
};
// Number of vertices in each polygon:
static int32_t numvertices[8] = { 3, 3, 3, 3, 4, 4, 4, 4 };
// Normals for each polygon:
static float norms[8][3] =
{
	{ 0, .555, .832 },{ .832, .555, 0 }, //front, left tris
	{ 0, .555, .832 },{ .832, .555, 0 }, //rear, right tris
	{ 0, .0739, .9973 },{ .9972, .0739, 0 },//front, left quads
	{ 0, .0739, .9973 },{ .9972, .0739, 0 },//rear, right quads
};


int main(int, char ** argv)
{
	
	HWND window = SoWin::init("Oil Well");
	if (window == NULL) exit(1);
	SoWinExaminerViewer * viewer = new SoWinExaminerViewer(window);
	viewer->setDecoration(false);
	viewer->setSize(SbVec2s(800, 600));
	SoSeparator *root = new SoSeparator;
	root->ref();
	SoSeparator *obelisk = new SoSeparator();

	// Define the normals used:
	SoNormal *myNormals = new SoNormal;
	myNormals->vector.setValues(0, 8, norms);
	obelisk->addChild(myNormals);
	SoNormalBinding *myNormalBinding = new SoNormalBinding;
	myNormalBinding->value = SoNormalBinding::PER_FACE;
	obelisk->addChild(myNormalBinding);
	// Define material for obelisk
	SoMaterial *myMaterial = new SoMaterial;
	myMaterial->diffuseColor.setValue(.4, .4, .4);
	obelisk->addChild(myMaterial);
	// Define coordinates for vertices
	SoCoordinate3 *myCoords = new SoCoordinate3;
	myCoords->point.setValues(0, 28, vertices);
	obelisk->addChild(myCoords);
	// Define the FaceSet
	SoFaceSet *myFaceSet = new SoFaceSet;
	myFaceSet->numVertices.setValues(0, 8, numvertices);
	obelisk->addChild(myFaceSet);

	root->addChild(obelisk);

	viewer->setSceneGraph(root);
	viewer->setTitle("Oil Well");
	viewer->show();
	SoWin::show(window);
	SoWin::mainLoop();
	delete viewer;
	root->unref();
	return 0;
}
