#include "GrafoLSE.h"
#include "Nodo.h"
#include "NodoLH.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------------------------------

Grafo::ListaDeHijos::ListaDeHijos(){
    primero = nullptr;
}

//--------------------------------------------------------------------------------------

Grafo::ListaDeHijos::~ListaDeHijos(){

}
//--------------------------------------------------------------------------------------

Grafo::Grafo(){

}



//METODOS GRAFO
//--------------------------------------------------------------------------------------
//INICIANDO GRAFO

/*
	Iniciar 
	Parámetros: ninguno
	Efecto: inicializa el grafo G
	Requiere: grafo no inicializado o destruido 
	Modifica: nada

*/
void Grafo::Iniciar(){
    listaDeHijos = new ListaDeHijos();
}

//--------------------------------------------------------------------------------------
//DESTRUIR GRAFO

Grafo::~Grafo(){
    Destruir();
    delete listaDeHijos;
}

//--------------------------------------------------------------------------------------
//DESTRUIR GRAFO
/*
	Destruir 
	Parámetros: grafo G
	Efecto: destruye grafo G
	Requiere: grafo G inicializado
	Modifica: nada

*/

void Grafo::Destruir(){
    NodoLH * control= PrimerVertice();
    NodoLH * borradoLH=PrimerVertice();
    NodoLH::SubLista::NodoSLH * borradoSL= PrimerVertice()->sublista->primeroSL;
    int contador=0;
    while(control!=nullptr){
        if(control->sublista->primeroSL != nullptr){
            
            while(control->sublista->primeroSL != nullptr){
                borradoSL=control->sublista->primeroSL;
                control->sublista->primeroSL= control->sublista->primeroSL->siguienteSL;
                delete borradoSL;       
            }
            
        }
        listaDeHijos->primero= control->siguiente;
        borradoLH= control;
        control=listaDeHijos->primero;
        delete borradoLH;
    }
}

//--------------------------------------------------------------------------------------
//VACIAR GRAFO

/*
	Vaciar
	Parámetros: grafo G
	Efecto: vacía el grafo G
	Requiere: grafo G inicializado
	Modifica: grafo G

*/
void Grafo::Vaciar(){
    Destruir();
    listaDeHijos->primero = nullptr;
}

//--------------------------------------------------------------------------------------
//VACIO
/*
	Vacío?
	Parámetros:grafo G
	Efecto: devuelve falso o verdadero si el grafo G está vacío
	Requiere: grafo G inicializado
	Modifica:nada 

*/
int Grafo::Vacio(){
    if(listaDeHijos->primero == nullptr){
        return true;
    }
    else{
        return false;
    }
}


//--------------------------------------------------------------------------------------
//AGREGAR VERTICE

/*
	AgregarVértice?
	Parámetros: e ->tipo elemento
	Efecto: agrega un vértice con el elemento e 
	Requiere: grafo G inicializado y elemento e válido 
	Modifica: grafo G

*/
NodoLH* Grafo::AgregarVertice(T etiqueta){
    //NodoLH * control = listaDeHijos->primero;
    //NodoLH * nuevo;
    NodoLH * nuevo= new NodoLH(etiqueta);
    if(listaDeHijos->primero == nullptr){
        listaDeHijos->primero = nuevo;
        listaDeHijos->primero->siguiente = nullptr;
    }else{
        nuevo->siguiente = listaDeHijos->primero;
        listaDeHijos->primero= nuevo;
    }
    
    return nuevo;
}

//--------------------------------------------------------------------------------------

/*
	EliminarVértice
	Parámetros: v tipo vértice
	Efecto: eliminada el vértice v del grafo G
	Requiere:grafo G inicializado y vértice v válido 
	Modifica: grafo V

*/
//Requiere que el vertice sea aislado

