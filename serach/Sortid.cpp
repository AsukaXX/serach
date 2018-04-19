#include"search.h"
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
		head_var_name,
		output_name,
		out_var_name,
		out_sys_name,
		end
	};
	map<string, sort> sortmap;
	sum_m summap;
	sortmap["129"] = system_name;
	sortmap["137"] = headfile_name;
	sortmap["4227"] = out_sys_name;
	sortmap["4233"] = head_var_name;
	sortmap["4097"] = variable_name;
	sortmap["4098"] = output_name;
	sortmap["4099"] = out_var_name;
	sortmap["4225"] = function_name;
	sortmap["4497"] = class_name;
	sortmap["4499"] = class_name;

	for (string st : dir) {
		sum_m count;
		sum_m::iterator co_it;
		rdir = "rmdir /s/q " + st + "\\sort";
		system(rdir.c_str());
		cdir = "md " + st + "\\sort";
		system(cdir.c_str());
		fs.open(st + "\\symbols.txt");
		if (!fs)
			cout << "cannot open file!" << endl;
		while (getline(fs, line)) {
			int i = line.rfind("\t");
			s1 = line.substr(0, i);
			s2 = line.substr(i + 1, line.size());
			switch (sortmap[s2])
			{
			case system_name:
				s2 = "system";
				sortfile(s1,s2, st, count);
				break;
			case headfile_name:
				s2 = "headfile";
				sortfile(s1, s2, st, count);
				break;
			case head_var_name:
				s2 = "headfile";
				sortfile(s1, s2, st, count);
				s2 = "variable";
				sortfile(s1, s2, st, count);
				break;
			case variable_name:
				s2 = "variable";
				sortfile(s1, s2, st, count);
				break;
			case output_name:
				s2 = "output";
				sortfile(s1, s2, st, count);
				break;
			case out_sys_name:
				s2 = "output";
				sortfile(s1, s2, st, count);
				s2 = "system";
				sortfile(s1, s2, st, count);
				break;
			case out_var_name:
				s2 = "output";
				sortfile(s1, s2, st, count);
				s2 = "variable";
				sortfile(s1, s2, st, count);
				break;
			case function_name:
				s2 = "function";
				sortfile(s1, s2, st, count);
				break;
			case class_name:
				s2 = "classn";
				sortfile(s1, s2, st, count);
				break;
			default:
				sortfile(s1, s2, st, count);
				break;
			}
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

void sortfile(const string id,const string f_n,const string path,sum_m& count) {
	ofstream fs_s;
	sum_m::iterator co_it;
	fs_s.open(path + "\\sort" + "\\" + f_n + ".txt", ios::app);
	fs_s << id << endl;
	co_it = count.find(f_n);
	if (co_it == count.end())
		count.insert(sum_m_e(f_n, 1));
	else
		co_it->second++;
	fs_s.close();
}