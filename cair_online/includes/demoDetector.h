/**
 * File: demoDetector.h
 * Date: November 2011
 * Author: Dorian Galvez-Lopez
 * Description: demo application of DLoopDetector
 */

#ifndef __DEMO_DETECTOR__
#define __DEMO_DETECTOR__

#include <iostream>
#include <vector>
#include <string>

// OpenCV
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

// DLoopDetector and DBoW2
#include "DBoW2.h"
#include "DLoopDetector.h"
#include "DUtils.h"
#include "DUtilsCV.h"
#include "DVision.h"
#include "helperfunctions.h"
#include <pthread.h>

using namespace DLoopDetector;
using namespace DBoW2;
using namespace std;
using namespace cv;

pthread_mutex_t myMutex1;
bool to_consider = false;

struct for_libviso_relative_thread
{
  Matrix relate;
  int ind1;
  int ind2;
  string dir;
};

 void *libviso_relative_thread(void *t)
 {
    cout << "ENTER RELATIVE thread!" << endl;
    for_libviso_relative_thread* obj = (for_libviso_relative_thread *) t;

    to_consider = my_libviso2_relative(obj->relate, obj->ind1, obj->ind2, obj->dir);
    cout << to_consider << endl;

    cout << "X RELATIVE thread!!" << endl;
    return (void *)obj;
 }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

/// Generic class to create functors to extract features
template<class TDescriptor>
class FeatureExtractor
{
public:
  /**
   * Extracts features
   * @param im image
   * @param keys keypoints extracted
   * @param descriptors descriptors extracted
   */
  virtual void operator()(const cv::Mat &im, 
    vector<cv::KeyPoint> &keys, vector<TDescriptor> &descriptors) const = 0;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

/// @param TVocabulary vocabulary class (e.g: Surf64Vocabulary)
/// @param TDetector detector class (e.g: Surf64LoopDetector)
/// @param TDescriptor descriptor class (e.g: vector<float> for SURF)
template<class TVocabulary, class TDetector, class TDescriptor>
/// Class to run the demo 
class demoDetector
{
public:

  /**
   * @param vocfile vocabulary file to load
   * @param imagedir directory to read images from
   * @param posefile pose file
   * @param width image width
   * @param height image height
   */
   demoDetector(const std::string &vocfile, const std::string &imagedir,
    int width, int height);

  //  //my demo
  // demoDetector(std::vector<int> &v1, std::vector<int> &v2, const std::string &vocfile, const std::string &imagedir,
  //   const std::string &posefile, int width, int height);
    
  ~demoDetector(){}

  /**
   * Runs the demo
   * @param name demo name
   * @param extractor functor to extract features
   */
  void run(std::vector<Matrix> &m,std::vector<int> &v1, std::vector<int> &v2, const std::string &name, 
    const FeatureExtractor<TDescriptor> &extractor);

protected:

  /**
   * Reads the robot poses from a file
   * @param filename file
   * @param xs
   * @param ys
   */
  // void readPoseFile(const char *filename, std::vector<double> &xs, 
  //   std::vector<double> &ys) const;

protected:

