#include"search.h"

void getDirectory(const string path, vector<string>& dir,const int flag=0) {
	long hfile;
	static _finddata_t fileinfo;
	string p;
	//regex r("[.]*+.cpp");
	if ((hfile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if (flag == 0) {
				if (fileinfo.attrib == _A_SUBDIR) {
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
						dir.push_back(p.assign(path).append("\\").append(fileinfo.name));
					}
				}
			}
			if (flag == 1) {
				if (fileinfo.attrib != _A_SUBDIR) {
					if (strcmp(fileinfo.name,"[*.cpp]") == 1)
						dir.push_back(path + "\\" + fileinfo.name);
				}
			}
		} while (_findnext(hfile, &fileinfo) == 0);
	}
	_findclose(hfile);
}

void searchFile(const vector<string> dir,const string findpath) {
	fstream fs;
	for (string sd : dir) {
		fs.open("d:\\t\\Settings.txt", ios::in);
		if (!fs)
			cout << "cannot open file!" << endl;
		string str, mpath;
		vector<string> text;
		while (getline(fs, str)) {
			text.push_back(str);
		}
		fs.close();
		fs.open("d:\\t\\Settings.txt", ios::out);
		text[0] = sd;
		if (text.size() > 3)
			text.pop_back();
		if (text[2] == "0")
			text[2] = "needsReScan";
		for (string s : text) {
			fs << s << endl;
		}
		fs.close();
		system("start \" \" /min \"D:\\t.whe\" d:\\t ");
		//system("d:\\t.whe | (timeout /t 1 >nul & taskkill /f /t /im whereis.exe)");
		system("timeout /t 1 >nul& taskkill /f /t /im whereis.exe");
		mpath = "copy " + findpath + "\\symbols.txt " + sd;
		system(mpath.c_str());

	}
}

void path(string dir) {
	int i = 0;
	while ((i = dir.find("\\", i)) != string::npos) {
		dir.insert(i, "\\");
		i+=2;
	}
}

sum_m sortWord(const vector<string> dir) {
	ifstream fs;
	ofstream fsi;
	string s1, s2, line, cdir, rdir;
	enum sort {
		start,
		class_name,
		variable_name,
		function_name,
		headfile_name,
		system_name,
		stl_name,
		output_name,
		string_name,
		end
	};
	map<string, sort> sortmap;
	sum_m summap;
	sortmap["129"] = system_name;
	sortmap["137"] = headfile_name;
	sortmap["4233"] = stl_name;
	sortmap["4097"] = variable_name;
	sortmap["4098"] = output_name;
	sortmap["4099"] = string_name;
	sortmap["4225"] = function_name;
	sortmap["4497"] = class_name;
	sortmap["4499"] = class_name;

	for (string st : dir) {
		sum_m count;
		sum_m::iterator co_it;
		rdir = "rmdir /s/q " + st + "\\sort";
		system(rdir.c_str());
		cdir = "md "+st+ "\\sort";
		system(cdir.c_str());
		fs.open(st + "\\symbols.txt");
		if (!fs)
			cout << "cannot open file!" << endl;
		while (getline(fs, line)) {
			int i = line.rfind("\t");
			s1 = line.substr(0,i);
			s2 = line.substr(i + 1, line.size());
			switch (sortmap[s2])
			{
			case system_name:
				s2 = "system";
				break;
			case headfile_name:
				s2 = "headfile";
				break;
			case stl_name:
				s2 = "stl";
				break;
			case variable_name:
				s2 = "variable";
				break;
			case output_name:
				s2 = "output";
				break;
			case string_name:
				s2 = "string";
				break;
			case function_name:
				s2 = "function";
				break;
			case class_name:
				s2 = "class";
				break;
			default:
				break;
			}
			fsi.open(st +"\\sort"+"\\"+ s2 + ".txt",ios::app);
			fsi << s1 << endl;
			co_it = count.find(s2);
if (co_it == count.end())
count.insert(sum_m_e(s2, 1));
else
co_it->second++;
fsi.close();
		}
		fs.close();
		cout << st << " sort finished!" << endl;
		int sum = 0;
		fsi.open(st + "\\sort\\count.txt", ios::trunc);
		for (sum_m_e i : count) {
			fsi << i.first << " " << i.second << endl;
			sum += i.second;
		}
		fsi.close();
		summap.insert(sum_m_e(st, sum));
		cout << st << " count finished!" << endl;
	}
	return summap;
}