void Grafo::EliminarVertice(NodoLH* vertice){
    NodoLH * control = listaDeHijos->primero;
    bool eliminado = false;

    if(control->siguiente == nullptr){
        listaDeHijos->primero = nullptr;
        delete control;

    }else{
        while(control->siguiente != nullptr && eliminado != true){

            //Caso que haya que eliminar el primero
            if(control == vertice && eliminado != true){
                listaDeHijos->primero = listaDeHijos->primero->siguiente;
                delete vertice;
                eliminado = true;
            }
            //Caso que haya que eliminar un vertice entre dos
            if(control->siguiente == vertice  && control->siguiente->siguiente != nullptr && eliminado != true){
                control->siguiente = control->siguiente->siguiente;
                delete vertice;
                eliminado = true;
            }
            //Caso que haya que eliminar un vertice que se encuentre de ultimo
            if(control->siguiente == vertice  && control->siguiente->siguiente == nullptr && eliminado != true){            
                control->siguiente = nullptr;
                delete vertice;
                eliminado = true;
            }else{
                control = control->siguiente;
            }
        }
    }
}

//--------------------------------------------------------------------------------------
/*
	ModificarEtiqueta
	Parámetros: v tipo vértice, e tipo elemento 
	Efecto: cambia la etiqueta actual del vértice v por el elemento e 
	Requiere:grafo inicializado, vértice v y elemento e válidos  
	Modifica: vértice v
*/

void Grafo::ModificarEtiqueta(NodoLH* vertice,T etiqueta){
    vertice->setEtiqueta(etiqueta);
}

//--------------------------------------------------------------------------------------
/*
	Etiqueta?
	Parámetros: v tipo vértice 
	Efecto:devuelve la etiqueta actual del vértice v 
	Requiere: grafo G inicializado y vértice v válido
	Modifica: nada 
*/

char Grafo::Etiqueta(NodoLH* vertice){
    return (char)vertice->getEtiqueta();
}

//--------------------------------------------------------------------------------------
/*
	PrimerVértice?
	Parámetros:grafo G
	Efecto:devuelve el primer vértice del grafo G
	Requiere: grafo G inicializado 
	Modifica: nada

*/
NodoLH* Grafo::PrimerVertice(){
    return listaDeHijos->primero;
}

//--------------------------------------------------------------------------------------
/*
	AgregarArista
	Parámetros: v1, v2 tipos vértices , p tipo peso
	Efecto: agrega una arista a de peso p entre los vértices v1 y v2
	Requiere: vértices v1,v2 válidos, peso p válido y que no exista una arista entre v1 y v2
	Modifica: grafo G

*/

//Agregar Arista Modulada para evitar duplicar codigo
void AgregarAristaModulada(NodoLH* v,NodoLH::SubLista::NodoSLH * nuevoS1){
    nuevoS1->siguienteSL= v->sublista->primeroSL; // el primero de la sublista.
    v->sublista->primeroSL=nuevoS1;
    v->sublista->primeroSL->etiqueta = (char)v->getEtiqueta();

}

//REQUIERE VERTICES VALIDOS
void Grafo::AgregarArista(NodoLH* v1,NodoLH* v2,int p){

    NodoLH::SubLista::NodoSLH * nuevoS1 = new NodoLH::SubLista::NodoSLH(v1,p);
    NodoLH::SubLista::NodoSLH * nuevoS2 = new NodoLH::SubLista::NodoSLH(v2,p);


    AgregarAristaModulada(v2,nuevoS1);
    AgregarAristaModulada(v1,nuevoS2);
    
}

//--------------------------------------------------------------------------------------
/*
	EliminarArista
	Parámetros: v1,v2 tipo vértices 
	Efecto: elimina la arista a entre los vértices v1 y v2 
	Requiere: arista a entre v1 y v2 existente 
	Modifica: grafo G
*/

void EliminarAristaModulado(NodoLH* v, NodoLH* v2){ 
    bool eliminado = false;
    NodoLH::SubLista::NodoSLH * control = v->sublista->primeroSL;

    if(control->siguienteSL == nullptr){
        v->sublista->primeroSL = nullptr;
        delete control;
        eliminado = true;
    }else{
        while(control->siguienteSL != nullptr && eliminado != true){            
            
            if(char(control->getEtiqueta()) == char(v2->getEtiqueta()) && eliminado != true){
                v->sublista->primeroSL = control->siguienteSL;
                delete control;
                eliminado = true;
            }
 
            if(control->siguienteSL != nullptr){
                if(char(control->siguienteSL->getEtiqueta()) == char(v2->getEtiqueta())  && control->siguienteSL->siguienteSL != nullptr && eliminado != true){
                    control->siguienteSL = control->siguienteSL->siguienteSL;
                    delete control;
                    eliminado = true;
                }
            }

            if(control->siguienteSL->siguienteSL == nullptr && eliminado!= true){

                if(char(control->siguienteSL->getEtiqueta()) == char(v2->getEtiqueta()) && eliminado != true){

                    delete control->siguienteSL;
                    control->siguienteSL = nullptr;
                    eliminado = true;
                }
                else{
                    control = control->siguienteSL;
                }
            }
            if(eliminado != true){
                control = control->siguienteSL;
            }
        }
    }

}

