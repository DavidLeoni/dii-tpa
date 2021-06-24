#include <iostream>
#include <stdexcept>

using namespace std;

/**  Con le eccezioni (una feature del C++) possiamo terminare prematuramente il programma in presenza di input non corretti.
*/

/**
    Se il parametro i è negativo, lancia una eccezione e termina funzione E programma
*/
int f(int i){
    cout << "INIZIO FUNZIONE" << endl;
    if (i < 0){
        throw std::invalid_argument( "Numero negativo!" ); // verrà poi visualizzato a video
    }
    cout << "FINE FUNZIONE" << endl;   // non verrà stampato
}

int main() {
  std::cout << "Hello World!\n";  

  f(-5);  
  
  std::cout << "FINE PROGRAMMA!\n";  // non verrà stampato

}