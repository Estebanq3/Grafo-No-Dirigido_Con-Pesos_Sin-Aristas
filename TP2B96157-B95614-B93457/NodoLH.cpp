#include "NodoLH.h"

//NodoLH
NodoLH::NodoLH(){
    
}

NodoLH::NodoLH(T etiqueta):Nodo(etiqueta){
    siguiente = nullptr;
    sublista = new SubLista();
}

NodoLH::~NodoLH(){
    
}


//SubLista
NodoLH::SubLista::SubLista(){
    primeroSL=nullptr;

}

NodoLH::SubLista::~SubLista(){
    primeroSL=nullptr;
}

//NodoSLH
NodoLH::SubLista::NodoSLH::NodoSLH(NodoLH* nodo, int peso):Nodo(etiqueta){
    siguienteSL = nullptr;
    this->nodo = nodo;
    this->peso = peso;
}

NodoLH::SubLista::NodoSLH::~NodoSLH(){
}

T NodoLH::SubLista::NodoSLH::getEtiqueta(){
    return nodo->getEtiqueta();
}

