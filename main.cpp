#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

struct lista_sec
{
  char nombre[200];
  list<char> secuencias;
  int longitud_linea = 0;
};

struct lista_sec_codifica
{
  char nombre[200];
  list<string> secuencias;
  list<char> bases;
  int longitud_linea = 0;
};

struct nodo_huffman
{
  char base;
  int frecuen;
  nodo_huffman *izquierdo, *derecho;
};

struct buscafrecuencia
{
  bool i;
  bool operator()(nodo_huffman *izquierdo, nodo_huffman *derecho)
  {
    return izquierdo->frecuen > derecho->frecuen;
    //return i;
  }
};

lista_sec buscarLista(list<lista_sec>, string);
void leerArchivo(string, list<lista_sec> &);
void conteo(list<lista_sec>);
int es_subsecuencia(list<lista_sec>, string);
void listar_secuencias(list<lista_sec>);
void histograma(list<char>, string);
void guardarArchivo(string, list<lista_sec>);
void enmascarar(list<lista_sec> &, string);
void imprimirLista(list<char>);
void encriptado(list<lista_sec> listaADN, string nombrearch);
void imprimeHuffman(unordered_map<char, string> codificacion);
void listar_codificados(list<lista_sec_codifica> auxiliar);
void desencriptar(string nombrearch);

