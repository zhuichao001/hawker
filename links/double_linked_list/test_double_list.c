#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "double_list_head.h"


struct Person {
    int age;
    char name[20];
    ListHead list;

    Person() {
        init_list_head(&list);
        name[0] = 0;
    }

    Person(int _age, char *_name) {
        age = _age;
        int len = strlen(_name);
        memcpy(name, _name, len);
        name[len] = 0;
        init_list_head(&list);
    }
};


void printPersonList(Person *person_head) {
    printf("\n==== for each print ====\n");
    ListNode *pos;
    list_for_each(pos, &person_head->list) {
        Person * entry = list_entry(pos, Person, list);
        printf("name:%s, age:%d\n", entry->name, entry->age);
    }
    printf("\n");

}


int main (int argc, char* argv[]) {
    Person person_head;

    //add Persons
    for (int i=0; i<5; ++i) {
        char bufname[20]={0,};
        sprintf(bufname, "I am no:%d", i+1);
        Person *p = new Person(18+i, bufname);

        list_add_tail(&p->list, &person_head.list);
    }

    printPersonList(&person_head);

    //del Node of age:20
    printf("==== delete node(age:20) ====\n");
    ListNode *pos, *next;
    list_for_each_safe(pos, next, &person_head.list) {
        Person *entry = list_entry(pos, Person, list);
        if(entry->age == 20) {
            list_del(pos);
            free(entry);
        }
    }

    printPersonList(&person_head);

    //release all nodes
    list_for_each_safe(pos, next, &person_head.list) {
        Person *entry = list_entry(pos, Person, list);
        list_del(pos);
        free(entry);
    }
    return 0;
}
