#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<io.h>
using namespace std;

using similpath_v = vector< pair<string, string>>;
using sum_m = map<string, int>;
using similpath_v_e = pair<string, string>;
using sum_m_e = pair<string, int>;

void getDirectory(const string path, vector<string>& dir);
void searchFile(const vector<string> dir, const string findpath);
void path(string dir);
sum_m sortWord(const vector<string> dir);
similpath_v countsimil(const sum_m sum);
inline int inttostring(const string ss);
sum_m readsum(const string path);
similpath_v similpath(const similpath_v s_path);
void cos_simil(const sum_m& p1, const sum_m& p2);