#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;
void leerArchivo(string);

int main(int argc, char *argv[]) {

  if(strcmp(argv[1],"cargar")==0)
    leerArchivo(argv[2]);


}

void leerArchivo(string archivo){
      ifstream arch; 
      string txt;

     arch.open(archivo, ios::in); //Se abre el archivo
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

void cargar (){
  
}

void conteo(){

}
