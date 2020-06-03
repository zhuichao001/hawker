package main


import(
    "fmt"
    "errors"
)


type Entry struct {
    prev, next *Entry 
    key string
    value interface{}
}

type Lru struct {
    head, tail *Entry
    index map[string]*Entry
    n, capacity uint32
}


func NewLru(c uint32) (u *Lru) {
    if c == 0 {
        panic("Lru's capacity must not be zero")
    }

    u = &Lru{}
    u.capacity = c
    u.n = 0
    u.head = nil
    u.tail = nil
    u.index = make(map[string]*Entry, c)
    return
}

func (u *Lru) print() {
    cur := u.head
    for cur != nil {
       fmt.Println("key=%+v, value=%+v", cur.key, cur.value)
       cur = cur.next
    }
}

func (u *Lru) elect(e *Entry) {
    if e == u.head {
        return
    }
    if e == u.tail {
        u.tail.prev.next = nil
        u.tail = e.prev

        u.head.prev = e
        e.next = u.head
    } else {
        e.next.prev = e.prev
        e.prev.next = e.next

        e.next = u.head
        u.head.prev = e
    }
    u.head = e
}


func (u *Lru) add(key string, value interface{}) {
    e := &Entry{nil, nil, key, value}

    if u.head !=nil {
        u.head.prev = e
        e.next = u.head
    }
    u.head = e

    if u.n == u.capacity {
        u.tail.prev.next = nil
        u.tail = u.tail.prev
    } else {
        u.n += 1 
    }

    if u.tail == nil {
        u.tail = e
    }
    u.index[key] = e
}


func(u *Lru) Put(key string, value interface{}) error {
    if e, ok:= u.index[key]; ok {
        e.value = value
        u.elect(e)        
    } else {
        u.add(key, value)
    }
    return nil
}


func(u *Lru) Get(key string) (value interface{}, err error){
   if e, ok:= u.index[key]; ok {
       u.elect(e)
       return e.value, nil
   } else {
       return nil, errors.New(fmt.Sprintf("Key[%s] Not Exist", key))
   }
}

