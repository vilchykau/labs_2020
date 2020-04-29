#include <algorithm>
#include <iostream>
using namespace std;

struct KTNode {
	explicit KTNode(int aVal) : right(nullptr), left(nullptr), info(aVal) {}
	KTNode* right;
	KTNode* left;
	int info;
};
class Tree {
private:
	KTNode* fRoot;
public:
	Tree() :fRoot(nullptr) {}
	void insert(int aVal);
	void erase(int aVal);
	void pre_order(KTNode* p);
	void pre_order();
	void in_order(KTNode* p);
	void in_order();
	void post_order(KTNode* p);
	void post_order();
	bool Length();
	bool Length(KTNode* p, int& radius);
	friend istream& operator>>(istream& in, Tree& t);
};
