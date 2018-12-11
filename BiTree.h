//����ƽ�����ڵ�
#include"iostream"
using namespace std;
class Bi_Node
{
public:
	int value;
	int bf;
	Bi_Node *left;
	Bi_Node *right;
	Bi_Node *parent;//ָ���丸�ڵ�
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

//����ƽ����
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

//���뺯��
bool Bi_Tree::insert(int value2)
{
	Bi_Node *_parent = 0;
	Bi_Node *cur = root;
	//�����Ϊ��
	if (0 == root)
	{
		root = new Bi_Node(value2);
		return true;
	}
	else//�ҵ������λ��
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
	cur = new Bi_Node(value2);//�����½ڵ�
	if (_parent->value>value2)
	{
		_parent->left = cur;//�����ɵ��½ڵ����ӵ�����
		cur->parent = _parent;//�����½ڵ㸸�ڵ���Ϣ
	}
	else
	{
		_parent->right = cur;
		cur->parent = _parent;

	}
	while (_parent)
	{
		//����ƽ������
		if (_parent->left == cur)
			_parent->bf--;//�����������ƽ������Ϊ����
		else
			_parent->bf++;
		//����ƽ�����ӣ�ȷ������
		if (_parent->bf == 0)
		{
		}
		else if (_parent->bf == 1 || _parent->bf == -1)//���ݸ����游�ڵ�ƽ������
		{
			cur = _parent;
			_parent = cur->parent;

		}
		else if (_parent->bf == -2)
		{
			if (cur->bf > 0)
			     RotateLR(_parent);//������
			else
			    RotateR(_parent);//����
			break;

		}
		else
		{
			if (cur->bf < 0)
		       RotateRL(_parent);
			else
				RotateL(_parent);
				
			break;//��ת�����������ѭ��
		}
		
    }
}
//����
void  Bi_Tree::RotateL(Bi_Node *&rtl_node) //����Ҫ����parentָ���ֵ����Ҫ����parent��������Ӧ�ô�˫��ָ��
{
	//����ڵ㸸�ڵ���Ϣ
	Bi_Node *father_Node = rtl_node->parent;
	//�����ҽڵ���Ϣ
	Bi_Node *right_Node = rtl_node->right;
	//�����ҽڵ����ڵ���Ϣ
	Bi_Node *right_Node_L = right_Node->left;
	rtl_node->right=right_Node_L;
	if (right_Node_L!=0)
	    right_Node_L->parent = rtl_node;//���Ǹ��ڵ㷢���仯�Ķ��ü�ʱ���¸��ڵ���Ϣ

	right_Node->left = rtl_node;
	rtl_node->parent = right_Node;
	if (father_Node == 0) //˵����ǰ�ĵ��Ѿ����������ĸ�����ôҪ��������ڵ�
	{
		root = right_Node;
		right_Node->parent = 0;

	}
	else if (father_Node->value > right_Node->value)  //����father_Node��right_Node���ж����ұ߻��������
	{
		father_Node->left = right_Node;
		right_Node->parent = father_Node;
	}
	else
	{
		father_Node->right = right_Node;
		right_Node->parent = father_Node;
	}
	//����ƽ������
	rtl_node->bf = 0;
	right_Node->bf = 0 ;
	rtl_node =right_Node;
	//rtl_node = right_Node;
}

//����
void  Bi_Tree::RotateR(Bi_Node *&rtr_node) //����Ҫ����parentָ���ֵ����Ҫ����parent��������Ӧ�ô�˫��ָ��
{
	//����ڵ㸸�ڵ���Ϣ
	Bi_Node *father_Node = rtr_node->parent;
	//������ڵ���Ϣ
	Bi_Node *left_Node = rtr_node->left;
	//������ڵ���ҽڵ���Ϣ
	Bi_Node *left_Node_R = left_Node->right;
	rtr_node->left = left_Node_R;
	if (left_Node_R != 0)
		left_Node_R->parent = rtr_node;//���Ǹ��ڵ㷢���仯�Ķ��ü�ʱ���¸��ڵ���Ϣ

	left_Node->right = rtr_node;
	rtr_node->parent = left_Node;
	if (father_Node == 0) //˵����ǰ�ĵ��Ѿ����������ĸ�����ôҪ��������ڵ�
	{
		root = left_Node;
		left_Node->parent = 0;

	}
	else if (father_Node->value > left_Node->value)  //����father_Node��right_Node���ж����ұ߻��������
	{
		father_Node->left = left_Node;
		left_Node->parent = father_Node;
	}
	else
	{
		father_Node->right = left_Node;
		left_Node->parent = father_Node;
	}
	//����ƽ������
	rtr_node->bf = 0;
	left_Node->bf = 0;
	rtr_node = left_Node;
	//rtl_node = right_Node;
}
//������
void Bi_Tree::RotateLR(Bi_Node *&rtrl_node)
{
	//���游�ڵ���Ϣ
	Bi_Node *father_Node = rtrl_node->parent;
	//������ڵ����Ϣ
	Bi_Node *lleft_Node = rtrl_node->left;
	//������ڵ���ҽڵ���Ϣ����ΪҪ����ڵ�����
	Bi_Node *lleft_Node_R = lleft_Node->right;
	//����ڵ��������
	RotateL(lleft_Node);
	RotateR(rtrl_node);

	//����ƽ������

}
//������
void Bi_Tree::RotateRL(Bi_Node *&rtlr_node)
{
	Bi_Node *rright_Node = rtlr_node->right;
	RotateLR(rright_Node);
	RotateL(rtlr_node);
}

//�����ĸ߶�
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
 
//�ж����Ƿ�ƽ��
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