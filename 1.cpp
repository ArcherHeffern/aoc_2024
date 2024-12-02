#include "bits/stdc++.h"
// #include "debug.h"

using namespace std;


int main() {

	ifstream f("./data/1.in");
	int num_lines;
	vector<int> nums1;
	vector<int> nums2;
	int num;
	
	while (f >> num) {
		nums1.push_back(num);
		f>>num;
		nums2.push_back(num);
		num_lines+=2;
	}
	
	unordered_map<int, int> c1;
	unordered_map<int, int> c2;
	for (int i = 0; i < nums1.size(); i++) {
		c1[nums1[i]]++;
		c2[nums2[i]]++;
	}

	int total = 0;
	for (int i = 0 ;i < nums1.size();i ++) {
		total += c2[nums1[i]] * nums1[i];
		// total += c1[nums2[i]] * nums2[i];

	}
	cout << total;
	return 0;
}
