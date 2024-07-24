#include <stdio.h>
#include <utility>

template <typename T, size_t N>
class ringBuffer {
public:
    explicit ringBuffer():
        capacity_(N+1),
        begin_(0),
        end_(0){
        data_ = new T[capacity_];
    }

    ~ringBuffer(){
        delete []data_;
    }

    bool empty() const {
        return end_ == begin_;
    }

    bool full(){
        return length() == capacity_-1;
    }

    bool push(T &&value){
        if(full()){
            return false;
        }
        data_[end_] = value;
        end_ = (end_+1)  % capacity_;
        return true;
    }

    bool pop(T &value){
        if(empty()){
            return false;
        }
        value = data_[begin_];
        begin_ = (begin_+1)  % capacity_;
        return true;
    }

    int length(){
        return (end_+capacity_-begin_) % capacity_;
    }

private:
    int capacity_;
    int begin_;
    int end_;
    T *data_;
};


template <typename T>
class ringBuffer<T,10>;

int main(){
    ringBuffer<int> r(4);
    r.empty();
    r.push(1);
    r.push(2);
    r.push(3);
    r.push(4);

    int v;
    for(int i=0; i<5; i++){
       bool ok = r.pop(v);
       printf("ok:%d , %d\n", ok, v);
    }
    return 0;
}