  std::string m_vocfile;
  std::string m_imagedir;
  // std::string m_posefile;
  int m_width;
  int m_height;
};

// ---------------------------------------------------------------------------

template<class TVocabulary, class TDetector, class TDescriptor>
demoDetector<TVocabulary, TDetector, TDescriptor>::demoDetector
  (const std::string &vocfile, const std::string &imagedir,
  int width, int height)
  : m_vocfile(vocfile), m_imagedir(imagedir),
    m_width(width), m_height(height)
{
}

// ---------------------------------------------------------------------------

template<class TVocabulary, class TDetector, class TDescriptor>
void demoDetector<TVocabulary, TDetector, TDescriptor>::run
  (std::vector<Matrix> &M,std::vector<int> &index1, std::vector<int> &index2, const std::string &name, const FeatureExtractor<TDescriptor> &extractor)
{
  namedWindow( "Display window", WINDOW_AUTOSIZE );
  cout << "LoopDetector" << endl;
  
  // Set loop detector parameters
  typename TDetector::Parameters params(m_height, m_width);
 

   pthread_mutex_init(&myMutex1,0);

  // Parameters given by default are:
  // use nss = true
  // alpha = 0.3
  // k = 3
  // geom checking = GEOM_DI
  // di levels = 0

  pthread_t thread1;
  pthread_attr_t attr1;

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr1);
  pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_JOINABLE);
  
  // We are going to change these values individually:
  params.use_nss = true; // use normalized similarity score instead of raw score
  params.alpha = 0.3; // nss threshold
  params.k = 1; // a loop must be consistent with 1 previous matches
  params.geom_check = GEOM_DI; // use direct index for geometrical checking
  params.di_levels = 2; // use two direct index levels
  
  // To verify loops you can select one of the next geometrical checkings:
  // GEOM_EXHAUSTIVE: correspondence points are computed by comparing all
  //    the features between the two images.
  // GEOM_FLANN: as above, but the comparisons are done with a Flann structure,
  //    which makes them faster. However, creating the flann structure may
  //    be slow.
  // GEOM_DI: the direct index is used to select correspondence points between
  //    those features whose vocabulary node at a certain level is the same.
  //    The level at which the comparison is done is set by the parameter
  //    di_levels:
  //      di_levels = 0 -> features must belong to the same leaf (word).
  //         This is the fastest configuration and the most restrictive one.
  //      di_levels = l (l < L) -> node at level l starting from the leaves.
  //         The higher l, the slower the geometrical checking, but higher
  //         recall as well.
  //         Here, L stands for the depth levels of the vocabulary tree.
  //      di_levels = L -> the same as the exhaustive technique.
  // GEOM_NONE: no geometrical checking is done.
  //
  // In general, with a 10^6 vocabulary, GEOM_DI with 2 <= di_levels <= 4 
  // yields the best results in recall/time.
  // Check the T-RO paper for more information.
  //
  
  // Load the vocabulary to use
  cout << "Loading " << name << " vocabulary..." << endl;
  TVocabulary voc(m_vocfile);
  
  // Initiate loop detector with the vocabulary 
  cout << "Processing sequence..." << endl;
  TDetector detector(voc, params);
  
  // Process images
  vector<cv::KeyPoint> keys;
  vector<TDescriptor> descriptors;

  // load image filenames  
  string n = m_imagedir + "left/";
  //std::string &name = n; 

  vector<string> filenames = 
  DUtils::FileFunctions::Dir(n.c_str(), ".jpg", true);
  cout << "I am here!" << endl;
  cout << filenames[0].c_str() << endl;
  // // load robot poses
  // vector<double> xs, ys;
  // readPoseFile(m_posefile.c_str(), xs, ys);
  
  // we can allocate memory for the expected number of images
  detector.allocate(filenames.size());
  
  // prepare visualization windows
  DUtilsCV::GUI::tWinHandler win = "Current image";
  //DUtilsCV::GUI::tWinHandler winplot = "Trajectory";
  
  // DUtilsCV::Drawing::Plot::Style normal_style(2); // thickness
  // DUtilsCV::Drawing::Plot::Style loop_style('r', 2); // color, thickness
  
  // DUtilsCV::Drawing::Plot implot(240, 320,
  //   - *std::max_element(xs.begin(), xs.end()),
  //   - *std::min_element(xs.begin(), xs.end()),
  //   *std::min_element(ys.begin(), ys.end()),
  //   *std::max_element(ys.begin(), ys.end()), 20);
  
  // prepare profiler to measure times
  DUtils::Profiler profiler;
  
  int count = 0, inliercount=0;
  
  //namedWindow( "Image1", WINDOW_AUTOSIZE );
  for_libviso_relative_thread myviso;
  //cout << "dir: " << name1 <<endl;
  myviso.dir = m_imagedir;

  string ss,comment,final;
  comment = "\n#loop closure - \n";
  mythread_comm.loop_write_done = false;
  // go
  for(unsigned int i = 0; i < filenames.size(); ++i)
  {
    //mythread_comm.g2o_loop_flag = false;
    pthread_mutex_lock(&myMutex1);
    mythread_comm.loop_wait = true;
    pthread_mutex_unlock(&myMutex1);
    // cout << "In dloop, dloop flag initial: " << mythread_comm.loop_wait << endl;
    
    cout << "\t\t" << "Adding image " << i  << "... " << endl;

    Mat im;
    // get image
    cv::Mat color = cv::imread(filenames[i].c_str(), 1); // color
    
    // show image
    imshow("Display window", color);
    waitKey(30);
    cvtColor(color,im,CV_BGR2GRAY);

    // get features
    profiler.profile("features");
    extractor(im, keys, descriptors);
    profiler.stop();
        
    // add image to the collection and check if there is some loop
    DetectionResult result;
    
    profiler.profile("detection");
    detector.detectLoop(keys, descriptors, result);
    profiler.stop();
    
    if(result.detection())
    {
      cout << "\t\t" << "- Loop found with image " << result.match << "!"
      << endl;
      count++;
      //index1.push_back(i);
      //index2.push_back(result.match);
      myviso.ind1 = i;
      myviso.ind2 = result.match;
      pthread_create(&thread1, &attr1, libviso_relative_thread, (void *)&myviso);
      pthread_join(thread1,NULL);

      if(to_consider==true)
      {
        ss = my_for_g2o_edge(i,result.match,myviso.relate);
        mywriter.my_write_file << comment + ss + "# Done loop closure\n" << endl;
        mywriter.g2o_string = mywriter.g2o_string + comment + ss + "# Done loop closure\n";

        pthread_mutex_lock(&myMutex1);
        mythread_comm.g2o_loop_flag = true;
        pthread_mutex_unlock(&myMutex1);
        
        inliercount++;
        //M.push_back(myviso.relate);
      }

      
    }
    else
    {
      cout << "\t\t" << "- No loop: ";
      switch(result.status)
      {
        case CLOSE_MATCHES_ONLY:
          cout << "\t\t" << "All the images in the database are very recent" << endl;
          break;
          
        case NO_DB_RESULTS:
          cout << "There are no matches against the database (few features in"
            " the image?)" << endl;
          break;
          
        case LOW_NSS_FACTOR:
          cout << "Little overlap between this image and the previous one"
            << endl;
          break;
            
        case LOW_SCORES:
          cout << "\t\t" << "No match reaches the score threshold (alpha: " <<
            params.alpha << ")" << endl;
          break;
          
        case NO_GROUPS:
          cout << "Not enough close matches to create groups. "
            << "Best candidate: " << result.match << endl;
          break;
          
        case NO_TEMPORAL_CONSISTENCY:
          cout << "\t\t" << "No temporal consistency (k: " << params.k << "). "
            << "Best candidate: " << result.match << endl;
          break;
          
        case NO_GEOMETRICAL_CONSISTENCY:
          cout << "\t\t" << "No geometrical consistency. Best candidate: " 
            << result.match << endl;
          break;
          
        default:
          break;
      }
    }
    
    cout << endl;

    pthread_mutex_lock(&myMutex1);
    mythread_comm.loop_wait = false;
    pthread_mutex_unlock(&myMutex1);

    while(mythread_comm.viso_wait_flag==true)
    {
    }
    

  }
  
  if(count == 0)
  {
    cout << "\t\t" << "No loops found in this image sequence" << endl;
  }
  else
  {
    cout << "\t\t" << " Total loops found in this image sequence: " << count << endl;
    cout << "\t\t" << " Loops after inlier filtering in this image sequence: " << inliercount << endl;
  } 

  cout << endl << "Execution time:" << endl
    << " - Feature computation: " << profiler.getMeanTime("features") * 1e3
    << " ms/image" << endl
    << " - Loop detection: " << profiler.getMeanTime("detection") * 1e3
    << " ms/image" << endl;

  cout << endl << "Found loops!..." << endl;

  mythread_comm.loop_write_done = true;

  cvDestroyWindow("Display window");
}

#endif

