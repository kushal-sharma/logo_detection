#include "lib.cpp"
#include "vocab.h"
#include "flickr.h"
#include "index.h"

int main(int charc, char** argv){
  string root = argv[1];
  string vocabFile = root + "/cpp_vocab_orb_train_val";
  string hasherFile = root + "/cpp_hash_keys";
  string indexDir = root + "/cpp_index_orb_train_val";

  FlickrReader reader(root);
  vector<string> fileSet;
  loadFile(reader.valSet, fileSet, root);
  
  cout << "Loading vocab file " << endl;
  Vocab vocab(vocabFile);
  cout << "Loaded vocab file " << endl;

  vector<MinHash> hashers;
  loadHashers(hasherFile, hashers);

  Ptr<ORB> detector = ORB::create();

  for(string f: fileSet){
      /**
      * Convert to bag of words along with keypoints
      */
     string cat = reader.getCategory(f);
     if(cat == "no-logo")continue;
     Mat d;
     vector<KeyPoint>kp;
     bow_t bow;
     getDesc(f, detector, kp, d);
     vocab.bow(d, bow);

     /**
      * @brief bundles storage to hold bundles for a given image;
      */
     vector<vector<Bundle> >bundles;

     /**
      * @brief getSketches Compute sketch for a given image and store in bundles
      */
     getSketches(bow, kp, hashers, bundles);

     string imgid = reader.getImgId(f);
     cout << "Img Id:" << imgid << endl;
     cout << "Bundles: "<< bundles.size() << endl;
     saveIdx(imgid,
        bundles,
        indexDir);
  }

  return 0;
}
