#include "lib.cpp"
#include "flickr.h"
#include "query.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv){
    /**
   * @brief configuration files required by all files
   * TODO wrap in separate class
   */
  string root = argv[1];
  string vocabFile = root + "/cpp_vocab_orb_train_val";
  string hasherFile = root + "/cpp_hash_keys";
  string indexDir = root + "/cpp_index_orb_train_val";

  map<string, string> index;
  FlickrReader reader(root);
  vector<string> trainSet, testSet, valSet;

  /**
     Load train and test set
   */
  loadFile(reader.trainSet, trainSet, root);
  loadFile(reader.testSet, testSet, root);
  loadFile(reader.valSet, valSet, root);
  /**
     Create SIFT detector
   */
  Ptr<ORB> detector = ORB::create();

  /**
     Load Vocabulary
   */
  Vocab vocab(vocabFile);
  /**
     Load hashers for hashing
   */
  vector<MinHash> hashers;
  loadHashers(hasherFile, hashers);

  /**
     Load index from train set
   */
  cout << "Loading index" << endl;
  for(string f: trainSet){
    string imgId = reader.getImgId(f);
    string cat = reader.getCategory(f);
    string idxFile = indexDir + "/" + imgId + ".txt";
    loadIndex(idxFile, cat, index);
  }
  cout << "Loading done .. " << endl;
  loadFile(reader.valSet, trainSet, root);
  unsigned int acc = 0;
  unsigned int tot = 0;
  unsigned int mfreq = 0;
  for(string f: testSet){

    tot++;
    Mat img = imread(f);
    Mat d;
    vector<KeyPoint> kp;
    detector->detect(img, kp);
    detector->compute(img, kp, d);

    bow_t bow;
    vocab.bow(d, bow);
    vector<string>results;
    map<string, size_t> ftable;
    query(bow, kp, hashers, index, results);

    fTable(results, ftable);
    string cat = reader.getCategory(f);
    cout << f << endl;

    double frac = ftable[cat] * 100 / (1 + (double) results.size());

    int freq = 0;
     string mfreqCat = "";
    for(auto it = ftable.begin(); it!= ftable.end(); it++){
        if(it->second > freq){
            mfreqCat = it->first;
            freq = it->second;
        }
    }

    cout << "Truth = " << cat << ", prediction = " << frac;

    if (frac >= 25.0 ) acc ++;
    if (mfreqCat == cat) mfreq++;

    cout << " Accu = " << (double)acc / (double)tot << ' '
         << " Mfreq = " << (double)mfreq / (double)tot << ' '
         << " most frequent = " << mfreqCat << endl;
  }
  return 0;
}
