//定义平衡树节点
#include"iostream"
using namespace std;
class Bi_Node
{
public:
	int value;
	int bf;
	Bi_Node *left;
	Bi_Node *right;
	Bi_Node *parent;//指向其父节点
	Bi_Node();
	Bi_Node(int value1);
};
Bi_Node::Bi_Node()
{
	value = 0;
	bf = 0;
	left = right = parent = 0;
}
Bi_Node::Bi_Node(int value1)
{
	value = value1;
	bf = 0;
	left = right = parent = 0;
}

//定义平衡树
class Bi_Tree
{
private:
	int GetDepth(Bi_Node *gdp);
	bool isBalance(Bi_Node *idp);
public:
	Bi_Node *root;
	Bi_Tree();
	bool insert(int value2);
	void RotateL(Bi_Node *&rtl_node); 
	void RotateR(Bi_Node *&rtr_node);
	void RotateLR(Bi_Node *&rtrl_node0);
	void RotateRL(Bi_Node *&rtlr_node);
	int GetDepth();
	bool isBalance();
	
};
Bi_Tree::Bi_Tree()
{
	root = 0;
}

//插入函数
bool Bi_Tree::insert(int value2)
{
	Bi_Node *_parent = 0;
	Bi_Node *cur = root;
	//如果树为空
	if (0 == root)
	{
		root = new Bi_Node(value2);
		return true;
	}
	else//找到插入的位置
	{
		
		while (cur)
		{
			if (cur->value > value2)
			{
				_parent = cur;
				cur = cur->left;
			}
			else if (cur->value < value2)
			{
				_parent = cur;
				cur = cur->right;

			}

			else return false;
		}

	}
	cur = new Bi_Node(value2);//生成新节点
	if (_parent->value>value2)
	{
		_parent->left = cur;//将生成的新节点连接到树上
		cur->parent = _parent;//保存新节点父节点信息
	}
	else
	{
		_parent->right = cur;
		cur->parent = _parent;

	}
	while (_parent)
	{
		//更新平衡因子
		if (_parent->left == cur)
			_parent->bf--;//如果左树多则平衡因子为负数
		else
			_parent->bf++;
		//检验平衡因子，确定操作
		if (_parent->bf == 0)
		{
		}
		else if (_parent->bf == 1 || _parent->bf == -1)//回溯更新祖父节点平衡因子
		{
			cur = _parent;
			_parent = cur->parent;

		}
		else if (_parent->bf == -2)
		{
			if (cur->bf > 0)
			     RotateLR(_parent);//左右旋
			else
			    RotateR(_parent);//右旋
			break;

		}
		else
		{
			if (cur->bf < 0)
		       RotateRL(_parent);
			else
				RotateL(_parent);
				
			break;//旋转完毕立即跳出循环
		}
		
    }
}
//左旋
void  Bi_Tree::RotateL(Bi_Node *&rtl_node) //除了要更新parent指向的值，还要更新parent本身所以应该传双重指针
{
	//保存节点父节点信息
	Bi_Node *father_Node = rtl_node->parent;
	//保存右节点信息
	Bi_Node *right_Node = rtl_node->right;
	//保存右节点的左节点信息
	Bi_Node *right_Node_L = right_Node->left;
	rtl_node->right=right_Node_L;
	if (right_Node_L!=0)
	    right_Node_L->parent = rtl_node;//凡是父节点发生变化的都得及时更新父节点信息

	right_Node->left = rtl_node;
	rtl_node->parent = right_Node;
	if (father_Node == 0) //说明当前的点已经是整棵树的根，那么要重新设根节点
	{
		root = right_Node;
		right_Node->parent = 0;

	}
	else if (father_Node->value > right_Node->value)  //连接father_Node与right_Node，判断连右边还是连左边
	{
		father_Node->left = right_Node;
		right_Node->parent = father_Node;
	}
	else
	{
		father_Node->right = right_Node;
		right_Node->parent = father_Node;
	}
	//重设平衡因子
	rtl_node->bf = 0;
	right_Node->bf = 0 ;
	rtl_node =right_Node;
	//rtl_node = right_Node;
}

//右旋
void  Bi_Tree::RotateR(Bi_Node *&rtr_node) //除了要更新parent指向的值，还要更新parent本身所以应该传双重指针
{
	//保存节点父节点信息
	Bi_Node *father_Node = rtr_node->parent;
	//保存左节点信息
	Bi_Node *left_Node = rtr_node->left;
	//保存左节点的右节点信息
	Bi_Node *left_Node_R = left_Node->right;
	rtr_node->left = left_Node_R;
	if (left_Node_R != 0)
		left_Node_R->parent = rtr_node;//凡是父节点发生变化的都得及时更新父节点信息

	left_Node->right = rtr_node;
	rtr_node->parent = left_Node;
	if (father_Node == 0) //说明当前的点已经是整棵树的根，那么要重新设根节点
	{
		root = left_Node;
		left_Node->parent = 0;

	}
	else if (father_Node->value > left_Node->value)  //连接father_Node与right_Node，判断连右边还是连左边
	{
		father_Node->left = left_Node;
		left_Node->parent = father_Node;
	}
	else
	{
		father_Node->right = left_Node;
		left_Node->parent = father_Node;
	}
	//重设平衡因子
	rtr_node->bf = 0;
	left_Node->bf = 0;
	rtr_node = left_Node;
	//rtl_node = right_Node;
}
//左右旋
void Bi_Tree::RotateLR(Bi_Node *&rtrl_node)
{
	//保存父节点信息
	Bi_Node *father_Node = rtrl_node->parent;
	//保存左节点的信息
	Bi_Node *lleft_Node = rtrl_node->left;
	//保存左节点的右节点信息，因为要对左节点左旋
	Bi_Node *lleft_Node_R = lleft_Node->right;
	//对左节点进行左旋
	RotateL(lleft_Node);
	RotateR(rtrl_node);

	//重设平衡因子

}
//右左旋
void Bi_Tree::RotateRL(Bi_Node *&rtlr_node)
{
	Bi_Node *rright_Node = rtlr_node->right;
	RotateLR(rright_Node);
	RotateL(rtlr_node);
}

//求树的高度
int Bi_Tree::GetDepth()
{
	return GetDepth(root);
}
int Bi_Tree::GetDepth(Bi_Node *gdp)
{
	if (gdp == 0)
		return 0;
	
	
   int left_depth = GetDepth(gdp->left);
  int right_depth = GetDepth(gdp->right);

  return (left_depth > right_depth) ? (left_depth + 1) : (right_depth + 1);

}
 
//判断树是否平衡
bool Bi_Tree::isBalance()
{
	return isBalance(root);
}
bool Bi_Tree::isBalance(Bi_Node *ibp)
{ 
	if (ibp == 0)  return true;
    else if (ibp->bf > -2 && ibp->bf < 2 && isBalance(ibp->left) && isBalance(ibp->right))
		 return true;
	     else
		 return false;
}