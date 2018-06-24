#include "lib.cpp"

int loadFile(string fileLoc, vector<string>& vec, string prefix){
  ifstream file;
  string fname;
  file.open(fileLoc);
  while(file.good()){
    file >> fname;
    vec.push_back(prefix + "/" + fname);
  }

  file.close();
  return 0;
}


int split(string s, char delim, vector<string>& v){
  string token = "";
  for(char c : s){
    if (c == delim){
      v.push_back(token);
      token = "";
    }
    else token += c;
  }
  v.push_back(token);
  return 0;
}