void Grafo::EliminarArista(NodoLH* v,NodoLH* v2){
    if(v!= nullptr && v2!=nullptr){
        EliminarAristaModulado(v,v2);
        EliminarAristaModulado(v2,v);
    }

}

   
//--------------------------------------------------------------------------------------

/*
	ModificarPeso
	Parámetros: v1,v2 tipo vértices, p tipo peso
	Efecto: modifica el peso p de la arista a entre v1 y v2
	Requiere: arista entre v1 y v2 existente, vértices v1,v2 válidos,peso p válido 
	Modifica: arista a

*/
void ModificarPesoModulado(NodoLH* v,NodoLH* v2, int peso){
    NodoLH::SubLista::NodoSLH * control = v->sublista->primeroSL;
    bool encontrado = false;
    while(control!= nullptr && encontrado != true){
        if (char(control->getEtiqueta()) == char(v2->getEtiqueta())){
            control->peso = peso;
            encontrado = true;
        }
        control = control->siguienteSL;
    }
}

void Grafo::ModificarPeso(NodoLH* v,NodoLH* v2, int peso){
        ModificarPesoModulado(v,v2,peso);
        ModificarPesoModulado(v2,v,peso);
}

//--------------------------------------------------------------------------------------

/*
	Peso?
	Parámetros:v1,v2 tipo vértices 
	Efecto: devuelve el peso p de la arista entre v1 y v2
	Requiere: vértices v1,v2 válidos, arista existente entre v1 y v2
	Modifica:nada 

*/
int Grafo::Peso(NodoLH* v,NodoLH*v2){
    NodoLH::SubLista::NodoSLH * control = v->sublista->primeroSL;
    bool encontrado = false;
    int pesoToReturn = 0;
    while(control!= nullptr && encontrado != true){
        if (char(control->getEtiqueta()) == char(v2->getEtiqueta())){            
            pesoToReturn = control->peso;
            encontrado = true;
        }
        control = control->siguienteSL;
    }
    return pesoToReturn;
}

//--------------------------------------------------------------------------------------
/*
	ExisteArista?
	Parámetros:v1,v2 tipo vértices 
	Efecto:devuelve verdadero o falso si existe la arista entre v1 y v2
	Requiere: vértices v1,v2 válidos 
	Modifica: nada

*/
bool Grafo::ExisteArista(NodoLH* v,NodoLH* v2){
    NodoLH::SubLista::NodoSLH * control = v->sublista->primeroSL;
    bool encontrado = false;
    while(control!= nullptr && encontrado != true){
        if (char(control->getEtiqueta()) == char(v2->getEtiqueta())){            
            encontrado = true;
        }
        control = control->siguienteSL;
    }
    return encontrado;
}

//--------------------------------------------------------------------------------------

/*
	SiguienteVértice?
	Parámetros: v tipo vértice
	Efecto:devuelve el siguiente vértice de v dentro del grafo G
	Requiere: grafo G inicializado, vértice v válido
	Modifica: nada

*/
NodoLH* Grafo::SiguienteVertice(NodoLH* v){
    NodoLH* control = v;
    if(control->siguiente == nullptr){
        return NULL;
    }else{
        return control->siguiente;
    }
}

//--------------------------------------------------------------------------------------

/*
	PrimerVérticeAdyacente?
	Parámetros:v tipo vértice 
	Efecto: devuelve el primer vértice adyacente del vértice v 
	Requiere: vértice v válido
	Modifica: nada

*/
NodoLH* Grafo::PrimerVerticeAdyacente(NodoLH* v){
    NodoLH* control = v;
    if(v->sublista->primeroSL != nullptr){
        return v->sublista->primeroSL->nodo;
    }else{
        return nullptr;
    }    
}

