#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {

	ofstream huginscript;

	//replace the following line with the directory your images are stored in
	huginscript.open ("/home/alessandro/Documents/ImageData/150915/lamb/corrected/huginscript.sh");

	huginscript << "# usage...hugin-cmd-stitch.sh outputprefix fov \n\n#get the output file prefix \nPrefix=$1 \n\n# get the fov \nFOV=$2 \n\npto_gen --projection=0 --fov=$FOV -o project.pto ";

	int nImages = 3;

	for(int i=0;i<nImages;i++)
		{
			huginscript  <<"./lamb0_" << setfill('0') << setw(5)<< i+1 << "-correctedGPU.tif ";
		}

	huginscript  << "\n \npto_lensstack -o project1.pto ";
	for(int i=0;i<nImages-1;i++)
	{
		huginscript <<  " --new-lens i"<< i+1 ;
	}
	huginscript << " project.pto\n";

	huginscript << "cpfind -o project1.pto --multirow project1.pto \ncpclean -o project2.pto project1.pto \nlinefind -o project3.pto project2.pto \npto_var -o setoptim.pto --opt r,d,e,!r0,!d0,!e0 project3.pto \nautooptimiser -n -o autoptim.pto setoptim.pto \npano_modify  --projection=0 --fov=AUTO --center --canvas=AUTO --crop=AUTO -o autoptim2.pto autoptim.pto \npto2mk -o project.mk -p $Prefix autoptim2.pto \nmake -j 2 -f project.mk all ";

	huginscript.close();

	return 0;
}
