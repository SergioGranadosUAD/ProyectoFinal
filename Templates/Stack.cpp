#include "Stack.h"

template <typename T>
Stack<T>::~Stack(){
	SNode<T>* actualNode = mTop;
	for (int i = 0; i < mSize; i++) {
		SNode<T>* nextNode = actualNode->GetmNext();
		if (actualNode != nullptr) {
			delete actualNode;
		}
		actualNode = nextNode;
	}
}

//Método que establece el valor de un nodo.
template <typename T>
void SNode<T>::SetmValue(T i) {
	mValue = i;
}

//Método que establece el puntero al siguiente elemento de un nodo.
template <typename T>
void SNode<T>::SetmNext(SNode<T>* n) {
	mNext = n;
}

template <typename T>
void Stack<T>::Push(T value) {
	SNode<T>* actualNode = new SNode<T>(value);
	actualNode->SetmNext(mTop);
	mTop = actualNode;
	mSize++;
}

template <typename T>
T Stack<T>::Pop() {
	SNode<T>* tempNode;
	if (mTop != nullptr) {
		T value;
		tempNode = mTop;
		mTop = mTop->GetmNext();
		value = tempNode->GetmValue();
		delete tempNode;
		mSize--;
		return value;
	}
	else {
		cout << "No hay elementos en el Stack!" << endl;
	}
}

template <typename T>
T Stack<T>::Peek() {
	if (mTop != nullptr) {
		return mTop->GetmValue();
	}
	else {
		cout << "No hay elementos en el Stack!" << endl;
	}
}