//--------------------------------------------------------------------------------------
/*
	SiguienteVérticeAdyacente?
	Parámetros: v1,v2 tipo vértices 
	Efecto:devuelve el siguiente vértice adyacente de v1, después de v2
	Requiere: vértices v1,v2 válidos 
	Modifica: nada 

*/

NodoLH* Grafo::SiguienteVerticeAdyacente(NodoLH* v,NodoLH* v2){
    NodoLH::SubLista::NodoSLH * control = v->sublista->primeroSL;
    NodoLH* nodeToReturn = nullptr;
    bool encontrado = false;
    while(control != nullptr && encontrado != true){
        if (char(control->getEtiqueta()) == char(v2->getEtiqueta())){            
            encontrado = true;
            if(control->siguienteSL != nullptr){
                nodeToReturn = control->siguienteSL->nodo;          
            }
        }
        control = control->siguienteSL;
    }

    if(encontrado == true){
        return nodeToReturn;
    }else{
        return nullptr;    
    }
    
}

//--------------------------------------------------------------------------------------

/*
	NumVértices?
	Parámetros:grafo G
	Efecto:devuelve la cantidad total de vértices del grafo G
	Requiere:grafo G inicializado 
	Modifica: nada

*/
int Grafo::NumVertices(){
    int numeroDeVertices = 0;
    if(listaDeHijos->primero == nullptr){
        numeroDeVertices = 0;
    }else{
        NodoLH * control= listaDeHijos->primero;
        
        while(control != nullptr){
            numeroDeVertices++;
            control=control->siguiente;
        }
    }
    

    return numeroDeVertices;
}

//--------------------------------------------------------------------------------------
/*
	NumVérticesAdyacentes?
	Parámetros: v tipo vértice
	Efecto: devuelve la cantidad de vértices adyacentes del vértice v
	Requiere: vértice v válido 
	Modifica:nada
*/
int Grafo::NumVerticesAdyacentes(NodoLH* v){
    int verticesAdyacentes = 0;
    NodoLH::SubLista::NodoSLH * control = v->sublista->primeroSL;
    while(control !=  nullptr){
            verticesAdyacentes++;
            control = control->siguienteSL;    
        }

    return verticesAdyacentes;
}

//--------------------------------------------------------------------------------------
/*
	NumAristas?
	Parámetros:grafo G
	Efecto:devuelve la cantidad total de aristas del grafo G
	Requiere: grafo G inicializado 
	Modifica: nada

*/
int Grafo::NumAristas(){
    int aristas = 0;
    
    if(listaDeHijos->primero == nullptr){
        aristas = 0;
    }else{
        NodoLH * control= listaDeHijos->primero;
        NodoLH::SubLista::NodoSLH * control2= control->sublista->primeroSL;
        while(control!=nullptr){
            
            while(control2 !=  nullptr){
                aristas++;
                control2 = control2->siguienteSL;    
            }

            control=control->siguiente;
            if(control == nullptr){
            }else
            control2 = control->sublista->primeroSL; 
            
        }
    }    
    return aristas/2;
}

//--------------------------------------------------------------------------------------

void Grafo::imprimirSublistas(){
    NodoLH * control= listaDeHijos->primero;
    NodoLH::SubLista::NodoSLH * control2= control->sublista->primeroSL;

    while(control!=nullptr){
        cout << " +" << char(control->getEtiqueta()) << " ";

        
        while(control2 !=  nullptr){
            cout << " *" << char(control2->getEtiqueta())<< "(" << control2->peso << ")";
            control2 = control2->siguienteSL;    
        }

        control=control->siguiente;
        cout << endl;
        if(control == nullptr){
        }else
        control2 = control->sublista->primeroSL; 
        
    }

cout << endl;
}

//--------------------------------------------------------------------------------------

void Grafo::imprimir(){
    NodoLH * control= listaDeHijos->primero;

    while(control!=nullptr){
        cout << char(control->getEtiqueta()) << "-";
        control=control->siguiente;
    }
}

//--------------------------------------------------------------------------------------

 NodoLH* Grafo::traductorNodo(char nodo){
    NodoLH * control= listaDeHijos->primero;
    NodoLH * nodeToReturn= nullptr;

    while(control != nullptr){
        if(char(control->getEtiqueta()) == nodo){
            nodeToReturn = control;
        }else{

        }
    control = control->siguiente;
    }

    return nodeToReturn;
}

