#ifndef _Grafo
#define _Grafo
#include "Nodo.h"
#include "NodoLH.h"
#include <iostream>
using namespace std;

class Grafo{

    private:
        class ListaDeHijos{
            public:
                NodoLH * primero;
                ListaDeHijos();
                ~ListaDeHijos();
        };
        

    public:
        ListaDeHijos * listaDeHijos;
        Grafo();
        ~Grafo();
        void Iniciar();
        void Destruir();
        void Vaciar();
        int Vacio();
        NodoLH* AgregarVertice(T);
        void EliminarVertice(NodoLH*);
        void ModificarEtiqueta(NodoLH*,T);
        NodoLH* PrimerVertice();
        void AgregarArista(NodoLH*,NodoLH*,int);      
        void EliminarArista(NodoLH*,NodoLH*);
        void ModificarPeso(NodoLH*,NodoLH*,int peso);
        int Peso(NodoLH*,NodoLH*);
        bool ExisteArista(NodoLH*,NodoLH*);
        NodoLH* SiguienteVertice(NodoLH*);
        NodoLH* PrimerVerticeAdyacente(NodoLH*);
        NodoLH* SiguienteVerticeAdyacente(NodoLH*,NodoLH*);
        int NumVertices();
        int NumVerticesAdyacentes(NodoLH*);
        int NumAristas();
        char Etiqueta(NodoLH*);
        bool EsAdyacente(NodoLH*,NodoLH*);
        bool EsVerticeNulo(NodoLH*);

        NodoLH* getVerticeNulo();

        void imprimirSublistas();
        void imprimir();
        NodoLH* traductorNodo(char);

};



#endif