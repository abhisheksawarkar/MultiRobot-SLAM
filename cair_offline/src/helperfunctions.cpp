// To find number of images in a directory

#include <sys/types.h>
#include <dirent.h>
#include "helperfunctions.h"
#include "filewriter.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdint.h>
#include <sstream> 

#include <viso_stereo.h>
//#include <png++/png.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <pthread.h>

using namespace std;
using namespace cv;

#define PI 3.14159265

bool dloop_wait_flag = true;
bool viso_wait_flag = true;
bool loop_write_done = false;

writer mywriter;
//ofstream myfile1;

pthread_mutex_t myMutex;


double valx;
double valz;

int listdir(char *dir) {
  struct dirent *dp;
  DIR *fd;
  int counter =0;
  cout << dir<<endl;

  if ((fd = opendir(dir)) == NULL) {
    fprintf(stderr, "listdir: can't open %s\n", dir);
    return -1;
  }
  while ((dp = readdir(fd)) != NULL) {
  if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
    continue;    /* skip self and parent */
  	counter++;
  }
  closedir(fd);
  return counter;
}


void my_libviso2(std::vector<Matrix> &Tr_local, std::vector<Matrix> &Tr_global, string dir, int numImg) {
  
  // set most important visual odometry parameters
  // for a full parameter list, look at: viso_stereo.h
  VisualOdometryStereo::parameters param;
  
  // calibration parameters for sequence 2010_03_09_drive_0019 
  param.calib.f  = 711.9212646484375; // focal length in pixels
  param.calib.cu = 647.0408325195312; // principal point (u-coordinate) in pixels
  param.calib.cv = 360.7899169921875; // principal point (v-coordinate) in pixels
  param.base     = 0.12; // baseline in meters

   pthread_mutex_init(&myMutex,0);

   mywriter.my_write_file.open("data/traj3_loop.g2o");
   //myfile1.open("data/traj.g2o");
   string ss;

  // init visual odometry
  VisualOdometryStereo viso(param);
  
  Matrix pose = Matrix::eye(4);
  Tr_global.push_back(pose);
  
  Matrix extra_relations;
  bool is_good = false;
  // loop through all frames i=0:372
  for (int32_t i=1; i<=numImg; i++) 
  {  

    pthread_mutex_lock(&myMutex);
    viso_wait_flag = true;
    pthread_mutex_unlock(&myMutex);

    // input file names
    char base_name[256]; sprintf(base_name,"%04d.jpg",i);
    string left_img_file_name  = dir + "left/" + base_name;
    string right_img_file_name = dir + "right/" + base_name;
    
    // catch image read/write errors here
    try {

      // load left and right input image
      Mat left_img_src, right_img_src;
      left_img_src = imread(left_img_file_name,CV_LOAD_IMAGE_COLOR);
      right_img_src = imread(right_img_file_name,CV_LOAD_IMAGE_COLOR);

      Mat left_img,right_img;
      cvtColor(left_img_src,left_img,CV_BGR2GRAY);
      cvtColor(right_img_src,right_img,CV_BGR2GRAY);

      int32_t width  = left_img.cols;
      int32_t height = left_img.rows;

      // convert input images to uint8_t buffer
      uint8_t* left_img_data  = (uint8_t*)malloc(width*height*sizeof(uint8_t));
      uint8_t* right_img_data = (uint8_t*)malloc(width*height*sizeof(uint8_t));
      int32_t k=0;
      for (int32_t row=0; row < left_img.rows; row++) {
        for (int32_t col=0; col < left_img.cols; col++) {

          left_img_data[k]  = left_img.at<uchar>(row,col);
          right_img_data[k] = right_img.at<uchar>(row,col);
          k++;
        }
      }

      // status
      cout << "Processing: Frame: " << i << endl;
      
      // compute visual odometry
      int32_t dims[] = {width,height,width};
      //==if (viso.process(left_img_data,right_img_data,dims)) {
      
        viso.process(left_img_data,right_img_data,dims);
        // on success, update current pose

        Tr_local.push_back(Matrix::inv(viso.getMotion()));
        
        ss = my_for_g2o_edge(i,i+1,Matrix::inv(viso.getMotion()));
        mywriter.my_write_file << ss;


        if((i%5==0) && (i+5 < numImg))
        {
          is_good = my_libviso2_relative(extra_relations,i,i+5,dir);

            if(is_good)
            {
              ss = my_for_g2o_edge(i,i+5,extra_relations);
              mywriter.my_write_file << ss;
            }

            cout << "extra!! " << i << " " << i+5 << endl;
        }


        if(i>1)
        {
          pose = pose * Matrix::inv(viso.getMotion());
          Tr_global.push_back(pose);  
        }
        


        // output some statistics
        // double num_matches = viso.getNumberOfMatches();
        // double num_inliers = viso.getNumberOfInliers();
        // cout << ", Matches: " << num_matches;
        // cout << ", Inliers: " << 100.0*num_inliers/num_matches << " %" << ", Current pose: " << endl;
        // cout << pose << endl << endl;


      // release uint8_t buffers
      free(left_img_data);
      free(right_img_data);

    // catch image read errors here
    } catch (...) {
      cerr << "ERROR: Couldn't read input files!" << endl;
      break;
    }

    pthread_mutex_lock(&myMutex);
    viso_wait_flag = false;
    pthread_mutex_unlock(&myMutex);



    while(dloop_wait_flag)
    {}
 }

pthread_mutex_destroy(&myMutex);

 while(!loop_write_done)
  {}

mywriter.my_write_file << "\nFIX 1 \n";
mywriter.my_write_file.close();
  //cout << "Demo complete! Exiting ..." << endl;
}


