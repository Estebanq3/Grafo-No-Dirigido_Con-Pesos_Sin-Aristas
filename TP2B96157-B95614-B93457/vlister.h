#include <iostream>
#include <sstream>
using namespace std;
#define Maximo 999999999
#define TAMANYO 100

template <class T>
class VL {
	private: 
	T* vertices;
	int* indices; 
	int ultimoLleno; 
	
	public:
	VL();
	void Agregar(T ver, int indice); 
	void Iniciar();
	int Indice(T ver); 
	T Vertice(int indice);  
	void Destruir(); 
	string PrintVL(); 	
}; 


template <class T>
VL<T>::VL() {
}
//----------------------------------------------------------------------------
template <class T>
void VL<T>::Destruir() {
	
	free(this->vertices); 
	free(this->indices); 
}
//----------------------------------------------------------------------------
template <class T>
void VL<T>::Iniciar() {
	this->vertices = (T*)calloc(TAMANYO, sizeof(T));
	this->indices = (int*)calloc(TAMANYO, sizeof(int)); 
	this->ultimoLleno = 0; 
}
//----------------------------------------------------------------------------

template <class T>
void VL<T>::Agregar(T ver, int indice) {
	if (this->ultimoLleno < TAMANYO) {
		this->vertices[ultimoLleno] = ver; 
		this->indices[ultimoLleno] = indice; 
		++this->ultimoLleno; 
	}
	else {
		std::cout << "VL full space used" << std::endl; 
	}
	
}
//----------------------------------------------------------------------------

template <class T>
int VL<T>::Indice(T ver) {
	int index = 0;
	int image = -1; 
	bool found = false;  
	while (index < this->ultimoLleno && !found) {
		if (this->vertices[index] == ver) {
			found = true; 
			image = this->indices[index]; 
		}
		else {
			index++; 		
		}	
	}
	
	 return image; 
}

//----------------------------------------------------------------------------

template <class T>
T VL<T>::Vertice(int indice) {
	int index = 0; 
	bool found = false; 
	T image = this->vertices[0];
	while (index < this->ultimoLleno && !found) {
		if (this->indices[index] == indice) {
			found = true; 
			image = this->vertices[index];  
		}
		else {
			index++; 
		} 	
	}
	 return image; 	
}
//----------------------------------------------------------------------------

template <class T>
string VL<T>::PrintVL() {
stringstream ss; 
for (int index = 0; index < this->ultimoLleno; ++index) {
	ss << this->vertices[index] << " = " << this->indices[index] << "\n"; 
}

return ss.str(); 	
}
