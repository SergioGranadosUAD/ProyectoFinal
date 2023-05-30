#pragma once

#include <iostream>
using std::out_of_range;

//Clase que contiene el valor del elemento de la lista y un puntero que lleva al siguiente elemento.
template <typename T>
class Node {
public:
	//Constructor del nodo.
	Node(T val) :
		mValue(val), mNext(nullptr) {}

	//Getters and Setters para acceder a los atributos del nodo.
	T GetmValue() const { return mValue; }
	Node<T>* GetmNext() const { return mNext; }
	void SetmValue(T i);
	void SetmNext(Node* n);

private:
	//Declaración de las propiedades.
	T mValue;
	Node<T>* mNext;
};

//Clase que sirve como una lista ligada que almacena enteros, contando con métodos para su manipulación.
template <typename T>
class SimpleList {
public:
	//Constructor de la lista.
	SimpleList() :
		mSize(0), mFirst(nullptr), mLast(nullptr) {}
	//Declaración del destructor de la lista.
	~SimpleList();

	//Método que regresa el tamaño de la lista.
	size_t Size() const {
		return mSize;
	}

	//Métodos auxiliares para la manipulación de la lista.
	void Add(T value);
	T At(size_t index);
	void Insert(T value, size_t index);
	void Delete(size_t index);

	//Método auxiliar que revisa si el índice introducido está dentro del rango de la lista.
	void CheckRange(size_t index);

	//Sobrecarga del operador [].
	T operator[](size_t i);
private:
	//Declaración de los atributos.
	size_t mSize;
	Node<T>* mFirst;
	Node<T>* mLast;
};

