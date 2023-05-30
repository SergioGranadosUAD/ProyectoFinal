#pragma once
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class SNode {
public:
	SNode(T val) :
		mValue(val), mNext(nullptr) {}

	T GetmValue() const { return mValue; }
	SNode<T>* GetmNext() const { return mNext; }
	void SetmValue(T i);
	void SetmNext(SNode* n);

private:
	T mValue;
	SNode<T>* mNext;
};

template <typename T>
class Stack {
public:
	Stack() :
		mSize(0), mTop(nullptr) {}
	~Stack();

	size_t Size() const {
		return mSize;
	}

	void Push(T value);
	T Pop();
	T Peek();

private:
	size_t mSize;
	SNode<T>* mTop;
};
