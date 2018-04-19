#include"search.h"

int getDirectory(const string path, vector<string>& dir, const int flag) {
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
					if (strcmp(fileinfo.name, "[*.cpp]") == 1)
						dir.push_back(path + "\\" + fileinfo.name);
				}
			}
		} while (_findnext(hfile, &fileinfo) == 0);
	}
	else {
		cout << "no have" << endl;
		return 0;
	}
	_findclose(hfile);
	return 1;
}