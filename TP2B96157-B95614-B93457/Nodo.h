#ifndef _NODO
#define _NODO

#include <iostream>
#include <string>
using namespace std;


typedef int T;


class Nodo{


	public:
		T etiqueta;

		Nodo();
		Nodo(T);
		T getEtiqueta();
		void setEtiqueta(T);
		virtual ~Nodo();

};


#endif