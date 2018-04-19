#include"search.h"
void searchFile(const vector<string> dir, const string findpath) {
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