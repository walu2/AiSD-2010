#include <iostream>

using namespace std;

#define MAX_M 100000

struct Wsp {
       int i;
       int j;
};

Wsp A[MAX_M + 2];
int heap_size = 0;
bool B[MAX_M+1];

inline int parent(int i) {
       return i>>1;
}

inline int left(int i) {
       return i<<1;
}

inline int right(int i) {
       return (i<<1)+1;
}

void heapify(int i) {
     int l = left(i);
     int r = right(i);
     int largest;
     Wsp tym;
     if ((l <= heap_size) &amp;&amp; (A[l].i*A[l].j > A[i].i*A[i].j))
            largest = l;
     else
            largest = i;
     if ((r <= heap_size) &amp;&amp; (A[r].i*A[r].j > A[largest].i*A[largest].j))
            largest = r;
     if (largest != i) {
                 //zamien A[i] A[largest]
                 tym.i = A[i].i;
                 tym.j = A[i].j;
                 A[i].i = A[largest].i;
                 A[i].j = A[largest].j;
                 A[largest].i = tym.i;
                 A[largest].j = tym.j;
                 heapify(largest);
     }
}

Wsp extract_max() {
    Wsp max = A[1];
    B[abs(max.i-max.j)]=false;
    A[1] = A[heap_size];
    heap_size--;
    heapify(1);
    return max;
}

void insert(Wsp key) {
     heap_size++;
     int i = heap_size;
     while ((i > 1) &amp;&amp; (A[parent(i)].i*A[parent(i)].j < key.i*key.j)) {
           A[i].i = A[parent(i)].i;
           A[i].j = A[parent(i)].j;
           i = parent(i);
     }
     A[i].i = key.i;
     A[i].j = key.j;
}

int main(int argc, char *argv[])
{
    for (int i=0;i<=MAX_M;i++) B[i]=false;
    Wsp next_max;
    int M,k;
    scanf("%d %d", &amp;M, &amp;k);
    A[0].i = -1;
    A[0].j = -1;
    long long poprz = -1;
    long long val;
    Wsp e = {M, M};
    insert(e);
    while (k>0) {
          next_max = extract_max();
     if (!B[abs(next_max.i - 1 - next_max.j)]) {
     B[abs(next_max.i - 1 - next_max.j)]=true;
          e.i = next_max.i - 1;
          e.j = next_max.j;
          insert(e);
     }
     if (!B[abs(next_max.i - next_max.j + 1)]) {
     B[abs(next_max.i - next_max.j + 1)]=true;
          e.i = next_max.i;
          e.j = next_max.j - 1;
          insert(e);
     }
          val = (long long)((long long)next_max.i * (long long)next_max.j);
          if (val != poprz) {
             printf("%lld\n", val);
             poprz = val;
             k--;
          }
    }

    return EXIT_SUCCESS;
}
