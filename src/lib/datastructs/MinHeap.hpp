#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <iostream>
#include <stdexcept>

/**
 * @brief A template class implementing a min heap data structure.
 * 
 * @tparam T The type of elements stored in the heap.
 */
template <class T> class MinHeap {
    private:
        T* array;
        int length;
        int cap;
        bool isDynamic;
        
        inline int parent(int idx) const { return (idx - 1) / 2; }
        inline int left(int idx) const { return idx * 2 + 1; } 
        inline int right(int idx) const { return idx * 2 + 2;}

        void resize() {
            this->cap *= 2;
            T* temp = new T[this->cap];

            for(int i = 0; i < this->length; i++) 
                temp[i] = this->array[i];

            delete[] this->array;
            this->array = temp;
        }

        void siftUp(int idx) {
            int p = this->parent(idx);

            while(idx != 0 && this->array[p] > this->array[idx]) {
                this->swap(idx, p);
                idx = p;
                p = this->parent(idx);
            }
        }

        void siftDown(int idx) {
            int l = this->left(idx),
                r = this->right(idx),
                min = idx;

            while((l < this->length && this->array[l] < this->array[idx]) || 
                  (r < this->length && this->array[r] < this->array[idx])) {
                
                min = r >= this->length || this->array[l] < this->array[r] ? l : r;
                this->swap(idx, min);

                idx = min;
                l = this->left(idx);
                r = this->right(idx);
            }
        }

        int indexOf(const T& element) const {
            int idx = 0;

            while(idx < length) {
                if(array[idx] == element) 
                    return idx; 

                if(element < array[idx]) 
                    idx = left(idx);
                else 
                    idx = right(idx);
            }

            return -1;
        }

        void swap(int i, int j) {
            T tmp = this->array[i];
            this->array[i] = this->array[j];
            this->array[j] = tmp;
        }

    public:

        MinHeap() {
            this->array = new T[10];
            this->isDynamic = true;
            this->length = 0;
            this->cap = 10;
        }

        MinHeap(const MinHeap<T>& heap) {
            this->array = new T[heap.capacity()];
            this->isDynamic = heap.isDynamic;
            this->length = heap.size();
            this->cap = heap.capacity();

            for(int i = 0; i < this->length; i++) 
                this->array[i] = heap.array[i];
        }

        MinHeap(const T* arr, int capacity) {
            this->array = new T[capacity];
            this->isDynamic = false;
            this->length = capacity;
            this->cap = capacity;

            for(int i = 0; i < this->length; i++) 
                this->array[i] = arr[i];

            for(int i = (this->length - 2) / 2; i >= 0; --i) 
                this->heapify(i);
        }

        MinHeap(int capacity) {
            this->array = new T[capacity];
            this->isDynamic = false;
            this->length = 0;
            this->cap = capacity;
        }

        ~MinHeap() {
            delete[] this->array;
        }

        inline int size() const { return this->length; }

        inline int capacity() const { return this->cap; }

        inline bool isFull() const { return !this->isDynamic && this->length == this->cap; }
        
        inline bool isEmpty() const { return this->length == 0; }

        void add(const T& element) {
            if(this->isDynamic && this->length >= this->cap * 0.75)
                this->resize();

            this->array[this->length++] = element;
            this->siftUp(this->length - 1);
        }

        T replace(int idx, const T& element) {
            if(idx < 0 || idx >= this->length)
                throw std::out_of_range("Index out of range");

            T res = this->array[idx];
            this->array[idx] = element;

            if(element < res)
                this->siftUp(idx);
            else
                this->siftDown(idx);

            return res;
        }

        T pop() {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            T element = this->array[0];
            this->array[0] = this->array[--this->length];
            this->siftDown(0);

            return element;
        }

        T min() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            return this->array[0];
        }

        T max() const {
            if(this->isEmpty())
                throw std::out_of_range("Heap is empty");

            int max = 0;

            for(int i = 1; i < this->length; i++)
                if(this->array[i] > this->array[max])
                    max = i;

            return this->array[max];
        }

        bool contains(const T& element) const {
            return this->indexOf(element) != -1;
        }

        void clear() {
            this->length = 0;
        }

        T& operator[](int idx) {
            if(idx < 0 || idx >= this->length)
                throw std::out_of_range("Index out of range");

            return this->array[idx];
        }

        MinHeap<T>& operator=(const MinHeap<T>& heap) {
            if(this != &heap) {
                delete[] this->array;

                this->isDynamic = heap.isDynamic;
                this->length = heap.size();
                this->cap = heap.capacity();
                this->array = new T[heap.capacity()];

                for(int i = 0; i < this->length; i++) 
                    this->array[i] = heap.array[i];
            }

            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const MinHeap<T>& heap) {
            for(int i = 0; i < heap.length; i++)
                out << heap.array[i] << " ";
            
            return out;
        }

        friend bool operator==(const MinHeap<T>& heap1, const MinHeap<T>& heap2) {
            bool eq = heap1.length == heap2.length;

            for(int i = 0; eq && i < heap1.length; i++) 
                eq = heap1.array[i] == heap2.array[i];

            return eq;
        }

        inline friend bool operator!=(const MinHeap<T>& heap1, const MinHeap<T>& heap2) { return !(heap1 == heap2); }
};

#endif