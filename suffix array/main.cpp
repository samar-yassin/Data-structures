#include <iostream>
using namespace std;

struct suffixNode {
	int index;
	int rank[2];	
	
};

class SuffixArray {

private:
	struct suffixNode suffixes[265];
	char s[265];
	int len = 0;
public:

	SuffixArray(string str) {
		len = str.length();
		for (int i = 0; i < len; i++)
			s[i] = str.at(i);
		

	}

	void ConstructUsingPrefixDoubling() {
		for (int i = 0; i < len; i++) {
			suffixes[i].index = i;
			suffixes[i].rank[0] = s[i] - 'a';
			if (i + 1 < len )suffixes[i].rank[1] = s[i+1] - 'a';
			else suffixes[i].rank[1] = -1;

		}

		sortArray(suffixes, len);

		struct suffixNode tempsuffixes[265];
		for (int i = 0; i <len; i++) {
			tempsuffixes[i] = suffixes[i];
		}

		int rank = 0;
		suffixes[0].rank[0] = rank;
		for (int i = 1; i < len ; i++) {

			if (tempsuffixes[i].rank[0] == tempsuffixes[i - 1].rank[0] && tempsuffixes[i].rank[1] == tempsuffixes[i - 1].rank[1]) {

				suffixes[i].rank[0] = rank;
			}
			else {
				suffixes[i].rank[0] = ++rank;
			}
		}

		for (int i = 1; i <len; i++) {

			if (suffixes[i].index + 2 < len) {
				int ind = suffixes[i].index + 2;
				suffixNode node;
				for (int j = 0; j <len; j++) {

					if (suffixes[j].index == ind) {
						node = suffixes[j];
					}
				}
				suffixes[i].rank[1] = node.rank[0];
			}
			else {
				suffixes[i].rank[1] = -1;
			}
		}

		sortArray(suffixes, len );


	}


	static void sortArray(suffixNode * suffixes,int len) {
		suffixNode temp;
		for (int i = 0; i <len; i++) {
			for (int j = 0; j <len - 1; j++) {
				if (suffixes[j].rank[1] > suffixes[j + 1].rank[1]) {
					temp = suffixes[j];
					suffixes[j] = suffixes[j + 1];
					suffixes[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len - 1; j++) {
				if (suffixes[j].rank[0] > suffixes[j + 1].rank[0]) {
					temp = suffixes[j];
					suffixes[j] = suffixes[j + 1];
					suffixes[j + 1] = temp;
				}
			}
		}
	}

	void Print() {
		for (int i = 0; i < len; i++) {
			cout << suffixes[i].index << "  ";
		}
	}


};



int main()
{
	SuffixArray t("ACGACTACGATAAC$");

	t.ConstructUsingPrefixDoubling();

	t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

	return 0;

}
