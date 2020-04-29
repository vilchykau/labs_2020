#include "Tree.h"
#include <iostream>

void Tree::pre_order(KTNode* p) {
	if (p) {
		cout << p->info << " ";
		pre_order(p->left);
		pre_order(p->right);
	}
}
void Tree::pre_order() {
	pre_order(fRoot);
}

void Tree::in_order(KTNode* p) {
	if (p) {
		in_order(p->left);
		cout << p->info << " ";
		in_order(p->right);
	}
}
void Tree::in_order() {
	in_order(fRoot);
}

void Tree::post_order(KTNode* p) {
	if (p) {
		post_order(p->left);
		post_order(p->right);
		cout << p->info << " ";
	}
}
void Tree::post_order() {
	post_order(fRoot);
}
void Tree::insert(int aVal) {
	KTNode* p = fRoot;
	KTNode** pp = &fRoot;
	while (p)
	{
		if (aVal < p->info)
		{
			pp = &p->left;
			p = p->left;
		}
		else
		{
			pp = &p->right;
			p = p->right;
		}
	}
	*pp = new KTNode(aVal);
}
void Tree::erase(int aVal) {
	KTNode* p = fRoot;
	KTNode* pprev = fRoot;
	while (p != nullptr && p->info != aVal) {
		if (aVal >= p->info) {
			pprev = p;
			p = p->right;
		}
		else {
			pprev = p;
			p = p->left;
		}
	}

	if (p == nullptr) {
		cout << "Error. Not found.";
		return;
	}

	if (p->left != nullptr && p->right != nullptr) {
		KTNode* p1 = p->right;
		pprev = p;
		while (p1->left) {
			pprev = p1;
			p1 = p1->left;
		}
		swap(p->info, p1->info);

		p = p1;
	}

	if (pprev->right == p) pprev->right = p->right;
	else pprev->left = p->left;

	delete p;
}

bool Tree::Length(KTNode* p, int& radius) {
	if (!p)
	{
		radius = 0;
		return 1;

	}
	else {
		int left;
		int right;
		const bool left_code = Length(p->left, left);
		const bool right_code = Length(p->right, right);
		radius = max(left, right) + 1;
		if (left == right && left_code && right_code)
		{
			return 1;
		}
		else return 0;
	}
}
bool Tree::Length() {
	int radius;
	return Length(fRoot, radius);
}

istream& operator>>(istream& in, Tree& t) {
	int n, a;
	cout << "n=";
	in >> n;
	for (int i = 0; i < n; ++i) {
		in >> a;
		t.insert(a);
	}
	return in;
}

