#include <map>
#include <assert.h>
#include <string>
#include <iostream>

template<typename VT>
class FreqNode;

template<typename VT>
class LFUCache;

template<typename VT>
class Node{
    std::string key;
    VT val;   

    Node<VT> *up, *down;
    FreqNode<VT> *slot;

    friend FreqNode<VT>;
    friend LFUCache<VT>;
public:
    Node(){
        up = this; 
        down = this;
        slot = nullptr;
    }

    Node(const std::string &k, const VT &v):
        key(k),
        val(v){
        Node();
    }
};

//FIFO
template<typename VT>
class FreqNode{
    int freq;
    Node<VT> dummy; 
    friend LFUCache<VT>;
public:
    FreqNode(int f): freq(f){
        assert(freq>0);
    }

    bool empty(){
        return dummy.down == &dummy;
    }

    void remove(Node<VT> *node){
        node->up->down = node->down;
        node->down->up = node->up;
    }

    Node<VT> *pop(){  //pop from head
        if(empty()){
            return nullptr; 
        }

        Node<VT> *res = dummy.down;
        remove(res);
        return res;
    }

    void push(Node<VT> *node){  //push to tail
        assert(node!=nullptr);
        node->up = dummy.up;
        node->down = &dummy;
        dummy.up->down = node;
        dummy.up = node;
    }

    void display(){
        Node<VT> *node = dummy.down;
        std::cout<<"    ";
        while(node!=&dummy){
           std::cout<<"("<<node->key<<","<<node->val<<"), "; 
           node = node->down;
        }
        std::cout<<std::endl;
    }
};

template<typename VT>
class LFUCache{
    std::map<std::string, Node<VT>*> cache_map;
    int size;
    const int capacity;
    std::map<int, FreqNode<VT> *> freq_map;

public:
    LFUCache(int c):
        size(0),
        capacity(c){
    }

    bool get(const std::string &key, VT &val){
        auto it = cache_map.find(key);
        if(it != cache_map.end()){
            Node<VT> *node = it->second;
            val = node->val;
            inc_freq(node);
            return true;
        } else {
            return false;
        }
    }

    void put(const std::string &key, VT &val){
        auto it = cache_map.find(key);
        if(it != cache_map.end()){ //update
            Node<VT> *node = it->second;
            node->val = val;
            inc_freq(node);
        } else { //add
            if(size==capacity){
                eliminate(); //pepare quota
            }

            Node<VT> *node = new Node<VT>(key, val);
            inc_freq(node);

            cache_map[key] = node;
            ++size;
        }
    }

    void display(){
        for(const auto &p : freq_map){
            if(p.second->empty()){
                continue;
            }
            std::cout << "freq:" <<p.second->freq << std::endl;
            p.second->display();
        }
        std::cout << "-------------------" << std::endl;
    }

private:
    void eliminate(){
        for(auto it=freq_map.begin(); it!=freq_map.end(); ++it){
            if(!it->second->empty()){
                Node<VT> *node = it->second->pop();
                cache_map.erase(node->key);
                delete node;
                break;
            }
        }
    }

    void inc_freq(Node<VT> *node){
        int new_freq = 1;
        if(node->slot!=nullptr){
            node->slot->remove(node);
            new_freq = node->slot->freq + 1;
        }
        auto it = freq_map.find(new_freq);
        FreqNode<VT> *freq_node = nullptr;
        if(it==freq_map.end()){
            freq_node = new FreqNode<VT>(new_freq);
            freq_map[new_freq] = freq_node;
        }else{
            freq_node = it->second;
        }
        node->slot = freq_node;
        freq_node->push(node);
    }
};
