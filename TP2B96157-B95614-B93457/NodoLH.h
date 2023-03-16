#ifndef _NODO_LH
#define _NODO_LH

#include "Nodo.h"

class NodoLH : public Nodo {
    friend class GrafoLSE;
    public:
        class SubLista{
            public:
                class NodoSLH : public Nodo{
                    public:
                        NodoSLH * siguienteSL;     
                        NodoLH * nodo;
                        int peso = -1;
                        
                        NodoSLH(NodoLH*,int peso);
                        ~NodoSLH();
                        T getEtiqueta();  
                };
                NodoSLH * primeroSL;

                SubLista();
                ~SubLista();

        };
        NodoLH * siguiente;
        SubLista * sublista;
        //int peso = -1;
        
    
        NodoLH();
        NodoLH(T);
        ~NodoLH();
};

#endif
