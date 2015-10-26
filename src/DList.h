#pragma once
#include <string>
using namespace std;

template<typename T>
class DList
{
private:
	class IndexNode
	{
	public:
		string mIndex;
		IndexNode* mNext;
		IndexNode(const string index);
		~IndexNode() {}
	};
	class StoreNode
	{
	public:
		T* mData;
		StoreNode* mNext;
		StoreNode(T* data);
		~StoreNode() { delete mData; }
	};
	class ListNode
	{
	public:
		IndexNode* mIndexNode;
		StoreNode* mStoreNode;
		ListNode() { mIndexNode = nullptr; mStoreNode = nullptr; }
		~ListNode() {}
	};
	int mNrOfElements;
	int mCapacity;
	int mIncrement;
	ListNode* mList;
	StoreNode* mFirstStoreNode;
	IndexNode* mFirstIndexNode;
	void IncrementCapacity();
	int FindIndexPos(const string index);
	//int FindIndexSlotFor(const string index);
	int FindIndexSlot(const string index);
public:
	DList();
	DList(const int capacity);
	DList(const int capacity, const int increment);
	~DList();

	T* Add(const string index, T* data);
	T* operator[](const string index);
	bool CheckIndex(const string index);
};

template<typename T>
DList<T>::IndexNode::IndexNode(const string index)
{
	mIndex = index;
	mNext = nullptr;
}

template<typename T>
DList<T>::StoreNode::StoreNode(T* data)
{
	mData = data;
	mNext = nullptr;
}

template<typename T>
DList<T>::DList()
{
	mNrOfElements = 0;
	mCapacity = 1;
	mIncrement = 1;
	mList = new ListNode[mCapacity];
	mFirstIndexNode = nullptr;
	mFirstStoreNode = nullptr;
}

template<typename T>
DList<T>::DList(const int capacity)
{
	mNrOfElements = 0;
	mCapacity = capacity;
	mIncrement = 1;
	mList = new ListNode[mCapacity];
	mFirstIndexNode = nullptr;
	mFirstStoreNode = nullptr;
}

template<typename T>
DList<T>::DList(const int capacity, const int increment)
{
	mNrOfElements = 0;
	mCapacity = capacity;
	mIncrement = increment;
	mList = new ListNode[mCapacity];
	mFirstIndexNode = nullptr;
	mFirstStoreNode = nullptr;
}

template<typename T>
DList<T>::~DList()
{
	delete[] mList;
	while (mFirstIndexNode != nullptr)
	{
		IndexNode* next = mFirstIndexNode->mNext;
		delete mFirstIndexNode;
		mFirstIndexNode = next;
	}
	while (mFirstStoreNode != nullptr)
	{
		StoreNode* next = mFirstStoreNode->mNext;
		delete mFirstStoreNode;
		mFirstStoreNode = next;
	}
}

template<typename T> 
void DList<T>::IncrementCapacity()
{
	mCapacity += mIncrement;
	ListNode* tmp = new ListNode[mCapacity];
	for (int i = 0; i < mNrOfElements; i++)
	{
		//TODO opr= ListNode 
		tmp[i].mIndexNode = mList[i].mIndexNode;
		tmp[i].mStoreNode = mList[i].mStoreNode;
	}
	delete[] mList;
	mList = tmp;
}

template<typename T>
int DList<T>::FindIndexPos(const string index)
{
	int first = 0;
	int last = mNrOfElements - 1;
	int mid = last / 2;
	while (first <= last)
	{
		if (mList[mid].mIndexNode->mIndex > index)
		{
			last = mid - 1;
			mid /= 2;
		}
		else if (mList[mid].mIndexNode->mIndex < index)
		{
			first = mid + 1;
			mid = (last + first) / 2;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

template<typename T>
int DList<T>::FindIndexSlot(const string index)
{
	if (mNrOfElements == 0)
	{
		return 0;
	}
	//index can't be in array
	int first = 0;
	int last = mNrOfElements - 1;
	int mid = last / 2;
	while (first <= last)
	{
		if (mList[mid].mIndexNode->mIndex > index)
		{
			last = mid - 1;
			mid /= 2;
		}
		else
		{
			first = mid + 1;
			mid = (last + first) / 2;
		}
	}
	return first;
}

template<typename T>
T* DList<T>::Add(const string index, T* data)
{
	if (FindIndexPos(index) != -1)
	{
		return nullptr; //Index is allready in list
	}

	if(mNrOfElements == mCapacity)
	{
		IncrementCapacity();
	}

	int pos = FindIndexSlot(index);
	for (int i = mNrOfElements; i > pos; i--)
	{
		mList[i].mIndexNode = mList[i-1].mIndexNode;
		mList[i].mStoreNode = mList[i-1].mStoreNode;
	}

	IndexNode* indexNode = new IndexNode(index);
	StoreNode* storeNode = new StoreNode(data);
	IndexNode* nextIndex = mFirstIndexNode;
	mFirstIndexNode = indexNode;
	mFirstIndexNode->mNext = nextIndex;
	StoreNode* nextStore = mFirstStoreNode;
	mFirstStoreNode = storeNode;
	mFirstStoreNode->mNext = nextStore;
	//mList[mNrOfElements].mIndexNode = indexNode;
	//mList[mNrOfElements].mStoreNode = storeNode;
	mList[pos].mIndexNode = indexNode;
	mList[pos].mStoreNode = storeNode;
	mNrOfElements++;
	return storeNode->mData;
}

template<typename T>
T* DList<T>::operator[](const string index)
{
	int pos = FindIndexPos(index);
	if(pos != -1)
	{
		return &mList[pos].mStoreNode->mData;
	}
	return nullptr;
}

template<typename T>
bool DList<T>::CheckIndex(const string index)
{
	if(FindIndexPos(index) != -1)
	{
		return true;
	}
	return false;
}
