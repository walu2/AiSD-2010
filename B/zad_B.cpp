#include <iostream>
#include <stdio.h>

using namespace std;

void resetujTab(int t1[], int val, int r) {
     for (int i = 0; i < r; i++)
         t1[i] = val;
}

int nowyInx(int i, int j) {
    int val = i;
    int wynik = j;
    int dwadoii = 32;
    for (int ii = 0; ii < 5; ii++) {
        wynik += (val%2)*dwadoii;
        val = val / 2;
        dwadoii = dwadoii * 2;
    }
    //cout<<"nowy inx:"<<i<<" "<<j<<" "<<wynik<<endl;
    return wynik;
}

int suma(int t[], int P) {
    int suma = 0;
    for (int i = 0; i < 1024; i++) {
         suma += t[i];
         suma = (suma % P);
    }
    return suma;
}

void copy(int t1[], int t2[]) {
    for (int i = 0; i < 1024; i++)
        t1[i] = t2[i];
}

int ileKolorowan(int N, int P, int z[]) {
    int t1[1024];
    int t2[1024];
    resetujTab(t1, 1, 1024);
    resetujTab(t2, 0, 1024);
    for (int nn = 2; nn < N; nn++) {
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 32; j++) {
            int nowyindex = nowyInx(i, j);
            if (z[i*32+j] == 1) {
                        t2[nowyindex] += t1[i];
                        t2[nowyindex] = (t2[nowyindex]%P);
            }
        }
    }
    copy(t1, t2);
    resetujTab(t2, 0, 1024);
    }
    return suma(t1, P);
}

int elem(char zn) {
    if (zn == 'x')
        return 1;
    return 0;
}

void doZakazanychKolorowan(char tab1[], char tab2[], char tab3[], int z[]) {
     int a[3];int b[3];
        for (int k1=0; k1<=1;k1++){
        for (int k2=0; k2<=1;k2++){
        for (int k3=0; k3<=1;k3++){
        for (int k4=0; k4<=1;k4++){
        for (int k5=0; k5<=1;k5++){
        for (int k6=0; k6<=1;k6++){ a[0]=k1;a[1]=k2;a[2]=k3;b[0]=k4;b[1]=k5;b[2]=k6;
        int kolorowanieZakazane = 0;
        int dwadopot = 1;
        for (int j=2;j>=0;j--){
            kolorowanieZakazane = kolorowanieZakazane + 
            a[j] * dwadopot * 2*2*2*2+
            b[j] * dwadopot * 2* 2* 2+
            elem(tab1[j]) * dwadopot*2*2 + 
            elem(tab2[j]) * dwadopot * 2 + 
            elem(tab3[j]) * dwadopot;
            dwadopot = dwadopot * 32;
        }
        z[kolorowanieZakazane]=0;//cout<<kolorowanieZakazane<<endl;
        }}}}}}
        
        
        for (int k1=0; k1<=1;k1++){
        for (int k2=0; k2<=1;k2++){
        for (int k3=0; k3<=1;k3++){
        for (int k4=0; k4<=1;k4++){
        for (int k5=0; k5<=1;k5++){
        for (int k6=0; k6<=1;k6++){ a[0]=k1;a[1]=k2;a[2]=k3;b[0]=k4;b[1]=k5;b[2]=k6;
        int kolorowanieZakazane = 0;
        int dwadopot = 1;
        for (int j=2;j>=0;j--){
            kolorowanieZakazane = kolorowanieZakazane + 
            a[j] * dwadopot * 2*2*2*2+
            elem(tab1[j]) * dwadopot*2*2 *2 + 
            elem(tab2[j]) * dwadopot * 2*2 + 
            elem(tab3[j]) * dwadopot*2+
            b[j] * dwadopot;
            dwadopot = dwadopot * 32;
        }
        z[kolorowanieZakazane]=0;
        }}}}}}
        
        
        for (int k1=0; k1<=1;k1++){
        for (int k2=0; k2<=1;k2++){
        for (int k3=0; k3<=1;k3++){
        for (int k4=0; k4<=1;k4++){
        for (int k5=0; k5<=1;k5++){
        for (int k6=0; k6<=1;k6++){ a[0]=k1;a[1]=k2;a[2]=k3;b[0]=k4;b[1]=k5;b[2]=k6;
        int kolorowanieZakazane = 0;
        int dwadopot = 1;
        for (int j=2;j>=0;j--){
            kolorowanieZakazane = kolorowanieZakazane + 
            elem(tab1[j]) * dwadopot*2*2*2*2 + 
            elem(tab2[j]) * dwadopot * 2 *2*2+ 
            elem(tab3[j]) * dwadopot *2*2+
            a[j] * dwadopot * 2+
            b[j] * dwadopot;
            dwadopot = dwadopot * 32;
        }
        z[kolorowanieZakazane]=0;
        }}}}}}
}

int main(int argc, char *argv[])
{
    int n,p,m;
   // FILE *f = fopen("we.txt", "r");
    scanf("%d", &amp;n);
    scanf("%d", &amp;p);
    scanf("%d", &amp;m);
    //cout<<"n="<<n<<"p="<<p<<"m="<<m<<endl;
    /* tablica zakazanych polaczen */
    int z[1024*32];
    resetujTab(z, 1, 1024*32);
    for (int i=0;i<p;i++){
        char tab1[4];
        char tab2[4];
        char tab3[4];
        scanf("%s", tab1);
        scanf("%s", tab2);
        scanf("%s", tab3);
     //   cout<<"wzorzec:"<<endl<<tab1<<endl<<tab2<<endl<<tab3<<endl;
        doZakazanychKolorowan(tab1, tab2, tab3, z);
    }
    
    int k = ileKolorowan(n, m, z);
    
	printf("%d", k);
   // cout<<"ilosc kolorowan: "<<k<<endl;
    
  //  fclose(f);
    
   // system("PAUSE");
    return EXIT_SUCCESS;
}
