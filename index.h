#include "lib.cpp"
#include "hash.h"

template<typename T>
int fTable(vector<T>& v, map<T, size_t>& table){
  for(T vi: v){
    if (table.find(vi) == table.end())
      table[vi] = 1;
    else table[vi] += 1;
  }
  return 0;
}

float getScale(const KeyPoint& kpt)
{
    int octave = kpt.octave & 255;
    int layer = (kpt.octave >> 8) & 255;
    octave = octave < 128 ? octave : (-128 | octave);
    float scale = octave >= 0 ? 1.f/(1 << octave) : (float)(1 << -octave);
    return scale;
}

int loadIndex(string idxFile, string cat, map<string, string>& index){
  string s;
  ifstream file;
  file.open(idxFile);
  while(file.good()){
    file >> s;
    index[s] = cat;
  }
  return 0;
}

int saveIdx(const string imgId,
            vector<vector<Bundle> >& bundles, const string indexDir){
  ofstream file;
  string fname = indexDir + "/" + imgId + ".txt";
  file.open(fname);
  for(auto i = 0; i < bundles.size(); i++){
    for(auto b: bundles[i]){
      file << b.index();
      file << '\n';
    }
  }
  file.close();
  return 0;
}

int getSketches(const bow_t& bow, const vector<KeyPoint>kps,
               vector<MinHash>& hashers, vector<vector<Bundle> >& bundles,
               double smin = 0.5, double smax = 2.0){
    for(auto i = 0; i < kps.size(); i++){
        bow_t Ni;
        for(auto j = 0; j < kps.size(); j++){
            if(i == j) continue;
            /**
              Check norm
              */
            if(cv::norm(kps[i].pt - kps[j].pt) < kps[i].size){
                float si = getScale(kps[i]), sj = getScale(kps[j]);
                float scaleRatio = si / sj;
                /**
                  Check scale
                  */
                if(scaleRatio >= smin && scaleRatio <= smax){
                        Ni.push_back(j);
                }
            }
        }

        vector<Bundle> vb;
        if(Ni.size() == 0)continue;
        for(auto k = 0 ;k < hashers.size(); k++){
            size_t hik = hashers[k].get(Ni);
            vb.push_back(Bundle(bow[i], hik));
        }
        bundles.push_back(vb);
    }
    return 0;
}
