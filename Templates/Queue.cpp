#include "Queue.h"

template <typename T>
Queue<T>::~Queue() {
	QNode<T>* actualNode = mRear;
	for (int i = 0; i < mSize; i++) {
		QNode<T>* nextNode = actualNode->GetmNext();
		if (actualNode != nullptr) {
			delete actualNode;
		}
		actualNode = nextNode;
	}
}

//Método que establece el valor de un nodo.
template <typename T>
void QNode<T>::SetmValue(T i) {
	mValue = i;
}

//Método que establece el puntero al siguiente elemento de un nodo.
template <typename T>
void QNode<T>::SetmNext(QNode<T>* n) {
	mNext = n;
}

//Método que añade un valor al final del queue.
template <typename T>
void Queue<T>::Enqueue(T value) {
	QNode<T>* newNode = new QNode<T>(value);
	if (mRear == nullptr) {
		mRear = newNode;
		mFront = newNode;
		mSize++;
	}
	else {
		mRear->SetmNext(newNode);
		mRear = newNode;
		mSize++;
	}
}

//Metodo que devuelve el valor al frente del queue y lo elimina.
template <typename T>
T Queue<T>::Dequeue() {
	if (mFront != nullptr) {
		T value;
		QNode<T>* tempNode = mFront;
		mFront = mFront->GetmNext();

		if (mFront == nullptr) {
			mRear == nullptr;
		}

		value = tempNode->GetmValue();
		delete tempNode;
		mSize--;
		return value;
	}
}