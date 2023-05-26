//leecode 1109
//这里有 n 个航班，它们分别从 1 到 n 进行编号。有一份航班预订表 bookings ，
//表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi] ，
//意味着在从 firsti 到 lasti （包含 firsti 和 lasti ）的每个航班上预订了 seatsi 个座位。
//请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。
//
#include <stdio.h>
#include <memory.h>

void flight_seats(int bookings[][3], const int m, int seats[], const int n){
    memset(seats, 0, sizeof(int)*n);
    int diff[n]={0,};
    for(int i=0; i<m; ++i){
        int l = bookings[i][0]-1;
        int r = bookings[i][1];
        const int incr = bookings[i][2];
        diff[l] += incr;
        if(r<n){
            diff[r]-=incr;
        }
    }
    seats[0]=diff[0];
    for(int i=1; i<n; ++i){
        seats[i]=diff[i]+seats[i-1];
    }
}

int main(){
    int bookings[][3] = {{1,2,10},{2,3,20},{2,5,25}};
    int n = 5;
    int seats[n];
    flight_seats(bookings, 3, seats, n);
    for(int i=0; i<n; ++i){
        printf("flight-%d, seats:%d\n", i, seats[i]);
    }
}

