#include <vector>
#include <iostream>
using namespace std;

  template <class T>
	struct Grafo
	{
		int numVertices;
		vector<T> listaVertices; 
        vector< vector<float> > matrizAdy; 

		public:
			Grafo();
            Grafo(int nvertices);
            void insertarVertice(T vertice);
            void insertarArista(long origen, long destino, float peso);
            void imprimirAdyacencia();
	};


	template<class T>
	Grafo<T>::Grafo(){}

    template<class T>
	Grafo<T>::Grafo(int numVertices){
		this->numVertices = numVertices; 
        this->matrizAdy.resize(numVertices, vector<float>(numVertices,0)); 
    }

    template<class T>
    void Grafo<T>::insertarVertice(T vertice){
        this->listaVertices.push_back(vertice); 
    }

    template<class T>
    void Grafo<T>::insertarArista(long origen, long destino, float peso){
        this->matrizAdy[origen][destino] = peso; 
    }

    template<class T>
    void Grafo<T>::imprimirAdyacencia(){
        for(int i = 0; i < this->numVertices; i++){
            for(int j = 0; j < this->numVertices; j++) {
                cout << this->matrizAdy[i][j] << " "; 
            }
        }
        cout << endl;
    }