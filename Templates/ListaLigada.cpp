#include "ListaLigada.h"

//Destructor de la lista. Itera desde el primer hasta el último elemento liberando la memoria.
template <typename T>
SimpleList<T>::~SimpleList() {
	Node<T>* actualNode = mFirst;
	for (int i = 0; i < mSize; i++) {
		Node<T>* nextNode = actualNode->GetmNext();
		if (actualNode != nullptr) {
			delete actualNode;
		}
		actualNode = nextNode;
	}
}

//Método que añade un elemento al final de la lista.

template <typename T>
void SimpleList<T>::Add(T value) {
	//Si se añade un elemento por primera vez, se establece que es el primero y último en la lista.
	if (mSize == 0) {
		Node<T>* newNode = new Node<T>(value);
		mFirst = newNode;
		mLast = newNode;
	}
	//En caso de haber más, se obtiene el último nodo, se crea el nuevo nodo y se asigna al último nodo la dirección del nuevo nodo.
	//Posteriormente el nuevo nodo pasa a ser el último nodo de la lista.
	else {
		Node<T>* lastNode = mLast;
		Node<T>* newNode = new Node<T>(value);
		lastNode->SetmNext(newNode);
		mLast = newNode;

	}
	mSize++;
}

//Método que itera sobre la lista y devuelve el valor que se encuentra en el índice.
template <typename T>
T SimpleList<T>::At(size_t index) {
	CheckRange(index);
	Node<T>* iterNode = mFirst;
	//Se itera sobre el tamaño de la lista.
	for (int i = 0; i < mSize; i++) {
		//Si la iteración actual equivale al índice, devuelve el valor de esta.
		if (i == index) {
			return iterNode->GetmValue();
		}
		//En caso contrario pasa al siguiente puntero.
		else {
			iterNode = iterNode->GetmNext();
		}
	}
}

//Método que inserta un elemento en el indice indicado de la lista.
template <typename T>
void SimpleList<T>::Insert(T value, size_t index) {
	CheckRange(index);
	Node<T>* iterNode = mFirst;
	Node<T>* previousNode = mFirst;

	//Si se inserta en el primer espacio, se le asigna a este nuevo nodo la dirección del que antes era el primer elemento, y se vuelve
	//el primer elemento de la lista.
	if (index == 0) {
		Node<T>* newNode = new Node<T>(value);
		newNode->SetmNext(mFirst);
		mFirst = newNode;
		mSize++;
	}
	else if (index == mSize - 1) {
		Node<T>* newNode = new Node<T>(value);
		newNode->SetmNext(nullptr);
		mLast->SetmNext(newNode);
		mLast = newNode;
		mSize++;
	}
	//En caso contrario, itera sobre la lista hasta encontrar el índice.
	else {
		for (int i = 0; i < mSize; i++) {
			if (i == index) {
				//se le asigna la dirección del nuevo nodo al nodo anterior, y al nuevo nodo se le asigna la dirección del nodo que sigue.
				Node<T>* newNode = new Node<T>(value);
				previousNode->SetmNext(newNode);
				newNode->SetmNext(iterNode);
				mSize++;
				return;
			}
			//Se guarda el nodo anterior y se sigue iterando.
			else {
				previousNode = iterNode;
				iterNode = iterNode->GetmNext();
			}
		}
	}
}

//Método que elimina un elemento de la lista en el índice indicado.
template <typename T>
void SimpleList<T>::Delete(size_t index) {
	CheckRange(index);
	Node<T>* iterNode = mFirst;
	Node<T>* previousNode = mFirst;

	//Si se elimina en el primer espacio, se le asigna la dirección del primer nodo al segundo espacio, y se elimina el primer nodo
	//de la memoria. Posteriormente se reduce el tamaño de la lista.
	if (index == 0) {
		mFirst = iterNode->GetmNext();
		delete iterNode;
		mSize--;
	}
	//En caso contrario, se itera a través de la lista hasta que se encuentra el índice.
	else {
		for (int i = 0; i < mSize; i++) {
			if (i == index) {
				//Se le asigna la dirección del nodo que sigue al nodo anterior, y se elimina el nodo actual de la memoria. Posteriormente
				//se reduce el tamaño de la lista.
				previousNode->SetmNext(iterNode->GetmNext());
				delete iterNode;

				mSize--;
				return;
			}
			//Se guarda el nodo anterior y se sigue iterando.
			else {
				previousNode = iterNode;
				iterNode = iterNode->GetmNext();
			}
		}
	}
}

//Método auxiliar que verifica que el indice introducido no sea mayor al tamaño de la lista.
template <typename T>
void SimpleList<T>::CheckRange(size_t index) {
	if (index > mSize-1) {
		throw out_of_range("El indice esta fuera del rango de la lista");
	}
}

//Método que establece el valor de un nodo.
template <typename T>
void Node<T>::SetmValue(T i) {
	mValue = i;
}

//Método que establece el puntero al siguiente elemento de un nodo.
template <typename T>
void Node<T>::SetmNext(Node<T>* n) {
	mNext = n;
}

//Sobrecarga de operador que llama a la función At() para devolver el valor de un elemento de la lista en la posición indicada.
template <typename T>
T SimpleList<T>::operator[](size_t i) {
	return At(i);
}