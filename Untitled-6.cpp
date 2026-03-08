//plik testowy
#include<iostream>
using namespace std;
int main(){
    #define ROZMIAR 5 
    int liczby[ROZMIAR]={ 3, 8, 10, 3, 9}; 
    int *wsk1, *wsk2;
    wsk1 = liczby;
    wsk2 = &liczby[3];

    cout<<*wsk1;
}