#include"search.h"

int main() {
	string findPath;
	vector<string> scanDir;
	sum_m sum_map;
	similpath_v similPath, similPath_2;
	do {
		cin >> findPath;
	} while (!getDirectory(findPath, scanDir));
	searchFile(scanDir, findPath);
	sum_map = sortWord(scanDir);
	similPath = countsimil(sum_map);
	if (similPath.size() != 0)
		similPath_2 = similpath(similPath);
	
	return 0;
}