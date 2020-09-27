#include <map>

using namespace std;

struct FreqNode;

struct Node{
    string key;
    string val;   
    Node *up;
    Node *down;
    FreqNode *slot;
    Node(const string &k, const string &v):key(k),val(v){
        slot = nullptr;
        up = nullptr; 
        down = nullptr;
    }
};

struct FreqNode{
    int freq;
    FreqNode *prev;
    FreqNode *post;
    Node *first;
    Node *last;

    FreqNode(int f):freq(f){
        prev = nullptr;
        post = nullptr;
        first = nullptr;
        last = nullptr;
    }

    bool empty(){
        return first == nullptr;
    }

    void remove(Node *node){
        if(node == first){
            first = first->down;
            if(first==nullptr){
                last = nullptr;
            }
            return;
        }

        if(node == last){
            last = last->up;
            if(last==nullptr){
                first = nullptr;
            }
            return;
        }

        node->up->down = node->down;
        node->down->up = node->up;
    }

    Node *pop(){
        if(first==nullptr){
            return NULL; 
        }

        Node *res = first;;
        first = first->down;
        if(first==nullptr){
            last = nullptr;
        }
        return res;
    }

    void append(Node *node){
        node->down = nullptr;
        node->slot = this;
        if(first == nullptr){
            first = last = node;
            return;
        }
        last->down = node;    
        node->up = last;
        last = node;
    }
};

struct LFUCache{
    map<string, Node*> cache;
    int size;
    const int capacity;
    FreqNode freq_list;

    LFUCache(int c):capacity(c),size(0),freq_list(0){}

    void add_slot(FreqNode *br, int freq){
        FreqNode *tmp = new FreqNode(freq);
        if(br->post != nullptr){
            tmp->post = br->post;
            br->post->prev = tmp;
        }
        tmp->prev = br;
        br->post = tmp;
    }

    void del_slot(FreqNode *br){
        if(br->post!=nullptr){
            br->post->prev = br->prev;        
        }
        if(br->prev!=nullptr){
            br->prev->post = br->post;
        }
        delete br;
    }

    int get(const string &key, string &val){
        auto it = cache.find(key);
        if(it != cache.end()){
            Node *node = it->second;
            val = node->val;
            inc_freq(node);
            return 0;
        } else {
            return -1;
        }
    }

    void inc_freq(Node *node){
        node->slot->remove(node);
        const int freq = node->slot->freq + 1;
        if(node->slot->post == nullptr || node->slot->post->freq != freq){
            add_slot(node->slot, freq);
        }

        if(node->slot->empty()){
            del_slot(node->slot);
        }

        node->slot->post->append(node);
    }
    
    void put(const string &key, const string &val){
        auto it = cache.find(key);
        if(it != cache.end()){ //update
            Node *node = it->second;
            node->val = val;
            inc_freq(node);
            cache[key] = node;
        } else { //add
            if(size==capacity){
                if(freq_list.post!=nullptr){
                    freq_list.post->pop();
                }
            }

            if(freq_list.post==nullptr || freq_list.post->freq != 1){
                add_slot(&freq_list, 1);
            }

            Node *node = new Node(key, val);
            freq_list.post->append(node);
            cache[key] = node;
            ++size;
        }
    }
};

