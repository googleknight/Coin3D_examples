
#include<windows.h>
#include <Inventor/Win/SoWin.h>

#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCone.h>

int
main(int, char ** argv)
{

	HWND window = SoWin::init(argv[0]);
	if (window == NULL) exit(1);

	SoWinExaminerViewer * viewer = new SoWinExaminerViewer(window);	
	
	viewer->setDecoration(false);
	

	SoSeparator * root = new SoSeparator;
	SoCone * cone = new SoCone;

	root->ref();
	root->addChild(cone);

	viewer->setSceneGraph(root);
	viewer->show();

	SoWin::show(window);
	SoWin::mainLoop();
	delete viewer;
	root->unref();
	return 0;
}