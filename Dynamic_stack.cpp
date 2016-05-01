#include "Dynamic_stack.h"

template <typename Type>
Dynamic_stack<Type>::Dynamic_stack(int n) :
	entry_count(0),
	initial_capacity(n),
	array_capacity(n),
	array(new Type[array_capacity]),
	stack_pointer(array - 1) {
}

template <typename Type>
Dynamic_stack<Type>::Dynamic_stack(Dynamic_stack<Type> const &stack) :
	entry_count(0),
	initial_capacity(stack.initial_capacity),
	array_capacity(stack.array_capacity),
	array(new Type[array_capacity]),
	stack_pointer(array - 1) {
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure

	Type *pointer = stack.stack_pointer;

	// Copy the stored objects
	for (int i = (stack.size() - 1); i >= 0; i--) {
		push(*(pointer - i));
	}
}

template <typename Type>
Dynamic_stack<Type>::~Dynamic_stack() {
	// Frees the memory allocated for the array
	delete[] array;
}

template <typename  Type>
Type Dynamic_stack<Type>::top() const {
	if (size() == 0) {
		throw std::exception("Empty Stack");
	}
	else {
		return *stack_pointer;
	}
}

template <typename Type>
int Dynamic_stack<Type>::size() const {
	return entry_count;
}

template <typename Type>
bool Dynamic_stack<Type>::empty() const {
	return entry_count == 0;
}

template <typename Type>
int Dynamic_stack<Type>::capacity() const {
	return array_capacity;
}

template <typename Type>
void Dynamic_stack<Type>::swap(Dynamic_stack<Type> &stack) {
	std::swap(entry_count, stack.entry_count);
	std::swap(initial_capacity, stack.initial_capacity);
	std::swap(array_capacity, stack.array_capacity);
	std::swap(array, stack.array);
	std::swap(stack_pointer, stack.stack_pointer);
}

template <typename Type>
Dynamic_stack<Type> &Dynamic_stack<Type>::operator=(Dynamic_stack<Type> const &rhs) {
	// Check if the argument is itself
	// if so, do nothing
	if (this == &rhs) {
		return *this;
	}

	Dynamic_stack<Type> copy(rhs);

	swap(copy);

	return *this;
}

template <typename Type>
void Dynamic_stack<Type>::push(Type const &obj) {
	// If array is full, then double the capacity
	if (size() == capacity()) {
		Dynamic_stack<Type> *new_stack = new Dynamic_stack<Type>(2 * capacity());

		for (int i = (size() - 1); i >= 0; i--) {
			new_stack->push(*(stack_pointer - i));
		}

		// Store the original initial_capacity
		int original_initial_capacity = initial_capacity;
		this->swap(*new_stack);
		this->initial_capacity = original_initial_capacity;
		push(obj);
	}
	else {
		*(++stack_pointer) = obj;
		entry_count++;
	}
}

template <typename Type>
Type Dynamic_stack<Type>::pop() {
	// Check if array empty,
	// if so, throw underflow exception
	if (empty()) {
		throw std::exception("Empty Stack");
	}

	// Store the object at the top of the stack
	// and move down the stack_pointer by 1 step
	Type obj = *stack_pointer--;
	entry_count--;

	// Check if the array size has gone down
	// to 1/4 of the current capacity,
	// if so, half the capacity
	if (entry_count == (capacity() / 4) &&
		capacity() > initial_capacity) {
		array_capacity = capacity() / 2;
		Dynamic_stack<Type> *new_stack = new Dynamic_stack<Type>(*this);
		swap(*new_stack);
	}

	return obj;
}

template <typename Type>
void Dynamic_stack<Type>::clear() {
	delete[] array;
	array = new Type[initial_capacity];
}