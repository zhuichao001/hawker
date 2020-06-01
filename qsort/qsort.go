package main

import (
    "fmt"
)

func qsort(a []int, l, r int) {
    if l < r {
        key := a[(l+r)/2]
        i, j := l, r
        for {
            for a[i] < key {
                i++
            }
            for a[j] > key {
                j--
            }
            if i >= j {
                break
            }
            a[i], a[j] = a[j], a[i]
            i, j = i+1, j-1
        }
        qsort(a, l, i-1)
        qsort(a, j+1, r)
    }
}

func test(){
    a := []int{15, 20, 3, 8, 9, 7, 2, 16, 7, 3, 1, 11, 18, 10,6}
    qsort(a, 0, len(a)-1)    
    for _, x := range a {
        fmt.Println(x)
    }
}

func main(){
    test()
}
