#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

// generator klicu pro playfair-ovu sifru, bude ukladat do souboru vystupniho "klice.txt"

int kolik_klicu = 50;
int zamichat_kolikrat = 500; // pocet pomichani pole_abecada pred zobrazenim kazdeho klice

int rnd_1, rnd_2, aa, bb, cc, mix, pom;
const int MAX = 25; // zde dat o jednu vice dat nez je pozadovane maximum

int main() {
// vystupni "txt" soubor z klicema
string output_file = "klice.txt";
//string cesta = "C:\\work\\klice.txt";

// otevreni souboru pro zapis z osetrenim pripadne chyby ReadOnly apod.
ofstream zapis(output_file);
if (!zapis){
cout<<"chyba pri zapisu do souboru "<<'"'<<output_file<<'"'<<endl; // ReadOnly apod.
system("pause");
exit(1); // chybovej exit 1
}
	
// definuje prazdnej vector	
vector<char> pole_abeceda;
//vector <char> pole_abeceda = {"q","w","e"};

// naplni vector pismenama abecedy a-z, z vynechanim znaku "q"
for (aa = 97; aa <= 122; aa++) { // 26-1 znak
if (aa != 113) // vynecha znak "q", jeden radek = bez nutnosti {}
pole_abeceda.push_back(static_cast<char>(aa)); // na konec pole vlozi ascii char(aa)
}
//size_t d_pole_abeceda = pole_abeceda.size(); cout<<d_pole_abeceda<<endl;

// kontrolni vypis naplneneho pole_abeceda
//for (char c : pole_abeceda) {cout<<c;}; cout<<endl;

// zapne neco jako je treba randomize os.time()
//srand(time(nullptr)); // seed podle aktuálního casu
srand( static_cast<unsigned>(time(NULL))); // funguje znahodneni !
// ^ funguji oba zpusoby, tezko rict kterej ze dvou je lepsi

// bude mezi sebou prohazovat vzdy dva nahone prvky pole_abeceda
// bude opakovat x krat podle hodnoty promenny "zamichat_kolikrat"

// kolik bude out klicu
for (cc = 1; cc <= kolik_klicu; cc++) {

//radek = "";
for (mix = 1; mix <= zamichat_kolikrat; mix++){
rnd_1 = rand() % MAX;
rnd_2 = rand() % MAX;
//cout<<rnd_2<<" "<<rnd_1<<endl; // kontrolni vypis RND

// nahodne mezi sebou proghazuje klice $pole_abeceda
pom = pole_abeceda[rnd_1];
pole_abeceda[rnd_1] = pole_abeceda[rnd_2];
pole_abeceda[rnd_2] = pom;
}
/* puvodni verze
// vypis zamychanyho pole_abeceda pro kontrolu
for ( char znak : pole_abeceda) { // "char znak" musi bejt definovano az tady v main()
cout<<znak;
zapis<<znak;
}
cout<<endl;
zapis<<endl;
*/
for (bb=1; bb<=24; bb++){ // nova verze
cout<<pole_abeceda[bb];
zapis<<pole_abeceda[bb]; // zapisuje jak mam
}
cout<<endl;
zapis<<endl;

} // for cc

zapis.close(); // uzavreni souboru "klice.txt"
cout<<"zapsano do souboru "<<'"'<<output_file<<'"'<<endl;

system("pause");
return 0;
}

