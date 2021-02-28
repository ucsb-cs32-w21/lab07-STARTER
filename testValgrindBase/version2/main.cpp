/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "shape.h"
#include "color.h"
#include "rect.h"
#include "implicit2D.h"
#include "polygon.h"
#include "util.h"

using namespace std;

/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */
void writeOut(ostream& out, ppmR& theWriter, 
				vector<shape *> theShapes) {

	float res;
	color inC;
	color drawC;
	color background(112, 134, 156);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations
			for (auto eq : theShapes) {
				if (eq->eval(x, y) && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
					
			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	vector<shape *> theShapes;

	//a triangle
	theShapes.push_back( new Polygon(vec2(100, 30), 5, color(252)) );
	((Polygon *)theShapes.at(0))->addVert(vec2(120, 10));
	((Polygon *)theShapes.at(0))->addVert(vec2(145, 30));

	Polygon * t2 = new Polygon(vec2(140, 130), 5, color(252)) ;
	t2->addVert(vec2(160, 110));
	t2->addVert(vec2(185, 120));

	Polygon *t3 = new  Polygon(vec2(140, 230), 5, color(252)) ;
	t3->addVert(vec2(180, 210));
	t3->addVert(vec2(195, 220));

	theShapes.push_back(t2);

	theShapes.push_back(t3);

	color ellipseColor = color(61, 21, 21);
	
	for (int j=0; j < 5; j++) {
		theShapes.push_back(new Implicit2D(nicerRand(100, 200), nicerRand(100, 200), 
								nicerRand(11, 30), nicerRand(11, 30), ellipseColor));	
	}

	theShapes.push_back(new Rect(vec2(200, 200), 60, 60, color(120), 14));

	for (int i=0; i < 10; i++) {
		theShapes.push_back(new Rect(vec2(nicerRand(0, 300), nicerRand(0, 300)), 
				nicerRand(18, 43), nicerRand(15, 32), color(nicerRand(123, 250)), nicerRand(1, 20)));
	}

	string outFilename;
	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		ppmR theWriter(sizeX, sizeY);

		//just write out one for this lab
		for (int i=0; i < 1; i++) {
			//code to write the files
		  outFilename.append(argv[3]);
		  if (i < 10)
		  	outFilename.append(to_string(0));
		  outFilename.append(to_string(i));
		  outFilename.append(".ppm");
		  outFile.open(outFilename);

		  if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theShapes);
			outFile.close();
			outFilename.erase();
		  } else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		  }
		} //end animation loop

	} //end valid command line parameters

}
