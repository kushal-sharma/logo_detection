#include "lib.cpp"
#include "vocab.h"
#include "flickr.h"

using namespace cv;
using namespace std;
int main(int argc, char** argv){
  string root = argv[1];
  string vocabFile = root + "/cpp_vocab_orb_train_val";

  Ptr<ORB>detector = ORB::create();
  FlickrReader reader(root);
  vector<string>fileList;

  loadFile(reader.trainSet, fileList, root);
  loadFile(reader.valSet, fileList, root);

  cout << "computing descriptors" << endl;
  for(string f: fileList){
      string descFile = f + "_orb";
      FileStorage fs(descFile, FileStorage::WRITE);
      vector<KeyPoint> kp;
      Mat d;
      getDesc(f, detector, kp, d);
      fs << "desc" << d;
  }
  Mat vocab;
  for(string f: fileList){
      cout << "Loading .. " << f << endl;
      string descFile = f + "_orb";
      FileStorage fs(descFile, FileStorage::READ);
      Mat d;
      fs["desc"] >> d;
      vocab.push_back(d);
  }

  FileStorage fs(vocabFile, FileStorage::WRITE);
  fs << "vocab" << vocab;
  return 0;
}
