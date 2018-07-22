/*
			���ɸ㶨�����еĶ�������Ŀ
	https://blog.csdn.net/luckyxiaoqiang/article/details/7518888
*/

#include <queue>
#include <list>
#include <xutility> // max

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	BinaryTreeNode()
	{
		m_nValue = 0;
		m_pLeft = NULL;
		m_pRight = NULL;
	}
	BinaryTreeNode(int nVaule)
	{
		m_nValue = nVaule;
		m_pLeft = NULL;
		m_pRight = NULL;
	}
};

// ����������Ĵ���
////////////////////////////////////////
BinaryTreeNode* CreateBiTree(int nDepth)
{
	if (nDepth<=0)
	{
		return NULL;;
	}
	BinaryTreeNode* pNode = new BinaryTreeNode;
	pNode->m_nValue = nDepth;

	pNode->m_pLeft = CreateBiTree(nDepth-1);
	pNode->m_pRight = CreateBiTree(nDepth-1);


	return pNode;
}
////////////////////////////////////////

// ���ʸ��ڵ�

void Visit(BinaryTreeNode* pNode)
{
	printf("%d\n",pNode->m_nValue);
}

// ��������еĽڵ����

int GetNodeNum(BinaryTreeNode *pRoot)
{
	if (pRoot == NULL) // �ݹ����
		return 0;
	return GetNodeNum(pRoot->m_pLeft) + GetNodeNum(pRoot->m_pRight) +1;
}

// ������������

int GetDepth(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)  // �ݹ����
	{
		return 0;
	}
	int depthLeft = GetDepth(pRoot->m_pLeft);
	int depthRight = GetDepth(pRoot->m_pRight);
	return depthLeft > depthRight? depthLeft+1 : depthRight +1;
}

// ǰ�����

void PreOrderTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	Visit(pRoot); // ���ʸ��ڵ�
	PreOrderTraverse(pRoot->m_pLeft);
	PreOrderTraverse(pRoot->m_pRight);
}

// �������

void InOrderTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	InOrderTraverse(pRoot->m_pLeft);
	Visit(pRoot);
	InOrderTraverse(pRoot->m_pRight);
}

// ��������

void PostOrderTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	PostOrderTraverse(pRoot->m_pLeft);
	PostOrderTraverse(pRoot->m_pRight);
	Visit(pRoot);
}

// �ֲ����������

void LevelTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	std::queue<BinaryTreeNode*> q;
	q.push(pRoot);
	while(!q.empty())
	{
		BinaryTreeNode* pNode = q.front();
		q.pop();
		Visit(pNode);
		if (pNode->m_pLeft != NULL)
			q.push(pNode->m_pLeft);
		if (pNode->m_pRight != NULL)
			q.push(pNode->m_pRight);
	}
}


// �������������Ϊ�����˫������

void Convert(BinaryTreeNode * pRoot,BinaryTreeNode *& pFirstNode,BinaryTreeNode*& pLastNode)
{
	BinaryTreeNode* pFirstLeft,*pLastLeft,*pFirstRight,*pLastRight;
	if (pRoot == NULL)
	{
		pFirstNode = NULL;
		pLastNode = NULL;
		return;
	}

	if (pRoot->m_pLeft == NULL)
	{
		// ���������Ϊ�գ���Ӧ˫����������ĵ�һ���ڵ��Ǹ��ڵ�
		pFirstNode = pRoot;
	}
	else
	{
		Convert(pRoot->m_pLeft,pFirstLeft,pLastLeft);
		pFirstNode = pFirstLeft;
		pRoot->m_pLeft = pLastLeft;
		pLastLeft->m_pRight = pRoot;
	}
	
	if (pRoot->m_pRight == NULL)
	{
		pLastNode = pRoot;
	}
	else
	{
		Convert(pRoot->m_pRight,pFirstRight,pLastRight);
		pLastNode = pLastRight;
		pRoot->m_pRight = pFirstRight;
		pFirstRight->m_pLeft  = pRoot;
	}
	return;
}

// ��������K��Ľڵ����

int GetNodeNumKthLevel(BinaryTreeNode* pRoot,int k)
{
	if (pRoot == NULL || k <1)
		return 0;
	if ( k == 1)
		return 1;
	int numLeft = GetNodeNumKthLevel(pRoot->m_pLeft,k-1);
	int numRight = GetNodeNumKthLevel(pRoot->m_pRight,k-1);
	return numLeft + numRight;
}

