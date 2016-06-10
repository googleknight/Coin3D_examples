
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include<windows.h>
#include <Inventor/Win/SoWin.h>
#include<Inventor/nodes/SoTransform.h>
#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include<Inventor/nodes/SoLineSet.h>
#include<Inventor\nodes\SoText2.h>
#include <Inventor/nodes/SoDrawStyle.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#define X_MIN 0
#define X_MAX 50
#define Y_MIN 0
#define Y_MAX 50
#define Z_MIN 0
#define Z_MAX 50
#define STEP 10
//#include<CoinPipes.h>
SoSeparator* drawLines(SbVec3f *verLine,int totalpoints, SbColor color, char *txt, float width, SbVec3f verLabel)
{
	SoSeparator *step = new SoSeparator;
	SoCoordinate3 *coord = new SoCoordinate3();
	SoLineSet *line = new SoLineSet();
	//label
	SoText2 *label = new SoText2;
	label->string.setValue(txt);
	SoTransform *labelTransform = new SoTransform;
	labelTransform->translation.setValue(verLabel);
	//color
	SoMaterial *linecolor = new SoMaterial;
	linecolor->diffuseColor.setValue(color);
	step->addChild(linecolor);
	//line properties
	SoDrawStyle *linePro = new SoDrawStyle;
	linePro->lineWidth = width;

	//line
	coord->point.setValues(0, totalpoints, verLine);
	line->numVertices.set1Value(0, totalpoints);
	step->addChild(linePro);
	step->addChild(coord);
	step->addChild(line);
	step->addChild(labelTransform);
	step->addChild(label);
	return step;
}
void drawSteps(SoSeparator* root, SbColor colorbig, SbColor colorsmall, int x, int y, int z)
{
	unsigned int scale = (X_MAX - X_MIN) / STEP;
	SbVec3f ver[2];
	char text[10];
	//Major axis
	for (int i = 0; i <= STEP; i++)
	{
		ver[0] = SbVec3f(x == 1 ? i*scale: z==1? 0 : 1.7, y==1? i*scale: 1.7, z==1? i*scale:0);
		ver[1] = SbVec3f(x == 1 ? i*scale : z == 1 ? 0 : -1.7, y == 1 ? i*scale : -1.7, z == 1 ? i*scale : 0);
		root->addChild(drawLines(ver, 2,colorbig, itoa(i*scale,text,10), 2.2, SbVec3f(x == 1 ? i*scale : z == 1 ? 0 : -2.7, y == 1 ? i*scale : -2.2, z == 1 ? i*scale : 0)));
	}
	//Minor axis
	for (int i = 0; i <X_MAX; i++)
	{
		ver[0] = SbVec3f(x == 1 ? i : z == 1 ? 0 : 1, y == 1 ? i : 1, z == 1 ? i : 0);
		ver[1] = SbVec3f(x == 1 ? i : z == 1 ? 0 : -1, y == 1 ? i : -1, z == 1 ? i : 0);
		root->addChild(drawLines(ver, 2,colorsmall, " ", 1.8, SbVec3f(0,0,0)));
	}
}
int main(int, char **argv)
{
	// Initialize Inventor. This returns a main window to use.
	// If unsuccessful, exit.
	HWND myWindow = SoWin::init("Axis"); // pass the app name
	if (myWindow == NULL) exit(1);

	//root nodes 
	SoSeparator *root = new SoSeparator;

	float color[3] = { 1,0,0 };
	//Y- axis co-ordinates
	 SbVec3f yvert[2] = { SbVec3f(0,Y_MAX,0),SbVec3f(0,0,0) };
	//X- axis co-ordinate
	 SbVec3f xvert[2] = { SbVec3f(X_MAX,0,0),SbVec3f(0,0,0) };
	//Z- axis co-ordinate
	 SbVec3f zvert[2] = { SbVec3f(0,0,Z_MAX),SbVec3f(0,0,0) };
	//X-Y axis co-ordinate
	 SbVec3f xyvert[3] = { SbVec3f(0,Y_MAX,0),SbVec3f(X_MAX,Y_MAX,0),SbVec3f(X_MAX,0,0) };

	root->ref();
	root->addChild(drawLines(xvert,2, SbColor(1,0,0), "X-axis", 4.0, SbVec3f(X_MAX/2,-5,0)));
	root->addChild(drawLines(yvert, 2,SbColor(0, 1,0), "Y-axis", 4.0,SbVec3f(-15, Y_MAX/2, 0)));
	root->addChild(drawLines(zvert,2, SbColor(0, 0, 1), "Z-axis", 4.0,SbVec3f(0, -5, Z_MAX/2)));
	root->addChild(drawLines(xyvert, 3,SbColor(0, 1, 1), "", 2.0, SbVec3f(0, 0,0)));
	//steps
	drawSteps(root, SbColor(0,0,1), SbColor(0, 1,0),1, 0, 0);
	drawSteps(root, SbColor(1,0,0), SbColor(0, 0, 1),0, 1, 0);
	drawSteps(root, SbColor(1,0,0), SbColor(1, 0, 1),0, 0, 1);
	SoWinExaminerViewer *myRenderArea = new SoWinExaminerViewer(myWindow);
	SbColor backColor;
	backColor.setValue(1.0, 1.0, 1.0);
	myRenderArea->setBackgroundColor(backColor);
	myRenderArea->setSceneGraph(root);
	myRenderArea->setTitle("Axis");
	myRenderArea->show();
	SoWin::show(myWindow); // Display main window
	SoWin::mainLoop(); // Main Inventor event loop
	delete myRenderArea;
	root->unref();
	return 0;
}