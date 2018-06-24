#include "lib.cpp"
#include "utils.h"

class FlickrReader{
public:
  FlickrReader(string root);
  string root;
  string trainSet;
  string valSet;
  string testSet;
  string getImgId(string path);
  string getCategory(string path);
};


FlickrReader::FlickrReader(string root){
  this->root = root;
  this->trainSet = this->root + "/trainset.relpaths.txt";
  this->testSet = this->root + "/testset.relpaths.txt";
  this->valSet = this->root + "/valset.relpaths.txt";
}

string FlickrReader::getImgId(string path){
  vector<string>sp;
  split(path, '/', sp);
  string s= sp[sp.size() - 1];
  sp.clear();
  split(s, '.', sp);
  return sp[sp.size() - 2];

}

string FlickrReader::getCategory(string path){
  vector<string>sp;
  split(path, '/', sp);
  return sp[sp.size() - 2];
}
