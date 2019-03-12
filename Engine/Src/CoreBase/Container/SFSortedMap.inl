////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2014 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////
	//
	//	SortedMap<KeyType,ValueType>::MapNode
	//
namespace SF {


		template<class KeyType, class ValueType>
		int SortedMap<KeyType, ValueType>::MapNode::UpdateBalanceFactor()
		{
			auto left = Left;
			auto right = Right;
			int iLeftDepth = 0, iLeftChildren = 0;
			int iRightDepth = 0, iRightChildren = 0;
			if (left != nullptr)
			{
				iLeftDepth = left->DepthOfChildren + 1;
				iLeftChildren = left->NumberOfChildren + 1;
			}
			if (right != nullptr)
			{
				iRightDepth = right->DepthOfChildren + 1;
				iRightChildren = right->NumberOfChildren + 1;
			}

			// Original AVL just uses -BalanceTolerance ~ BalanceTolerance expression
			Balance = iRightDepth - iLeftDepth;
			DepthOfChildren = std::max(iRightDepth, iLeftDepth);
			NumberOfChildren = iLeftChildren + iRightChildren;

			return Balance;
		}

		///////////////////////////////////////////////////////////////////////////
		//
		//	SortedMap<KeyType,ValueType>::MapNode
		//

		template<class KeyType, class ValueType>
		typename SortedMap<KeyType, ValueType>::ReferenceAccessPoint* SortedMap<KeyType, ValueType>::OperationTraversalHistory::GetParentAccessPoint(int nodeIndex, MapNode* pNode)
		{
			ReferenceAccessPoint* pParentPointer = nullptr;
			Assert(GetHistory(nodeIndex) == pNode);
			if (GetHistorySize() <= 1 || nodeIndex < 1) // only the found node is in there
			{
				pParentPointer = &m_Root;
			}
			else
			{
				auto parentNode = GetHistory(nodeIndex - 1);
				if (parentNode->Left == pNode)
					pParentPointer = &parentNode->Left;
				else
					pParentPointer = &parentNode->Right;

				Assert(*pParentPointer == pNode);
			}

			return pParentPointer;
		}


		///////////////////////////////////////////////////////////////////////////
		//
		//
		//

		template<class KeyType, class ValueType>
		SortedMap<KeyType, ValueType>::SortedMap(IHeap& memoryManager)
			: m_Root(nullptr)
			, m_ItemCount(0)
			, m_DeleteNodePool(false)
			, m_Heap(memoryManager)
			, m_pNodePool(nullptr)
		{
			if (m_pNodePool == nullptr)
			{
				m_DeleteNodePool = true;
				m_pNodePool = new(memoryManager) ObjectPoolT<MapNode>(memoryManager);
			}
		}

		template<class KeyType, class ValueType>
		SortedMap<KeyType, ValueType>::~SortedMap()
		{
			ClearMap();

			if (m_pNodePool != nullptr && m_DeleteNodePool)
			{
				GetHeap().Delete(m_pNodePool);
			}
		}

		template<class KeyType, class ValueType>
		void SortedMap<KeyType, ValueType>::ClearMap()
		{
			MapNode* pCurNode = m_Root;
			std::queue<MapNode*> mapNodes;

			m_Root = nullptr;
			m_ItemCount = 0;

			if (pCurNode != nullptr) mapNodes.push(pCurNode);
			while (mapNodes.size() > 0)
			{
				pCurNode = mapNodes.front();
				mapNodes.pop();

				if (pCurNode->Left != nullptr)	mapNodes.push(pCurNode->Left);
				if (pCurNode->Right != nullptr)	mapNodes.push(pCurNode->Right);

				FreeNode(pCurNode);
			}

			//while (m_FreeNodes != nullptr)
			//{
			//	auto next = m_FreeNodes->Next;
			//	delete m_FreeNodes;
			//	m_FreeNodes = next;
			//}
		}