int main()
{
  //string t;
  char comand[50];
  char *entrada;
  char *entrada2;
  char X[100];
  bool salir = false;
  list<lista_sec> listaADN;
  cout << "Bienvenido al sistema de manejo de archivos FASTA" << endl;
  cout << "SI NECESITA AYUDA DIGITE: ayuda" << endl;

  while (salir != true)
  {
    cout << "~$ ";
    cin.getline(comand, 50, '\n');
    entrada = strstr(comand, "cargar");
    entrada2 = strstr(comand, "ayuda");
    if (entrada != NULL && entrada2 == NULL)
    { //Cargar archivo
      cout << "cargando" << endl;
      char *p;
      int conta = 0;
      p = strtok(entrada, " ");
      p = strtok(NULL, " ");
      strcpy(X, p);
      string t(X);
      leerArchivo(t, listaADN);
    }
    else
    { //Contar
      entrada = strstr(comand, "conteo");
      entrada2 = strstr(comand, "ayuda");
      if (entrada != NULL && entrada2 == NULL)
      {
        conteo(listaADN);
      }
      else
      { //Listar secuencias
        entrada = strstr(comand, "listar_secu");
        entrada2 = strstr(comand, "ayuda");
        if (entrada != NULL && entrada2 == NULL)
        {
          listar_secuencias(listaADN);
        }
        else //Histograma
        {
          entrada = strstr(comand, "histograma");
          entrada2 = strstr(comand, "ayuda");
          if (entrada != NULL && entrada2 == NULL)
          {

            char *q;
            q = strtok(entrada, " ");
            q = strtok(NULL, " ");
            strcpy(X, q);
            string m(X);

            if (listaADN.size() != 0)
            {
              cout << "Histograma" << endl;
              lista_sec lista_temporal = buscarLista(listaADN, m);
              histograma(lista_temporal.secuencias, m);
            }
            else
            {
              cout << "No hay secuencias cargadas." << endl;
            }
          }
          else
          {
            entrada = strstr(comand, "es_subsecuencia"); //subsecuencia
            entrada2 = strstr(comand, "ayuda");
            if (entrada != NULL && entrada2 == NULL)
            {
              cout << "Buscando subsecuencia" << endl;
              char *i;
              i = strtok(entrada, " ");
              i = strtok(NULL, " ");
              strcpy(X, i);
              string m(X);

              if (listaADN.size() != 0)
              {
                cout << "Nombre: " << m << endl;
                int resultado = es_subsecuencia(listaADN, m);
                if (resultado == 0)
                {
                  cout << "No se han encontrado secuencias iguales." << endl;
                }
                else
                {
                  cout << "Se han encontrado " << resultado << " secuencias iguales." << endl;
                }
              }
              else
              {
                cout << "No hay secuencias cargadas." << endl;
              }
            }
            else
            {
              entrada = strstr(comand, "enmascarar"); //Enmascarar
              entrada2 = strstr(comand, "ayuda");
              if (entrada != NULL && entrada2 == NULL)
              {

                char *r;
                r = strtok(entrada, " ");
                r = strtok(NULL, " ");
                strcpy(X, r);
                string m(X);
                if (listaADN.size() != 0)
                {
                  cout << "Enmascarar" << endl;
                  cout << "Nombre: " << m << endl;
                  enmascarar(listaADN, m);
                }
                else
                {
                  cout << "No hay secuencias cargadas." << endl;
                }
              }
              else
              {
                entrada = strstr(comand, "guardar "); //Guardar archivo
                entrada2 = strstr(comand, "ayuda");
                if (entrada != NULL && entrada2 == NULL)
                {
                  char *o;
                  o = strtok(entrada, " ");
                  o = strtok(NULL, " ");
                  strcpy(X, o);
                  string m(X);
                  if (listaADN.size() != 0)
                  {
                    cout << "Guardar" << endl;
                    cout << "Nombre: " << m << endl;
                    guardarArchivo(m, listaADN);
                  }
                  else
                  {
                    cout << "No hay secuencias cargadas." << endl;
                  }
                }
                else
                {
                  entrada = strstr(comand, "salir"); //salir del programa
                  entrada2 = strstr(comand, "ayuda");
                  if (entrada != NULL && entrada2 == NULL)
                  {
                    cout << "Saliendo" << endl;
                    salir = true;
                  }
                  else
                  {
                    entrada = strstr(comand, "ayuda"); //Listar ayudas
                    entrada2 = strstr(comand, " ");
                    if (entrada != NULL && entrada2 == NULL)
                    {
                      cout << "_Lista de comandos_" << endl;
                      cout << "° cargar nombre_archivo: Carga en memoria los datos del archivo seleccionado" << endl;
                      cout << "° conteo: Muestra la cantidad de secuencias cargadas en memoria" << endl;
                      cout << "° listar_secuencias: Imprime la información básica de las secuencias cargadas" << endl;
                      cout << "° histograma descripcion_secuencia: Muestra la fecuencia de cada código en una secuencia dada" << endl;
                      cout << "° es_subsecuencia subsecuencia: Determina si la secuencia dad existe dentro de las cargadas" << endl;
                      cout << "° enmascarar secuencia: Enmascara una secuencia dada por el usuario" << endl;
                      cout << "° guardar nombre_archivo: guarda en un nuevo archivo (nombre_archivo) las secuencias cargadas en memoria" << endl;
                      cout << "° salir: Terminar ejecucion. Seperderán todos los datos cargados que no se hayan guardado" << endl;
                      cout << "° codificar nombre.fabin: codifca en un archivo de nombre  (nombre.fabin) las secuencias en memoria" << endl;
                      cout << "° decodificar nombre.fabin: decodifca un archivo de nombre  (nombre.fabin) e imprime su contenido original" << endl;
                      cout << "° clean: Limpia la pantalla" << endl;
                    }
                    else
                    {
                      entrada = strstr(comand, "clean"); //limpiar pantalla
                      if (entrada != NULL)
                      {
                        system("cls");
                      }
                      else
                      {
                        entrada = strstr(comand, "ayuda cargar");
                        if (entrada != NULL)
                        {
                          cout << "cargar nombre_archivo: Digite cargar seguido del nombre del archivo que desee abrir para cargarlo" << endl;
                        }
                        else
                        {
                          entrada = strstr(comand, "ayuda conteo");
                          if (entrada != NULL)
                          {
                            cout << "conteo: Digite conteo para ver la cantidad de secuencias cargadas en memoria" << endl;
                          }
                          else
                          {
                            entrada = strstr(comand, "ayuda listar_");
                            if (entrada != NULL)
                            {
                              cout << "listar_secuencias: Digite el codigo para ver las secuancias cargadas y su cantidad de bases" << endl;
                            }
                            else
                            {
                              entrada = strstr(comand, "ayuda histograma");
                              if (entrada != NULL)
                              {
                                cout << "histograma: Digite para ver la frecuencia de aparicion de cada base en una secuencia" << endl;
                              }
                              else
                              {
                                entrada = strstr(comand, "ayuda es_subsec");
                                if (entrada != NULL)
                                {
                                  cout << "es_subsecuencia secuencia: Ingrese en secuencia la secuencia que desea buscar como subsecuencia" << endl;
                                  cout << "esto le muestra cuantas veces esta aparece como subsecuencia. EJ: es_subsecuencia ATUACG" << endl;
                                }
                                else
                                {
                                  entrada = strstr(comand, "ayuda enmascarar");
                                  if (entrada != NULL)
                                  {
                                    cout << "enmascarar secuencia: Ingrese en secuancia la secuencia que desee enmascarar en" << endl;
                                    cout << "todas las secuencias almacenadas. Se cambiara por el valor X. EJ: enmascarar ACT" << endl;
                                  }
                                  else
                                  {
                                    entrada = strstr(comand, "ayuda guardar nomb");
                                    if (entrada != NULL)
                                    {
                                      cout << "guardar nombre_archivo: ingrese en nombre_archivo el nombre que desee para el archivo en el que" << endl;
                                      cout << "se van a escribir las secuencias guardadas en memoria EJ: guardar fastanuevo.fa" << endl;
                                    }
                                    else
                                    {
                                      entrada = strstr(comand, "codificar"); 
                                      if (entrada != NULL && strstr(comand, "de") == NULL)
                                      {
                                        char *p;
                                        p = strtok(entrada, " ");
                                        p = strtok(NULL, " ");
                                        strcpy(X, p);
                                        string m(X);
                                        if (listaADN.size() != 0)
                                        {
                                          cout << "Encriptando" << endl;
                                          cout << "Nombre: " << m << endl;
                                          encriptado(listaADN, m);
                                        }
                                        else
                                        {
                                          entrada = strstr(comand, "decodificar");
                                          if (entrada != NULL && strstr(comand, "de") != NULL)
                                          {
                                            char *q;
                                            q = strtok(entrada, " ");
                                            q = strtok(NULL, " ");
                                            strcpy(X, q);
                                            string m(X);
                                            if (listaADN.size() != 0)
                                            {
                                              cout << "desencriptando" << endl;
                                              cout << "Nombre: " << m << endl;
                                              desencriptar(m);
                                            }
                                            else
                                            {
                                              cout << "Digite un comando valido" << endl;
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
    }
  }
}

/*cargar nombre_archivo
Salida en pantalla. 
(Archivo vacío) “nombre_archivo ” no contiene ninguna secuencia.
(Una sola secuencia) 1 secuencia cargada correctamente desde “nombre_archivo ”.
(Varias secuencias) n secuencias cargadas correctamente desde “nombre_archivo ”.
descripción: Carga en memoria los datos contenidos en el archivo identificado por nombre_archivo.*/

void leerArchivo(string archivo, list<lista_sec> &listaADN)
{
  ifstream arch;
  string txt;
  char temp[5000];

  arch.open(archivo, ios::in); //Se abre el archivo
  if (arch.fail())
  { //Condicion por si falla
    cout << "No se puede abrir" << endl;
    exit(1);
  }
  //////
  lista_sec aux;
  int cont = 0;
  int ayuda;
  while (!arch.eof())
  {
    char nom[200];
    ayuda = 0;
    getline(arch, txt);
    strcpy(temp, txt.c_str());

    for (int j = 0; j < txt.size(); j++)
    {
      if (txt[j] == '>')
      {
        ayuda = 1;
      }
    }

    aux.longitud_linea = txt.size();

    if (ayuda != 0)
    {
      if (cont > 0)
      {
        listaADN.push_back(aux);
        aux.secuencias.clear();
      }
      cont = 1;
    }
    bool terminado = false;
    if (ayuda != 0)
    {
      strcpy(aux.nombre, temp);
      ayuda = 0;
    }
    else
    {
      for (int i = 0; i < txt.size(); i++)
      {
        char t = txt[i];
        aux.secuencias.push_back(t);
      }
    }
    if (arch.eof())
    {
      listaADN.push_back(aux);
    }
  }

  cout << listaADN.size() << " secuencia(s) cargada(s) con exito" << endl;
  arch.close();
}

/*comando: conteo
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(Una sola secuencia) 1 secuencia en memoria.
(Varias secuencias) n secuencias en memoria.
descripción: Imprime por pantalla la cantidad de secuencias cargadas en memoria.*/
void conteo(list<lista_sec> listaADN)
{
  if (listaADN.size() > 0)
  {
    cout << listaADN.size() << " secuencia(s) cargada(s) en memoria " << endl;
  }
  else
  {
    cout << "No hay secuencias cargadas en memoria" << endl;
  }
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
void listar_secuencias(list<lista_sec> listaADN)
{
  int a = 0;
  if (listaADN.size() == 0)
  {
    cout << "No hay secuencias cargadas" << endl;
  }
  else
  {
    list<lista_sec>::iterator it;
    for (it = listaADN.begin(); it != listaADN.end(); ++it)
    {
      cout << endl;
      lista_sec aux1 = *it;
      //para conocer si es indeterminado
      list<char>::iterator it2;
      for (it2 = aux1.secuencias.begin(); it2 != aux1.secuencias.end(); ++it2)
      {
        if (*it2 == '-')
        {
          a = 1;
        }
      }
      if (a == 0)
      {
        cout << "Secuencia completa de archivo no vacio" << endl;
        cout << "Secuencia " << aux1.nombre << " contiene " << aux1.secuencias.size() << " bases." << endl;
      }
      else
      {
        cout << "Secuencia incompleta de archivo no vacio" << endl;
        cout << "Secuencia " << aux1.nombre << " contiene al menos " << aux1.secuencias.size() << " bases." << endl;
      }

      list<char>::iterator it1;
      for (it1 = aux1.secuencias.begin(); it1 != aux1.secuencias.end(); ++it1)
      {
        cout << *it1;
      }
      cout << endl;
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
void histograma(list<char> lista, string m)
{

  list<pair<int, char>> bases;

  pair<int, char> p1 = make_pair(0, 'A');
  bases.push_back(p1);
  pair<int, char> p2 = make_pair(0, 'C');
  bases.push_back(p2);
  pair<int, char> p3 = make_pair(0, 'G');
  bases.push_back(p3);
  pair<int, char> p4 = make_pair(0, 'T');
  bases.push_back(p4);
  pair<int, char> p5 = make_pair(0, 'U');
  bases.push_back(p5);
  pair<int, char> p6 = make_pair(0, 'R');
  bases.push_back(p6);
  pair<int, char> p7 = make_pair(0, 'Y');
  bases.push_back(p7);
  pair<int, char> p8 = make_pair(0, 'K');
  bases.push_back(p8);
  pair<int, char> p9 = make_pair(0, 'M');
  bases.push_back(p9);
  pair<int, char> p10 = make_pair(0, 'S');
  bases.push_back(p10);
  pair<int, char> p11 = make_pair(0, 'W');
  bases.push_back(p11);
  pair<int, char> p12 = make_pair(0, 'B');
  bases.push_back(p12);
  pair<int, char> p13 = make_pair(0, 'D');
  bases.push_back(p13);
  pair<int, char> p14 = make_pair(0, 'H');
  bases.push_back(p14);
  pair<int, char> p15 = make_pair(0, 'V');
  bases.push_back(p15);
  pair<int, char> p16 = make_pair(0, 'N');
  bases.push_back(p16);
  pair<int, char> p17 = make_pair(0, 'X');
  bases.push_back(p17);

  list<char>::iterator it1;
  list<pair<int, char>>::iterator it2;
  char actual;

  pair<int, char> base_actual;

  for (it1 = lista.begin(); it1 != lista.end(); ++it1)
  {
    actual = *it1;
    for (it2 = bases.begin(); it2 != bases.end(); ++it2)
    {
      pair<int, char> base_actual = *it2;
      if (actual == base_actual.second)
      {
        base_actual.first++;
        *it2 = base_actual;
      }
    }
  }

  list<pair<int, char>>::iterator it3;

  for (it3 = bases.begin(); it3 != bases.end(); ++it3)
  {
    pair<int, char> base_actual = *it3;
    cout << "Base: " << base_actual.second << " : " << base_actual.first << endl;
  }
}

lista_sec buscarLista(list<lista_sec> listaADN, string nombre)
{

  list<lista_sec>::iterator it;
  lista_sec actual = listaADN.front();

  for (it = listaADN.begin(); it != listaADN.end(); ++it)
  {
    lista_sec actual = *it;
    char *nombre_actual = actual.nombre;
    char *aux = const_cast<char *>(nombre.c_str());

    if (strcmp(nombre_actual, aux) == 0)
      return *it;
  }
  return *it;
}

/*comando: es_subsecuencia secuencia
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(La secuencia no existe) La secuencia dada no existe.
(Varias secuencias) La secuencia dada se repite s veces.
descripción: Determina si una secuencia, dada por el usuario, existe dentro de las secuencias
cargadas. Si es así, determina la cantidad de veces en las que esta secuencia dada se repite.*/
int es_subsecuencia(list<lista_sec> listaADN, string x)
{

  lista_sec aux = buscarLista(listaADN, x);
  int veces = 0;

  list<lista_sec>::iterator it;
  for (it = listaADN.begin(); it != listaADN.end(); ++it)
  {
    lista_sec actual = *it;
    list<char>::iterator it2;
    list<char>::iterator itpsecuencia;
    for (it2 = actual.secuencias.begin(); it2 != actual.secuencias.end(); ++it2)
      for (itpsecuencia = aux.secuencias.begin(); itpsecuencia != aux.secuencias.end(); ++itpsecuencia)
      {
        if (*itpsecuencia != *it2)
        {
        }
        else
        {
          veces++;
          break;
        }
      }
  }
  return 0;
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

void imprimirLista(list<char> lista)
{
  list<char>::iterator it;

  for (it = lista.begin(); it != lista.end(); ++it)
    cout << *it;
  cout << endl;
}

void enmascarar(list<lista_sec> &lista, string nombre)
{

  char *nombre_aux = const_cast<char *>(nombre.c_str());

  list<lista_sec>::iterator it;
  list<char>::iterator it2;

  //list<char> aux = *lista;
  for (it = lista.begin(); it != lista.end(); ++it)
  {
    lista_sec aux = *it;
    if (strcmp(aux.nombre, nombre_aux) == 0)
    {
      for (it2 = aux.secuencias.begin(); it2 != aux.secuencias.end(); ++it2)
        *it2 = 'X';
      *it = aux;
    }
  }
}
/* comando: guardar nombre_archivo
salida en pantalla:
(No hay secuencias cargadas) No hay secuencias cargadas en memoria.
(Escritura exitosa) Las secuencias han sido guardadas en “nombre_archivo ”.
(Problemas en archivo) Error guardando en ”nombre_archivo ”.
descripción: Guarda en el archivo nombre_archivo las secuencias cargadas en memoria. Se debe
tener en cuenta la justificación (de líneas) del archivo inicial. */
void guardarArchivo(string nombre, list<lista_sec> lista)
{
  ofstream archivo;
  archivo.open(nombre, ios::out);

  if (archivo.fail())
  {
    cout << "No se pudo abrir abrir el archivo" << endl;
    exit(1);
  }

  list<lista_sec>::iterator it;
  lista_sec actual;
  for (it = lista.begin(); it != lista.end(); ++it)
  {
    actual = *it;
    list<char>::iterator it2;
    archivo << actual.nombre << "\n";
    for (it2 = actual.secuencias.begin(); it2 != actual.secuencias.end(); ++it2)
    {
      archivo << *it2;
    }
    archivo << "\n";
  }

  archivo.close();
}

/*comando: salir
salida en pantalla:
(No tiene salida por pantalla)
descripción: Termina la ejecución de la aplicación*/
//-ESTE COMANDO SE EJECUTA EN EL MENU INICIAL-//

/*
comando: codificar nombre_archivo.fabin
salida en pantalla:
(mensaje de error) No se pueden guardar las secuencias cargadas en nombre_archivo.fabin .
(codificación exitosa) Secuencias codificadas y almacenadas en nombre_archivo.fabin .
descripción: El comando debe generar el archivo binario con la correspondiente codificación de
Huffman en el formato descrito más arriba, almacenándolo en disco bajo el nombre:
nombre_archivo.fabin .
*/
//Construcción del arbol y llenado
nodo_huffman *asigna_valor(char base, int frecuenc, nodo_huffman *izquierdo, nodo_huffman *derecho)
{
  nodo_huffman *aux = new nodo_huffman();
  //aux = new nodo_huffman();
  aux->base = base;
  aux->frecuen = frecuenc;
  aux->izquierdo = izquierdo;
  aux->derecho = derecho;
  return aux;
} //Esta funciona como un "Constructor" que asigna los valores de un nodo de acuerdo a los parametros que le pasan al llamar la función

void encriptaHuffman(nodo_huffman *raiz, string cadena, unordered_map<char, string> &codificacion) //Funcion recursiva
{
  if (raiz == nullptr)
  {
    return; //Verifica que la raiz haya sido creada
  }
  if (!raiz->izquierdo && !raiz->derecho)
  {
    codificacion[raiz->base] = cadena;
  }
  encriptaHuffman(raiz->izquierdo, cadena + "0", codificacion); //recurisvidad. La raiz cambia por el nodo izquierdo
  encriptaHuffman(raiz->derecho, cadena + "1", codificacion);   //Recursividad. La raiz cambia por el nodo derecho
}

void encriptado(list<lista_sec> listaADN, string nombrearch)
{

  char X[100];
  unordered_map<char, int> frecuen; //Mapa para guardar inicialmente nuestras bases y la cantidad de veces que aparecen

  //Recorrido a toda la lista de secuencias cargadas

  list<lista_sec>::iterator it;
  for (it = listaADN.begin(); it != listaADN.end(); ++it)
  {
    //Almacenamiento de cada letra para contar sus frecuencias
    lista_sec aux = *it;
    strcpy(X, aux.nombre);
    string m(X);        //Conversion de char a string para recorerlo
    for (char base : m) //Base es el elemento temporal que almacena lo que hay en m. Funciona hasta que acaba el string
    {
      frecuen[base]++; // se almacena la base en el char y se hace incremento a las veces que aparece (PARA EL NOMBRE)
    }
    list<char>::iterator it2;
    for (it2 = aux.secuencias.begin(); it2 != aux.secuencias.end(); ++it2)
    {
      char aux2 = *it2; //Variable que almacena lo que contiene el iterador que recorre la lista
      frecuen[aux2]++;  //Se almacena la base o en caso de que ya exista se hace incremento. (PARA LA CADENA DE ADN)
    }
  } //Fin del for //Este almacena cada letra con sus secuencias

  priority_queue<nodo_huffman *, vector<nodo_huffman *>, buscafrecuencia> colapriori; //ESTA COLA VA A ORGANIZAR CADA FRECUENCIA DE VARIABLES
  //Fin de lectura inicial
  //Se agregan los nodos
  for (auto val : frecuen)
  {
    colapriori.push(asigna_valor(val.first, val.second, nullptr, nullptr)); //Guarda en la cola de prioridad el primer valor y segundo de la lista de frecuencias.
  }
  while (colapriori.size() != 1)
  {
    nodo_huffman *izquierdo = colapriori.top();
    colapriori.pop();
    nodo_huffman *derecho = colapriori.top();
    colapriori.pop();
    int total = izquierdo->frecuen + derecho->frecuen;
    colapriori.push(asigna_valor('\0', total, izquierdo, derecho)); // EL '\0' significa que agrega vacio, evita la basura y deja la variable vacía
  }

  //Creamos la raiz
  nodo_huffman *raiz = colapriori.top();    //RAIZ DEL ARBOL apuntado a cabeza de la cola de prioridad
  unordered_map<char, string> codificacion; //En este mapa se almacenan las bases y su frecuenia.

  encriptaHuffman(raiz, "", codificacion); //Paso de parametro para llenado de codificación arrancando desde la raíz

  //Almacenamiento en lista para guardar codificacion
  list<lista_sec_codifica> auxiliar; //Para almacenar todas las secuencias codificadas
  //lista_sec_codifica auxipush;

  char tempo[100];
  list<lista_sec>::iterator it3;
  for (it3 = listaADN.begin(); it3 != listaADN.end(); ++it3)
  {
    lista_sec_codifica auxipush;

    lista_sec auxi = *it3;

    strcpy(tempo, auxi.nombre);
    string m(tempo);
    string guardanombre = "";
    for (char base : m)
    {
      guardanombre += codificacion[base];
    }
    strcpy(auxipush.nombre, guardanombre.c_str()); //Almacena el nombre codificado en el auxiliar que se le va a hacer push

    string guardabases = "";
    list<char>::iterator it4;
    for (it4 = auxi.secuencias.begin(); it4 != auxi.secuencias.end(); ++it4)
    {
      char auxibases = *it4;
      auxipush.secuencias.push_back(codificacion[auxibases]);
      auxipush.bases.push_back(auxibases);

      //guardabases += codificacion[auxibases];
    }

    auxiliar.push_back(auxipush);
  } //Fin del for

  //Escritura en el archivo
  FILE *fp;
  char nombrearchivo[50];

  fp = fopen(nombrearch.c_str(), "ab");
  if (fp == NULL)
  {
    puts("Archivo invalido");
  }
  fwrite(&auxiliar, sizeof(lista_sec_codifica), 1, fp);
  cout << "Se ha creado un archivo de tipo binario con el nombre: " << nombrearch << " de manera satisfactoria." << endl;

  int des;
  cout << "Le gustaria ver la codificacion de cada caracter? (Si = 0, No = 1)" << endl;
  cin >> des;
  if (des == 0)
  {
    imprimeHuffman(codificacion); //Esto imprime el mapa. Donde se muestra para cada variable el equivalente en binario que le fue asignado
    cout << "___________________" << endl;
    listar_codificados(auxiliar); // LLamado para imprimir todo codificado
  }
  else
  {
    cout << "Ha elegido no ver la codificacion por caracter" << endl;
  }

  fclose(fp);
}

void imprimeHuffman(unordered_map<char, string> codificacion)
{
  cout << "Frecuencias dadas por algoritmo: " << endl; //
  for (auto val : codificacion)
  {
    cout << val.first << " " << val.second << endl;
  }

  cout << "El documento encriptado es el siguiente" << endl; //
}

void listar_codificados(list<lista_sec_codifica> auxiliar) //Imprime las secuencias codificadas para poder ver lo que va a ir al archivo.
{
  int a = 0;
  if (auxiliar.size() == 0)
  {
    cout << "No hay secuencias cargadas" << endl;
  }
  else
  {
    list<lista_sec_codifica>::iterator it;
    for (it = auxiliar.begin(); it != auxiliar.end(); ++it)
    {
      cout << endl;
      lista_sec_codifica aux1 = *it;

      cout << aux1.nombre << endl;

      list<string>::iterator it1;
      for (it1 = aux1.secuencias.begin(); it1 != aux1.secuencias.end(); ++it1)
      {
        cout << *it1;
      }
      cout << endl;
    }
  }
}

/*
comando: decodificar nombre_archivo.fabin
salida en pantalla:
(mensaje de error) No se pueden cargar las secuencias en nombre_archivo.fabin .
(decodificación exitosa) Secuencias decodificadas desde nombre_archivo.fabin y cargadas
en memoria.
descripción: El comando debe cargar en memoria las secuencias contenidas en el archivo binario
nombre_archivo.fabin , que contiene una codificación Huffman de un conjunto de secuencias en
el formato descrito más arriba
*/

void desencriptar(string nombrearch)
{
  unordered_map<char, int> frecuen;
  list<lista_sec_codifica> auxiliar;
  FILE *pf;
  pf = fopen(nombrearch.c_str(), "rb");
  fread(&auxiliar, sizeof(lista_sec_codifica), 1, pf);

  int a = 0;
  if (auxiliar.size() == 0) //Verfica que el archivo contenga algún tipo de contenido
  {
    cout << "No hay secuencias cargadas en el archivo" << endl;
  }
  else
  {
    cout << "El contenido codificado es: " << endl;
    list<lista_sec_codifica>::iterator it;
    for (it = auxiliar.begin(); it != auxiliar.end(); ++it)
    {
      cout << endl;
      lista_sec_codifica aux1 = *it;

      cout << aux1.nombre << endl;

      list<string>::iterator it1;
      for (it1 = aux1.secuencias.begin(); it1 != aux1.secuencias.end(); ++it1)
      {
        cout << *it1;
      }
      cout << endl;
    }
    
    cout << "El contenido decodificado de " << nombrearch << " es: " << endl; 

    





    







}