This program executes Libviso, DLoop and g2o in parallel threads for trajectory estimation and optimization using stereo vision.

Procedure -

1. Install 

   a. Libviso2 - http://www.cvlibs.net/software/libviso/

   b. DLoop - https://github.com/dorian3d/DLoopDetector (along with DLib and DBow2)

   c. g2o - https://github.com/RainerKuemmerle/g2o


2. cd cair_online/ 
3. mkdir build
4. cd build
5. cmake ..
6. make -j5
7. ./main


<-------------------------------->

Source code - main.cpp

Supporting files - src/*.cpp

Header files - includes/*.h

<-------------------------------->

Main function calls -

1. Libviso2 for intial trajectory estimates from src/helper.cpp - my_libviso2

2. DLoop Detector for loop closure from includes/demoDetector.h - run

3. g2o is called after every 500th frame and once at the end of trajectory.

<-------------------------------->

Parameters - 

In main function 

1. IMG_DIR1 - Directory where Images are stored. Format -> dir/loop1/left and dir/loop1/right

2. VOC_FILE - Vocabulary file. Generated from DBOW2

3. IMAGE_W, IMAGE_H - Image Width, Image Height - Keep default.

In helperfunctions.cpp

1. param.calib.f  - focal length in pixels
   param.calib.cu - principal point (u-coordinate) in pixels
   param.calib.cv - principal point (v-coordinate) in pixels
   param.base     - baseline in meters

In demoDetector.h

1. params.use_nss    - use normalized similarity score instead of raw score
   params.alpha      - nss threshold
   params.k          - a loop must be consistent with 1 previous matches
   params.geom_check - use direct index for geometrical checking
   params.di_levels  - use two direct index levels

In TemplatedLoopDetector.h

1. dislocal = number * f - for skipping 'number' of frames between loops.

