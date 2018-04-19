#include"search.h"

similpath_v countsimil(const sum_m sum) {
	sum_m::const_iterator s_it1, s_it2;
	similpath_v similpath;
	sum_m path_v1,path_v2;
	double si = 0.00;
	s_it1 = sum.begin();
	for (; s_it1 != sum.end(); ) {
		slove_v(s_it1->first, path_v1);
		path_v1.insert(sum_m_e("sum", s_it1->second));
		for (s_it2 = ++s_it1; s_it2 != sum.end(); s_it2++) {
			slove_v(s_it2->first, path_v2);
			path_v2.insert(sum_m_e("sum", s_it2->second));
				similpath.push_back(similpath_v_e(s_it1->first, s_it2->first));
		}
	}
	return similpath;
}

inline int inttostring(const string ss) {
	stringstream str_m(ss);
	int i = 0;
	str_m >> i;
	return i;
}

int slove_v(const string path,sum_m& path_v) {
	ifstream count_f;
	enum golb {
		system,
		headfile,
		function,
		classn,
	};
	map<string, golb> count_m;
	count_m["sysytem"] = system;
	count_m["headfile"] = headfile;
	count_m["function"] = function;
	count_m["classn"] = classn;
	count_f.open(path + "\\sort\\count.txt");
	string line, c_name, c_sum;
	while (getline(count_f, line)) {
		int i = line.rfind(" ");
		c_name = line.substr(0, i);
		c_sum = line.substr(i + 1, line.size());
		switch (count_m[c_name]) {
		case system:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case headfile:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case function:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		case classn:
			inster("gol", inttostring(c_sum), path_v);
			inster(c_name, inttostring(c_sum), path_v);
			break;
		default:
			inster("loc", inttostring(c_sum), path_v);
			break;
		}
	}
}

inline void inster(const string n, int i,sum_m& path_v) {
	sum_m::iterator s;
	s = path_v.find(n);
	if (s == path_v.end())
		path_v.insert(sum_m_e(n, i));
	else
		s->second += i;
}

similpath_v similpath(const similpath_v s_path) {
	sum_m path1, path2;
	similpath_v similpath_2;
	set<string> sameword;
	double simil = 0.0;
	for (similpath_v_e s_e : s_path) {
		path1 = readsum(s_e.first);
		path2 = readsum(s_e.second);
		if ((path1.size() > path2.size() ? path1.size() - path2.size() : path2.size() - path1.size()) < 3) {
			int s_t = 0;
			for (sum_m_e p_e : path1) {
				sum_m::iterator p_e2 = path2.find(p_e.first);
				if (p_e2 != path2.end()) {
					double s = (p_e.second > p_e2->second ? (double)p_e2->second / p_e.second : (double)p_e.second / p_e2->second);
					if (s > 0.79f)
						++s_t;
				}
			}
			if ((double)(s_t / (path1.size() > path2.size() ? path1.size() : path2.size())) > 0.79f) {
				similpath_2.push_back(s_e);
				simil = cos_simil(path1, path2, s_e, sameword);
			}
			if (simil > 0.79f)
				print(s_e, simil, cout, sameword);
			//cout << simil << endl;
		}
	}
	//for (string s : sameword)
	//cout << s << endl;
	return similpath_2;
}
double cos_simil(const sum_m& p1, const sum_m& p2, const similpath_v_e& path, set<string>& sameword) {
	ifstream c_fs;
	string f_n;
	int c_s = 0, f_s = 0;
	double	c_f = 0.0;
	set<string> st1;
	set<string>::iterator s;
	sum_m::const_iterator p_n;
	for (sum_m_e p_c : p1) {
		c_s = 0;
		p_n = p2.find(p_c.first);
		if (p_n != p2.end()) {
			c_fs.open(path.first + "\\sort\\" + p_c.first + ".txt");
			while (getline(c_fs, f_n)) {
				st1.insert(f_n);
			}
			c_fs.close();
			c_fs.open(path.second + "\\sort\\" + p_c.first + ".txt");
			while (getline(c_fs, f_n)) {
				s = find(st1.begin(), st1.end(), f_n);
				if (s != st1.end()) {
					sameword.insert(f_n);
				}
				++c_s;
			}
			c_fs.close();
			if ((double)(sameword.size() / (st1.size() > c_s ? st1.size() : c_s)) > 0.79f)
				++f_s;
		}
		st1.clear();
	}
	c_f = (double)(f_s / (p1.size() > p2.size() ? p1.size() : p2.size()));
	if (c_f > 0.79f)
		return c_f;
	else
		return -1.0;
}