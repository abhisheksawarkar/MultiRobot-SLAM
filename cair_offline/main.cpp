#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <fstream>
#include <pthread.h>

#include "includes/helperfunctions.h"

// DLoopDetector and DBoW2
#include <DBoW2/DBoW2.h> // defines Surf64Vocabulary
#include "DLoopDetector.h" // defines Surf64LoopDetector
#include <DUtilsCV/DUtilsCV.h> // defines macros CVXX

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
// Demo
#include "includes/demoDetector.h"

using namespace DLoopDetector;
using namespace DBoW2;
using namespace std;
using namespace cv;


#define PI 3.14159265

// Directory of Images
string IMG_DIR1 = "/home/abhishek/iiit/Data/oct11_dusshera/loop3/";

// Resources for DLoop
static const string VOC_FILE = "./resources/huskymerge_voc.voc.gz";
static const string IMAGE_DIR = IMG_DIR1 + "left/";
static const int IMAGE_W = 640; // image size
static const int IMAGE_H = 480;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
void my_dloop(std::vector<Matrix> &m,std::vector<int> &index1, std::vector<int> &index2,string file, string img_dir, int a, int b);
/// This functor extracts SURF64 descriptors in the required format
class SurfExtractor: public FeatureExtractor<FSurf64::TDescriptor>
{
public:
  /** 
   * Extracts features from an image
   * @param im image
   * @param keys keypoints extracted
   * @param descriptors descriptors extracted
   */
  virtual void operator()(const cv::Mat &im, 
    vector<cv::KeyPoint> &keys, vector<vector<float> > &descriptors) const;
};

// Struct for passing variables to viso thread 
struct for_libviso_thread
{
  std::vector<Matrix> Tr_local;
  std::vector<Matrix> Tr_global;
  int numimages;
  string imgdir;
};

// Struct for passing variables to Dloop thread
struct for_dloop_thread
{
  std::vector<Matrix> mat;
  std::vector<int> i1;
  std::vector<int> i2;
};


void *libviso_thread(void *t)
{
cout << "entering libviso2 thread!" << endl;
for_libviso_thread* obj = (for_libviso_thread *) t;

my_libviso2(obj->Tr_local,obj->Tr_global,obj->imgdir,obj->numimages);

//printf("exiting thread:- %ld\n",tid);
cout << "exiting libviso thread!!" << endl;
return (void *)obj;
}

 void *dloop_thread(void *t)
{
    cout << "entered Dloop thread! "<< endl;
    for_dloop_thread* obj = (for_dloop_thread *) t;
    my_dloop(obj->mat,obj->i1,obj->i2,VOC_FILE,IMG_DIR1,IMAGE_W,IMAGE_H);

    //pthread_exit((void*) t);
    //printf("exiting thread:- %ld\n",tid);
    cout << "exiting Dloop thread!!" << endl;
    return (void *)obj;
    //go_flag2 = true;
 }

// For single loop

