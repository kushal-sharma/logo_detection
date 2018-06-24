#include<iostream>
#include<string>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<iterator>
#include<random>
#include<algorithm>
#include<boost/filesystem.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

namespace Bfs = boost::filesystem;

typedef unsigned int word_t;
typedef vector<word_t> bow_t;







