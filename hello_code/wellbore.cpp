//
//#include<windows.h>
//
//#include <Inventor/Win/SoWin.h>
//#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
//#include <Inventor/nodes/SoSeparator.h>
//#include <Inventor/nodes/SoCone.h>
//#include <Inventor/nodes/SoDrawStyle.h>
//#include <Inventor/nodes/SoComplexity.h>
//#include <Inventor/nodes/SoNurbsCurve.h>
//#include <Inventor/nodes/SoCoordinate3.h>
//
//#include <Inventor/nodes/SoCube.h>
//#include <Inventor/nodes/SoDrawStyle.h>
//#include <Inventor/nodes/SoLightModel.h>
//#include <Inventor/nodes/SoMaterial.h>
//#include <Inventor/nodes/SoMaterialBinding.h>
//#include <Inventor/nodes/SoSeparator.h>
//#include <Inventor/nodes/SoShapeHints.h>
//#include <Inventor/nodes/SoTranslation.h>
//#include <Inventor/VRMLnodes/SoVRMLExtrusion.h>
//
//#include <Inventor/nodes/SoText2.h>
//#include <Inventor/nodes/SoLineSet.h>
//#include <Inventor/nodes/SoCylinder.h>
//#include <Inventor/nodes/SoPointSet.h>
//
//#include <Inventor/nodes/SoSeparator.h>
//
//#include <math.h> // for M_PI
//
//
//
//
//
///////////////////////////////////////////////////////////////
////
//// Class to store a simple "well bore" data set
////
//// TODO: Data members should be private
//
//
//
//
//class WellBore {
//
//public:
//	WellBore() : nPoints(0), points(NULL), dataMin(0),
//		dataMax(1), data0(NULL), data1(NULL) {}
//
//	~WellBore()
//	{
//		delete points;
//		delete data0;
//		delete data1;
//	}
//
//	int nPoints;      // Number of data points
//	SbVec3f *points;  // 3D coordinate of each data point
//	float    dataMin; // Smallest data value
//	float    dataMax; // Largest data value
//	float   *data0;   // First set of data values
//	float   *data1;   // (Optional) Second set of data values
//};
//
///////////////////////////////////////////////////////////////
////
//// Class to store a simple color map
////
//// TODO: Data members should be private
//
//class ColorMap {
//
//public:
//	ColorMap() : nColors(0), colors(NULL) {}
//
//	~ColorMap()
//	{
//		delete colors;
//	}
//
//	int   nColors;    // Number of color values in map
//	SbColor *colors;  // Color values
//};
//
///////////////////////////////////////////////////////////////
////
//// Read a "well bore" data set from a simple file format
////
//// Careful... this code is fragile...  only an example!
//
//WellBore *readWellBore(const char *filename)
//{
//	WellBore *pWell = new WellBore;
//
//	FILE *fp = fopen(filename, "r");
//	if (fp == NULL) {
//		fprintf(stderr, "*** Unable to open data file '%s'.\n", filename);
//		return NULL;
//	}
//
//	int nPoints = 0;
//
//	const int BUFLEN = 256;
//	char buffer[BUFLEN];
//	char *p;
//
//	while ((p = fgets(buffer, BUFLEN, fp))) {
//		while (*p == ' ') p++; // skip whitespace
//		if (*p == '#' || *p == '\0' || *p == '\n') // Comment or end-of-line
//			continue;
//		if (!strncmp(p, "nVertices", 9)) {
//			p += 9;
//			sscanf(p, "%d", &nPoints);
//		}
//		else if (!strncmp(p, "Coords", 6)) {
//			pWell->nPoints = nPoints;
//			pWell->points = new SbVec3f[nPoints];
//			for (int i = 0; i < nPoints; ++i) {
//				float x, y, z;
//				p = fgets(buffer, BUFLEN, fp);
//				sscanf(p, "%g %g %g", &x, &y, &z);
//				pWell->points[i].setValue(x, y, z);
//			}
//		}
//		else if (!strncmp(p, "Data", 4)) {
//			pWell->data0 = new float[nPoints];
//			for (int i = 0; i < nPoints; ++i) {
//				float val;
//				p = fgets(buffer, BUFLEN, fp);
//				sscanf(p, "%g", &val);
//				pWell->data0[i] = val;
//			}
//		}
//	}
//
//	// We happen to know the range for the data in this example
//	pWell->dataMin = 0;
//	pWell->dataMax = 255;
//
//	fclose(fp);
//	printf("--- Loaded data file '%s': %d points.\n",
//		filename, nPoints);
//
//	return pWell;
//}
//
///////////////////////////////////////////////////////////////
////
//// Careful... this code is fragile...
//
//ColorMap *
//readColorMap(const char *filename)
//{
//	FILE *fp = fopen(filename, "r");
//	if (fp == NULL) {
//		fprintf(stderr, "*** Unable to open colormap file '%s'.\n", filename);
//		return NULL;
//	}
//
//	ColorMap *pMap = NULL;
//
//	const int BUFLEN = 256;
//	char buffer[BUFLEN];
//	char *p;
//
//	while ((p = fgets(buffer, BUFLEN, fp))) {
//		while (*p == ' ') p++; // skip whitespace
//		if (*p == '#' || *p == '\0' || *p == '\n') // Comment or end-of-line
//			continue;
//		if (!strncmp(p, "nColors", 7)) {
//			p += 7;
//			int nColors;
//			sscanf(p, "%d", &nColors);
//			pMap = new ColorMap;
//			pMap->nColors = nColors;
//			pMap->colors = new SbColor[nColors];
//
//			for (int i = 0; i < nColors; ++i) {
//				float r, g, b;
//				p = fgets(buffer, BUFLEN, fp);
//				sscanf(p, "%g %g %g", &r, &g, &b);
//				pMap->colors[i].setValue(r, g, b);
//			}
//		}
//	}
//
//	fclose(fp);
//	printf("--- Loaded colormap file '%s': %d colors.\n",
//		filename, (pMap ? pMap->nColors : 0));
//
//	return pMap;
//}
//
///////////////////////////////////////////////////////////////
//
//
//
//SoSeparator* MakeTrajectory(WellBore *pWell)
//{
//
//	SoSeparator *pSep = new SoSeparator;
//	SoCoordinate3 *coord = new SoCoordinate3;
//	coord->point.setValues(0, pWell->nPoints, pWell->points);
//	SoLineSet *line = new SoLineSet;	
//	SoPointSet *point = new SoPointSet;
//	
//	
//
//	SoDrawStyle *pStyle = new SoDrawStyle;
//	pStyle->style = SoDrawStyle::LINES;
//	pStyle->lineWidth = 6;
//	//pStyle->linePattern = patterns[1];
//
//
//	float initHeight = 0;
//	float x=0, y=0, z=0;
//	for (int i = 0; i < pWell->nPoints; i++)
//	{
//		pWell->points->getValue(x, y, z);
//		SoSeparator *tmpSep = new SoSeparator;
//		SoTranslation *trans = new SoTranslation;
//		SoCylinder *cylinder = new SoCylinder;
//
//		cylinder->radius = 3;
//		if (i == 0)
//		{
//			cylinder->height = 1;
//			initHeight = 1;
//		}
//		else
//		{			
//			float diffHeight = z - initHeight;
//			cylinder->height = diffHeight;
//			initHeight = z;
//		}
//		trans->translation.setValue(x, y, z);
//
//		tmpSep->addChild(trans);
//		tmpSep->addChild(cylinder);
//		//pSep->addChild(tmpSep);
//	}
//	
//
//	//cylinder->setValue(&ln, 3);
//	//pSep->addChild(pStyle);
//	pSep->addChild(coord);
//	pSep->addChild(point);
//	return pSep;
//
//}
//
//SoSeparator *
//makeExtrusion(WellBore *pWell,
//ColorMap *pMap,
//int   numSides = 12,
//float minValForColor = -1,
//float maxValForColor = -1,
//float scaleFactor = 1)
//{
//	// Group the attribute nodes and extrusion
//	SoSeparator *pSep = new SoSeparator;
//
//	// Extrusion will be considered "solid" to enable back-face culling.
//	// Also set crease angle to "smooth" surface for more than 4 sides.
//	SoShapeHints *pHints = new SoShapeHints;
//	pHints->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
//	pHints->shapeType = SoShapeHints::SOLID;
//	pHints->creaseAngle = (float)(M_PI / 2.1);
//	pSep->addChild(pHints);
//
//
//	SoVRMLExtrusion *pExt = new SoVRMLExtrusion;
//
//	//SoExtrusion *pExt = new SoExtrusion;
//
//	// Cross section (prescaled to diameter=1 to allow meaningful scaling)
//	// 16 sides makes a reasonable cylinder (with smoothing).
//	//  4 sides is useful for checking twist or to improve performance.
//
//	// Compute x and z coordinates around circle
//	if (numSides < 2)
//		numSides = 2;
//	int   side;
//	float theta = 0.0f;
//	float dTheta = (float)(2.0 * M_PI / (double)numSides);
//	const float eps = 1e-6f;
//
//	pExt->crossSection.setNum(numSides + 1);
//
//	for (side = 0; side < numSides; side++) {
//		float x = 0.5f * sin(theta);
//		float z = 0.5f * cos(theta);
//		if (fabs(x) < eps) x = 0;
//		if (fabs(z) < eps) z = 0;
//		pExt->crossSection.set1Value(side, SbVec2f(x, z));
//		theta += dTheta;
//	}
//	pExt->crossSection.set1Value(numSides, SbVec2f(0, 0.5f)); // close loop
//
//	// Coordinates of well bore define the spine
//	pExt->spine.setValues(0, pWell->nPoints, pWell->points);
//
//	// Get data range
//	int   nPoints = pWell->nPoints;
//
//	// First data set maps to color
//	// (requires new SoExtrusion node)
//	if (pWell->data0 && pMap) {
//
//		// Assign color value to each spine point
//		SoMaterialBinding *pBind = new SoMaterialBinding;
//		pBind->value = SoMaterialBinding::PER_VERTEX;
//
//		// Define colors (one per spine vertex)
//		SoMaterial *pMat = new SoMaterial;
//		pMat->diffuseColor.setNum(nPoints);
//
//		// Number of colors in map
//		int nColors = pMap->nColors;
//
//		for (int i = 0; i < nPoints; ++i) {
//			float data = pWell->data0[i];
//			SbColor color;
//			if (data <= minValForColor)
//				color = pMap->colors[0];
//			else if (data >= maxValForColor)
//				color = pMap->colors[pMap->nColors - 1];
//			else {
//				float t = (data - minValForColor) / (maxValForColor - minValForColor);
//				t *= nColors;
//				int index = (int)(t + 0.5);
//				color = pMap->colors[index];
//			}
//			pMat->diffuseColor.set1Value(i, color);
//		}
//
//		pSep->addChild(pBind);
//		pSep->addChild(pMat);
//	}
//
//	// Second data set maps to radius (defines scale factor)
//	if (pWell->data1) {
//
//		pExt->scale.setNum(pWell->nPoints);
//
//		for (int i = 0; i < pWell->nPoints; ++i) {
//			float scale = pWell->data1[i];
//
//			// Apply global scale factor
//			scale *= scaleFactor;
//			pExt->scale.set1Value(i, SbVec2f(scale, scale));
//		}
//	}
//	// Else just use global scale factor for all points
//	else {
//		pExt->scale.setValue(SbVec2f(scaleFactor, scaleFactor));
//	}
//
//	pSep->addChild(pExt);
//	return pSep;
//}
//
//
//const unsigned short
//patterns[5] = {
//	0xFFFF, // solid
//	0x000F, // dash 
//	0x1111, // dot
//	0x041F, // dash-dot
//	0x111F, // dash-dot-dot
//};
//
//
//SoSeparator* AddLabel(SoCube *cube)
//{
//	SoSeparator *tmpMainSep = new SoSeparator;
//
//	SoSFFloat _width = cube->width;
//	SoSFFloat _height = cube->height;
//	SoSFFloat _depth = cube->depth;
//
//	SoSeparator *originSep = new SoSeparator;
//	SoText2 *xyz = new SoText2;
//	xyz->string = "(0,0)";
//	SoMaterial *mat = new SoMaterial;
//	mat->diffuseColor.setValue(0, 0, 0);
//	SoTranslation *trans = new SoTranslation;
//	trans->translation.setValue(0, 0, 0);
//	originSep->addChild(trans);
//	originSep->addChild(mat);
//	originSep->addChild(xyz);
//
//
//	tmpMainSep->addChild(originSep);
//
//	return tmpMainSep;
//}
//
//
///////////////////////////////////////////////////////////////
//
//int
//main(int, char ** argv)
//{
//
//	HWND window = SoWin::init(argv[0]);
//	if (window == NULL) exit(1);
//
//	SoWinExaminerViewer * viewer = new SoWinExaminerViewer(window);
//
//	viewer->setBackgroundColor(SbColor(1, 1, 1));
//	SoSeparator * root = new SoSeparator;
//	root->ref();
//	
//	// Try to read the files
//	char *DataDir0 = "data0.txt";
//	char *DataDir1 = "data1.txt";
//	char *colormapDir = "colormap.txt";
//
//	WellBore *pWell0 = readWellBore(DataDir0);
//	WellBore *pWell1 = readWellBore(DataDir1);
//	ColorMap *pCMap = readColorMap(colormapDir);
//
//	if (!pWell0 || !pWell1 || !pCMap) {
//		fprintf(stderr, "Exiting -- unable to load data or colormap\n");
//		return 0;
//	}
//
//	// Simulate having a second data set on the second bore
//	pWell1->data1 = new float[pWell1->nPoints];
//	memcpy(pWell1->data1, pWell1->data0, pWell1->nPoints * sizeof(float));
//
//
//	// We happen to know the bounds of the data volume these
//	// well bores are associated with...
//	float xmax = 300;
//	float ymax = 455;
//	float zmax = 91;
//
//	// Simple bounding box
//	{
//		SoTranslation *pTrans = new SoTranslation;
//		pTrans->translation.setValue(xmax / 2, ymax / 2, zmax / 2);
//
//		SoDrawStyle *pStyle = new SoDrawStyle;
//		pStyle->style = SoDrawStyle::LINES;
//		pStyle->lineWidth = 3;
//		pStyle->linePattern = patterns[4];
//
//
//		SoMaterial *lineColor = new SoMaterial;
//		lineColor->diffuseColor.setValue(0, 1, 0);
//
//		SoLightModel *pModel = new SoLightModel;
//		pModel->model = SoLightModel::BASE_COLOR;
//
//		SoCube *pCube = new SoCube;
//		pCube->width = xmax;
//		pCube->height = ymax;
//		pCube->depth = zmax;
//
//		SoSeparator *pBoxSep = new SoSeparator;
//		pBoxSep->addChild(lineColor);
//		pBoxSep->addChild(pTrans);
//		pBoxSep->addChild(pStyle);
//		pBoxSep->addChild(pModel);
//		pBoxSep->addChild(pCube);
//
//		root->addChild(pBoxSep);
//	}
//
//	// Create well bore visualizations
//	SoSeparator *pBoreSep;
//
//	// Number of sides (12-16 gives a reasonable looking cylinder)
//	const int   numSides = 12;
//
//	// Range of data values that color map actually applies to
//	const float dataMin = 125;
//	const float dataMax = 200;
//
//	// First bore only has one data set, so default bore will have
//	// diameter of 1.  Scale it by 8 to be more visible.
//	pBoreSep = makeExtrusion(pWell0, pCMap, numSides, dataMin, dataMax, 8);
//	root->addChild(pBoreSep);
//
//	// Second bore has two data sets (actually both contain same values),
//	// so bore diameter will be taken from second data set.  Scale it
//	// down to be approximately in scale with the first bore.
//	pBoreSep = makeExtrusion(pWell1, pCMap, numSides, dataMin, dataMax, 0.08f);
//	root->addChild(pBoreSep);
//
//
//
//	viewer->setSceneGraph(root);
//	viewer->show();
//
//	SoWin::show(window);
//	SoWin::mainLoop();
//	delete viewer;
//	root->unref();
//	return 0;
//}