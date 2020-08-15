package main

import(
    "time"
    "fmt"
    "os"
    "bufio"
    "sync/atomic"
)


type BucketLimiter struct {
    Bucket int32
    Rest  int32
    Interval int32
}


func NewBucketLimiter(bucket int32, rate int32) (limiter *BucketLimiter) {
    limiter = &BucketLimiter{
        Bucket: bucket,
        Rest: 0,
        Interval: 1000000/rate, //MiliSecond
    }
    return
}


func (c *BucketLimiter)Acquire() bool {
    rest := c.Rest
    if rest <= 0 {
        return false
    }

    ok := atomic.CompareAndSwapInt32(&c.Rest, rest, rest-1)
    return ok
}


func (c *BucketLimiter)Run() {
    dura := time.Duration(c.Interval)*time.Microsecond
    ticker := time.NewTicker(dura)
    for {
        select {
            case <- ticker.C:
            if c.Rest >= c.Bucket {
                continue
            }
            atomic.CompareAndSwapInt32(&c.Rest, c.Rest, c.Rest+1)
            fmt.Println("@Add 1 Bucket")
        }
    }
}


func consume(limiter *BucketLimiter) {
    reader := bufio.NewReader(os.Stdin)
    for {
        reader.ReadString('\n')
        ok := limiter.Acquire()
        fmt.Println(ok)
    }
}


func main(){
    limiter := NewBucketLimiter(2, 3);
    go limiter.Run()
    consume(limiter)
}
