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

// Directroy of Images
string IMG_DIR1 = "/home/abhishek/iiit/Data/sept_30_junaid/loop1/";

// DLoop resources
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

// Viso Thread
 void *libviso_thread(void *t)
 {
    cout << "entering libviso2 thread!" << endl;
    for_libviso_thread* obj = (for_libviso_thread *) t;

    // Calling libviso function
    my_libviso2(obj->Tr_local,obj->Tr_global,obj->imgdir,obj->numimages);
    
    cout << "exiting libviso thread!!" << endl;
    return (void *)obj;
 }

// DLoop Thread
 void *dloop_thread(void *t)
{
    cout << "entered Dloop thread! "<< endl;
    for_dloop_thread* obj = (for_dloop_thread *) t;

    // Calling Dloop function
    my_dloop(obj->mat,obj->i1,obj->i2,VOC_FILE,IMG_DIR1,IMAGE_W,IMAGE_H);

    cout << "exiting Dloop thread!!" << endl;
    return (void *)obj;
 }

// For single loop
int main()
{
 
  pthread_t thread[2];
  pthread_attr_t attr;

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // Number of images in given directory
  int numImages1 =0;
  std::string path1 = IMG_DIR1 + "/left/";
  char * dst1 = new char[path1.length() + 1];
  std::strcpy(dst1,path1.c_str());

  numImages1 = listdir(dst1);

  for_libviso_thread lib;
  for_dloop_thread dthread;

  lib.imgdir = IMG_DIR1;
  lib.numimages = numImages1;

  // Create Dloop and Viso Thread 
  pthread_create(&thread[0], &attr, dloop_thread, (void *)&dthread);
  pthread_create(&thread[1], &attr, libviso_thread, (void *)&lib);  
  
  // Wait for Completion
  pthread_join(thread[0],NULL);
  pthread_join(thread[1],NULL);

  cout << "done" << endl;

  return 0;
}


// DLoop helper functions
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