// ���������Ҷ�ӽڵ�ĸ���

int GetLeafNodeNum(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)
		return 1;
	int numLeft = GetLeafNodeNum(pRoot->m_pLeft);
	int numRight = GetLeafNodeNum(pRoot->m_pRight);
	return numLeft + numRight;
}

// �ж����ö������Ƿ�ṹ��ͬ


bool StructureCmp(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
		return true;
	else if (pRoot1 == NULL || pRoot2 == NULL)
		return false;
	bool resultLeft = StructureCmp(pRoot1->m_pLeft,pRoot2->m_pRight);
	bool resultRight = StructureCmp(pRoot1->m_pRight,pRoot2->m_pRight);
	return resultLeft && resultRight;
}

// �ж϶������ǲ���ƽ�������

bool IsAVL(BinaryTreeNode* pRoot,int & height)
{
	if (pRoot == NULL)
	{
		height = 0;
		return true;
	}
	int heightLeft = 0;
	bool resultLeft = IsAVL(pRoot->m_pLeft,heightLeft);
	int heightRight = 0;
	bool resultRight = IsAVL(pRoot->m_pRight,heightRight);
	if (resultLeft && resultRight  && abs(heightLeft - heightRight) <= 1)
	{
		height = std::max(heightLeft,heightRight) + 1;
		return true;
	}
	else
	{
		height = std::max(heightLeft,heightRight) + 1;
		return false;
	}
}


// ��������ľ���,��ԭ���޸�

BinaryTreeNode * Mirror(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return NULL;
	BinaryTreeNode* pLeft = Mirror(pRoot->m_pLeft);
	BinaryTreeNode* pRight = Mirror(pRoot->m_pRight);

	// ������������
	pRoot->m_pLeft = pRight;
	pRoot->m_pRight = pLeft;
	return pRoot;
}

// ��������������ڵ����͹������Ƚڵ�

bool FindNode(BinaryTreeNode* pRoot,BinaryTreeNode* pNode)
{
	if (pRoot == NULL || pNode == NULL)
		return false;
	if (pRoot == pNode)
		return true;
	bool found = FindNode(pRoot->m_pLeft,pNode);
	if (!found)
		found = FindNode(pRoot->m_pRight,pNode);
	return found;
}

BinaryTreeNode* GetLastCommonParent(BinaryTreeNode* pRoot,BinaryTreeNode* pNode1,
									BinaryTreeNode* pNode2)
{
	if (FindNode(pRoot->m_pLeft,pNode1))
	{
		if (FindNode(pRoot->m_pRight,pNode2))
			return pRoot;
		else
			return GetLastCommonParent(pRoot->m_pLeft,pNode1,pNode2);
	}
	else
	{	
		if (FindNode(pRoot->m_pLeft,pNode2))
			return pRoot;
		else
			return GetLastCommonParent(pRoot->m_pRight,pNode1,pNode2);
	}
}

// �ݹ�ⷨЧ�ʺܵͣ��кܶ��ظ��ı��������濴һ�·ǵݹ�ⷨ��
// �ǵݹ�ⷨ��
// ����Ӹ��ڵ㵽�����ڵ��·����Ȼ���ٱȽ϶�Ӧ·���Ľڵ���У����һ����ͬ�Ľڵ�Ҳ���������ڶ������е���͹������Ƚڵ�

bool GetNodePath(BinaryTreeNode* pRoot,BinaryTreeNode* pNode,
				 std::list<BinaryTreeNode*> & path)
{
	if (pRoot == pNode)
	{
		path.push_back(pRoot);
		return true;
	}
	if (pRoot == NULL)
		return false;
	path.push_back(pRoot);
	bool found = false;
	found = GetNodePath(pRoot->m_pLeft,pNode,path);
	if (!found)
		found = GetNodePath(pRoot->m_pRight,pNode,path);
	if (!found)
		path.pop_back();
	return found;
}

