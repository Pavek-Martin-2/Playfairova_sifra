#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
 Playfairova sifra, desifruj 
 output.txt -> output_desifrovano.txt

 zapiseme malymi pismeny otevreny text, malo se vyskytujici pismeno (v cestine "q") zamenime za
 jine a text rozdelime do dvojic tzv. BIGAMU ,pokud se v bigamu obevi dve stejna pismena,oddelime 
 je jinym pismenem napr. "x". Ma-li text lichy pocet pismen, opet doplnime "x". Sestavime ctverec
 5x5, do nehoz napiseme dohodnute heslo (opakujici se znaky jen jednou) a doplnime dalsimy znaky
 abecedy, ktere se nevyskytuji v hesle. Sifrovani probiha nasledovne
 
 * Pokud obe pismena v bigamu lezi na stejnem radku, nahradi se pismeny lezicimy napravo od
   nich. Pokud je jedno z pismen posledni v radku, nahradi se prvnim ze stejneho radku
   
 * Pokud obe pismena jsou ve stejnem sloupci, nahradi se pismeny pod nimi. Pokud je jedno z
   pismen posledni ve sloupci, nahradi se prvnim z tehoz sloupce
   
 * Pokud obe pismena nelezi ani na stejnem radku, ani ve stejnem sloupci, je kazde z nich
   nahrazeno pismenem lezicim na pruseciku radku daneho pismena a sloupce druheho pismena
   
   nekolik ukazek tototo popisu je v adresari scr\, soubory "sifrovaci_tabulka_N.jpg"
 */
 
string klic = "klice\\"; // v ceste musej bejt dve lomita "\\"
string volba;
string vstup =  "zasifrovano.txt";
string vystup = "desifrovano.txt";

// Vytvoøení 5x5 tabulky z klíèe
vector<vector<char>> createTable(const string &key) {
    string filtered;
    vector<vector<char>> table(5, vector<char>(5));
    bool used[26] = {false};

    // Zpracování klíèe
    for (char c : key) {
        if (isalpha(c)) {
            c = toupper(c); // prevadi mali pismena na velky
            if (c == 'Q') c = 'K'; // puvodne bylo J -> I v anglicky verzi
            if (!used[c - 'A']) {
                filtered += c;
                used[c - 'A'] = true;
            }
        }
    }

    // Doplnìní zbytku abecedy
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'Q') continue; // puvodne J v angl. verzi
        if (!used[c - 'A']) {
            filtered += c;
            used[c - 'A'] = true;
        }
    }
    
    // Naplnìní tabulky
    int index = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        table[i][j] = filtered[index++];

    return table;
}

// Zobrazení tabulky
void printTable(const vector<vector<char>> &table) {
    cout << "Sifrovaci tabulka 5x5:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
        cout << table[i][j] << " ";
        cout << endl;
    }
}

// Najde pozici znaku v tabulce
pair<int,int> findPos(const vector<vector<char>> &table, char c) {
    if (c == 'Q') c = 'K'; // puvodne J -> I
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (table[i][j] == c)
                return {i, j};
    return {-1, -1};
}

// Dešifrování dvojice znakù
string decryptPair(char a, char b, const vector<vector<char>> &table) {
    auto p1 = findPos(table, a);
    auto p2 = findPos(table, b);

    if (p1.first == p2.first) {
        return {
            table[p1.first][(p1.second + 4) % 5],
            table[p2.first][(p2.second + 4) % 5]
        };
    }
    if (p1.second == p2.second) {
        return {
            table[(p1.first + 4) % 5][p1.second],
            table[(p2.first + 4) % 5][p2.second]
        };
    }

    // Obdélník
    return {
        table[p1.first][p2.second],
        table[p2.first][p1.second]
    };
}

int main(){
	
	// Info
	cout<<"Playfairova sifra - Desifrovani"<<endl;
	
	// volba souboru klice z adresare "klice", zadava se bez pripony "txt"
	cout<<"zadej nazev souboru klice z adresare "<<klic<<endl;
	cin>>volba;
	klic += volba;
	klic += ".txt"; // sam doplni priponu souboru txt
	
	// Naètení klíèe
    ifstream fk(klic);
    if (!fk){
    cout<<"nenasel jsem soubor klice "<<'"'<<klic<<'"'<<endl;
    system("pause");
    return 1;
    }
    
    cout<<"nactu soubor klice "<<'"'<<klic<<'"'<<endl;
    string key;
    getline(fk, key);
    fk.close();
    
    cout<<"klic:"<<endl;
    cout<<key<<endl<<endl;
    
    // Vytvoøení tabulky
    auto table = createTable(key);
    
    // Naètení vstupního textu ( zašifrovaného )
    ifstream fi(vstup); // puvodne input.txt od AI verze
    if (!fi){
    cout<<"nenasel jsem vstupni soubor "<<'"'<<vstup<<'"'<<endl;
    system("pause");
    return 1;
    }
    
    cout<<"nactu vstupni soubor "<<'"'<<vstup<<'"'<<endl;
    string text((istreambuf_iterator<char>(fi)), istreambuf_iterator<char>());
    fi.close();
    
    cout<<"nacteno:"<<endl;
    cout<<text<<endl<<endl;
    
    // Dešifrování
    string decrypted;
    for (size_t i = 0; i < text.size(); i += 2) {
    decrypted += decryptPair(text[i], text[i+1], table);
    }
    
    // Uložení
    ofstream fo(vystup); // output.txt -> output_desifrovano.txt
    if (!fo){ // chyba ReadOnly apod.
    cout<<"chyba pri zapisu do souboru "<<'"'<<vystup<<'"'<<endl;
    system("pause");
    return 1;
    }
    
    fo<<decrypted;
    fo.close();
    
    // Tisk sifrovaci tabulky
    printTable(table); // tento radek zobrazuje tabulku 5x5
    cout<<endl;
    
    // Tisk desifrovaneho textu
    cout<<"desifrovano:"<<endl;
    cout<<decrypted<<endl<<endl;

    cout<<"textovy soubor "<<'"'<<vstup<<'"'<<" byl uspesne desifrovan";
	cout<<" do souboru "<<'"'<<vystup<<'"'<<endl;
	system("pause");
    return 0;
}


