/*
   Written by: Piotr Walkowski
   Index nr: 221135

   =======================================
   
   Przepis na ciasteczka migdalowe z pistacjami:
   Skladniki:
    - 250 g slodkich migdalow
    - 6-7 gorzkich migdalow
    - 30 g pistacji
    - 8 bialek
    - 0.5 lyzki cukru waniliowego
    - 5 lyzek cukru
    - zapach pomaranczowy

   Sposob wykonania:
    Pistacje oraz migdaly zemlec po czym wymieszac z bialkiem i zapachem pomaranczowym.
    Nastepnie dodac cukier i cukier waniliowy a na koniec piane z 7 bialek.
    Calosc delikatnie polaczyc.
    Przelac ciasto do foremek, wstawic do rozgrzanego piekarnika i piec okolo 15 minut
*/

#include <cstdlib>
#include <iostream>
#include <queue>
#include <limits.h>

#define __uli__ unsigned long int
#define BITLEN 32

using namespace std;

void make_set(__uli__ d, __uli__ dN, priority_queue<__uli__, vector <__uli__>, greater<__uli__> > , result)
{   
      __uli__ bit = 1;
      
      int counter = 1;
      while((counter < BITLEN) &amp;&amp; (bit <= dN))
      {
           if((bit &amp; dN) == (bit)) result.push((__uli__)(d*bit)); 
           bit <<= 1; ++counter;
      }
}

    std::priority_queue<__uli__, vector <__uli__>, greater<__uli__> > pq;
    __uli__ senti = ULONG_MAX;

int main(void)
{
   std::ios_base::sync_with_stdio(0);

    int m, dN;
    int d;
    
    scanf("%d", &amp;m);
    
    for(int i = 0; i < m; i++){
      scanf("%d %d", &amp;d, &amp;dN);
      make_set(d,dN,pq);
    }
  
    __uli__ count = 0;
    __uli__ current = senti;
    int quant = 1;

    while (!pq.empty()) {      
      if((pq.top() != current)) {
        if((quant == 1)) { ++count; }
        else {
           make_set(current, quant, pq); 
           quant = 1; 
           if(current == pq.top()) { quant = 0; }
        }
      }
      
      if((pq.top() == current)) {
          ++quant;
      }

      current = pq.top();  pq.pop();
    }
   
    printf("%lu", count);
 
    #ifndef SPRAWDZACZKA
      system("pause");
    #endif
    
    return 0;
}
