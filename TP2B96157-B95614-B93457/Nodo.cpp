#include "Nodo.h"

Nodo::Nodo(){
	
}

Nodo::Nodo(T etiqueta){
	this->etiqueta = etiqueta;
}

T Nodo::getEtiqueta(){
	return etiqueta;
}

void Nodo::setEtiqueta(T etiqueta){
	this->etiqueta = etiqueta;
}

Nodo::~Nodo(){
	
}