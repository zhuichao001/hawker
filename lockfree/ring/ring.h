
template<class T>
class Ring {
public:
    enum FLAG_STATE{
        FLAG_FREE    = 0,
        FLAG_WRITING = 1,
        FLAG_READY  = 2,
        FLAG_READING = 3,
    };

    Ring(int n):
        capacity_(n){
        num_ = 0;
        head_ = 0;
        tail_ = 0;

        flags_ = new FLAG_STATE[capacity_];
        memset(flags_, FLAG_FREE, capacity_);

        array_ = new T[capacity_];
    }

    ~Ring() {
        delete []flags_;
        delete []array_;
    }

    bool push(const T & e){
        if(num_ == capacity_){
            return false;
        }

        int idx = tail_;
        FLAG_STATE * flag = flags_ + idx;
        
        // busy wait until flag is occupied
        while (!__sync_bool_compare_and_swap(flag, FLAG_FREE, FLAG_WRITING)) {
            idx = tail_;
            flag = flags_ +  idx;
        }

        int tail = (idx + 1) % capacity_;
        //maybe has been updated by other thread
        __sync_bool_compare_and_swap(&tail_, idx, tail);

        *(array_ + idx) = e;
        *flag = FLAG_READY;

        __sync_fetch_and_add(&num_, 1);

        return true;
    }

    bool pop(T * e) {
        if (num_ == 0){
            return false;
        }

        int idx = head_;
        FLAG_STATE * flag = flags_ + idx;

        while (!__sync_bool_compare_and_swap(flag, FLAG_READY, FLAG_READING)) {
            idx = head_;
            flag = flags_ + idx;
        }

        int head = (idx + 1) % capacity_;
        __sync_bool_compare_and_swap(&head_, idx, head);

        *e = *(array_ + idx);
        *flag = FLAG_FREE;

        __sync_fetch_and_sub(&num_, 1);

        return true;
    }

private:
    T * array_;
    FLAG_STATE * flags_;
    int capacity_;  
    int num_; 
    int head_;
    int tail_;
};
