#pragma once
#include"BiTree.h"
#include"implement/linkList/LinkList.h"

namespace Hella {
	template <typename ElemType>
	struct BiTNode
	{
		ElemType data = -1;
		BiTNode<ElemType>* lchild = NULL;
		BiTNode<ElemType>* rchild = NULL;
	};

	template <typename ElemType>
	class BiLinkBiTree : public BiTree<ElemType>
	{
	public:
		// 通过 BiTree 继承
		virtual Status Init() override;
		virtual Status Create(ElemType* e, ElemType format, ElemType type = 0) override;
		virtual Status Destroy() override;
		virtual Status Clear() override;
		virtual Status IsEmpty() override;
		virtual Status Depth(int& depth) override;
		virtual Status Length(int& len) override;
		virtual Status Value(Position p, ElemType& e) override;
		virtual Status Assign(Position p, ElemType value) override;
		virtual Status Root(ElemType& e) override;
		virtual Status Parent(ElemType e, ElemType& parent) override;
		virtual Status LeftChild(ElemType e, ElemType& lchild) override;
		virtual Status RightChild(ElemType e, ElemType& rchild) override;
		virtual Status LeftSibling(ElemType e, ElemType& lsibling) override;
		virtual Status RightSibling(ElemType e, ElemType& rsibling) override;
		virtual Status PreOrderTraverse(void(*visit)(ElemType&)) override;
		virtual Status InOrderTraverse(void(*visit)(ElemType&)) override;
		virtual Status PostOrderTraverse(void(*visit)(ElemType&)) override;
		virtual Status LevelOrderTraverse(void(*visit)(ElemType&)) override;
		virtual Status GetElemByIndex(int, ElemType&) override;
	private:
		Status ClearRec(BiTNode<ElemType>* &);
		Status DepthRec(BiTNode<ElemType>*,int&);
		Status CreateRec(ElemType* &e, ElemType format, BiTNode<ElemType>* &node);
		Status PreOrderTraverseRec(void(*visit)(ElemType&),BiTNode<ElemType>*);
		Status InOrderTraverseRec(void(*visit)(ElemType&),BiTNode<ElemType>*);
		Status PostOrderTraverseRec(void(*visit)(ElemType&),BiTNode<ElemType>*);
		Status AssignRec(Position p,ElemType value, BiTNode<ElemType>* node, int index);
		BiTNode<ElemType>* m_Root;
	};
}




namespace Hella {

