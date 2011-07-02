/*
   Piotr Walkowski 221135
   Zadanie E z pracowni AISD 
   
   Implementacja z uzyciem 'List z przeskokami' ;)
   
   W ponizszym kodzie 'wzorowano' sie na nastepujacych dokumentach:
    a) http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_skip.aspx  (*)
    b) http://ocw.mit.edu/OcwWeb/Electrical-Engineering-and-Computer-Science/6-046JFall-2005/VideoLectures/detail/embed12.htm (nawiasem, genialny wyklad!) (**)
    c) http://cg.scs.carleton.ca/~morin/teaching/5408/refs/p90b.pdf  (***)

    ========
    BONUS: Przepis na sernik po wiedensku
    "
    Smaczny i szybki sernik. W pracy wszystkim smakowa3:)

    jajka 8 szt
    bakalie ró?ne 1 szklanka
    cukier waniliowy 2 opakowania
    ziemniaki gotowane 2 szt
    m1ka kartoflana 2 3y?ki
    m1ka (najlepiej szymanowska b1d? tortowa) 2 3y?ki
    cukier puder 2 szklanki
    mas3o 25 dag
    ser bia3y mielony 1 kg

    Ziemniaki zmielia lub przecisn1a przez praske. Mas3o utrzea z cukrem pudrem i cukrami waniliowymi na puch, dodawaa stopniowo po jednym ?ó3tku ca3y czas przy tym ucieraj1c. 
    Nastepnie dodaa ser i zmielone ziemniaki, wymieszaa. Potem dodaa kolejno obie m1ki oraz bakalie, wymieszaa. Na koncu dodaa ubit1 na sztywno piane z bia3ek, delikatnie wymieszaa. 
    Przygotowan1 mase serow1 wy3o?ya do wysmarowanej t3uszczem i wysypanej bu3k1 tart1 ?redniej wielko?ci blaszki, wyrównaa. 
    Ciasto piec w temperaturze 175 stopni przez 1 godzine. Wystudzony sernik mo?na polukrowaa lub polaa polew1 czekoladow1.
    "
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

using namespace std;

#define MAXIMAL_DEPTH 16 // because 2^16 > 5*10^k, max depth is floor(log(n)) (**)
#define SENTINEL -1000000000000000001LL // little bit tricky ;)

#define SEARCH_ITERATE(x, i, key) \
    while((x->next[i] != NULL) &amp;&amp; (x->next[i]->key < key)) x = x->next[i];

#define NOT_NULL(x) (x != NULL)

struct Node {
    long long key;
    Node ** next; 
};

class Skiplist {
  public:         
    Skiplist() {
        headPtr = createNode(MAXIMAL_DEPTH, 0);
        degree = 0;
    }
    Node* createNode(int, long long); 
    int hasKey(long long);
    void insert(long long);
    long long upperBound(long long);
    long long lowerBound(long long);
    void del(long long);
    inline int getRndDepth();
    inline long long getMinimum();
  private:
    Node* headPtr;
    int degree;
};


inline int Skiplist::getRndDepth() {
   int bits = 0;
   int found = 0;
   int h = 0;
   
   while(!found) {
     if ( bits == 0 )
       bits = rand();
   
       found = bits % 2;
       bits = bits / 2;
       h++;
   }
 
   if ( h >= MAXIMAL_DEPTH ) h = MAXIMAL_DEPTH - 1;
 
   return h;
} 

Node* Skiplist::createNode(int degree, long long key) 
{
    Node* sn = new Node; 
    sn->next =  (Node**)calloc(degree + 1, sizeof(Node *));  // awful syntax, but who cares ? ;) c++ suxx..

    sn->key = key;
    return sn;
}

int Skiplist::hasKey(long long key) {
    Node* x = headPtr;
    int i = degree;
    
    while(i >= 0) {
      SEARCH_ITERATE(x, i, key)
       i--;
    } x = x->next[0];

    return (NOT_NULL(x) &amp;&amp; (x->key == key)) ? 1 : 0;
}


void Skiplist::insert(long long key) {
    Node* x = headPtr;    
    Node* upTable[MAXIMAL_DEPTH + 1];
    
    memset(upTable, 0, MAXIMAL_DEPTH + 1);
    
   int i = degree;
    while( i >= 0 ) {
        SEARCH_ITERATE(x, i, key)
        upTable[i] = x;
        i--;
    } x = x->next[0];

    if((x == NULL) || (x->key != key)) {        
        int dpth = getRndDepth();
  
        if(dpth > degree) {
          int i = degree + 1;
          while(i <= dpth) { upTable[i] = headPtr; i++; }
          degree = dpth;
        } x = createNode(dpth, key);

        int i = 0;
        while( i <= dpth) { x->next[i] = upTable[i]->next[i]; upTable[i]->next[i] = x; i++; }
    }
}

inline long long Skiplist::getMinimum()
{
    Node* x = headPtr->next[0];
    while(NOT_NULL(x)) return x->key;
    return SENTINEL;
}

long long Skiplist::lowerBound(long long key) {
    Node* x = headPtr;
    long long minimum = getMinimum();
    
    if((minimum == SENTINEL) or ( minimum > key)) return SENTINEL;
    else if(hasKey(key)) return key;
    else {
        for(int i = degree; i >= 0; i--) SEARCH_ITERATE(x, i, key)           
        return (NOT_NULL(x)) ? x->key : SENTINEL; 
    }   
}

long long Skiplist::upperBound(long long key) {
    long long minimum = getMinimum();
    Node* x = headPtr;

    if((minimum == SENTINEL)) return SENTINEL;

    for(int i = degree; i >= 0; i--) SEARCH_ITERATE(x, i, key)
    x = x->next[0];

    return (NOT_NULL(x)) ? x->key : SENTINEL;  
}

void Skiplist::del(long long key) {
    Node* x = headPtr;    
    Node* upTable[MAXIMAL_DEPTH + 1];
    memset(upTable, 0, MAXIMAL_DEPTH + 1);
    
    int i = degree;
    while( i >= 0 ) {
        SEARCH_ITERATE(x, i, key)
        upTable[i] = x;
        i--;        
    } x = x->next[0];
    
    if(x->key == key) {
        int i = 0; 
        while(i <= degree) {
           if(upTable[i]->next[i] != x) break;
           upTable[i]->next[i] = x->next[i]; 
           i++;
        } delete x;
        
        while((degree > 0) &amp;&amp; (headPtr->next[degree] == NULL)) degree--; 
    }
}

int main(void) {

    Skiplist* sl = new Skiplist();
 
    int n;
    char type;
    long long key;
    scanf("%d\n", &amp;n);

    int i = 0;
    while( i < n) 
    {
       scanf("%c %lld\n", &amp;type, &amp;key);
     
       if(type == 'I') {
          sl->insert(key);
       } else if(type == 'D') { 
          if(sl->hasKey(key)) { sl->del(key); printf("%s\n", "OK"); }
          else printf("%s\n", "BRAK");
       } else if(type == 'U') {
          long long res = sl->upperBound(key);
          if(res == SENTINEL) printf("%s\n", "BRAK");
          else printf("%lld\n", res);
       } else if(type == 'L') {
          long long res = sl->lowerBound(key);
          if(res == SENTINEL) printf("%s\n", "BRAK");
          else printf("%lld\n", res);
       } 
       i++;
    } 
    
    return EXIT_SUCCESS;
}
