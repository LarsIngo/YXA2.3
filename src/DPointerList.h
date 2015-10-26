#pragma once
#include <string>
using namespace std;

template<typename T>
class DPointerList
{
private:
	class Node
	{
	public:
		string mIndex;
		T* mpData;
		Node(string index, T* pData) { mIndex = index; mpData = pData; }
		~Node() { delete mpData; mpData = nullptr; }
	};
	Node** mpList;
	int mCap;
	int mInc;
	int mNrOfElement;

	void IncCap();
public:
	DPointerList();
	DPointerList(int cap, int inc);
	~DPointerList();

	T* Add(string index, T* pData);
	T* operator[](const int pos);
	int operator[](const string index);
	void Clear();
	int Size();
};

template<typename T>
DPointerList<T>::DPointerList()
{
	mCap = 0;
	mInc = 1;
	mNrOfElement = 0;
	mpList = new Node*[cap];
}

template<typename T>
DPointerList<T>::DPointerList(int cap, int inc)
{
	mCap = cap;
	mInc = inc;
	mNrOfElement = 0;
	mpList = new Node*[cap];
}

template<typename T>
DPointerList<T>::~DPointerList()
{
	Clear();
}

template<typename T>
T* DPointerList<T>::Add(string index, T* pData)
{
	if (mCap == mNrOfElement)
	{
		IncCap();
	}

	T* data = nullptr;
	for (int i = 0; i < mNrOfElement && data == nullptr; i++)
	{
		if (mpList[i]->mIndex == index)
		{
			data = mpList[i]->mpData;
		}
	}
	if(data != nullptr)
	{
		delete pData;
		return data;
	}
	Node* node = new Node(index, pData);
	mpList[mNrOfElement++] = node;
	return node->mpData;
}

template<typename T>
T* DPointerList<T>::operator[](const int pos)
{
	return mpList[pos]->mpData;
}

template<typename T>
void DPointerList<T>::IncCap()
{
	mCap += mInc;
	Node** tmp = new Node*[mCap];
	for (int i = 0; i < mNrOfElement; i++)
	{
		tmp[i] = mpList[i];
	}
	delete[] mpList;
	mpList = tmp;
}

template<typename T>
void DPointerList<T>::Clear()
{
	for (int i = 0; i < mNrOfElement; i++)
	{
		if (mpList[i] != nullptr)
		{
			delete mpList[i];
			mpList[i] = nullptr;
		}
	}
	delete[] mpList;
}

template<typename T>
int DPointerList<T>::operator[](const string index)
{
	for (int i = 0; i < mNrOfElement; i++)
	{
		if(mpList[i]->mIndex == index)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
int DPointerList<T>::Size()
{
	return mNrOfElement;
}