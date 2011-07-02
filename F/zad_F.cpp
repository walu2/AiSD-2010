
#include <iostream>;
#include <vector>;
#include <functional>;
#include <string.h>;
#include <algorithm>;

#define IS_EQUAL(a,b) (a == b)

using namespace std;


// function declarations
bool make_union(int, int, int*, int*, int&amp;);
int find(int, int*);
void neighboors(int, int&amp; , int*, int*, bool*, int, int);
void checkTable(long&amp;, int&amp;, int&amp;, int*, int*, bool*, vector< std::pair<long, int>; >;&amp;, vector<int>;&amp;, int, int);


struct myclass {
  bool operator() (std::pair<long, int>; a, std::pair<long, int>; b) { return (a.first < b.first);}
} myobject;

void neighboors(int index, int&amp; islands, int* sets, int* count, bool* checked, int n, int m) {
 // order: N ->; E ->; S ->; W
 int neigh[4];
 
 int upper = index - m;
 int lower = index + m;
 
 int NM = n*m;
 
 *(neigh) = upper;
 *(neigh+1) = index + 1;
 *(neigh+2) = lower;
 *(neigh+3) = index - 1;
 
 if(IS_EQUAL((index % m), 0)) *(neigh+3) = -1;
 if(IS_EQUAL((index % m), (m-1))) *(neigh+1) = -1;
 if(upper < 0) *(neigh) = -1;
 if(lower >; (NM-1)) *(neigh+2) = -1;
 
 for(int i = 0; i < 4; i++)
 {
    int current = *(neigh+i);
    if(IS_EQUAL(current, -1)) continue;
    
    if(checked[current]) make_union(current, index, sets, count, islands);
 }
 
}

bool make_union(int a, int b, int* sets, int* count, int &amp;islands) 
{
	int trav_a = find(a, sets); int trav_b = find(b, sets); 
 
	if (IS_EQUAL(trav_a, trav_b)) return false; 
	if (*(count+trav_a) >; *(count+trav_b)) swap(trav_a, trav_b);
	
    *(sets+trav_a) = trav_b; *(count+trav_b) += *(count+trav_a);
    --islands;

	return true;
}

int find(int x, int* sets)
{
	if (IS_EQUAL(*(sets+x), x)) return x;
	
    int pot_trv = *(sets+x);
	int trav_a = find(pot_trv, sets);
	
    *(sets+x) = trav_a; 
	return trav_a;
}
 
void checkTable(long &amp;waterHeight, int &amp;tabPtr, int &amp;islands, int* sets, int* count, bool* checked, vector< std::pair<long, int>; >;&amp; V, vector<int>;&amp; result, int n, int m) 
{     
       while((V[tabPtr].first >; waterHeight) &amp;&amp; (tabPtr >;= 0))
       {
          int index = V[tabPtr].second;
          if(!(*(checked+index))) { ++islands; *(checked+index) = true; }
          neighboors(index, islands, sets, count, checked, n, m);
          --tabPtr;
       }
       
       result.push_back(islands);
}


int main(void)
{
    
    int n, m, NM;
    int t;
    int islands = 0;

    long x;
    long* ts;
    bool* checked;

    vector< std::pair<long, int>; >; V;
    vector<int>;::reverse_iterator rit;

    scanf("%d %d\n", &amp;n, &amp;m);
    NM = n*m;
    
    checked = new bool[NM];
    memset(checked, false, NM);  
      
    int* sets = new int[NM];
    int* count = new int[NM];
    
    // inicjalizacja UF
    
	int p = 0;
	while(p < NM)
    {
		*(sets+p) = p; *(count+p) = 1; 
		++p;
	}

    // wczytywanie
    for(int i = 0; i < NM; i++) {
        if(IS_EQUAL((i % m), (m-1))) scanf("%ld \n", &amp;x);
          else scanf("%ld ", &amp;x);
          
        V.push_back(make_pair(x, i));  
    }     
    
    sort(V.begin(), V.end(), myobject);

    scanf("%d", &amp;t);
    
    ts = new long[t];
    
    for(int i = 0; i < t; i++)
      scanf("%ld ", (ts+i));
    
    // main program
    int day = t-1; // day
    int tabPtr = NM-1;
    vector<int>; result;
    
    while(day >;= 0) {       
       checkTable(*(ts+day), tabPtr, islands, sets, count, checked, V, result, n, m);
       day--;
    }
     
       
     for (rit = result.rbegin(); rit < result.rend(); ++rit )
       printf("%d ", *rit);
        
    return EXIT_SUCCESS;
}