similpath_v countsimil(const sum_m sum) {
	sum_m::const_iterator s_it1, s_it2;
	similpath_v similpath;
	string path_m;
	int s1 = 0, s2 = 0;
	double si = 0.00;
	s_it1 = sum.begin();
	for (; s_it1 != sum.end(); ) {
		path_m = s_it1->first;
		s1 = s_it1->second;
		for (s_it2 = ++s_it1; s_it2 != sum.end(); s_it2++) {
			s2 = s_it2->second;
			si = (double)(s2 > s1 ? s1 / s2 : s2 / s1);
			cout << s1 << " " << s2 << " " << si << endl;
			if (si > 0.79f)
				similpath.push_back(similpath_v_e(path_m, s_it2->first));
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

sum_m readsum(const string path) {
	sum_m e_path;
	ifstream count_f;
	count_f.open(path + "\\sort\\count.txt");
	string line, c_name, c_sum;
	while (getline(count_f, line)) {
		int i = line.rfind(" ");
		c_name = line.substr(0, i);
		c_sum = line.substr(i + 1, line.size());
		e_path.insert(sum_m_e(c_name, inttostring(c_sum)));
	}
	return e_path;
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
					double s = (double)(p_e.second > p_e2->second ? p_e2->second / p_e.second : p_e.second / p_e2->second);
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

ostream& print(const similpath_v_e path, const double count, ostream& os, const set<string> word) {
	os << path.first << " " << path.second << " " << count << endl;
	vector<string> filepath1, filepath2;
	ifstream f_c1, f_c2;
	getDirectory(path.first, filepath1, 1);
	getDirectory(path.second, filepath2, 1);
	f_c1.open(*filepath1.begin());
	f_c2.open(*filepath2.begin());
	for(string w : word){
		cout << w << ":" << endl;
		int size = w.size();
		string line;
		while (getline(f_c1, line)) {
			int i = line.find(w);
			if (i != string::npos) {
				if(judgestring(line,i,size))
					cout << line << endl;
			}
		}
		while (getline(f_c2, line)) {
			int j = line.find(w);
			if (j != string::npos) {
				if (judgestring(line, j, size))
					cout << line << endl;
			}
		}
		f_c1.clear();
		f_c1.seekg(0, ios::beg);
		f_c2.clear();
		f_c2.seekg(0, ios::beg);
}
	return os;
}

bool judgestring(string s, const int i, const int size) {
	string l, r;
	if (i == 0)
		r = s.substr(i + size, 1);
	else {
		l = s.substr(i - 1, 1);
		r = s.substr(i + size, 1);
	}
	//cout << s.substr(i - 1, i) << *r << endl;
	if(l.size()!=0)
		switch (l[0]) {
		case'<':
			break;
		case' ':
			break;
		case'&':
			break;
		case'*':
			break;
		case'\t':
			break;
		case'=':
			break;
		case',':
			break;
		case'#':
			break;
		case':':
			break;
		case'"':
			break;
		default:
			return 0;
		}
	switch (r[0]) {
	case'<':
		return 1;
	case'>':
		return 1;
	case'=':
		return 1;
	case';':
		return 1;
	case' ':
		return 1;
	case'(':
		return 1;
	case':':
		return 1;
	case')':
		return 1;
	case',':
		return 1;
	case'"':
		return 1;
	case'{':
		return 1;
	default:
		return 0;
	}
}

double cos_simil(const sum_m& p1,const sum_m& p2,const similpath_v_e& path,set<string>& sameword) {
	ifstream c_fs;
	string f_n;
	int c_s = 0, f_s = 0;
	double	c_f=0.0;
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

int main() {
	string findPath;
	vector<string> scanDir;
	sum_m sum_map;
	similpath_v similPath,similPath_2;
	cin >> findPath;
	getDirectory(findPath, scanDir);
	searchFile(scanDir, findPath);
	sum_map = sortWord(scanDir);
	similPath = countsimil(sum_map);
	if (similPath.size() != 0)
		similPath_2 = similpath(similPath);
	
	return 0;
}