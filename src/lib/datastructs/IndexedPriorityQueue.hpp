#ifndef INDEX_PRIORITY_QUEUE_HPP
#define INDEX_PRIORITY_QUEUE_HPP

#include <iostream>
#include <stdexcept>

template <class T> class IndexedPriorityQueue {
    private:
        int length;
        int cap;
        int degree;
        int *child, *parent;
        int* positionMap;
        int* inverseMap;
        T* array;

        void sink(int i) {
            int j = this->minChild(i);
            while(j != -1) {
                this->swap(i, j);
                i = j;
                j = this->minChild(i);
            }
        }

        void swim(int i) {
            while(this->array[this->inverseMap[i]] < this->array[this->inverseMap[this->parent[i]]]) {
                this->swap(i, this->parent[i]);
                i = this->parent[i];
            }
        }

        int minChild(int i) {
            int idx = -1;
            int start = this->child[i];
            int end = std::min(this->length, start + this->degree);

            for(int j = start; j < end; j++) 
                if(this->array[this->inverseMap[j]] < this->array[this->inverseMap[i]]) 
                    idx = i = j;

            return idx;
        }

        void swap(int i, int j) {
            this->positionMap[this->inverseMap[j]] = i;
            this->positionMap[this->inverseMap[i]] = j;

            int tmp = this->inverseMap[i];
            this->inverseMap[i] = this->inverseMap[j];
            this->inverseMap[j] = tmp;
        }

    public:

        IndexedPriorityQueue(int capacity = 3, int degree = 2) {
            if(degree < 2 || capacity < degree + 1) 
                throw std::invalid_argument("Invalid degree or capacity.");
    
            this->degree = degree;
            this->cap = capacity;
            this->length = 0;

            this->child = new int[this->cap];
            this->parent = new int[this->cap];
            this->positionMap = new int[this->cap];
            this->inverseMap = new int[this->cap];
            this->array = new T[this->cap];

            for(int i = 0; i < this->cap; i++) {
                this->child[i] = i*this->degree + 1;
                this->parent[i] = (i - 1)/this->degree;
                this->positionMap[i] = -1;
                this->inverseMap[i] = -1;
            }
        }

        IndexedPriorityQueue(const IndexedPriorityQueue<T>& queue) {
            this->degree = queue.degree;
            this->cap = queue.cap;
            this->length = queue.length;
        }

        ~IndexedPriorityQueue() {
            delete[] this->child;
            delete[] this->parent;
            delete[] this->positionMap;
            delete[] this->inverseMap;
            delete[] this->array;
        }

        IndexedPriorityQueue& operator=(const IndexedPriorityQueue<T>& queue) {
            if(this != &queue) {
                this->degree = queue.degree;
                this->cap = queue.cap;
                this->length = queue.length;
            }

            return *this;
        }

        inline int size() const { return this->length; }
        inline bool isEmpty() const { return this->length == 0; }
        inline bool isFull() const { return this->length == this->cap; }

        bool contains(int k) const {
            if(k < 0 || k >= this->cap)
                throw std::invalid_argument("Invalid index.");

            return this->positionMap[k] != -1;
        }

        int minKey() {
            if(this->isEmpty())
                throw std::out_of_range("Queue is empty.");

            return this->inverseMap[0];
        }

        int pollKey() {
            int k = this->minKey();
            this->remove(k);
            return k;
        }

        T peek() {
            if(this->isEmpty())
                throw std::out_of_range("Queue is empty.");

            return this->array[this->inverseMap[0]];
        }

        T poll() {
            T value = this->peek();
            this->remove(this->minKey());
            return value;
        }

        void insert(int k, const T& value) {
            if(this->contains(k))
                throw std::invalid_argument("Index already exists.");
            
            this->positionMap[k] = this->length;
            this->inverseMap[this->length] = k;
            this->array[k] = value;

            this->swim(this->length++);
        }

        T valueOf(int k) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            return this->array[k];
        }

        T remove(int k) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            int idx = this->positionMap[k];
            this->swap(idx, --this->length);
            this->swim(idx);
            this->sink(idx);

            T value = this->array[k];
            this->positionMap[k] = -1;
            this->inverseMap[this->length] = -1;
            this->array[k] = T();

            return value;
        }

        T change(int k, T value) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            T oldValue = this->array[k];

            this->array[k] = value;
            this->sink(this->positionMap[k]);
            this->swim(this->positionMap[k]);

            return oldValue;
        }

        void decrease(int k, T value) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            if(value < this->array[k]) {
                this->array[k] = value;
                this->swim(this->positionMap[k]);
            }
        }

        void increase(int k, T value) {
            if(!this->contains(k))
                throw std::invalid_argument("Index does not exist.");

            if(this->array[k] < value) {
                this->array[k] = value;
                this->sink(this->positionMap[k]);
            }
        }

        void clear() {
            for(int i = 0; i < this->length; i++) {
                this->positionMap[this->inverseMap[i]] = -1;
                this->inverseMap[i] = -1;
                this->array[i] = T();
            }

            this->length = 0;
        }

        friend std::ostream& operator<<(std::ostream& strm, const IndexedPriorityQueue<T>& queue) {
            strm << "[";
            for(int i = 0; i < queue.length; i++) {
                strm << queue.array[queue.inverseMap[i]];
                if(i != queue.length - 1) strm << ", ";
            }
            return strm << "]";
        }
};

#endif