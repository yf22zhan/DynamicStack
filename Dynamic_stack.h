#pragma once
#include <stdexcept>

template <typename Type>
class Dynamic_stack {
	private:
		int entry_count;
		int initial_capacity;
		int array_capacity;
		Type *array;
		Type *stack_pointer;

	public:
		Dynamic_stack( int = 10 );
		Dynamic_stack( Dynamic_stack const & );
		~Dynamic_stack();

		Type top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Dynamic_stack & );
		Dynamic_stack &operator=( Dynamic_stack const & );
		void push( Type const & );
		Type pop();
		void clear();
};