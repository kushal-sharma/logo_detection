#include "lib.cpp"
#include "hash.h"

int main(int argc, char** argv){
   string root = argv[1];
   cout << "loading hashers .. " << endl;
   string hasherFile = root + "/cpp_hash_keys";
   vector<MinHash> hashers;
   loadHashers(hasherFile, hashers);

   int ksize = 13211905;
   for(int i = 0 ;i < ksize; i++){
       for(auto j = 0 ;j < 4;j ++){
           cout << hashers[j].keys[i] << ' ';
       }
       cout << endl;
   }
   return 0;
}
