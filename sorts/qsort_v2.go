package main

import (
    "math"
    "fmt"
)

func qsort(a []int) {
    size := math.Ilogb(float64(len(a)))*2+2
    stack, top := make([]int, size), 0

    stack[top], stack[top+1] = 0, len(a)-1
    top += 2

    for top > 0 {
        l, r := stack[top-2], stack[top-1]
        top -= 2

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

        if i-1 > l { 
            stack[top], stack[top+1] = l, i-1
            top += 2
        }
        if j+1 < r { 
            stack[top], stack[top+1] = j+1, r
            top += 2
        }
    }
}

func test(){
    a := []int{15, 20, 3, 8, 9, 7, 2, 16, 7, 3, 1, 11, 18, 10,6}
    qsort(a)    
    for _, x := range a {
        fmt.Println(x)
    }
}

func main(){
    test()
}