int main()
{
 
  pthread_t thread[2];
  pthread_attr_t attr;

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

 	// ofstream myfile1, myfile2, for_plot, for_g2o_traj, for_g2o_traj_with_loops;
 	// myfile1.open("data/Tr_local.txt");
 	// myfile2.open("data/Tr_global.txt");
 	// for_plot.open("data/2d_coords.txt");
 	// for_g2o_traj.open("data/traj1.g2o");
 //	for_g2o_traj_with_loops.open("my_complete_data_2/traj1_with_loops.g2o");

 	int numImages1 =0, numImages2 =0;
 	std::string path1 = IMG_DIR1 + "/left/";
	char * dst1 = new char[path1.length() + 1];
	std::strcpy(dst1,path1.c_str());

	numImages1 = listdir(dst1);
	//numImages2 = listdir(IMG_DIR2);
	cout << numImages1 << endl;

  for_libviso_thread lib;
  for_dloop_thread dthread;

  lib.imgdir = IMG_DIR1;
  lib.numimages = numImages1;

  std::vector<Matrix> Tr_local;
  std::vector<Matrix> Tr_global;

  std::vector<int> index1;
  std::vector<int> index2;

  pthread_create(&thread[0], &attr, dloop_thread, (void *)&dthread);
  pthread_create(&thread[1], &attr, libviso_thread, (void *)&lib);  

  // while(go_flag1&&go_flag2)
  // {}
  pthread_join(thread[0],NULL);
  pthread_join(thread[1],NULL);

  cout << "done" << endl;

  // Tr_local = lib.Tr_local;
  // Tr_global = lib.Tr_global;
  
  
 
  

    
  //cout << m.a << " " << m.b << " " << m.c << endl;


//   std::vector<Matrix> mymat;
// //  my_dloop(index1,index2,VOC_FILE,IMAGE_DIR,IMAGE_W,IMAGE_H);

//   index1 = dthread.i1;
//   index2 = dthread.i2;
//   mymat = dthread.mat;

	// // my_libviso2(Tr_local,Tr_global,IMG_DIR1,numImages1);


	 // Matrix aboutX = Matrix::rotMatX(-PI,4);
	 // Matrix new_tr;

	// double valx;
	// double valz;
	
	// for (int i=0; i<Tr_global.size(); i++)
 //    {
 //    	myfile1 << "frame: " << i+1 << endl << Tr_local[i] << endl << endl;
 //    	myfile2 << "frame: " << i+1 << endl << Tr_global[i] << endl << endl; 
    	
 //    	valx = Tr_global[i].getData(0,3);
 //    	valz = Tr_global[i].getData(2,3); 
    	
 //    	for_plot << valx << '\t' << valz << endl;

 //    	new_tr = aboutX*Tr_local[i];

 //    	double dx = new_tr.getData(0,3);
 //    	double dz = new_tr.getData(2,3);
 //    	double thetay = atan2(-new_tr.getData(2,0), sqrt(new_tr.getData(2,1)*new_tr.getData(2,1) + new_tr.getData(2,2)*new_tr.getData(2,2)));

 //    	if(i<Tr_global.size()-1)
 //    	{
 //    		for_g2o_traj << "EDGE_SE2 " << i+1 <<' '<< i+2 <<' '<< -dz <<' '<< -dx <<' '<< thetay <<' '<< "1000 0 0 1000 0 10000" << endl;
 //    		for_g2o_traj_with_loops	<< "EDGE_SE2 " << i+1 <<' '<< i+2 <<' '<< -dz <<' '<< -dx <<' '<< thetay <<' '<< "1000 0 0 1000 0 10000" << endl;
 //    	}
    	

 //    }

 //  myfile1.close();
	// myfile2.close();
	// for_plot.close();
	// for_g2o_traj.close();

	// for_g2o_traj_with_loops << endl;

  // std::vector<Tr_relative> relative;

  // my_libviso2_relative(relative, index1, index2, IMG_DIR1);

  // myfile1.open("data/loop1.txt");
  // myfile2.open("data/edges1.g2o");

  // for (int i = 0; i < index1.size(); i++)
  // {
  //    //  Tr_relative t = relative[i];
  //    //  Matrix m = t.transform;

  //    //  	myfile1 << t.frame1 << '\t' << t.frame2 << endl;
    	
  //   	// valx = m.getData(0,3);
  //   	// valz = m.getData(2,3); 

  //   	// new_tr = aboutX*m;

  //   	// double dx = new_tr.getData(0,3);
  //   	// double dz = new_tr.getData(2,3);
  //   	// double thetay = atan2(-new_tr.getData(2,0), sqrt(new_tr.getData(2,1)*new_tr.getData(2,1) + new_tr.getData(2,2)*new_tr.getData(2,2)));

  //   	// //if(i<Tr_global.size()-1)
  //   	// myfile2 << "EDGE_SE2 " << t.frame1 <<' '<< t.frame2 <<' '<< -dz <<' '<< -dx <<' '<< thetay <<' '<< "1000 0 0 1000 0 10000" << endl;
  //   	// for_g2o_traj_with_loops << "EDGE_SE2 " << t.frame1 <<' '<< t.frame2 <<' '<< -dz <<' '<< -dx <<' '<< thetay <<' '<< "1000 0 0 1000 0 10000" << endl;

  //   cout << index1[i] << " " << index2[i] << " " << endl;
  //   cout << mymat[i] << endl << endl;
  //   cout << dthread.mat[i] << endl;

  //     //cout << t.transform << endl;
  // }

  // cout << "size of relative: " << relative.size() << endl;
  // cout << "size of index1: " << index1.size() << endl;
  // cout << "size of index2: " << index2.size() << endl;

  // myfile1.close();
  // myfile2.close();
  // for_g2o_traj_with_loops << endl << "FIX 1";
  // for_g2o_traj_with_loops.close();			
	//myfile1.open("edges.g2o");

	// for (int i = 0; i < relative.size(); i++)
	// {
	// 	Tr_relative tr = relative[i];
	// 	int index1_loop = tr.frame1;
	// 	int index2_loop = tr.frame2;

	// 	Matrix Tr = aboutX*tr.transfom;

	// 	double dx = Tr.getData(0,3);
 //    	double dz = Tr.getData(2,3);
 //    	double thetay = atan2(-Tr.getData(2,0), sqrt(Tr.getData(2,1)*Tr.getData(2,1) + Tr.getData(2,2)*Tr.getData(2,2)));

 //    	myfile1 << "EDGE_SE2 " << index1_loop <<' '<< index2 <<' '<< -dz <<' '<< -dx <<' '<< thetay <<' '<< "1000 0 0 1000 0 10000" << endl;
	// }

	// myfile1.close();



	// for (int i = 0; i < vec1.size(); i++)
	// {
		

	// }



	//Read loop.txt pairs
	
	//matlab formatting in cpp for extracting loop pairs
	//run libviso2 on loop pairs
	//store edge transformations and concat with entire trajectory


	//cout << "size " << myvec.size() << endl;
	// //cout << "last " << myvec[numImages1-1] << endl;

	
	return 0;
}

