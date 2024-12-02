#include "bits/stdc++.h"
// #include "debug.h"

using namespace std;

bool validate(vector<int>& v);
void find_safe(vector<vector<int>>& lines);

int main() {

	ifstream f("./data/2.in");
	int num_lines;
	vector<vector<int>> lines;
	string line;
	
	while (getline(f, line)) {
		vector<int> nums;
		stringstream ss(line);
		int n;
		while (ss>>n) {
			nums.push_back(n);
		}
		lines.push_back(nums);
		num_lines++;
	}

	find_safe(lines);
}
	
void find_safe(vector<vector<int>>& lines) {
	int safe = 0;
	for (vector<int>& v: lines) {

		if (validate(v)) {
			safe++;
			continue;
		}
		for (int i = 0; i < v.size(); i++) {
			char c = v[i];
			v.erase(v.begin()+i);
			if (validate(v)) {
				safe++;
				break;
			}
			v.insert(v.begin()+i, 1, c);
		}
	}
	cout << safe << endl;
}

bool validate(vector<int>& v) {
	// Check is increasing
	// Check is decreasing

	// Find sum
	bool increasing = true;
	bool decreasing = true;

	for (int i = 1; i < v.size(); i++) {
		int num = v[i];
		int prev_num = v[i-1];

		if (prev_num > num) {
			increasing = false;
		}
		if (prev_num < num) {
			decreasing = false;
		}
		int diff = abs(prev_num-num);
		if (diff < 1 or diff > 3) {
			return false;
		} 
	}
	return increasing or decreasing;

}