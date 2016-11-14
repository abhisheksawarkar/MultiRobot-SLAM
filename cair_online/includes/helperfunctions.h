
#include <string>
#include <vector>

#include <viso_stereo.h>
#include <vector>
#include <fstream>
#include <sstream> 

#include "filewriter.h"
#include "threadcomm.h"

extern comm mythread_comm;
extern writer mywriter;

#ifndef _HELPER_FINCTIONS_h
#define _HELPER_FINCTIONS_h

// extern bool dloop_wait_flag;
// extern bool viso_wait_flag;
// extern bool loop_write_done;
//extern ofstream myfile1;

// To find number of images in a directory
int listdir(char *dir);

// To find Visual Odometry using libviso2
void my_libviso2(std::vector<Matrix> &myvec1, std::vector<Matrix> &myvec2, std::string dir, int numImg);

// Class to hold relative poses

class Tr_relative
{
    public:
      int frame1;
      int frame2;
      Matrix transform;      

};

// To find relative transformations between loop closing frames
void my_libviso2_relative(std::vector<Tr_relative> &relative, std::vector<int> index1, std::vector<int> index2, std::string dir);

bool my_libviso2_relative(Matrix &Tr_final, int index1, int index2, std::string dir);

std::string my_for_g2o_edge(int id1, int id2, Matrix transform);


#endif