// ----------------------------------------------------------------------------

void SurfExtractor::operator() (const cv::Mat &im, 
  vector<cv::KeyPoint> &keys, vector<vector<float> > &descriptors) const
{
  // extract surfs with opencv
   static cv::Ptr<cv::xfeatures2d::SURF> surf_detector = 
    cv::xfeatures2d::SURF::create(400);
  
  surf_detector->setExtended(false);
  
  keys.clear(); // opencv 2.4 does not clear the vector
  vector<float> plain;
  surf_detector->detectAndCompute(im, cv::Mat(), keys, plain);
  
  // change descriptor format
  const int L = surf_detector->descriptorSize();
  descriptors.resize(plain.size() / L);

  unsigned int j = 0;
  for(unsigned int i = 0; i < plain.size(); i += L, ++j)
  {
    descriptors[j].resize(L);
    std::copy(plain.begin() + i, plain.begin() + i + L, descriptors[j].begin());
  }
}

// ----------------------------------------------------------------------------

void my_dloop(std::vector<Matrix> &Mat,std::vector<int> &index1, std::vector<int> &index2,string VOC_FILE1,string IMAGE_DIR1, int IMAGE_W1, int IMAGE_H1)
{
   demoDetector<Surf64Vocabulary, Surf64LoopDetector, FSurf64::TDescriptor>
    demo(VOC_FILE1, IMAGE_DIR1, IMAGE_W1, IMAGE_H1);

  try 
  {  
    // run the demo with the given functor to extract features
    SurfExtractor extractor;
    demo.run(Mat,index1,index2,"SURF64", extractor);
  }
  catch(const std::string &ex)
  {
    cout << "Error: " << ex << endl;
  }
}