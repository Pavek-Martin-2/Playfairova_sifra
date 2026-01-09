#include <iostream>
#include <ctime> // randomize
#include <vector>
#include <fstream>
#include <windows.h> // pro funkci delay();
using namespace std;

// generator klicu pro playfair-ovu sifru, bude ukladat hromadne do souboru "kliceN.txt"

int kolik_klicu = 10; // pocet souboru klicu, tady pripadne menit
int zamichat_kolikrat = 500; // pocet pomichani pole_abecada pred zobrazenim kazdeho klice

int rnd_1, rnd_2, aa, bb, cc, mix, pom;
const int MAX = 25; // zde dat o jednu vice dat nez je pozadovane maximum ( pro RND )

int poc_file = 1;
string str_poc_file;

int cekej = 200; // pro Sleep()

int main() {

// upozorneni
cout<<"budou vygenerovany soubory klic1.txt - klic"<<kolik_klicu<<".txt"<<endl;
cout<<"pokud nejaky z nich v aktualnim adresari jiz existuje, bude prepsan"<<endl;
cout<<"pokracovat ?"<<endl;
system("pause");

// definuje prazdnej vector	
vector<char> pole_abeceda;

// naplni vector pismenama abecedy a-z, z vynechanim znaku "q"
for (aa = 97; aa <= 122; aa++) { // 26-1 znak
if (aa != 113) // vynecha znak "q", jeden radek = bez nutnosti {}
pole_abeceda.push_back(static_cast<char>(aa)); // na konec pole vlozi ascii char(aa)
}
//size_t d_pole_abeceda = pole_abeceda.size(); cout<<d_pole_abeceda<<endl;

// kontrolni vypis naplneneho pole_abeceda
//for (char c : pole_abeceda) {cout<<c;}; cout<<endl;

// zapne neco podonbniho jako randomize os.time()
//srand(time(nullptr)); // seed podle aktuálního casu
srand( static_cast<unsigned>(time(NULL))); // funguje znahodneni !
// ^ funguji oba zpusoby, tezko rict kterej ze dvou je lepsi

// bude mezi sebou prohazovat vzdy dva nahone prvky pole_abeceda
// bude opakovat x krat podle hodnoty promenny "zamichat_kolikrat"

// kolik bude out klicu
for (cc = 1; cc <= kolik_klicu; cc++) {
for (mix = 1; mix <= zamichat_kolikrat; mix++){
rnd_1 = rand() % MAX;
rnd_2 = rand() % MAX;
//cout<<rnd_2<<" "<<rnd_1<<endl; // kontrolni vypis RND

// nahodne mezi sebou proghazuje klice $pole_abeceda
pom = pole_abeceda[rnd_1];
pole_abeceda[rnd_1] = pole_abeceda[rnd_2];
pole_abeceda[rnd_2] = pom;
}

/* zapis soubor-u klic-u
udela nekolik samostatnych souboru z prfixem "klic_" a poradovy cislo + pripona "txt"
pokud nejaky soubor v aktualni adresari jiz exstuje jiz existuje,
tak ho bez ptani prepise novym obsahem */
string output_file = "klic";
str_poc_file = to_string(poc_file);
output_file += str_poc_file;
output_file += ".txt";
/*
// zarovani radku (asi zbytecny)
if( poc_file < 10 ){
cout<<output_file<<"  -  ";
} else {
cout<<output_file<<" -  ";	
}
*/
cout<<output_file<<" - ";

ofstream zapis(output_file);
if (!zapis){
cerr<<"chyba pri zapisu do souboru "<<'"'<<output_file<<'"'<<endl; // ReadOnly apod.
system("pause");
exit(1); // chybovej exit 1
}else{
/* puvodni verze
// vypis zamychanyho pole_abeceda pro kontrolu
for ( char znak : pole_abeceda) { // "char znak" musi bejt definovano az tady v main()
cout<<znak;
zapis<<znak;
}
cout<<endl;
zapis<<endl;
*/
for (bb=0; bb<=24; bb++){ // nova verze
cout<<pole_abeceda[bb];	
zapis<<pole_abeceda[bb]; // opraveno a zapisuje znaky jak ma
}
cout<<endl;
zapis<<endl;
poc_file++;
zapis.close();
}

Sleep(cekej); // bude cekat 200ms mezi jednotlivejma zapisama souboru
} // for cc

system("pause");
return 0;
}

