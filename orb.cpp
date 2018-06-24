#include "lib.cpp"
#include "flickr.h"
#include "query.h"

using namespace std;
int main(int argc, char** argv){
  Mat img = imread(argv[1]);
  Mat dst;
//  boundRotate(img, dst, 30);
  Ptr<ORB> orb = ORB::create();
  vector<KeyPoint>kps;
  Mat desc;
  orb->detect(img, kps);
  drawKeypoints(img, kps, dst);
  imwrite(argv[2], dst);
  return 0;
}
