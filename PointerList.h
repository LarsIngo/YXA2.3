#pragma once
using namespace std;

template<typename T>
class PointerList
{
private:
	T** mpList;
	int mCap;
	int mInc;
	int mNrOfElement;

	void IncCap();
public:
	PointerList();
	PointerList(int cap, int inc);
	//PointerList(PointerList& other)
	~PointerList();

	T* Add(T* pData);
	T* operator[](const int pos);
	void Clear();
	int Size();
	T* ReplaceAt(const int pos, T* pData);
};

template<typename T>
PointerList<T>::PointerList()
{
	mCap = 0;
	mInc = 1;
	mNrOfElement = 0;
	mpList = new T*[cap];
}

template<typename T>
PointerList<T>::PointerList(int cap, int inc)
{
	mCap = cap;
	mInc = inc;
	mNrOfElement = 0;
	mpList = new T*[cap];
}

//PointerList(PointerList& other)
//{
//
//}

template<typename T>
PointerList<T>::~PointerList()
{
	Clear();
}

template<typename T>
T* PointerList<T>::Add(T* pData)
{
	if(mCap == mNrOfElement)
	{
		IncCap();
	}
	return mpList[mNrOfElement++] = pData;
}

template<typename T>
T* PointerList<T>::operator[](const int pos)
{
	return mpList[pos];
}

template<typename T>
void PointerList<T>::IncCap()
{
	mCap += mInc;
	T** tmp = new T*[mCap];
	for (int i = 0; i < mNrOfElement; i++)
	{
		tmp[i] = mpList[i];
	}
	delete[] mpList;
	mpList = tmp;
}

template<typename T>
void PointerList<T>::Clear()
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
int PointerList<T>::Size()
{
	return mNrOfElement;
}

template<typename T>
T* PointerList<T>::ReplaceAt(const int pos, T* pData)
{
	if (pos >= 0 && pos < mNrOfElement)
	{
		//T* b = mpList[pos];
		delete mpList[pos];
		return mpList[pos] = new T(*pData);
	}
	return nullptr;
}