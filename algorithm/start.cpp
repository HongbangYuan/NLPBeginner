//
// Created by HarryPotter on 2022/9/6.
//
#include <iostream>
using namespace std;
int * bubble_sort(int a[],int,bool);
void reverse(int * A, int lo, int hi);
void print_array(int *,int );
int binary_sum(int A[],int lo,int hi);
void find_max2(const int * A, int lo,int hi,int &x1,int &x2);

int main(){
    int a[10] = {2,11,3,4,5,6,7,8,9,10};
//    int a[10] = {2,1,4};
    int N = 10;
//    int *b = bubble_sort(a,N, true);
//    reverse(a,0,N-1);
//    print_array(a,N);
    int x1,x2;
    find_max2(a,0,10,x1,x2);

    pair<int,pair<int,int>> result{1,{2,2}};
    result.first;
    cout << "A[x1]=" << a[x1] << " A[x2]=" << a[x2] << endl;
//    cout << binary_sum(a,0,9) << endl;
//    int a,b = {1,2};

    cout << "Hello World!" << endl;
}
void print_array(int * a,int N){
    for(int i = 0;i < N;i++)
        cout << "A[" << i << "]=" << a[i] << " ";
    cout << endl;
}
int binary_sum(int A[],int lo,int hi){
    if(lo == hi){
        return A[lo];
    }
    int mid = (lo + hi) >> 1;
    return binary_sum(A,lo,mid) + binary_sum(A,mid+1,hi);
}

void find_max2(const int * A, int lo,int hi,int &x1,int &x2){
    if(hi - lo == 2){
        if(A[lo] > A[lo+1]){
            x1 = lo;
            x2 = lo + 1;
        } else{
            x1 = lo + 1;
            x2 = lo;
        }
        return ;
    }
    if(hi - lo == 3){
        x1 = lo;
        x2 = lo;
        for(int i = lo+1;i < lo+3;i++){
            if(A[i] > A[x1]){
                x2 = x1;
                x1 = i;
            } else if(A[i] > A[x2]){
                x2 = i;
            }
        }
        return ;
    }

    int mid = (lo + hi) >> 1;
    int xl1,xl2,xr1,xr2;
    find_max2(A,lo,mid,xl1,xl2);
    find_max2(A,mid,hi,xr1,xr2);

    if(A[xl1] > A[xr1]) {
        x1 = xl1;
        x2 = A[xl2] > A[xr1] ? xl2 : xr1;
    } else{
        x1 = xr1;
        x2 = A[xl1] > A[xr2] ? xl1 : xr2;
    }


//    x1 = A[lo];
//    x2 = A[lo];
//    for(int i = lo+1;i < hi;i++){
//        if(A[i] > x1){
//            x2 = x1;
//            x1 = A[i];
//        }
//        else if (A[i] > x2){
//            x2 = A[i];
//        }
//    }
}

void reverse(int * A, int lo, int hi){
    while(lo < hi){
        int tmp = A[lo];
        A[lo] = A[hi];
        A[hi] = tmp;
        lo++;
        hi--;
    }
//    if(lo >= hi){
//        return;
//    }
//
//    int tmp = A[lo];
//    A[lo] = A[hi];
//    A[hi] = tmp;
//
//    reverse(A,++lo,--hi);
}

int * bubble_sort(int a[],int N,bool descend = false){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0;i < N-1;i++){
            if(a[i] > a[i+1] && !descend || a[i] < a[i+1] && descend){
                int tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
                sorted = false;
            }
        }
    }
    return a;
}


