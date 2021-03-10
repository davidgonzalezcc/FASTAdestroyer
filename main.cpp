#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
void leerArchivo();

int main() {

char comand[50]; 
char *entrada;
bool salir = false; 

  while(salir != true){
    cout << "~$ " ;
    cin.getline(comand, 50, '\n' );
    entrada = strstr(comand, "cargar"); 
     if(entrada != NULL){
       cout << "cargando" << endl; 
      }
      else {
          entrada = strstr(comand, "conteo"); 
          if(entrada != NULL){
          cout << "contando" << endl; 
          } 
          else {
                entrada = strstr(comand, "listar");
                if(entrada != NULL){
                cout << "listando" << endl;
                } 
                else {
                      entrada = strstr(comand, "histograma"); 
                      if(entrada != NULL){
                        cout << "histograma" << endl; 
                      }   
                      else {
                            entrada = strstr(comand, "es_subsecuencia"); 
                            if(entrada != NULL){
                             cout << "Buscando subsecuencia" << endl;
                            }
                            else {
                                  entrada = strstr(comand, "enmascarar"); 
                                  if(entrada != NULL){
                                    cout << "Enmascarando " << endl; 
                                  }
                                  else {
                                      entrada = strstr(comand, "guardar");
                                      if(entrada != NULL){
                                        cout << "Guardando archivo" << endl; 
                                      }
                                      else {
                                          entrada = strstr(comand, "salir"); 
                                          if(entrada != NULL){
                                            cout << "Saliendo" << endl; 
                                            salir = true; 
                                          }
                                          }
                                        }
                                    }     
                              } 
                        }  
                }

          }
      
    system("pause");      
    system("cls"); 
  }

  cout << endl; 
  leerArchivo();

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