//--------------------------------------------------------------------------------------

bool Grafo::EsAdyacente(NodoLH* v,NodoLH* v2){
    bool esAdyacente = false;
    NodoLH * control= v;
    NodoLH::SubLista::NodoSLH * control2= control->sublista->primeroSL;

        while(control2 !=  nullptr){
            if(char(control2->getEtiqueta()) == v2->getEtiqueta()){
                esAdyacente = true;
            }
            control2 = control2->siguienteSL;    
        }
           
    return esAdyacente;
}


//--------------------------------------------------------------------------------------

bool Grafo::EsVerticeNulo(NodoLH*v){
    if(v == nullptr){
        return true;
    }
    else{
        return false;
    }
}

//--------------------------------------------------------------------------------------

NodoLH* Grafo::getVerticeNulo(){
    NodoLH* verticeNulo;
    return verticeNulo;
}
//--------------------------------------------------------------------------------------

/*
int main(){

    Grafo grafo;
    grafo.Iniciar();
    
    //Pruebas realizadas a:
    //Iniciar, Vacio, AgregarVertice, 

    grafo.AgregarVertice('1');
    grafo.AgregarVertice('2');
    grafo.AgregarVertice('3');
    grafo.AgregarVertice('4');
    

    grafo.traductorNodo('4');
    //cout<< "\nEtiqueta: " << grafo.Etiqueta(grafo.listaDeHijos->primero->siguiente->siguiente->siguiente) << endl;
    grafo.imprimirSublistas();
    
    //grafo.EliminarVertice(grafo.traductorNodo('4'));
    //grafo.EliminarVertice(grafo.traductorNodo('3'));
    //grafo.EliminarVertice(grafo.traductorNodo('2'));
    //grafo.EliminarVertice(grafo.traductorNodo('1'));

    grafo.AgregarArista(grafo.traductorNodo('1'),grafo.traductorNodo('3'),10);
    grafo.AgregarArista(grafo.traductorNodo('1'),grafo.traductorNodo('2'),12);
    grafo.AgregarArista(grafo.traductorNodo('3'),grafo.traductorNodo('2'),15);
    grafo.AgregarArista(grafo.traductorNodo('4'),grafo.traductorNodo('2'),20);





    
    //grafo.EliminarArista(grafo.traductorNodo('2'),grafo.traductorNodo('4'));

    //grafo.AgregarArista(grafo.traductorNodo('2'),grafo.traductorNodo('4'),18);

    grafo.imprimirSublistas();
    grafo.EliminarArista(grafo.traductorNodo('4'),grafo.traductorNodo('2'));
    grafo.EliminarArista(grafo.traductorNodo('2'),grafo.traductorNodo('4'));

    cout << grafo.NumVerticesAdyacentes(grafo.traductorNodo('4')) << endl;

    //grafo.ModificarEtiqueta(grafo.traductorNodo('2'),'A');
    //cout << "Primer vertice es: " << char(grafo.PrimerVertice()->getEtiqueta()) << endl;
    
    //grafo.ModificarPeso(grafo.traductorNodo('4'),grafo.traductorNodo('2'),20);
    grafo.imprimirSublistas();
    cout << "Siguiente vertice: " << char(grafo.SiguienteVertice(grafo.traductorNodo('2'))->getEtiqueta()) << endl;
    //cout << "Siguiente vertice adyacente: " << char(grafo.SiguienteVerticeAdyacente(grafo.traductorNodo('2'),grafo.traductorNodo('1'))->getEtiqueta()) << endl;
   
    cout << "Etiqueta: " << grafo.Etiqueta(grafo.traductorNodo('4')) << endl;


    cout << "Es adyacente: " << grafo.EsAdyacente(grafo.traductorNodo('4'),grafo.traductorNodo('1')) << endl;
    //cout << "Esta vacio?: " << grafo.Vacio() << endl;


    



    //grafo.AgregarArista(grafo.listaDeHijos->primero, grafo.listaDeHijos->primero->siguiente,7);
    //grafo.AgregarArista(grafo.listaDeHijos->primero->siguiente, grafo.listaDeHijos->primero->siguiente->siguiente,9);
    //grafo.AgregarArista(grafo.listaDeHijos->primero->siguiente, grafo.listaDeHijos->primero->siguiente->siguiente->siguiente,10);
    //grafo.EliminarVertice(grafo.listaDeHijos->primero->siguiente->siguiente->siguiente->siguiente);


    
    //grafo.ModificarEtiqueta(grafo.listaDeHijos->primero,'9');
    // 1 -> 2(7)
    // 2 -> 1(7) -> 3(9)-> 4(10)
    // 3 -> 2(9)
    // 4 -> 2(10)
    //grafo.imprimirSublistas();
    //Agregando una arista entre el vertice '1' y el vertice '2'
    //cout << "\n Etiqueta deseada: " << char(grafo.listaDeHijos->primero->siguiente->sublista->primeroSL->getEtiqueta())<<endl;
    
    //grafo.EliminarVertice(grafo.listaDeHijos->primero);
    
    //grafo.EliminarArista(grafo.listaDeHijos->primero->siguiente, grafo.listaDeHijos->primero->siguiente->siguiente->siguiente);
    // 1 -> 2(7)
    // 2 -> 1(7) ->  4(10)
    // 3 -> 
    // 4 -> 2(10)
    //grafo.ModificarPeso(grafo.listaDeHijos->primero->siguiente, grafo.listaDeHijos->primero->siguiente->siguiente->siguiente,80);
    //cout << "Peso: " << grafo.Peso(grafo.listaDeHijos->primero->siguiente,grafo.listaDeHijos->primero) << endl;
    //cout << "Existe Arista: " << grafo.ExisteArista(grafo.listaDeHijos->primero->siguiente->siguiente,grafo.listaDeHijos->primero) << endl;
    //cout << "Primer Vertice: " << char(grafo.PrimerVertice()->getEtiqueta()) << endl;
    //grafo.SiguienteVertice(grafo.listaDeHijos->primero->siguiente->siguiente->siguiente);
    //cout << "Primer Vertice Adyacente: " << char(grafo.PrimerVerticeAdyacente(grafo.listaDeHijos->primero->siguiente->siguiente)->getEtiqueta()) << endl;
    //cout << "Siguiente Vertice Adyacente: " << char(grafo.SiguienteVerticeAdyacente(grafo.listaDeHijos->primero->siguiente->siguiente,grafo.listaDeHijos->primero->siguiente)->getEtiqueta()) << endl;
    //cout << "Numero de vertices: " << grafo.NumVertices() <<endl;
    //cout << "Numero de vertices adyacentes: " << grafo.NumVerticesAdyacentes(grafo.listaDeHijos->primero->siguiente->siguiente->siguiente->siguiente) <<endl;
    //cout << "Numero de aristas: " << grafo.NumAristas() <<endl;

    //grafo.imprimirSublistas();

    //cout << "Primero: " << char(grafo.listaDeHijos->primero->sublista->primeroSL->siguienteSL->getEtiqueta()) << endl;
    //grafo.imprimir();


    
    //cout << "\n Peso: " << grafo.listaDeHijos->primero->siguiente->sublista->primeroSL->siguienteSL->peso<<endl;
    //cout << "\n Peso: " << grafo.listaDeHijos->primero->sublista->primeroSL->peso<<endl;
    //cout << "\n Peso: " << grafo.listaDeHijos->primero->siguiente->sublista->primeroSL->peso<<endl;
    //cout << "\n Peso: " << grafo.listaDeHijos->primero->siguiente->siguiente->sublista->primeroSL->peso<<endl;

    //cout << "\n Etiqueta del vertice con el que esta enlazado: " << char(grafo.listaDeHijos->primero->sublista->primeroSL->getEtiqueta())<<endl << " con peso: " << grafo.listaDeHijos->primero->sublista->primeroSL->peso;
    //cout << "\n Peso: " << grafo.listaDeHijos->primero->siguiente->siguiente->sublista->primeroSL->peso<<endl;
    //ESTA HACIENDO LO MISMO DE GUARDAR COMO EN ORDEN INVERSO, CORREGIR TAL ERROR
    //cout << 
    //grafo.EliminarVertice(grafo.listaDeHijos->primero->siguiente->siguiente);
    



    //cout << "Vacio: " << grafo.Vacio() << endl;
    cout<< endl;
    //grafo.imprimir();

    cout << "\nFINAL" << endl;

    return 0;
}
*/
