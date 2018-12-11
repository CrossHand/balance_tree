#include "BiTree.h"

void main()
{

	Bi_Tree tree1;
	//tree1.insert(1);
	//tree1.insert(2);
	//tree1.insert(3);
	//tree1.insert(4);
	//tree1.insert(5);
	//tree1.insert(6);
	tree1.insert(10);
	tree1.insert(7);
	tree1.insert(12);
	tree1.insert(5);
	tree1.insert(6);
	tree1.insert(13);
	cout << tree1.GetDepth() << endl;
	if (tree1.isBalance())
		cout << "The tree is Balanced!" << endl;
	else
		cout << "The tree is not balanced!" << endl;
}