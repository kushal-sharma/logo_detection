#include "lib.cpp"
#include "query.h"
#include "flickr.h"

int main(int argc, char *argv[])
{
  string root = argv[1];
  string vocabFile = root + "/cpp_vocab_orb_train_val";
  string hasherFile = root + "/cpp_hash_keys";
  string indexDir = root + "/cpp_index_orb_train_val";
  string targetImg = argv[2];
  string testImg = argv[3];
  string cat = argv[4];
  FlickrReader reader (root);

  vector<string>trainSet;
  loadFile(reader.trainSet, trainSet, root);

  Vocab vocab(vocabFile);

  vector<MinHash> hashers;
  loadHashers(hasherFile, hashers);

  Ptr<ORB> detector = ORB::create();

  cout << "Loading index" << endl;

  map<string, string> index;
  for(string f: trainSet){
    string imgId = reader.getImgId(f);
    string cat = reader.getCategory(f);
    string idxFile = indexDir + "/" + imgId + ".txt";
    loadIndex(idxFile, cat, index);
  }

  Mat img = imread(targetImg);
  Mat d;
  vector<KeyPoint> kp;
  detector->detect(img, kp);
  detector->compute(img, kp, d);
  bow_t bow;
  vocab.bow(d, bow);

  vector<vector<Bundle> >bundles;
  getSketches(bow, kp, hashers, bundles);

  cout << "category = " << cat;
  vector<string>trainIdx, testIdx;
  for(int i = 0 ; i < bundles.size(); i++){
      for(int j =0 ;j < bundles[0].size(); j++){
         string idx = bundles[i][j].index();
         index[idx] = cat;
         trainIdx.push_back(idx);
      }
  }

  img = imread(testImg);
  Mat d2;
  kp.clear();
  detector->detect(img, kp);
  detector->compute(img, kp, d2);
  bow.clear();
  vocab.bow(d2, bow);

  cout << " *** " << endl;
  vector<string>results;
  query(bow, kp, hashers, index, results);

  bundles.clear();
  getSketches(bow, kp, hashers, bundles);
  for(string r: results) cout << r << endl;

  for(int i = 0 ; i < bundles.size(); i++){
      for(int j =0 ;j < bundles[0].size(); j++){
         string idx = bundles[i][j].index();
         testIdx.push_back(idx);
      }
  }
  sort(trainIdx.begin(), trainIdx.end());
  sort(testIdx.begin(), testIdx.end());
  int end = (trainIdx.size() > testIdx.size()) ? trainIdx.size() : testIdx.size();
//  for(int i = 0 ;i < end; i++){
//      if (i < trainIdx.size()) cout << trainIdx[i];
//      cout << ',';
//      if (i < testIdx.size()) cout << testIdx[i];
//      cout << endl;
//  }
  return 0;
}

