#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
//#include <stdlib.h>
#include <list>

using namespace std;

struct lista_sec{
    char nombre [200];
    list<char> secuencias;   
};

void leerArchivo(string, list <lista_sec> &);

int main() {

char comand[50]; 
char *entrada;
bool salir = false; 
list <lista_sec> listaADN; 
cout << "Bienvenido al sistema de manejo de archivos FASTA" << endl; 
cout << "SI NECESITA AYUDA DIGITE: HELP"<< endl; 

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
                                          else {
                                              entrada = strstr(comand, "help"); 
                                              if(entrada != NULL){
                                                  cout << "_Lista de comandos_" << endl; 
                                                  cout << "° cargar nombre_archivo: Carga en memoria los datos del archivo seleccionado" << endl;
                                                  cout << "° conteo: Muestra la cantidad de secuencias cargadas en memoria" << endl; 
                                                  cout << "° listar_secuencias: Imprime la información básica de las secuencias cargadas" << endl;
                                                  cout << "° histograma descripcion_secuencia: Muestra la fecuencia de cada código en una secuencia dada" << endl;
                                                  cout << "° es_subsecuencia subsecuencia: Determina si la secuencia dad existe dentro de las cargadas" << endl;
                                                  cout << "° enmascarar secuencia: Enmascara una secuencia dada por el usuario" << endl;
                                                  cout << "° guardar nombre_archivo: guarda en un nuevo archivo (nombre_archivo) las secuencias cargadas en memoria" << endl;
                                                  cout << "° salir: Terminar ejecucion. Seperderán todos los datos cargados que no se hayan guardado" << endl;
                                              }
                                              else{
                                                  cout << "Ingrese un comando valido" << endl; 
                                              }                                                
                                          }
                                          }
                                        }
                                    }     
                              } 
                        }  
                }

          }   
  }

  cout << endl; 
  string t = "ejemplofasta1.fa"; 
  leerArchivo(t, listaADN);

}

/*cargar nombre_archivo
Salida en pantalla. 
(Archivo vacío) “nombre_archivo ” no contiene ninguna secuencia.
(Una sola secuencia) 1 secuencia cargada correctamente desde “nombre_archivo ”.
(Varias secuencias) n secuencias cargadas correctamente desde “nombre_archivo ”.
descripción: Carga en memoria los datos contenidos en el archivo identificado por nombre_archivo.*/

void leerArchivo(string archivo, list<lista_sec>& listaADN){
      ifstream arch; 
      string txt;
      char temp[5000]; 

     arch.open(archivo, ios::in); //Se abre el archivo
     if(arch.fail()){ //Condicion por si falla
       cout << "No se puede abrir" << endl; 
       exit(1);
     }
    ////// 
    lista_sec aux; 
    bool nomOcad = false; 
    int cont = 0;
    int ayuda; 
     while(!arch.eof()){ 
      char nom [200];
      ayuda = 0; 
      getline(arch, txt);
      strcpy(temp, txt.c_str()); 

      for(int j=0; j<txt.size(); j++){
        if(txt[j] == '>'){
          ayuda = 1; 
        }
      }      
    

      if(ayuda!=0){
        if(cont > 0){ 
          listaADN.push_back(aux); 
          aux.secuencias.clear(); 
        }
        cont = 1;         
        //nomOcad = true; 
      }

      if(ayuda!=0){
        strcpy(aux.nombre, temp);  
        //nomOcad = false;
        ayuda = 0;   
      } 
      else {
          for(int i=0; i<txt.size(); i++){
            char t = txt[i]; 
            aux.secuencias.push_back(t);  
          }         
      }       
     }

    arch.close();

///////////////////////////////////////////////

    cout << listaADN.size() << endl; 

     list<lista_sec> :: iterator it; 
     for(it = listaADN.begin(); it != listaADN.end(); ++it){
       lista_sec aux1 = *it;  
       cout << aux1.nombre << endl; 
       list<char> :: iterator it1; 
       for(it1 = aux1.secuencias.begin(); it1 != aux1.secuencias.end(); ++it1){
         cout << *it1; 
       }
       cout << endl; 
     }

} 

/*comando: conteo
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(Una sola secuencia) 1 secuencia en memoria.
(Varias secuencias) n secuencias en memoria.
descripción: Imprime por pantalla la cantidad de secuencias cargadas en memoria.*/
void conteo(){

}

/*comando: listar_secuencias
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(Secuencia completa de archivo no vacío) Secuencia “descripcion_secuencia ” contiene b bases.
(Secuencia incompleta de archivo no vacío) Secuencia “descripcion_secuencia ” contiene al
menos b bases.
descripción: Imprime en n líneas (una para secuencia) la información básica (cantidad de bases) de
cada secuencia. Si la secuencia es completa (i.e. no tiene el código ’-’) imprime el segundo mensaje,
si no, el tercero.*/
void listar_secuencias(list<lista_sec>& listaADN){
    if(listaADN.size() == 0){
      cout << "La lista está vacía" << endl; 
    } 
    else {
      list<lista_sec> :: iterator it; 
      for(it = listaADN.begin(); it != listaADN.end(); ++it){
       lista_sec aux1 = *it; 
       cout << aux1.nombre << endl; 

       cout << "#########" << endl; 
     }
    }

}

/*comando: histograma descripcion_secuencia
salida en pantalla:
(La secuencia no existe) Secuencia inválida.
(La secuencia existe) A : frecuencia_A \n C : frecuencia_C \n ...
descripción: Imprime el histograma de una secuencia, en caso de que exista. El histograma se
define como el conteo (frecuencia) de cada código en la secuencia. Por cada línea (’\n’ es el
caracter de salto de línea) se escribe el código y la cantidad de veces que aparece en la secuencia. El
ordenamiento del histograma está dado por la Tabla 1.*/
void histograma(){

}

/*comando: es_subsecuencia secuencia
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(La secuencia no existe) La secuencia dada no existe.
(Varias secuencias) La secuencia dada se repite s veces.
descripción: Determina si una secuencia, dada por el usuario, existe dentro de las secuencias
cargadas. Si es así, determina la cantidad de veces en las que esta secuencia dada se repite.*/
void es_subsecuencia(){

}

/*comando: enmascarar secuencia
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(No se enmascararon subsecuencias) La secuencia dada no existe, por tanto no se enmascara
nada.
(Una subsecuencia enmascarada) 1 secuencia ha sido enmascarada.
(Varias subsecuencias esmascaradas) s secuencias han sido enmascaradas.
descripción: Enmascara una secuencia dada por el usuario, si existe. Los elementos que pertenecen
a la subsecuencia se enmascaran, cambiando cada código por el código ’X’*/
void enmascarar(){
  
}

/* comando: guardar nombre_archivo
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(Escritura exitosa) Las secuencias han sido guardadas en “nombre_archivo ”.
(Problemas en archivo) Error guardando en ”nombre_archivo ”.
descripción: Guarda en el archivo nombre_archivo las secuencias cargadas en memoria. Se debe
tener en cuenta la justificación (de líneas) del archivo inicial. */
void guardarArchivo(){

}

/*comando: salir
salida en pantalla:
(No tiene salida por pantalla)
descripción: Termina la ejecución de la aplicación*/
//-ESTE COMANDO SE EJECUTA EN EL MENU INICIAL-//


