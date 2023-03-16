#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include <vector>

using namespace std;

template <class T>
class Diccionario
{
    public:
        vector<T> diccionario;
        
        void Iniciar(){
            
        }
//----------------------------------------------------------------------------
        void Agregar(T vertice){
            diccionario.push_back(vertice);
        }
//----------------------------------------------------------------------------
        bool Pertenece(T vertice){
            bool encontrado = false;
            typename vector<T>::iterator it;
            for(it=diccionario.begin(); (it<diccionario.end()) && !encontrado; it++){
                if(*it == vertice){
                    encontrado = true;
                }
            }
            return encontrado;
        }
//----------------------------------------------------------------------------
        void Destruir() {
			
		}
//----------------------------------------------------------------------------		
		int numElem() {
			return diccionario.size();
		}
//----------------------------------------------------------------------------
        void Vaciar(){
            typename vector<T>::iterator it;
            it=diccionario.begin();
            while(it != nullptr){
                diccionario.erase(diccionario.begin());
                it = diccionario.begin();
            }
        }
//----------------------------------------------------------------------------		
		void pop() {
			int amount_elements = numElem();
			diccionario.erase(diccionario.begin()+amount_elements);
		}
//----------------------------------------------------------------------------
        virtual ~Diccionario(){
        }
};

#endif