bool my_libviso2_relative(Matrix &Tr_final, int index1, int index2, std::string dir)
{
   // set most important visual odometry parameters
  // for a full parameter list, look at: viso_stereo.h
  VisualOdometryStereo::parameters param;
  
  
  // calibration parameters for sequence 2010_03_09_drive_0019 
  param.calib.f  = 711.9212646484375; // focal length in pixels
  param.calib.cu = 647.0408325195312; // principal point (u-coordinate) in pixels
  param.calib.cv = 360.7899169921875; // principal point (v-coordinate) in pixels
  param.base     = 0.12; // baseline in meters
  
  // init visual odometry
  VisualOdometryStereo viso(param);
  

    Matrix pose = Matrix::eye(4);
    string left_img_file_name;
    string right_img_file_name;

    for (int j = 1; j < 3; j++)
    {
      if (j==1)
      {
        char base_name[256]; sprintf(base_name,"%04d.jpg",index1);
        left_img_file_name  = dir + "left/" + base_name;
        right_img_file_name = dir + "right/" + base_name;
      }
      else
      {
        char base_name[256]; sprintf(base_name,"%04d.jpg",index2);
        left_img_file_name  = dir + "left/" + base_name;
        right_img_file_name = dir + "right/" + base_name; 
       
      }
        
      // catch image read/write errors here
      try {

      // load left and right input image
      Mat left_img_src, right_img_src;
      left_img_src = imread(left_img_file_name,CV_LOAD_IMAGE_COLOR);
      right_img_src = imread(right_img_file_name,CV_LOAD_IMAGE_COLOR);

      Mat left_img,right_img;
      cvtColor(left_img_src,left_img,CV_BGR2GRAY);
      cvtColor(right_img_src,right_img,CV_BGR2GRAY);

      int32_t width  = left_img.cols;
      int32_t height = left_img.rows;

      // convert input images to uint8_t buffer
      uint8_t* left_img_data  = (uint8_t*)malloc(width*height*sizeof(uint8_t));
      uint8_t* right_img_data = (uint8_t*)malloc(width*height*sizeof(uint8_t));
      int32_t k=0;
        for (int32_t row=0; row < left_img.rows; row++) {
          for (int32_t col=0; col < left_img.cols; col++) {

            left_img_data[k]  = left_img.at<uchar>(row,col);
            right_img_data[k] = right_img.at<uchar>(row,col);
            k++;
          }
        }

      // status
        cout << "Processing: Frame between: " << index1 << '\t' << index2 << endl;
      
        // compute visual odometry
      int32_t dims[] = {width,height,width};
      //==if (viso.process(left_img_data,right_img_data,dims)) {
      
        viso.process(left_img_data,right_img_data,dims);
        // on success, update current pose

        // output some statistics

        double num_matches = viso.getNumberOfMatches();
        double num_inliers = viso.getNumberOfInliers();
        double inliers_percent = 100.0*num_inliers/num_matches;
        // cout << ", Matches: " << num_matches;
        // cout << ", Inliers: " << inliers_percent << " %" << ", Current pose: " << endl;
        // cout << pose << endl << endl;

         if(j>1 && inliers_percent>30)
        {
          pose = pose * Matrix::inv(viso.getMotion());
          Tr_final = pose;  
          
          free(left_img_data);
          free(right_img_data);

          return true;
        }

        if(j>1 && inliers_percent<=30)
        {
          pose = pose * Matrix::inv(viso.getMotion());

          Tr_final = pose;  
          
          free(left_img_data);
          free(right_img_data);

          return false;
        }

      // release uint8_t buffers
      free(left_img_data);
      free(right_img_data);

      // catch image read errors here
    } 
      catch (...) 
      {
        cerr << "ERROR: Couldn't read input files!" << endl;
        break;
      }
   }

   return false;
}