		// Insert a key
		template<class KeyType, class ValueType>
		Result SortedMap<KeyType, ValueType>::Insert(KeyType key, const ValueType& value, int64_t *insertedOrder)
		{
			OperationTraversalHistory traversalHistory(GetHeap(), m_Root, m_ItemCount);

			MapNode* pFound = nullptr;
			if (!(FindNode(traversalHistory, key, pFound)))
			{
				if (m_Root != nullptr)
					return ResultCode::FAIL;
				else
				{
					auto newNode = AllocateNode(key, value);
					m_Root = newNode;

					if (newNode == nullptr)
						return ResultCode::OUT_OF_MEMORY;

					m_ItemCount++;

					if (insertedOrder != nullptr)
					{
						*insertedOrder = 0;
					}

					return ResultCode::SUCCESS;
				}
			}

			MapNode* pInserted = nullptr;
			if (key > pFound->Key) // duplicate key will be put at the left most side
			{
				auto right = pFound->Right;
				if (right != nullptr)
					return ResultCode::FAIL;

				pFound->Right = pInserted = AllocateNode(key, value);
			}
			else if (key == pFound->Key)
			{
				auto left = pFound->Left;
				if (left != nullptr)
				{
					auto biggestNode = FindBiggestNode(traversalHistory, left);
					auto right = biggestNode->Right;
					if (right != nullptr)
						return ResultCode::FAIL;

					biggestNode->Right = pInserted = AllocateNode(key, value);
				}
				else
				{
					pFound->Left = pInserted = AllocateNode(key, value);
				}
			}
			else // if (key < pCurNode->Key) 
			{
				auto left = pFound->Left;
				if (left != nullptr)
					return ResultCode::FAIL;

				pFound->Left = pInserted = AllocateNode(key, value);
			}

			// calculate order
			if (insertedOrder != nullptr)
			{
				*insertedOrder = CalculateOrder(traversalHistory, pInserted);
			}


			FixupBalance(traversalHistory);

			m_ItemCount++;

			return ResultCode::SUCCESS;
		}


		// Remove an item and return the removed value
		template<class KeyType, class ValueType>
		Result SortedMap<KeyType, ValueType>::Remove(KeyType key, ValueType& value)
		{
			OperationTraversalHistory travelHistory(GetHeap(), m_Root, m_ItemCount);

			MapNode* pRemoved = nullptr;
			MapNode* pFound = nullptr;
			if (!(FindNode(travelHistory, key, pFound)))
				return ResultCode::FAIL;

			// unique key
			if (pFound->Key != key)
				return ResultCode::FAIL;

			value = std::forward<ValueType>(pFound->Value);


			ReferenceAccessPoint *pParentPointer = nullptr;
			//MapNode* pParentOfReplaced = nullptr;
			MapNode* child = nullptr;

			auto left = pFound->Left;
			auto right = pFound->Right;
			// If it's not a leap node, find a replacement
			if (left != nullptr || right != nullptr)
			{
				// select a child to replace
				bool rightHeavy = false;
				int leftDepth = left == nullptr ? -1 : left->DepthOfChildren;
				int rightDepth = right == nullptr ? -1 : right->DepthOfChildren;
				if (leftDepth > rightDepth)
				{
				}
				else if (leftDepth < rightDepth)
				{
					rightHeavy = true;
				}
				else
				{
					int leftChildren = left == nullptr ? -1 : left->NumberOfChildren;
					int rightChildren = right == nullptr ? -1 : right->NumberOfChildren;
					if (leftChildren > rightChildren)
					{
					}
					else
					{
						rightHeavy = true;
					}
				}

				if (rightHeavy) // select heavy tree child
				{
					pRemoved = FindSmallestNode(travelHistory, right);
					Assert(pRemoved->Left == nullptr);
					child = pRemoved->Right;
				}
				else
				{
					pRemoved = FindBiggestNode(travelHistory, left);
					Assert(pRemoved->Right == nullptr);
					child = pRemoved->Left;
				}

				// swap value with replacement node
				pFound->Key = pRemoved->Key;
				pFound->Value = std::forward<ValueType>(pRemoved->Value);
			}
			else
			{
				// if it doesn't have any child
				pRemoved = pFound;
			}


			// remove replacement from the tree
			pParentPointer = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, pRemoved);
			*pParentPointer = child;

