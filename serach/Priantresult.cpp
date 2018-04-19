#include"search.h"

ostream& print(const similpath_v_e path, const double count, ostream& os, const set<string> word) {
	os << path.first << " " << path.second << " " << count << endl;
	vector<string> filepath1, filepath2;
	ifstream f_c1, f_c2;
	getDirectory(path.first, filepath1, 1);
	getDirectory(path.second, filepath2, 1);
	f_c1.open(*filepath1.begin());
	f_c2.open(*filepath2.begin());
	for (string w : word) {
		cout << w << ":" << endl;
		int size = w.size();
		string line;
		while (getline(f_c1, line)) {
			int i = 0;
			do {
				i = line.find(w, i);

				if (i != string::npos) {
					if (judgestring(line, i, size)) {
						cout << "1: " << line << endl;
						break;
					}
					++i;
				}
			} while (i != string::npos);
		}
		while (getline(f_c2, line)) {
			int j = 0;
			do {
				j = line.find(w, j);
				if (j != string::npos) {
					if (judgestring(line, j, size)) {
						cout << "2: " << line << endl;
						break;
					}
					++j;
				}
			} while (j != string::npos);
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
	//cout << i <<" "<<size<< endl;
	if (l.size() != 0)
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
		case'(':
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
	case'&':
		return 1;
	case'\t':
		return 1;
	default:
		return 0;
	}
}