// Old function using Vectors
void my_libviso2_relative(std::vector<Tr_relative> &Tr_final, std::vector<int> index1, std::vector<int> index2, std::string dir)
{
   // set most important visual odometry parameters
  // for a full parameter list, look at: viso_stereo.h
  VisualOdometryStereo::parameters param;
  
  
  // calibration parameters for sequence 2010_03_09_drive_0019 
  param.calib.f  = 711.9212646484375; // focal length in pixels
  param.calib.cu = 647.0408325195312; // principal point (u-coordinate) in pixels
  param.calib.cv = 360.7899169921875; // principal point (v-coordinate) in pixels
  param.base     = 0.12; // baseline in meters
  
  // init visual odometry
  VisualOdometryStereo viso(param);
  
  // loop through all frames i=0:372
  for (int i=0; i<index1.size(); i++) 
  {

    Matrix pose = Matrix::eye(4);
    Tr_relative r;
    string left_img_file_name;
    string right_img_file_name;

    for (int j = 1; j < 3; j++)
    {
      if (j==1)
      {
        char base_name[256]; sprintf(base_name,"%04d.jpg",index1[i]);
        left_img_file_name  = dir + "left/" + base_name;
        right_img_file_name = dir + "right/" + base_name;
        r.frame1 = index1[i];
      }
      else
      {
        char base_name[256]; sprintf(base_name,"%04d.jpg",index2[i]);
        left_img_file_name  = dir + "left/" + base_name;
        right_img_file_name = dir + "right/" + base_name; 
        r.frame2 = index2[i];
      }
        
      try {

      // load left and right input image
      Mat left_img_src, right_img_src;
      left_img_src = imread(left_img_file_name,CV_LOAD_IMAGE_COLOR);
      right_img_src = imread(right_img_file_name,CV_LOAD_IMAGE_COLOR);

      Mat left_img,right_img;
      cvtColor(left_img_src,left_img,CV_BGR2GRAY);
      cvtColor(right_img_src,right_img,CV_BGR2GRAY);
 
      int32_t width  = left_img.cols;
      int32_t height = left_img.rows;

      // convert input images to uint8_t buffer
      uint8_t* left_img_data  = (uint8_t*)malloc(width*height*sizeof(uint8_t));
      uint8_t* right_img_data = (uint8_t*)malloc(width*height*sizeof(uint8_t));
      int32_t k=0;
        for (int32_t row=0; row < left_img.rows; row++) {
          for (int32_t col=0; col < left_img.cols; col++) {
 
            left_img_data[k]  = left_img.at<uchar>(row,col);
            right_img_data[k] = right_img.at<uchar>(row,col);
            k++;
          }
        }

      // status
        cout << "Processing: Frame between: " << r.frame1 << '\t' << r.frame2 << endl;
      
        // compute visual odometry
        int32_t dims[] = {width,height,width};
      
        viso.process(left_img_data,right_img_data,dims);
        // on success, update current pose

        // output some statistics

        double num_matches = viso.getNumberOfMatches();
        double num_inliers = viso.getNumberOfInliers();
        double inliers_percent = 100.0*num_inliers/num_matches;
        cout << ", Matches: " << num_matches;
        cout << ", Inliers: " << inliers_percent << " %" << ", Current pose: " << endl;
        cout << pose << endl << endl;

         if(j>1 && inliers_percent>30)
        {
          pose = pose * Matrix::inv(viso.getMotion());
          r.transform = pose;
          Tr_final.push_back(r);  

          cout << "i: " << i << '\t' << "j: " << j <<endl << endl;
        }

      // release uint8_t buffers
      free(left_img_data);
      free(right_img_data);

      // catch image read errors here
    } 
      catch (...) 
      {
        cerr << "ERROR: Couldn't read input files!" << endl;
        break;
      }
   }
  }    
}

string my_for_g2o_edge(int id1, int id2, Matrix transform)
{
  stringstream out;

  Matrix aboutX = Matrix::rotMatX(-PI,4);
  Matrix new_tr;

  new_tr = aboutX*transform;
  
  double dx = new_tr.getData(0,3);
  double dz = new_tr.getData(2,3);
  double thetay = atan2(-new_tr.getData(2,0), sqrt(new_tr.getData(2,1)*new_tr.getData(2,1) + new_tr.getData(2,2)*new_tr.getData(2,2)));

  out << "EDGE_SE2 " << id1 <<' '<< id2 <<' '<< -dz <<' '<< -dx <<' '<< thetay <<' '<< "1000 0 0 1000 0 10000" << endl;
  
  return out.str();
}
