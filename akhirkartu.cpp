#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 10; 
struct Card { string name; int rank; int suit; }; 
struct DoubleStack { Card data[MAX]; int topFront = -1, topBack = MAX; };

bool isFull(DoubleStack s){ return s.topFront + 1 == s.topBack; }
bool isEmptyFront(DoubleStack s){ return s.topFront == -1; }
bool isEmptyBack(DoubleStack s){ return s.topBack == MAX; }

string getRank(int r){
    string ranks[] = {"", "", "Dua", "Tiga", "Empat", "Lima", "Enam", "Tujuh", 
                      "Delapan", "Sembilan", "Sepuluh", "Jack", "Queen", "King", "As"};
    return ranks[r];
}

string getJenis(int s){
    string jenis[] = {"Keriting", "Wajik", "Hati", "Sekop"};
    return jenis[s];
}

void push(DoubleStack &s, int rank, int suit, bool front){
    if(rank < 2 || rank > 14 || suit < 0 || suit > 3) return void(cout<<"Input tidak valid!\n");
    if(isFull(s)) return void(cout<<"Deck penuh!\n");
    string name = getRank(rank) + " " + getJenis(suit);
    if(front) s.data[++s.topFront] = {name, rank, suit}; 
    else s.data[--s.topBack] = {name, rank, suit};
    cout<<"Kartu "<<name<<" masuk dari "<<(front?"depan.\n":"belakang.\n");
}

void pop(DoubleStack &s, bool front){
    if((front && isEmptyFront(s)) || (!front && isEmptyBack(s))) return void(cout<<"Tidak ada kartu di "<<(front?"depan.\n":"belakang.\n"));
    cout<<"Kartu "<<s.data[front ? s.topFront-- : s.topBack++].name<<" dikeluarkan.\n";
}

void displayArena(DoubleStack s){
    cout<<"\n===== ARENA =====\n";
    if(isEmptyFront(s) && isEmptyBack(s)) return void(cout<<"Kosong.\n");
    cout << "Depan -> ";
    for (int i = 0; i <= s.topFront; i++) {
        cout << "[" << setw(9) << left << s.data[i].name << "] ";
    }
    cout << "<- Belakang\n";
    for (int i = s.topBack; i < MAX; i++) {
        cout << setw(20) << right << " " << "[" << s.data[i].name << "]\n";
    }

    
}



void battle(DoubleStack &s){
    if(isEmptyFront(s) || isEmptyBack(s)) return void(cout<<"Tidak bisa bertarung!\n");
    Card f = s.data[s.topFront], b = s.data[s.topBack];
    cout<<"Battle: "<<f.name<<" vs "<<b.name<<"\n";
    
    if(f.rank > b.rank || (f.rank == b.rank && f.suit > b.suit)){
        cout<<"Depan menang!\n"; pop(s, false);
    } else if(b.rank > f.rank || (b.rank == f.rank && b.suit > f.suit)){
        cout<<"Belakang menang!\n"; pop(s, true);
    } else {
        cout<<"Seri!\n"; pop(s, true); pop(s, false);
    }
}

void clear(DoubleStack &s){
    s.topFront = -1;
    s.topBack = MAX;
    cout << "Semua kartu telah dihapus. Arena kosong kembali.\n";
}

int main(){
    DoubleStack deck;
    int c, rank, suit;
    cout<<"=== BATTLE DECK KARTU ===\n";
    cout<<"Rank: 2-14 (11=J, 12=Q, 13=K, 14=A)\n";
    cout<<"Suit: 0=Keriting, 1=Wajik, 2=Hati, 3=Sekop\n";
    
    do{
        cout<<"\n1.Tambah Depan 2.Tambah Belakang\n3.Hapus Depan  4.Hapus Belakang\n5.Battle       6.Lihat Arena\n7.Clear Semua  8.Keluar\nPilih: ";
        cin>>c;
        switch(c){
            case 1: case 2:
                cout<<"Rank (2-14): "; cin>>rank;
                cout<<"Suit (0-3): "; cin>>suit;
                push(deck, rank, suit, c==1);
                break;
            case 3: pop(deck, 1); break;
            case 4: pop(deck, 0); break;
            case 5: battle(deck); break;
            case 6: displayArena(deck); break;
            case 7: clear(deck); break;
            case 8: cout<<"Terima kasih!\n"; break;
            default: cout<<"Pilihan tidak valid.\n";
        }
    } while(c != 8);
}
