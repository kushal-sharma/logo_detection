// TODO add query augmentation
#include "lib.cpp"
#include "index.h"
#include "vocab.h"

int matchIdx(vector<vector<Bundle> >& bundles,
             map<string, string>& index,
             vector<string>& matches,
             int k){
  for(auto i = 0 ;i < bundles.size(); i++){
    vector<string> m;
    for(auto b : bundles[i]){
      string idx = b.index();
      if (index.find(idx) != index.end())
        m.push_back(index[idx]);
    }

    map<string, size_t> freq;
    fTable(m, freq);
    for(auto it = freq.begin(); it != freq.end(); it++){
        matches.push_back(it->first);
    }
  }
  return 0;
}

int query(bow_t& bow, vector<KeyPoint>& vkp, vector<MinHash>& hashers,
          map<string, string>& index, vector<string>& results){
  vector<vector<Bundle> >vbundle;
  getSketches(bow, vkp, hashers, vbundle);
  matchIdx(vbundle, index, results, 2);
  return 0;
}

void boundRotate(const Mat& src, Mat& dst, double angle){
    Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    rot.at<double>(0,2) += bbox.width/2.0 - src.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - src.rows/2.0;
    warpAffine(src, dst, rot, bbox.size());
}

int query(const Mat& img, Vocab& vocab,
          map<string, string>& index, Ptr<ORB> detector, vector<MinHash>& hashers,
          vector<string>& results, double thetaMin = -30, double thetaMax = 30){
    for(double theta = thetaMin; theta <= thetaMax; theta += 5.0){
        Mat dst;
        boundRotate(img, dst, theta);

        Mat desc;
        vector<KeyPoint> kp;

        detector->detect(img, kp);
        detector->compute(img, kp, desc);
        bow_t bow;

        vocab.bow(desc, bow);
        query(bow, kp, hashers, index, results);
    }
    return 0;
}

string mostFrquent(map<string, size_t>& results){
    return 0;
}

