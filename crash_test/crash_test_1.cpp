#include <iostream>
using namespace std;

// crash test cerr + clog

int main(){
	
std::cerr<<"before crash, cerr\n"; // uvidis vzdy

std::cout<<"before crash, cout\n"; // mozna neuvidis nic, protoze cout se neflushnul
//std::ofstream out("output.txt");
//std:cout.rdbuf(out.rdbuf());

//std::clog<<"before crash, clog\n";
*(int*)0=1;
cout<<"zde"<<endl;

//system("pause");
return 0;
}

