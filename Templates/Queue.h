#pragma once

template <typename T>
class QNode {
public:
	QNode(T val) :
		mValue(val), mNext(nullptr) {}

	T GetmValue() const { return mValue; }
	QNode<T>* GetmNext() const { return mNext; }
	void SetmValue(T i);
	void SetmNext(QNode* n);

private:
	T mValue;
	QNode<T>* mNext;
};

template <typename T>
class Queue {
public:
	Queue() :
		mSize(0), mFront(nullptr), mRear(nullptr) {}
	~Queue();

	size_t Size() const {
		return mSize;
	}

	void Enqueue(T value);
	T Dequeue();

private:
	size_t mSize;
	QNode<T>* mFront;
	QNode<T>* mRear;
};