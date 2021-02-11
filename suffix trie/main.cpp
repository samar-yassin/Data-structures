
#include <iostream>
using namespace std;


/// linked list part

struct listNode {
	char data;
	struct listNode* child;
};

class linkedList {
	listNode *head;
	int length;

public:
	linkedList() {
		head = nullptr;
		length=0;
	}
	~linkedList() {
		delete head;
	}

	void insert(char c) {
		struct listNode *node = new listNode;
		struct listNode *current = head;
		length++;

		node->data = c;

		node->child = NULL;

		if (head == nullptr) {
			head = node;
			return;
		}

		while (current->child !=NULL)
		{
			current = current->child;
		}

		current->child = node;
	}

	listNode* operator[](int index)
	{
		if (index >= length) {
			return nullptr;
		}

		struct listNode* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->child;
		}

		return current;
	}
	
	string getWord() {
		string s = "";
		struct listNode* current = head;
		while (current!= NULL)
		{
			s += current->data;
			current = current->child;
		}
		return s;
	}
	

};


///suffix part

struct suffixNode {
	linkedList childern;
	int index;

public:
	void insertSuffix(string s, int ind) {
		index = ind;

		for (int i = 0; i < s.length(); i++) {
			char c = s.at(i);
			childern.insert(c);
		}

	}


};

class SuffixTrie
{
	suffixNode nodesArray[265];
	int stringLen;
public:
	SuffixTrie(string s)
	{
		stringLen = s.length();
		for (int i = 0; i < s.length(); i++) {
			nodesArray[i].insertSuffix(s.substr(i), i);
		}
	}

	void Search(string pattern) {
		for (int i = 0; i < stringLen  ; i++) {
			if (nodesArray[i].childern[0]->data == pattern.at(0)) {
				int index = i;
				int achieved = 0;

				for (int j = 0; j < pattern.length(); j++) {
					if (nodesArray[index].childern[j] == nullptr) {
						break;
					}

					if (pattern.at(j) == nodesArray[index].childern[j]->data) {
						achieved++;
					}
				}
				if (achieved == pattern.length())cout << nodesArray[index].index << " ";

			}
		}
		cout << endl;
	}
};







int main()
{
	
	SuffixTrie t("bananabanaba$");

	t.Search("ana"); // Prints: 1 3 7
	t.Search("naba"); // Prints: 4 8


	return 0;

}
