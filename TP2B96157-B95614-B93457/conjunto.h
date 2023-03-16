#include <iostream>
using namespace std; 
#include <sstream>
template <class T>
class Conjunto {

	private:
	T** set; 
	int* contador; 
	int cNum; 
	
	public: 
		Conjunto(); 
		void Inicializar(int max_amount_elements); 
		void AnadirConjunto(int conjunto);
		void AgregarAConjunto(T ver, int conjunto);  
		int Pertenece(T ver);
		void Union(int conjunto_1, int conjunto_2);
		bool Interseccion(int conjunto, Conjunto<T>&cc_1, int conjunto_cc1);   
		void PopElement(int conjunto, T ver); 
		int getConjunto(int index);
		void transferirElementos(Conjunto<T>&cc_1); 
		string printSet(); 
}; 

//---------------------------------------------------------------
template <class T>
Conjunto<T>::Conjunto() {
	
}
//---------------------------------------------------------------

template <class T>
void Conjunto<T>::transferirElementos(Conjunto<T>&set_1) {
	for (int conjunto = 0; conjunto < this->cNum; ++conjunto) {
		for (int ver = 1; ver <= this->contador[conjunto]; ++ver) {
			set_1.set[conjunto][ver] = this->set[conjunto][ver]; 
		} 
		set_1.cNum = this->cNum;
		for (int index = 0; index < this->cNum; ++index) {
			set_1.contador[index] = this->contador[index]; 
		} 		
	}	
}

//---------------------------------------------------------------
template <class T>
bool Conjunto<T>::Interseccion(int conjunto, Conjunto<T>&set_1, int conjunto_set1) {
	bool exist = false; 
	for (int index = 1; index <= this->contador[conjunto]; ++index) {
		for (int index_set = 1; index_set <= set_1.contador[conjunto_set1]; ++index_set) {
			if (this->set[conjunto][index] == set_1.set[conjunto_set1][index_set]) {
				exist = true; index_set = set_1.contador[conjunto_set1]+1; 
				index = this->contador[conjunto]+1; 
			}
		}
	}
	return exist; 	
}

//---------------------------------------------------------------
template <class T>
void Conjunto<T>::PopElement(int conjunto, T ver) {
	--this->contador[conjunto];  
}

//---------------------------------------------------------------
template <class T>
int Conjunto<T>::getConjunto(int index) {
	return index; 
} 

//---------------------------------------------------------------
template <class T>
void Conjunto<T>::Inicializar(int max_amount_elements) {
	this->set = (T**)calloc(max_amount_elements, sizeof(T*));
	for (int conjunto = 0; conjunto < max_amount_elements; ++conjunto) {
		this->set[conjunto] = (T*)calloc(max_amount_elements+1, sizeof(T)); 
	}
	
	this->contador = (int*)calloc(max_amount_elements, sizeof(int)); 																			 		
	this->cNum = 0;   																			
}

//---------------------------------------------------------------
template <class T>
void Conjunto<T>::AnadirConjunto(int conjunto) {
	++this->cNum; 	
}

//---------------------------------------------------------------
template <class T>
void Conjunto<T>::AgregarAConjunto(T ver, int conjunto) {
	if (conjunto < this->cNum) {
		++this->contador[conjunto];  
		this->set[conjunto][this->contador[conjunto]] = ver;  
	}
	else {
		std::cout << "Invalid add to an unexistent set" << std::endl; 
	}	
}

//---------------------------------------------------------------
template <class T>
int Conjunto<T>::Pertenece(T ver) {
	int conjunto = -1; 
	bool found = false; 
	for (int c = 0; c < this->cNum; ++c) {
		for (int v = 1; v <= this->contador[c]; ++v) {
			if (this->set[c][v] == ver) {
				conjunto = c; 
				v = this->contador[c]+1;
			}
		}
		if (found) {
			c = this->cNum;	
		}				
	}
	return conjunto; 
}
//---------------------------------------------------------------

template <class T>
void Conjunto<T>::Union(int conjunto_1, int conjunto_2) {
	if (conjunto_2 < conjunto_1) {
		int aux = conjunto_1; 
		conjunto_1 = conjunto_2; 
		conjunto_2 = aux; 
	}
	
	for (int ver = 1; ver <= this->contador[conjunto_2]; ++ver) {
		AgregarAConjunto(this->set[conjunto_2][ver], conjunto_1); 	
	}
	this->contador[conjunto_2] = 0; 
	
	int last_conjunto = this->cNum-1; 
	
	for (int ver = 1; ver <= this->contador[last_conjunto]; ++ver) {
		AgregarAConjunto(this->set[last_conjunto][ver], conjunto_2); 		
	} 
	--this->cNum; 			
	this->contador[last_conjunto] = 0; 
}

//---------------------------------------------------------------
template <class T>
string Conjunto<T>::printSet() {
stringstream ss; 	

std::cout << "Conjuntos : " << this->cNum << std::endl; 
for (int index = 0; index < this->cNum; ++index) {
	ss << this->contador[index] << ", "; 
}
std::cout << "Counter of sets: " << ss.str() << std::endl; 
ss.str(""); 

for (int conjunto = 0; conjunto < this->cNum; ++conjunto) {
	for (int ver = 1; ver <= this->contador[conjunto]; ++ver) {
		if (ver != this->contador[conjunto]) {
			ss << this->set[conjunto][ver] << ", "; 
		}
		else {
			ss << this->set[conjunto][ver]; 
		}
	}
	ss << "\n"; 
}	
	
return ss.str(); 	
}