BinaryTreeNode * GetLastCommonParent2(BinaryTreeNode * pRoot,BinaryTreeNode* pNode1,
									  BinaryTreeNode* pNode2)
{
	if (pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;
	std::list<BinaryTreeNode*> path1;
	bool bResult1 = GetNodePath(pRoot,pNode1,path1);
	std::list<BinaryTreeNode*> path2;
	bool bResult2 = GetNodePath(pRoot,pNode2,path2);
	if (!bResult1 || !bResult2)
		return NULL;
	BinaryTreeNode* pLast = NULL;
	std::list<BinaryTreeNode*>::const_iterator iter1 = path1.begin();
	std::list<BinaryTreeNode*>::const_iterator iter2 = path2.begin();
	while(iter1 != path1.end() && iter2 != path2.end())
	{
		if (*iter1 == *iter2)
			pLast = *iter1;
		else
			break;
		iter1++;
		iter2++;
	}
	return pLast;
}

// ��������нڵ��������

int GetMaxDistance(BinaryTreeNode * pRoot, int & maxLeft, int & maxRight)
{
	// maxLeft, �������еĽڵ������ڵ����Զ����
	// maxRight, �������еĽڵ������ڵ����Զ����
	if(pRoot == NULL)
	{
		maxLeft = 0;
		maxRight = 0;
		return 0;
	}
	int maxLL, maxLR, maxRL, maxRR;
	int maxDistLeft, maxDistRight;
	if(pRoot->m_pLeft != NULL)
	{
		maxDistLeft = GetMaxDistance(pRoot->m_pLeft, maxLL, maxLR);
		maxLeft = std::max(maxLL, maxLR) + 1;
	}
	else
	{
		maxDistLeft = 0;
		maxLeft = 0;
	}
	if(pRoot->m_pRight != NULL)
	{
		maxDistRight = GetMaxDistance(pRoot->m_pRight, maxRL, maxRR);
		maxRight = std::max(maxRL, maxRR) + 1;
	}
	else
	{
		maxDistRight = 0;
		maxRight = 0;
	}
	return std::max(std::max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}

// ��ǰ��������к�������������ؽ�������

BinaryTreeNode * RebuildBinaryTree(int* pPreOrder, int* pInOrder, int nodeNum)
{
	if(pPreOrder == NULL || pInOrder == NULL || nodeNum <= 0)
		return NULL;
	BinaryTreeNode * pRoot = new BinaryTreeNode;
	// ǰ������ĵ�һ�����ݾ��Ǹ��ڵ�����
	pRoot->m_nValue = pPreOrder[0];
	pRoot->m_pLeft = NULL;
	pRoot->m_pRight = NULL;
	// ���Ҹ��ڵ�����������е�λ�ã���������У����ڵ����Ϊ���������ұ�Ϊ������
	int rootPositionInOrder = -1;
	for(int i = 0; i < nodeNum; i++)
		if(pInOrder[i] == pRoot->m_nValue)
		{
			rootPositionInOrder = i;
			break;
		}
		if(rootPositionInOrder == -1)
		{
			throw std::exception("Invalid input.");
		}
		// �ؽ�������
		int nodeNumLeft = rootPositionInOrder;
		int * pPreOrderLeft = pPreOrder + 1;
		int * pInOrderLeft = pInOrder;
		pRoot->m_pLeft = RebuildBinaryTree(pPreOrderLeft, pInOrderLeft, nodeNumLeft);
		// �ؽ�������
		int nodeNumRight = nodeNum - nodeNumLeft - 1;
		int * pPreOrderRight = pPreOrder + 1 + nodeNumLeft;
		int * pInOrderRight = pInOrder + nodeNumLeft + 1;
		pRoot->m_pRight = RebuildBinaryTree(pPreOrderRight, pInOrderRight, nodeNumRight);
		return pRoot;
}

//�ж϶������ǲ�����ȫ������
bool IsCompleteBinaryTree(BinaryTreeNode * pRoot)
{
	if(pRoot == NULL)
		return false;
	std::queue<BinaryTreeNode *> q;
	q.push(pRoot);
	bool mustHaveNoChild = false;
	bool result = true;
	while(!q.empty())
	{
		BinaryTreeNode * pNode = q.front();
		q.pop();
		if(mustHaveNoChild) // �Ѿ��������п������Ľڵ��ˣ�������ֵı���ΪҶ�ڵ㣨����������Ϊ�գ�
		{
			if(pNode->m_pLeft != NULL || pNode->m_pRight != NULL)
			{
				result = false;
				break;
			}
		}
		else
		{
			if(pNode->m_pLeft != NULL && pNode->m_pRight != NULL)
			{
				q.push(pNode->m_pLeft);
				q.push(pNode->m_pRight);
			}
			else if(pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
			{
				mustHaveNoChild = true;
				q.push(pNode->m_pLeft);
			}
			else if(pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
			{
				result = false;
				break;
			}
			else
			{
				mustHaveNoChild = true;
			}
		}
	}
	return result;
}