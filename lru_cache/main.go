package main

import(
    "fmt"
)


func test() {
   u := NewLru(1) 
   u.Put("ab", "123")
   u.print()
   fmt.Println("--------------")
   u.Put("abc", "1234")
   u.Put("abc", "1")
   u.print()
}

func main(){
    test()
}