			// remove from the traversal history, replacement node will not be need to be took care
			travelHistory.RemoveLastHistory();


			FixupBalance(travelHistory);

			if (pRemoved) FreeNode(pRemoved);

			m_ItemCount--;

			return ResultCode::SUCCESS;
		}


		// Find a key value
		template<class KeyType, class ValueType>
		Result SortedMap<KeyType, ValueType>::Find(KeyType key, ValueType& value, int64_t *pOrder)
		{
			OperationTraversalHistory travelHistory(GetHeap(), m_Root, m_ItemCount);

			MapNode* pFound = nullptr;
			if (!(FindNode(travelHistory, key, pFound)))
				return ResultCode::FAIL;

			// unique key
			if (pFound->Key != key)
				return ResultCode::FAIL;

			value = pFound->Value;

			if (pOrder != nullptr)
			{
				*pOrder = CalculateOrder(travelHistory, pFound);
			}

			return ResultCode::SUCCESS;
		}


		// find parent node or candidate
		template<class KeyType, class ValueType>
		Result SortedMap<KeyType, ValueType>::FindNode(OperationTraversalHistory &travelHistory, KeyType key, MapNode* &pNode)
		{
			MapNode* pCurNode = m_Root;
			if (pCurNode == nullptr)
				return ResultCode::FAIL;

			travelHistory.Clear();
			travelHistory.SetPreserveDataOnResize(true);

			do
			{
				travelHistory.AddHistory(pCurNode);

				// multiple key
				if (pCurNode->Key == key)
				{
					pNode = pCurNode;
					return ResultCode::SUCCESS;
				}

				if (key > pCurNode->Key)
				{
					auto right = pCurNode->Right;
					if (right == nullptr)
					{
						pNode = pCurNode;
						return ResultCode::SUCCESS;
					}
					else
					{
						pCurNode = right;
					}
				}
				else // if (key <= pCurNode->Key)
				{
					auto left = pCurNode->Left;
					if (left == nullptr)
					{
						pNode = pCurNode;
						return ResultCode::SUCCESS;
					}
					else
					{
						// Handl multiple key
						// choose left most one
						if (pCurNode->Key == key)
						{
							if (left->Key != key)
							{
								pNode = FindBiggestNode(travelHistory, left);
								return ResultCode::SUCCESS;
							}
						}
						pCurNode = left;
					}
				}

			} while (pCurNode != nullptr);

			travelHistory.SetPreserveDataOnResize(false);

			return ResultCode::SUCCESS;
		}

		template<class KeyType, class ValueType>
		typename SortedMap<KeyType, ValueType>::MapNode* SortedMap<KeyType, ValueType>::FindSmallestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
		{
			if (pRootNode == nullptr) return nullptr;

			auto pCurNode = pRootNode;
			while (pCurNode != nullptr)
			{
				travelHistory.AddHistory(pCurNode);
				auto left = pCurNode->Left;
				if (left == nullptr)
					return pCurNode;

				pCurNode = left;
			}

			return pCurNode;
		}

		template<class KeyType, class ValueType>
		typename SortedMap<KeyType, ValueType>::MapNode* SortedMap<KeyType, ValueType>::FindBiggestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
		{
			if (pRootNode == nullptr) return nullptr;

			auto pCurNode = pRootNode;
			while (pCurNode != nullptr)
			{
				travelHistory.AddHistory(pCurNode);
				auto right = pCurNode->Right;
				if (right == nullptr)
					return pCurNode;

				pCurNode = right;
			}

			return pCurNode;
		}

		template<class KeyType, class ValueType>
		void SortedMap<KeyType, ValueType>::FixupBalance(OperationTraversalHistory &travelHistory)
		{
			int iRebalancing = 0;
			for (int iHistory = (int)travelHistory.GetHistorySize() - 1; iHistory >= 0; iHistory--)
			{
				auto pCurNode = travelHistory.GetHistory(iHistory);
				auto balance = pCurNode->UpdateBalanceFactor();

				if (std::abs(balance) < BalanceTolerance)
					continue;

				iRebalancing++;
				if (iRebalancing > MaxRebalancingTry)
					continue;

				// Truncate history, it's need to be update
				auto parentAccessPoint = travelHistory.GetParentAccessPoint(iHistory, pCurNode);
				travelHistory.TruncateHistoryFrom(iHistory);

				if (balance <= -BalanceTolerance)
				{
					auto left = pCurNode->Left;
					// left-right case
					if (left->Balance >= 0)
					{
						auto leftRight = left->Right;
						left->Right = leftRight->Left;
						pCurNode->Left = leftRight->Right;

						leftRight->Left = left;
						leftRight->Right = pCurNode;

						*parentAccessPoint = leftRight;
						travelHistory.AddHistory(leftRight);
					}
					else // left-left case
					{
						pCurNode->Left = left->Right;
						left->Right = pCurNode;
						*parentAccessPoint = left;
					}

					travelHistory.AddHistory(left);
				}
				else// if (balance >= BalanceTolerance)
				{
					auto right = pCurNode->Right;
					// right-left case
					if (right->Balance < 0)
					{
						auto rightLeft = right->Left;
						pCurNode->Right = rightLeft->Left;
						right->Left = rightLeft->Right;

						rightLeft->Left = pCurNode;
						rightLeft->Right = right;

						*parentAccessPoint = rightLeft;
						travelHistory.AddHistory(rightLeft);
					}
					else // right-right case
					{
						pCurNode->Right = right->Left;
						right->Left = pCurNode;
						*parentAccessPoint = right;
					}

					travelHistory.AddHistory(right);
				}

				travelHistory.AddHistory(pCurNode);

				iHistory = (int)travelHistory.GetHistorySize();// -1; // loop count will be decreased before procedeed
			}
		}

		template<class KeyType, class ValueType>
		int64_t SortedMap<KeyType, ValueType>::CalculateOrder(OperationTraversalHistory &travelHistory, MapNode* pNode)
		{
			if (pNode == nullptr)
				return 0;

			int64_t order = 0;
			int iDepth = (int)travelHistory.GetHistorySize() - 1;
			if (travelHistory.GetLastHistory() == pNode) // Should not include itself, but children bigger than it should be included
			{
				auto right = pNode->Right;
				if (right != nullptr)
				{
					order += right->NumberOfChildren + 1; // right + number of children  of right
				}
				iDepth--; // remove himself
			}

			for (; iDepth >= 0; iDepth--)
			{
				MapNode* pParentNode = travelHistory.GetHistory(iDepth);
				if (pParentNode->Right == pNode)
				{
					//order += pParentNode->Right == nullptr ? 1 : pParentNode->Right->NumberOfChildren;
				}
				else if (pParentNode->Left == pNode)
				{
					order += pParentNode->Right == nullptr ? 1 : pParentNode->Right->NumberOfChildren + 2;
				}
				else
				{
					Assert(false);
				}

				pNode = pParentNode;
			}

			return order;
		}


		template<class KeyType, class ValueType>
		typename SortedMap<KeyType, ValueType>::MapNode* SortedMap<KeyType, ValueType>::AllocateNode(KeyType key, const ValueType& value)
		{
			MapNode* pMapNode = nullptr;
			m_pNodePool->Alloc(pMapNode);
			if (pMapNode != nullptr)
				pMapNode->SetValue(key, value);

			return pMapNode;
		}

		template<class KeyType, class ValueType>
		void SortedMap<KeyType, ValueType>::FreeNode(MapNode* pNode)
		{
			m_pNodePool->Free(pNode);
		}


}