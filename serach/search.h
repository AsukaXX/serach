#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<regex>
#include<io.h>
#include<math.h>
using namespace std;

using similpath_v = vector< pair<string, string>>;
using sum_m = map<string, int>;
using similpath_v_e = pair<string, string>;
using sum_m_e = pair<string, int>;

//getdirctory.cpp
int getDirectory(const string path, vector<string>& dir,const int flag=0);
//searchis.cpp
void searchFile(const vector<string> dir, const string findpath);
//sortid.cpp
sum_m sortWord(const vector<string> dir);
void sortfile(const string id,const string f_n,const string path,sum_m& count);
//simil_count.cpp
similpath_v countsimil(const sum_m sum);
inline int inttostring(const string ss);
sum_m readsum(const string path);
similpath_v similpath(const similpath_v s_path);
double cos_simil(const sum_m& p1, const sum_m& p2,const similpath_v_e& path,set<string>& sameword);
//printresult.cpp
ostream& print(const similpath_v_e path, const double count,ostream& os,const set<string> word);
bool judgestring(string s, const int i, const int size);
//simil_fuction.cpp
inline vector<double> readvector(const sum_m path_v);
inline double max_d(const double l, const double r);
double cos_simil(const sum_m path_v1, const sum_m path_v2);
double dist_simil(const sum_m path_v1, const sum_m path_v2);
double dist_2_simil(const sum_m path_v1, const sum_m path_v2);