	/*
		@F:根据完全二叉树的序数值获取节点值。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::GetElemByIndex(int index, ElemType& e)
	{
		int len; Length(len);
		if (index < 0 || index >= len)
			return Status::HELLA_INFEASIBLE;
		index++;
		BiTNode<ElemType> node[100] = {};
		ElemType data[100] = {};
		int i = 0;


		if (m_Root) {
			node[0] = { 1,m_Root->lchild,m_Root->rchild };
			data[0] = m_Root->data;
			if (index == 1) {
				e = data[0];
				return Status::HELLA_OK;
			}
			while (i >= 0) {
				while (node[i].lchild) {
					node[i + 1] = { 2 * node[i].data,node[i].lchild->lchild,node[i].lchild->rchild };
					data[i + 1] = node[i].lchild->data;
					node[i].lchild = NULL;
					i++;
					if (node[i].data == index) {
						e = data[i];
						return Status::HELLA_OK;
					}
				}
				if (node[i].rchild) {
					node[i + 1] = { 2 * node[i].data + 1,node[i].rchild->lchild,node[i].rchild->rchild };
					data[i + 1] = node[i].rchild->data;
					node[i].rchild = NULL;
					i++;
					if (node[i].data == index) {
						e = data[i];
						return Status::HELLA_OK;
					}
				}
				if (!node[i].lchild && !node[i].rchild)
					i--;
			}
		}
		e = -1;
		return Status::HELLA_OK;
	}

	/*
		@F:递归清除节点。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::ClearRec(BiTNode<ElemType>* &node)
	{
		if (node) {
			ClearRec(node->lchild);
			ClearRec(node->rchild);

			HELLA_FREE(node);
			node = NULL;
		}
		return Status::HELLA_OK;
	}

	/*
		@F:获取深度。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::DepthRec(BiTNode<ElemType>* node, int& depth)
	{
		int ldepth, rdepth;
		if (!node) {
			depth = 0;
		}
		else {
			DepthRec(node->lchild,ldepth);
			DepthRec(node->rchild, rdepth);
			depth = (ldepth > rdepth ? ldepth : rdepth) + 1;
		}
		return Status::HELLA_OK;
	}

	/*
		@F:递归创建二叉树。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::CreateRec(ElemType* &e, ElemType format, BiTNode<ElemType>* &node)
	{
		if (!e) {
			return Status::HELLA_ERROR;
		}
		ElemType v = e[0];
		e++;
		if (v == format) {
			node = NULL;

		}
		else {
			node = HELLA_MALLOC(1, BiTNode<ElemType>);
			HELLA_ASSERT_MEMORY_MALLOC(node);
			node->data = v;
			CreateRec(e,format, node->lchild);
			CreateRec(e,format, node->rchild);
		}
		return Status::HELLA_OK;
	}
	
	
	/*
		@F:递归先序遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::PreOrderTraverseRec(void(*visit)(ElemType&), BiTNode<ElemType>* node)
	{
		if (node) {
			visit(node->data);
			PreOrderTraverseRec(visit,node->lchild);
			PreOrderTraverseRec(visit, node->rchild);
		}
		return Status::HELLA_OK;
	}
	
	/*
		@F:递归中序遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::InOrderTraverseRec(void(*visit)(ElemType&), BiTNode<ElemType>* node)
	{
		if (node) {
			PreOrderTraverseRec(visit, node->lchild);
			visit(node->data);
			PreOrderTraverseRec(visit, node->rchild);
		}
		return Status::HELLA_OK;
	}
	
	/*
		@F:递归后序遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::PostOrderTraverseRec(void(*visit)(ElemType&), BiTNode<ElemType>* node)
	{
		if (node) {
			PreOrderTraverseRec(visit, node->lchild);
			PreOrderTraverseRec(visit, node->rchild);
			visit(node->data);
		}
		return Status::HELLA_OK;
	}

	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::AssignRec(Position p, ElemType value, BiTNode<ElemType>* node, int index)
	{
		if (node) {

			if (index == std::pow(2, p.level - 1)  - 1 + p.order) {
				node->data = value;	
			}
			AssignRec(p, value, node->lchild, index * 2);
			AssignRec(p, value, node->rchild, index * 2 + 1);
		}
		return Status::HELLA_OK;
	}
	
	/*
		@F:初始化。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Init()
	{
		m_Root = NULL;
		return Status::HELLA_OK;
	}
	
	/*
		@F:创建。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Create(ElemType* e, ElemType format, ElemType type)
	{
		return CreateRec(e, format, m_Root);
	}
	
	/*
		@F:摧毁。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Destroy()
	{
		m_Root = NULL;
		return Status::HELLA_OK;
	}
	
	/*
		@F:清除。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Clear()
	{
		return ClearRec(m_Root);
	}

	/*
		@F:是否为空。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::IsEmpty()
	{
		if (m_Root) {
			return Status::HELLA_FALSE;
		}
		return Status::HELLA_TRUE;
	}

	/*
		@F:深度。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Depth(int& depth)
	{
		return DepthRec(m_Root, depth);
	}

	/*
		@F:求二叉树的长度（其完全二叉树形态的长度）
		@D:遍历时更新长度即可。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Length(int& len)
	{
		BiTNode<ElemType> node[100] = {};
		int i = 0, length = 0;
		if (m_Root) {
			node[0] = { 1,m_Root->lchild,m_Root->rchild };
			length++;
			while (i >= 0) {
				while (node[i].lchild) {
					node[i + 1] = { 2 * node[i].data,node[i].lchild->lchild,node[i].lchild->rchild };
					node[i].lchild = NULL;
					i++;
					if (node[i].data > length) {
						length = node[i].data;
					}
				}
				if (node[i].rchild) {
					node[i + 1] = { 2 * node[i].data + 1,node[i].rchild->lchild,node[i].rchild->rchild };
					node[i].rchild = NULL;
					i++;
					if (node[i].data > length) {
						length = node[i].data;
					}
				}
				if (!node[i].lchild && !node[i].rchild)
					i--;
			}
		}
		len = length;
		return Status::HELLA_OK;
	}

	/*
		@F:根据深度，序号取值。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Value(Position p, ElemType& e)
	{
		if (p.level < 1 || p.order < 1)
			return Status::HELLA_INFEASIBLE;
		int index = std::pow(2, p.level-1) - 1 + p.order;
		GetElemByIndex(index - 1, e);
		return Status::HELLA_OK;
	}
	
	/*
		@F:根据深度，序号赋值。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Assign(Position p, ElemType value)
	{
		if (p.level < 1 || p.order < 1)
			return Status::HELLA_INFEASIBLE;
		return AssignRec(p, value, m_Root, 1);
	}


	/*
		@F:根节点。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Root(ElemType& e)
	{
		if (!m_Root) {
			return Status::HELLA_INFEASIBLE;
		}
		e = m_Root->data;
		return Status::HELLA_OK;
	}

	/*
		@F:取元素的父节点。
		@D:遍历时判断其子节点值即可。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::Parent(ElemType e, ElemType& parent)
	{
		BiTNode<ElemType> node[100] = {};
		int i = 0;
		if (!m_Root || m_Root->data == e) {
			return Status::HELLA_INFEASIBLE;
		}
		node[0] = *m_Root;

		while (i >= 0) {
			while (node[i].lchild) {
				if (node[i].lchild->data == e) {
					parent = node[i].data;
					return Status::HELLA_OK;
				}
				node[i + 1] = *(node[i].lchild);
				node[i].lchild = NULL;
				i++;
			}	
			if (node[i].rchild) {
				if (node[i].rchild->data == e) {
					parent = node[i].data;
					return Status::HELLA_OK;
				}
				node[i + 1] = *(node[i].rchild);
				node[i].rchild = NULL;
				i++;
			}
			if (!node[i].lchild && !node[i].rchild)
				i--;
		}
		return Status::HELLA_NOT_FOUND;
	}

	/*
		@F:取元素的左孩子节点。
		@D:遍历找到节点即可。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::LeftChild(ElemType e, ElemType& lchild)
	{
		BiTNode<ElemType> node[100];
		int i = 0;
		if (!m_Root || m_Root->data == e) {
			return Status::HELLA_INFEASIBLE;
		}
		node[0] = *m_Root;
		while (i >= 0) {
			while (node[i].data != e && node[i].lchild) {
				node[i + 1] = *(node[i].lchild);
				node[i].lchild = NULL;
				i++;
			}
			if (node[i].data == e) {
				if (node[i].lchild) {
					lchild = node[i].lchild->data;
					return Status::HELLA_OK;
				}
				return Status::HELLA_INFEASIBLE;
			}

			if (node[i].rchild) {
				node[i + 1] = *(node[i].rchild);
				node[i].rchild = NULL;
				i++;
			}
			if (!node[i].lchild && !node[i].rchild && node[i].data != e)
				i--;
		}
		return Status::HELLA_NOT_FOUND;
	}

	/*
		@F:取元素的右孩子节点。
		@D:遍历找到节点即可。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::RightChild(ElemType e, ElemType& rchild)
	{
		BiTNode<ElemType> node[100];
		int i = 0;
		if (!m_Root || m_Root->data == e) {
			return Status::HELLA_INFEASIBLE;
		}
		node[0] = *m_Root;
		while (i >= 0) {
			while (node[i].data != e && node[i].lchild) {
				node[i + 1] = *(node[i].lchild);
				node[i].lchild = NULL;
				i++;
			}
			if (node[i].data == e) {
				if (node[i].lchild) {
					rchild = node[i].rchild->data;
					return Status::HELLA_OK;
				}
				return Status::HELLA_INFEASIBLE;
			}

			if (node[i].rchild) {
				node[i + 1] = *(node[i].rchild);
				node[i].rchild = NULL;
				i++;
			}
			if (!node[i].lchild && !node[i].rchild)
				i--;
		}
		return Status::HELLA_NOT_FOUND;
	}
	
	/*
		@F:取元素的左兄弟节点。
		@D:遍历时判断其右孩子值即可。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::LeftSibling(ElemType e, ElemType& lsibling)
	{
		BiTNode<ElemType> node[100];
		int i = 0;
		if (!m_Root || m_Root->data == e) {
			return Status::HELLA_INFEASIBLE;
		}
		node[0] = *m_Root;
		while (i >= 0) {
			while (node[i].rchild) {
				if (node[i].rchild->data == e) {
					if (node[i].lchild) {
						lsibling = node[i].lchild->data;
						return Status::HELLA_OK;
					}
				}
				node[i + 1] = *(node[i].rchild);
				node[i].rchild = NULL;
				i++;
			}

			if (node[i].lchild) {
				if (node[i].lchild->data == e) {
					return Status::HELLA_INFEASIBLE;
				}
				node[i + 1] = *(node[i].lchild);
				node[i].lchild = NULL;
				i++;
			}
			if (!node[i].lchild && !node[i].rchild)
				i--;
		}
		return Status::HELLA_NOT_FOUND;
	}


	/*
		@F:取元素的右兄弟节点。
		@D:遍历时判断其左孩子值即可。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::RightSibling(ElemType e, ElemType& rsibling)
	{
		BiTNode<ElemType> node[100];
		int i = 0;
		if (!m_Root || m_Root->data == e) {
			return Status::HELLA_INFEASIBLE;
		}
		node[0] = *m_Root;
		while (i >= 0) {
			while (node[i].lchild) {
				if (node[i].lchild->data == e) {
					if (node[i].rchild) {
						rsibling = node[i].rchild->data;
						return Status::HELLA_OK;
					}
				}
				node[i + 1] = *(node[i].lchild);
				node[i].lchild = NULL;
				i++;
			}

			if (node[i].rchild) {
				if (node[i].rchild->data == e) {
					return Status::HELLA_INFEASIBLE;
				}
				node[i + 1] = *(node[i].rchild);
				node[i].rchild = NULL;
				i++;
			}
			if (!node[i].lchild && !node[i].rchild)
				i--;
		}
		return Status::HELLA_NOT_FOUND;
	}
	
	/*
		@F: 先序遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::PreOrderTraverse(void(*visit)(ElemType&))
	{
		return PreOrderTraverseRec(visit,m_Root);
	}
	
	/*
		@F:中序遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::InOrderTraverse(void(*visit)(ElemType&))
	{
		return InOrderTraverseRec(visit,m_Root);
	}
	
	/*
		@F:后续遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::PostOrderTraverse(void(*visit)(ElemType&))
	{
		return PostOrderTraverseRec(visit,m_Root);
	}
	
	
	/*
		@F:层序遍历。
	*/
	template<typename ElemType>
	inline Status BiLinkBiTree<ElemType>::LevelOrderTraverse(void(*visit)(ElemType&))
	{
		int i, j;
		BiTNode<ElemType>* p[100];
		i = j = 0;
		if (m_Root) {
			p[j++] = m_Root;
		}
		while (i < j) {
			visit(p[i]->data);
			if (p[i]->lchild) {
				p[j++] = p[i]->lchild;
			}
			if (p[i]->rchild) {
				p[j++] = p[i]->rchild;
			}
			i++;
		}
		return Status::HELLA_OK;
	}
}


