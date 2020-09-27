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
    FreqNode *prev;
    FreqNode *post;

    int freq;

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

    void add_freq(FreqNode *br, int freq){
        FreqNode *tmp = new FreqNode(freq);
        if(br->post != nullptr){
            tmp->post = br->post;
            br->post->prev = tmp;
        }
        tmp->prev = br->prev;
        br->post = tmp;
    }

    void del_freq(FreqNode *br){
        br->post->prev = br->prev;        
        br->prev->post = br->post;
        delete br;
    }

    int get(const string &key, string &val){
        auto it = cache.find(key);
        if(it != cache.end()){
            Node *node = it->second;
            val = node->val;
            node->slot->remove(node);
            node->slot->append(node);
            return 0;
        } else {
            return -1;
        }
    }
    
    void put(const string &key, const string &val){
        auto it = cache.find(key);
        if(it != cache.end()){ //update
            Node *node = it->second;
            node->slot->remove(node);
            int freq = node->slot->freq + 1;
            if(node->slot->post == nullptr || node->slot->post->freq != freq){
                add_freq(node->slot, freq);
            }

            if(node->slot->empty()){
                del_freq(node->slot);
            }

            node->slot->post->append(node);
            cache[key] = node;
        } else { //add
            if(size==capacity){
                if(freq_list.post!=nullptr){
                    freq_list.post->pop();
                }
            }

            if(freq_list.post==nullptr || freq_list.post->freq != 1){
                add_freq(&freq_list, 1);
            }

            Node *node = new Node(key, val);
            freq_list.post->append(node);
            cache[key] = node;
            ++size;
        }
    }
};

