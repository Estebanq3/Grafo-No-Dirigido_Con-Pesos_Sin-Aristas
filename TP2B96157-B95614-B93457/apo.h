#include <iostream>
#include <sstream>
using namespace std; 
#define SIZE 100
#define Maximo 999999999

template <typename T>
struct arista_t{
	T vertice_origen; 
	T vertice_destino; 
	int peso; 	
}; 


template<class T>
class APO {
	private:
	arista_t<T>* heap_vector; 
	int ultimaPosicion;
	int cantidadNodos; 
	
	public:
	APO(); 
	void Iniciar(); 
	void Insertar(T vertice_origen, T vertice_destino, int peso);  
	arista_t<T>* Popear(); 
	string ImprimirAPO(); 
		
}; 


//----------------------------------------------------------------------------
template<class T>
	APO<T>::APO() {	
}

template <class T>
void APO<T>::Iniciar() {
	this->heap_vector = (arista_t<T>*)calloc(SIZE, sizeof(T)); 	
	this->cantidadNodos = 0; 
	this->ultimaPosicion = 1; 
}

//----------------------------------------------------------------------------
template <class T>
void APO<T>::Insertar(T vertice_origen, T vertice_destino, int peso){
	int index = this->ultimaPosicion;  
	bool finished = false;
	int father = 0; 
	if (this->cantidadNodos != 0) {
	
		while (!finished) {	
			if (index %2 == 0) {
				father = index/2; 
			}
			else {
				father = (index-1)/2; 
			}
			if (peso < this->heap_vector[father].peso) {
				this->heap_vector[index].vertice_origen = this->heap_vector[father].vertice_origen; 
				this->heap_vector[index].vertice_destino = this->heap_vector[father].vertice_destino; 
				this->heap_vector[index].peso = this->heap_vector[father].peso; 
				index = father; 
				
				if (index == 1) {
					finished = true; 	
				} 
			}
			else {
				finished = true; 
			}		
		}	
	}
	this->heap_vector[index].vertice_origen = vertice_origen; 
	this->heap_vector[index].vertice_destino = vertice_destino; 
	this->heap_vector[index].peso = peso; 
	++this->cantidadNodos; 
	++this->ultimaPosicion;  
	
}

//----------------------------------------------------------------------------


template <class T>
arista_t<T>* APO<T>::Popear(){
	arista_t<T>* arista  = NULL; 
	if (this->cantidadNodos != 0){
		arista = new arista_t<T>(); 
		arista->vertice_origen = this->heap_vector[1].vertice_origen; 
		arista->vertice_destino = this->heap_vector[1].vertice_destino; 	
		arista->peso = this->heap_vector[1].peso; 	
		--cantidadNodos; 

		bool finished = false; 
		int last_position = this->ultimaPosicion; 
		if (this->cantidadNodos != 0) {
			int weight = this->heap_vector[ultimaPosicion-1].peso; 
			int index = 1; 
			int son_selected = 0; 
			int weight_s1; 
			int weight_s2; 
			while (!finished){
				int pos_s1 = index*2; 
				int pos_s2 = (index*2)+1; 
				weight_s1 = Maximo; 
				weight_s2 = Maximo; 
				if (pos_s1 < last_position-1) {				
					weight_s1 = this->heap_vector[pos_s1].peso;  
				}
				if (pos_s2 < last_position-1) {	
					weight_s2 = this->heap_vector[pos_s2].peso;
				} 
				if (weight_s1 != Maximo || weight_s2 != Maximo) {	
					if (weight > weight_s1 || weight > weight_s2) {	 
						if (weight_s1 < weight_s2) {			
							son_selected = pos_s1;  
						}
						else{
							son_selected = pos_s2;  
						}
					
					this->heap_vector[index].vertice_origen = this->heap_vector[son_selected].vertice_origen; 
					this->heap_vector[index].vertice_destino = this->heap_vector[son_selected].vertice_destino; 
					this->heap_vector[index].peso = this->heap_vector[son_selected].peso; 
					index = son_selected; 
				}
				else {
					finished = true; 			
				}	
			}
			else {
				finished = true; 
			}
		}
		this->heap_vector[index].vertice_origen = this->heap_vector[this->ultimaPosicion-1].vertice_origen; 
		this->heap_vector[index].vertice_destino = this->heap_vector[this->ultimaPosicion-1].vertice_destino; 
		this->heap_vector[index].peso =  this->heap_vector[this->ultimaPosicion-1].peso; 	
	}
	--this->ultimaPosicion; 
	}
	else {
		cout << "APO se encuentra vacio" << endl;  
	}
	return arista; 
}

//----------------------------------------------------------------------------
template <class T>
string APO<T>::ImprimirAPO() {
	stringstream ss; 
	for (int index = 1; index < this->ultimaPosicion; ++index) {
		if (index != this->ultimaPosicion -1) { 
			ss << this->heap_vector[index].peso << "-";
		}
		else {
			ss << this->heap_vector[index].peso; 
		} 
	}
	ss << "\n";  	
	return ss.str();
}


