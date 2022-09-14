#include <assert.h>

template <typename T>
struct ring_array{
    int capacity;
    int start_idx;
    int end_idx;
    T *array;

    ring_array(int cap = 32):
        capacity(cap){ //holding at most capacity-1 elements
        start_idx = 0;
        end_idx = 0;
        array = new T[capacity]; //[,): left-close/right-open 
        assert(array!=nullptr);
    }

    int incr_pos(const int offset){
        return (offset+1) % capacity;
    }

    int decr_pos(const int offset){
        return (offset-1+capacity) % capacity;
    }

    bool full(){
        return size()==capacity-1;
    }

    bool empty(){
        return size()==0;
    }

    bool push_front(const T &t){
        if(full()){
            return false;
        }
        start_idx = decr_pos(start_idx);
        array[start_idx] = t;
        return true;
    }

    bool push_back(const T &t){
        if(full()){
            return false;
        }
        array[end_idx] = t;
        end_idx = incr_pos(end_idx);
        return true;
    }

    bool pop_front(T &t){
        if(empty()){
            return false;
        }
        t = array[start_idx];
        start_idx = incr_pos(start_idx);
        return true;
    }

    bool pop_back(T &t){
        if(empty()){
            return false;
        }
        end_idx = decr_pos(end_idx);
        t = array[end_idx];
    }

    int size(){
        return (end_idx + capacity - start_idx) % capacity;
    }
};

template <typename T>
class deque{
    int start_slot;
    int end_slot;

    int max_slot; //capcity of table
    ring_array<T> **table;

public:
    deque():
        start_slot(127),
        end_slot(127),
        max_slot(256){
        table = new ring_array<T> *[max_slot];
        for(int i=0; i<max_slot; ++i){
            table[i] = nullptr;
        }
        table[start_slot] = new ring_array<T>();
    }
    
    bool empty(){
        assert(end_slot>=start_slot);
        if(end_slot-start_slot>0){
            return false;
        }
        return table[start_slot]->empty();
    }

    void push_front(const T &t){
        if(table[start_slot]->full()){
            if(start_slot==0){ //resize
                expand();
            }
            --start_slot;
            if(table[start_slot]==nullptr){
                table[start_slot] = new ring_array<T>();
            }
        }
        table[start_slot]->push_front(t);
    }

    void push_back(const T &t){
        if(table[end_slot]->full()){
            if(end_slot==max_slot-1){ //resize
                expand();
            }
            ++end_slot;
            if(table[end_slot]==nullptr){
                table[end_slot] = new ring_array<T>();
            }
        }
        table[end_slot]->push_back(t);
    }

    bool pop_front(T &t){
        if(empty()){
            return false;
        }
        if(table[start_slot]->empty()){
            ++start_slot;
        }
        return table[start_slot]->pop_front(t);
    }

    bool pop_back(T &t){
        if(empty()){
            return false;
        }
        if(table[end_slot]->empty()){
            --end_slot;
        }
        return table[end_slot]->pop_back(t);
    }

    void expand(){
        int new_max_slot = 3*max_slot;

        ring_array<T> **new_table = new ring_array<T> *[new_max_slot];
        for(int i=0; i<new_max_slot; ++i){
            new_table[i] = nullptr;
        }

        for(int i=max_slot; i<max_slot*2; ++i){
            new_table[i] = table[i-max_slot];
        }

        start_slot = max_slot;
        end_slot = max_slot*2-1;
        delete []table;
        table = new_table;
        max_slot = new_max_slot;
    }

    bool size(){
        int total=0;
        for(int i=start_slot; i<=end_slot; ++i){
            assert(table[i]!=nullptr);
            total += table[i]->size();
        }
        return total;
    }
};
