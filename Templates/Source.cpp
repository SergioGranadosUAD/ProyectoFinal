#include <iostream>
#include "ListaLigada.h"
#include "ListaLigada.cpp"
#include "Stack.h"
#include "Stack.cpp"
#include "Queue.h"
#include "Queue.cpp"

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::out_of_range;
int main() {
	cout << "Ejercicios con la lista ligada:" << endl;
	try {
		
		cout << "Pruebas con lista ligada:" << endl;
		SimpleList<string> lista;
		lista.Add("Hola");
		lista.Add("esta");
		lista.Add("es");
		lista.Add("una");
		lista.Add("lista");
		cout << "List size: " << lista.Size() << endl;

		lista.Insert("ligada", 4);

		lista.Delete(3);
		for (int i = 0; i < lista.Size(); ++i) {
			cout << "elemento: " << lista[i] << endl;
		}

		cout << endl;

		cout << "Pruebas con stack:" << endl;
		Stack<string> stack;
		stack.Push("Hola");
		cout << stack.Peek() << endl;
		stack.Push("Probando");
		stack.Push("Test");
		cout << "Stack size: " << stack.Size() << endl;
		cout << stack.Pop() << endl;
		cout << stack.Peek() << endl;
		cout << "Stack size: " << stack.Size() << endl;
		
		cout << endl;

		cout << "Pruebas con queue: " << endl;
		Queue<string> queue;
		queue.Enqueue("Hola");
		queue.Enqueue("Probando");
		cout << "Queue size: " << queue.Size() << endl;
		cout << queue.Dequeue() << endl;
		cout << queue.Dequeue() << endl;
		cout << "Queue size: " << queue.Size() << endl;
	}
	catch (out_of_range& e) {
		cerr << e.what() << endl;
	}
}