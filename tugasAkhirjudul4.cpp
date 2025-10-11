#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX = 10; 
struct Card { string name; int power; };
struct DoubleStack { Card data[MAX]; int topFront = -1, topBack = MAX; };

bool isFull(DoubleStack s){ return s.topFront + 1 == s.topBack; }
bool isEmptyFront(DoubleStack s){ return s.topFront == -1; }
bool isEmptyBack(DoubleStack s){ return s.topBack == MAX; }

void push(DoubleStack &s,string name,int power,bool front){
    if(isFull(s)) return void(cout<<"Deck penuh!\n");
    if(front) s.data[++s.topFront]={name,power};
    else s.data[--s.topBack]={name,power};
    cout<<"Kartu "<<name<<" masuk dari "<<(front?"depan.\n":"belakang.\n");
}

void pop(DoubleStack &s,bool front){
    if((front&&isEmptyFront(s))||(!front&&isEmptyBack(s)))
        return void(cout<<"Tidak ada kartu di "<<(front?"depan.\n":"belakang.\n"));
    cout<<"Kartu "<<(front?"depan ":"belakang ") <<s.data[front?s.topFront--:s.topBack++].name<<" dikeluarkan.\n";
}

void displayArena(DoubleStack s){
    cout<<"\n===== ARENA =====\n";
    if(isEmptyFront(s)&&isEmptyBack(s)) return void(cout<<"Kosong.\n");
    cout<<"Depan -> ";
    for(int i=0;i<=s.topFront;i++) cout<<"["<<s.data[i].name<<"] ";
    cout<<"<- Belakang\n";
    for(int i=s.topBack;i<MAX;i++) cout<<"        ["<<s.data[i].name<<"] (belakang)\n";
}

void battle(DoubleStack &s){
    if(isEmptyFront(s)||isEmptyBack(s)) return void(cout<<"Tidak bisa bertarung!\n");
    Card f=s.data[s.topFront],b=s.data[s.topBack];
    cout<<"Battle: "<<f.name<<" vs "<<b.name<<"\n";
    if(f.power>b.power) pop(s,0);
    else if(b.power>f.power) pop(s,1);
    else pop(s,1),pop(s,0);
}

string randomCard(){
    string ranks[]={"As","Dua","Tiga","Empat","Lima","Enam","Tujuh","Delapan",
                    "Sembilan","Sepuluh","Jack","Queen","King"};
    string suits[]={"Sekop","Hati","Wajik","Keriting"};
    string card=ranks[rand()%13]+" "+suits[rand()%4];
    return card;
}

int main(){
    srand(time(0));
    DoubleStack deck;
    int c;
    cout<<"=== BATTLE DECK KARTU REMI ===\n";
    do{
        cout<<"\n1.Tambah Depan 2.Tambah Belakang\n3.Hapus Depan  4.Hapus Belakang\n5.Battle       6.Lihat Arena\n7.Keluar\nPilih: ";
        cin>>c;
        switch(c){
            case 1: push(deck,randomCard(),rand()%13+1,1);break;
            case 2: push(deck,randomCard(),rand()%13+1,0);break;
            case 3: pop(deck,1);break;
            case 4: pop(deck,0);break;
            case 5: battle(deck);break;
            case 6: displayArena(deck);break;
            case 7: cout<<"Terima kasih bermain!\n";break;
            default: cout<<"Pilihan tidak valid.\n";
        }
    }while(c!=7);
}
