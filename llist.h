#pragma once 
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <string>

const std::string LL_INDEX_OUT_OF_RANGE_MESSAGE = "(LL) Quack! Index out of range.";
const std::string LL_NEGATIVE_SIZE_MESSAGE = "(LL) Quack! Size < 0.";
const std::string LL_ZERO_SIZE_MESSAGE = "(LL) Quack! Size = 0.";

template <typename T> class LinkedList {
private:

	struct Node {
		T data; // данные 
		Node* next = nullptr; // указатель на следующий элемент 
	};

	Node* head = nullptr; // указатель на первый элмент, по умолчанию nullptr
	int length = 0; // длина списка, по умолчанию 0

public:
	// пустой конструктор, length = 0
	LinkedList() : length(0) {}
	// пустой конструктор определённого размера 
	LinkedList(int length) : LinkedList() {
		if (length < 0) throw std::length_error(LL_NEGATIVE_SIZE_MESSAGE);
		// обработка исключения 

		Node** tmp = &(this->head);
		for (int i = 0; i < length; i++) {
			*tmp = new Node;
			(*tmp)->data = T();
			tmp = &((*tmp)->next);
		}
		this->length = length;
	}
	// Копировать элементы из переданного массива
	LinkedList(T* datas, int length) : LinkedList() {
		if (length < 0) throw std::length_error(LL_NEGATIVE_SIZE_MESSAGE);

		Node** ptr = &(this->head);
		for (int i = 0; i < length; i++) {
			*ptr = new Node;
			(*ptr)->data = datas[i];
			ptr = &((*ptr)->next);
		}

		this->length = length;
	}
	// Копирующий конструктор
	LinkedList(const LinkedList<T>& list) {
		Node* ptr = list.head;
		Node** newPtr = &(this->head);

		for (int i = 0; i < list.length; i++, ptr = ptr->next) {
			*newPtr = new Node;
			(*newPtr)->data = ptr->data;
			newPtr = &((*newPtr)->next);

		}

		this->length = list.length;
	}
	// деструктор 
	virtual ~LinkedList() {
		Node* ptr = this->head;
		Node* next;
		while (ptr != nullptr) {
			next = ptr->next;
			delete ptr;
			ptr = next;
		}
		this->length = 0;
	}

	//Получить первый элемент в списке
	T getFirst() const {
		if (this->length == 0) throw std::length_error(LL_ZERO_SIZE_MESSAGE);

		return this->head->data;
	}
	// Получить последний элемент в списке
	T getLast() const {
		if (this->length == 0) throw std::length_error(LL_ZERO_SIZE_MESSAGE);

		Node* ptr = this->head;
		while (ptr->next != nullptr) ptr = ptr->next;
		return ptr->data;
	}	
	// Получить элемент по индексу
	T get(int index) const {
		if ((index < 0) || (index >= this->length)) throw std::out_of_range(LL_INDEX_OUT_OF_RANGE_MESSAGE);
		Node* ptr;
		{
			int i = 0;
			for (i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}
		return ptr->data;
	}

	// Изменить элемент по индексу
	void set(const T& data, int index) {
		if (index < 0 || index >= this->length) throw std::out_of_range(LL_INDEX_OUT_OF_RANGE_MESSAGE);
		Node* ptr;
		{
			int i = 0;
			for (i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}
		ptr->data = data;
	}

	// Получить список из всех элементов, с startIndex по endIndex (включительно)
	LinkedList<T>* getSublist(int start, int end) const { //end excluding
		if (start < 0 || start >= this->length) throw std::out_of_range(LL_INDEX_OUT_OF_RANGE_MESSAGE);
		if (end < 0 || end >= this->length) throw std::out_of_range(LL_INDEX_OUT_OF_RANGE_MESSAGE);
		if (start > end) throw std::logic_error("Quack! End must be not less than start.");

		LinkedList<T>* newList = new LinkedList<T>(); 

		Node* ptr = this->head;
		Node** newPtr = &newList->head;

		for (int i = 0; i <= end; i++, ptr = ptr->next) {
			if (i >= start) {
				*newPtr = new Node;
				(*newPtr)->data = ptr->data;
				newPtr = &((*newPtr)->next);
			}

		}

		newList->length = end - start + 1;

		return newList;
	}

	// Получить длину списка
	int getLength() const { return this->length; }

	//Добавляет элемент в конец списка
	void append(const T& data) {
		Node** ptr = &(this->head);
		while (*ptr != nullptr) ptr = &((*ptr)->next);

		(*ptr) = new Node;
		(*ptr)->data = data;

		this->length++;
	}

	// Добавляет элемент в начало списка
	void prepend(const T& data) {
		
		Node* ptr = new Node{ data, this->head };
		this->head = ptr;

		this->length++;
	}

	/*bool find(const T& data) {
		Node* ptr = this->head;
		while (ptr != nullptr) {
			if (ptr->data == data) return true;
			ptr = ptr->next;
		}
		return false;
	}*/

	// удаление по индексу
	void remove(int index) {
		if (index < 0 || index >= this->length) throw std::out_of_range(LL_INDEX_OUT_OF_RANGE_MESSAGE);

		// элемент, следующий для которого - начало списка
		Node preHead = { this->head->data, this->head };
		Node* ptr;

		// доходим до нужного нам (как следующего)
		{
			int i = 0;
			for (i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		Node* tmp = ptr->next; // запоминаем 
		ptr->next = ptr->next->next; // сдвигаем список
		delete tmp; // удаляем 

		this->head = preHead.next; // в случае если был удален первый элемент

		this->length--; // не забываем изменить размер списка
	}

	// Вставляет элемент в заданную позицию
	void insert(const T& data, int index) {
		if (index < 0 || index > this->length) throw std::out_of_range(LL_INDEX_OUT_OF_RANGE_MESSAGE);

		// аналогично remove, только
		Node preHead = { this->head->data, this->head };
		Node* ptr;

		{
			int i = 0;
			for (i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		ptr->next = new Node{ data, ptr->next }; //создаем и вставляем новый элемент списка
		this->head = preHead.next;

		this->length++; // увеличиваем длину 
	}

	//Сцепляет два списка
	LinkedList<T>* concat(const LinkedList<T>& list) const {
		Node* ptr1 = this->head;
		Node* ptr2 = list.head;

		LinkedList<T>* newList = new LinkedList<T>();
		Node** ptr = &(newList->head);
		// добавляем первый список
		while (ptr1 != nullptr) {
			*ptr = new Node{ //создаём элемент
				ptr1->data,
				ptr1->next
			};
			// переходим на следующую итерацию
			ptr1 = ptr1->next; // в первом списке
			ptr = &((*ptr)->next); // в получаемом списке
		}
		// добавляем второй список (ptr = nullptr), аналогично
		while (ptr2 != nullptr) {
			*ptr = new Node{
				ptr2->data,
				ptr2->next
			};

			ptr2 = ptr2->next;
			ptr = &((*ptr)->next);
		}

		newList->length = this->length + list.length; // не забываем указывать размер 
		return newList;
	}

	// сравнение списков 
	bool operator==(const LinkedList<T>& list) const {
		if (this->length != list.length) return false;

		for (int i = 0; i < this->length; i++) {
			if (this->get(i) != list.get(i)) return false;
		}

		return true;
	}

};


#endif // !LINKEDLIST_H