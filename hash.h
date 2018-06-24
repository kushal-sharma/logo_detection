#include "lib.cpp"

class MinHash{
private:
public:
  vector<double>keys;
  MinHash(size_t keysize, size_t seed);
  uint get(bow_t bow);
};


MinHash::MinHash(size_t keysize, size_t seed){
    cout << "keysize = " << keysize << endl;
  default_random_engine generator(seed);
  uniform_real_distribution<double> dist(0,1);
  for(size_t i = 0 ;i < keysize; i++){
    keys.push_back(dist(generator));
  }

}

word_t MinHash::get(bow_t bow){
  double val = 2.0;
  word_t key = 0;
  for(auto b : bow) {
      if (keys[b] < val) {
          key = b;
          val = keys[b];
      }
  }
  return key;
}

class Bundle{
private:
  size_t first;
  size_t second;
public:
  Bundle(size_t first, size_t second);
  ~Bundle() = default;
  size_t getFirst();
  size_t getSecond();
  string index();
};



Bundle::Bundle(size_t first, size_t second):
  first(first),
  second(second){}

string Bundle::index(){
  ostringstream _min;
  ostringstream _max;
  _min << min(first, second);
  _max << max(first, second);
  return _min.str() + "_" + _max.str();
}

size_t Bundle::getFirst(){
  return this->first;
}


size_t Bundle::getSecond(){
  return this->second;
}

void loadHashers(string seedFile, vector<MinHash>& hashers){
    ifstream file;
    file.open(seedFile);
    size_t seed;
    size_t keysize;
    size_t n;

    file >> keysize;
    file >> n;
    cout << keysize << ' ' << n << endl;
    for(int i = 0 ;i < n; i++){
        file >> seed;
        cout << seed << endl;
        hashers.push_back(MinHash(keysize, seed));
    }
}

