#include <iostream>
#include <fstream>
using namespace std;
void leerArchivo();

int main() {

  leerArchivo();

}

void leerArchivo(){
      ifstream arch; 
      string txt;

     arch.open("prueba.fa", ios::in); //Se abre el archivo
     if(arch.fail()){ //Condicion por si falla
       cout << "No se puede abrir" << endl; 
       exit(1);
     }

     while(!arch.eof()){
       getline(arch, txt);
       cout << txt << " " << endl;
     }

     arch.close();


} 
