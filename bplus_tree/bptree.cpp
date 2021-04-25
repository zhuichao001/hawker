#include "bptree.h"

namespace bplus_tree {

bpnode * bpjunc::split(){
    const int len = childs.size();
    bpjunc * apart = new bpjunc;
    for(auto it = childs.begin()+len/2; it!=childs.end();){
        apart->childs.push_back(*it);
        childs.erase(it);
    }
    apart->minkey = apart->childs[0]->minkey;
    apart->parent = this->parent;

    if(this->next!=nullptr){
        this->next->prev = apart;
    }
    apart->prev = this;
    apart->next = this->next;
    this->next = apart;
    return apart;
}

bpnode * bpjunc::descend(string key){
    const int len = childs.size();
    if(childs.size()==0 || key<childs[0]->minkey){
        return nullptr;
    }

    for(int i=0; i<len-1; ++i){
        if(key>=childs[i]->minkey && key<childs[i+1]->minkey){
            return childs[i];
        }
    }
    return childs[len-1];
}

int bpjunc::adopt(bpnode * son){
    if(childs.size()==0){
        childs.push_back(son);
        minkey = son->minkey;
        son->prev = nullptr;
        son->next = nullptr;
        son->parent = this;
        return 0;
    }

    vector<bpnode*>::iterator it = childs.begin();
    for(;it!=childs.end();++it){
        if((*it)->minkey > son->minkey){
            break;
        }
    }
    it = childs.insert(it, son);
    son->prev = *(it-1);
    son->next = *it;
    (*it)->prev = son;
    (*(it-1))->next = son;
    return 0;
}

int bpjunc::abandon(bpnode * son){
    auto it = find(childs.begin(), childs.end(), son);
    if(it==childs.end()){
        return -1;
    }

    if(*it==childs.front() && childs.size()>1){
        childs[1]->prev = nullptr;
        childs.erase(it);
        return 0;
    }

    (*(it-1))->next = (*it)->next;
    if(*it!=childs.back()){
        (*(it+1))->prev = (*it)->prev;
    }
    childs.erase(it);
    return 0;
}

bpnode * bpleaf::split(){
    vector<string> keys;
    for(auto it=kvgroup.begin(); it!=kvgroup.end(); ++it){
        keys.push_back(it->first);
    }
    sort(keys.begin(), keys.end());
    string midkey = keys[keys.size()/2];
    bpleaf *apart = new bpleaf;
    for(auto it=keys.begin(); it!=keys.end(); ++it){
        apart->put(*it, kvgroup[*it]);
        this->del(*it);
    }
    return apart;
}

int bpleaf::get(string key, string &val){
    auto it = kvgroup.find(key);
    if(it==kvgroup.end()){
        return -1;
    }else{
        val = it->second;
        return 0;
    }
}

int bpleaf::put(string key, string val){
    if(get(key,val)==0){
        kvgroup[key] = val;
        return 0;
    }

    if(key<minkey){
        return -1;
    }

    kvgroup[key] = val;

    if(full()){
        bpnode *apart = split();
        dynamic_cast<bpjunc*>(parent)->adopt(apart);
    }

    return 0;
}

int bpleaf::del(string key){
    auto it = kvgroup.find(key);
    if(it==kvgroup.end()){
        return -1;
    }
    kvgroup.erase(it);
    return 0;
}

int bptree::get(string key, string &val){
    bpnode *node = findlower(key);
    bpnode *dst = dynamic_cast<bpjunc*>(node)->descend(key);
    if(dst==nullptr){
        return -1;
    }
    return dynamic_cast<bpleaf*>(dst)->get(key, val);
}

bpnode * bptree::findlower(string key){
    bpnode *cur = root;
    bpnode *son = nullptr;
    while(true){
        son = dynamic_cast<bpjunc*>(cur)->descend(key);
        if(son==nullptr || son->isleaf()){
            break;
        }
        cur = son;
    }
    return cur;
}

int bptree::put(string key, string val){
    bpnode *node = findlower(key);
    bpnode *dst = dynamic_cast<bpjunc*>(node)->descend(key);
    if(dst==nullptr){
        bpleaf *leaf = new bpleaf;
        leaf->put(key, val);
        dynamic_cast<bpjunc*>(node)->adopt(leaf);
        if(node->full()){
            splitby(node);
        }
        return 0;
    }
    dynamic_cast<bpleaf*>(dst)->put(key, val);
    if(dst->full()){
        splitby(dst);
    }
    return 0;
}

int bptree::splitby(bpnode *node){
    if(node==nullptr){
        return -1;
    }
    while(true){
        bpnode *apart = node->split();
        if(node==root){
            root = new bpjunc;
            dynamic_cast<bpjunc*>(root)->adopt(node);
            dynamic_cast<bpjunc*>(root)->adopt(apart);
            return 0;
        }
        dynamic_cast<bpjunc*>(node->parent)->adopt(apart);
        if(!node->parent->full()){
            break;
        }
        node = node->parent;
    }
    return 0;
}

int bptree::del(string key){
    bpnode *node = findlower(key);
    bpnode *dst = dynamic_cast<bpjunc*>(node)->descend(key);
    if(dst==nullptr){
        return -1;
    }
    dynamic_cast<bpleaf*>(dst)->del(key);

    while(dst->empty() && dst!=root){
        dynamic_cast<bpjunc*>(dst->parent)->abandon(dst);
        bpnode *tmp = dst;
        dst = dst->parent;
        delete tmp;
    }
    return 0;
}

int bptree::scan(string lower, string upper){
    //TODO next version
    return 0;
}

} //end of namespace bplus_tree
