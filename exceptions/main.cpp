#include <iostream>

using namespace std;

/**
Il C++ mette a disposizione la classe string per manipolare facilmente sequenze di caratteri. string è mutabile, e si può anche variare la lunghezza con concatenazioni.

*/

string f(const char * inputs){

    string ret = "ciao";

    ret += inputs;

    return ret;
}


int main() {

  string s = "ciao";

  s += " mondo";

  std::cout << s << endl;

  std::cout << s.length() << endl;

  cout << f("esperimento") << endl;

  string stringa_fuori = f("prova2");

  cout << stringa_fuori << endl;

  stringa_fuori += " posso aggiungere";

  cout << stringa_fuori << endl;

}