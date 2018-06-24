#include "lib.cpp"
int getDesc(const string file, const Ptr<ORB>detector,
                    vector<KeyPoint>& kp, Mat& desc){
  Mat img = imread (file);
  cout <<  "Processing .." << file << endl;
  detector->detect(img, kp);
  detector->compute(img, kp, desc);
  return 0;
}

int getDesc(const vector<string>& files, const Ptr<ORB> detector,
		    vector<vector<KeyPoint> >& kps,
		    vector<Mat>& desc){

  for(int i = 0 ;i < files.size(); i++){
    vector<KeyPoint> kp;
    Mat d;
    getDesc(files[i], detector, kp , d);
    if (kp.size() == 0)
      continue;
    kps.push_back(kp);
    desc.push_back(d);
  }
  return 0;
}

class Vocab{
private:
  string fname;
  FlannBasedMatcher matcher;
public:
  Vocab(const Mat& desc);
  Vocab(string fileName);
  ~Vocab() = default;
  vector<bow_t> match(Mat query);
  int train();
  int load();
  int save(string fileName);
  int bow(const Mat& query, bow_t& bow);
};


Vocab::Vocab(string fileName){
  FileStorage fs;
  cout << "loading " << fileName << endl;
  fs.open(fileName, FileStorage::READ);
  Mat desc;
  fs["vocab"] >> desc;
  matcher = FlannBasedMatcher (makePtr<flann::LshIndexParams>(10, 20, 2));
  matcher.add(desc);
};

Vocab::Vocab(const Mat& desc){
  matcher = FlannBasedMatcher(makePtr<flann::LshIndexParams>(10, 20, 2));
  matcher.add(desc);
}

int Vocab::bow(const Mat& query, bow_t& bow){
  vector<DMatch> matches;
  this->matcher.match(_InputArray(query), matches);
  for(int i = 0 ;i < matches.size(); i++){
    bow.push_back(matches[i].trainIdx);
  }
  return 0;
}
  
int Vocab::load(){
  FileStorage fs;
  fs.open(fname, FileStorage::READ);
  Mat vocab;
  fs["vocab"] >> vocab;
  fs.release();
  matcher.add(vocab);
  return 0;
}
