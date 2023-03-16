#include <iostream>
#include <string>
#include <stdlib.h>
//-------------------------
//Estructuras
#include "GrafoLSE-LSE.h"
//#include "Grafo.h"
//-------------------------
#include "diccionario.h"
#include "apo.h"
#include "vlister.h"
#include "conjunto.h"
#include <list>
#include "NodoLH.h"
#include <queue>
using namespace std;
#define maximo 999999999

//-----------------------------------------------------------------------

/*

Nombre: Recorrido en Ancho Primero para averiguar si el grafo tiene ciclos
Parametros: G (tipo grafo), v (tipo vértice)
Efecto: Devuelve verdadero si el grafo tiene ciclos o falso si no tiene ciclos
Requiere: Grafo inicializado 
Modifica: N/A

*/

template<class T,class K>
int TieneCiclos(T v, K &Grafo){
    bool ciclos = false;
    T vertice  = Grafo.PrimerVertice();
    Diccionario<T> D; 
    queue<T> C; 
    D.Iniciar();
    int peso = 0;
    T vAux = NULL;
    int continuar = 0;

    while (!Grafo.EsVerticeNulo(vertice)) {
        if(!D.Pertenece(vertice)) {
            C.push(vertice); 
            D.Agregar(vertice); 
            while (!C.empty()) {
                T v2 = C.front(); 
                    T verticePrueba = Grafo.PrimerVerticeAdyacente(v2);
                    while(!Grafo.EsVerticeNulo(verticePrueba)){
                        peso += Grafo.Peso(v2,verticePrueba);
                        verticePrueba = Grafo.SiguienteVerticeAdyacente(v2,verticePrueba);

                    }
                C.pop();
                T v_ady = Grafo.PrimerVerticeAdyacente(v2);
                while (!Grafo.EsVerticeNulo(v_ady)) {
                    if (!D.Pertenece(v_ady)){
                        C.push(v_ady); 
                        D.Agregar(v_ady); 
                    }else{
                    	if(vAux != v_ady && continuar == 1){
	                   	 		ciclos = true;
	                   	 	
                   	 	}else{
                   	 		continuar = 1;
                   	 	}
                    }
                v_ady = Grafo.SiguienteVerticeAdyacente(v2,v_ady);
                }
                vAux = v2;
                continuar = 0;
            }
        }

    vertice = Grafo.SiguienteVertice(vertice);
    }

    cout << " \nTiene ciclos: " << ciclos << endl;
    return ciclos;
}


//---------------------------------------------------------------------------------------------------

/*

Nombre: Calcular la suma total de los pesos de todas las aristas
Parametros: G(tipo grafo), v(tipo vértice)
Efecto: Suma todos los pesos de las aristas del grafo G
Requiere: Grafo inicializado 
Modifica: N/A

*/

template<class T,class K>
int CalcularPesos(T v, K &Grafo){
	T vertice  = Grafo.PrimerVertice();
	Diccionario<T> D; 
	queue<T> C; 
	D.Iniciar();
	int peso = 0;
	  
	while (!Grafo.EsVerticeNulo(vertice)){
		if(!D.Pertenece(vertice)) {
			C.push(vertice); 
			D.Agregar(vertice); 

			while (!C.empty()) {
				T v2 = C.front(); 
					T verticePrueba = Grafo.PrimerVerticeAdyacente(v2);
					while(!Grafo.EsVerticeNulo(verticePrueba)){
						peso += Grafo.Peso(v2,verticePrueba);
						verticePrueba = Grafo.SiguienteVerticeAdyacente(v2,verticePrueba);
						
					}
				C.pop();
				T v_ady = Grafo.PrimerVerticeAdyacente(v2);
				while (!Grafo.EsVerticeNulo(v_ady)) {
					if (!D.Pertenece(v_ady)) {
						C.push(v_ady); 
						D.Agregar(v_ady); 
					}
				v_ady = Grafo.SiguienteVerticeAdyacente(v2,v_ady);	
				}		
			}
		}

		vertice = Grafo.SiguienteVertice(vertice);
	}	

	cout << "Peso: " << peso/2 << endl;
	return peso/2;
}

//---------------------------------------------------------------------------------------------------

/*

Nombre: Traducir nodo
Parametros: G(tipo grafo), v(tipo vértice), nodo(tipo char, es decir es una etiqueta)
Efecto: Devuelve el vertice que tiene la etiqueta solicitada
Requiere: Grafo inicializado 
Modifica: N/A

*/

template<class T,class K>
T TraductorNodo(T v,char nodo, K &Grafo){
    T control= Grafo.PrimerVertice();
    T nodeToReturn= NULL;

    while(!Grafo.EsVerticeNulo(control)){
        if(Grafo.Etiqueta(control) == nodo){
            nodeToReturn = control;
        }else{

        }
    control = Grafo.SiguienteVertice(control);
    }

    return nodeToReturn;
}

//---------------------------------------------------------------------------------------------------

/*

Nombre: Aislar un vértice
Parametros: G (tipo grafo), v (tipo vertice
Efecto: Aísla el nodo n eliminando todas sus aristas
Requiere: Grafo inicializado 
Modifica: Modifica al grafo G 

*/

template<class T,class K>
void AislarVertice(K &Grafo, T vertice) {
	T v_ady = Grafo.PrimerVerticeAdyacente(vertice); 
	while (!Grafo.EsVerticeNulo(v_ady)) {
		//cout << " Vertice: " << Grafo.Etiqueta(vertice) << " Vertice adyacente: " << Grafo.Etiqueta(v_ady) << endl; 
		Grafo.EliminarArista(vertice, v_ady);
		 
		if(Grafo.SiguienteVerticeAdyacente(vertice, v_ady) == NULL){
			v_ady = Grafo.PrimerVerticeAdyacente(vertice);
		}else{
			v_ady = Grafo.SiguienteVerticeAdyacente(vertice, v_ady); 
		}
	} 	
}

//---------------------------------------------------------------------------------------------------

/*

Nombre: Profundidad primero
Parametros: G (tipo grafo)
Efecto: Recorre el grafo imprimiendo el recorrido en profundida primero
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void profundidadPrimero(K &grafo, T ver){
    if (!grafo.Vacio()){
        Diccionario<T> diccionario; 
        diccionario.Iniciar();
        T v = grafo.PrimerVertice(); 
        while (!grafo.EsVerticeNulo(v)) {
            if (!diccionario.Pertenece(v)) {
                profundidadPrimeroR(grafo, v, diccionario); 
            }
            v = grafo.SiguienteVertice(v); 
        }
        diccionario.Destruir(); 
    }
    else {
        cout << "el grafo esta vacio " << endl; 
    }
}

template<class T,class K>
void profundidadPrimeroR(K &grafo, T ver, Diccionario<T> &diccionario) {
    diccionario.Agregar(ver); 
    cout << grafo.Etiqueta(ver) << endl; 
    T v_ady = grafo.PrimerVerticeAdyacente(ver); 
    while (!grafo.EsVerticeNulo(v_ady)) {
        if (!diccionario.Pertenece(v_ady)) {
            profundidadPrimeroR(grafo, v_ady, diccionario); 
        }
        v_ady = grafo.SiguienteVerticeAdyacente(ver, v_ady);
    }
}


//---------------------------------------------------------------------------------------

/*

Nombre: Recorrido en Profundidad Primero para averiguar si un grafo es conexo
Parametros: G (tipo grafo)
Efecto: Devuelve verdadero si el grafo es conexo o falso si no es conexo
Requiere: Grafo inicializado 
Modifica: N/A 

*/

template<class T, class K>
bool profundidadPrimeroConexo(K &grafo, T ver){
    bool conexo=true;
    if (!grafo.Vacio()){
        Diccionario<T> diccionario; 
        diccionario.Iniciar();
        int contador=0;

        T v = grafo.PrimerVertice(); 
        while (!grafo.EsVerticeNulo(v)) {
            if (!diccionario.Pertenece(v)) {
                if(v!=grafo.PrimerVertice()){
                    conexo=false;
                }
                profundidadPrimeroRConexo(grafo, v, diccionario); 
            }
            v = grafo.SiguienteVertice(v); 
        }
        diccionario.Destruir(); 
    }
    else {
        cout << "El grafo esta vacio " << endl; 
    }
    cout<<"Conexo"<<conexo<<endl;

    return conexo;
}

template<class T,class K>
void profundidadPrimeroRConexo(K &grafo, T ver, Diccionario<T> &diccionario) {
    diccionario.Agregar(ver);
    T v_ady = grafo.PrimerVerticeAdyacente(ver); 
    while (!grafo.EsVerticeNulo(v_ady)) {
        if (!diccionario.Pertenece(v_ady)) {
            profundidadPrimeroRConexo(grafo, v_ady, diccionario); 
        }
        v_ady = grafo.SiguienteVerticeAdyacente(ver, v_ady);
    }
}

//---------------------------------------------------------------------------------------

/*

Nombre: Prim
Parametros: G(tipo grafo), v (tipo vertice)
Efecto: Encuentra el árbol recubridor mínimo en un grafo conexo
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void Prim(K &grafo, T ver) {           
    Diccionario<T> diccionario;
    diccionario.Iniciar();
    diccionario.Agregar(ver); 
    T v; 
    T v_ady; 
    int minimo;
    T v_origen;
    T v_minimo;
    cout << "Aristas seleccionadas : " << endl;
    while (diccionario.numElem() < grafo.NumVertices()) {
        v = grafo.PrimerVertice(); 
        minimo = maximo; 
        while (!grafo.EsVerticeNulo(v)) {
            if (diccionario.Pertenece(v)) {
                v_ady = grafo.PrimerVerticeAdyacente(v); 
                while (!grafo.EsVerticeNulo(v_ady)) {
                    if (!diccionario.Pertenece(v_ady)) {
                        if (grafo.Peso(v, v_ady) < minimo){
                            minimo = grafo.Peso(v, v_ady); 
                            v_origen = v; 
                            v_minimo = v_ady; 
                        }
                    }
                    v_ady = grafo.SiguienteVerticeAdyacente(v, v_ady);
                }
            }
            v = grafo.SiguienteVertice(v); 
        }
        diccionario.Agregar(v_minimo);
        cout << "Vertice origen : " << grafo.Etiqueta(v_origen) << " Vertice destino : " << grafo.Etiqueta(v_minimo) << " Peso : " << minimo << endl;
    }
}

//---------------------------------------------------------------------------------------
/*

Nombre: Kruskal
Parametros: G(tipo grafo), v (tipo vertice)
Efecto: Encuentra el árbol recubridor mínimo en un grafo conexo
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void Kruskal(K &grafo, T vertice) {
    Conjunto<T> conjunto; APO<T> apo;
    conjunto.Inicializar(grafo.NumVertices());
    apo.Iniciar();  
    T v = grafo.PrimerVertice(); 
    int num_set = 0; 
    while (!grafo.EsVerticeNulo(v)) {
        conjunto.AnadirConjunto(num_set);
        conjunto.AgregarAConjunto(v, num_set);
        
        T v_ady = grafo.PrimerVerticeAdyacente(v);
        while (!grafo.EsVerticeNulo(v_ady)) {
            apo.Insertar(v,v_ady, grafo.Peso(v, v_ady));
            v_ady = grafo.SiguienteVerticeAdyacente(v,v_ady);     
        }
            
        ++num_set;
        v = grafo.SiguienteVertice(v); 
        
}


    int aristas_escogidas = 0; 
    std::cout << "Aristas seleccionadas : " << std::endl; 
    while (aristas_escogidas < grafo.NumVertices()-1) {
        arista_t<T>* arista = apo.Popear(); 
            if (arista != NULL) { 
            int CA = conjunto.Pertenece(arista->vertice_origen);
            int CB = conjunto.Pertenece(arista->vertice_destino); 
            if (CA != CB) {
                ++aristas_escogidas; 
                conjunto.Union(CA, CB);
                cout << "Vertice origen : " << grafo.Etiqueta(arista->vertice_origen) << " Vertice destino : " << grafo.Etiqueta(arista->vertice_destino) << " Peso : " << arista->peso << std::endl; 
            }
            else {
            } 
        }
        else {
            cout << "Invalid" << std::endl; 
        }
    } 
}

//---------------------------------------------------------------------------------------

/*

Nombre: Dijkstra
Parametros: 
G(tipo grafo), v (tipo vertice),pesos* tipo vector de ints,vertices* tipo vector de int
Efecto: devuelve el camino más corto a un vértice hacia todos los demás vértices del grafo.
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void Dijkstra(K &grafo, T ver, int*pesos, T*verticesPrecedesores){     
    VL<T> vl; 
    Diccionario<T> D;
    D.Iniciar(); 
    vl.Iniciar(); 
    T v = grafo.PrimerVertice();
    int numV = 0;  
    cout << "Orden de vertices analizados: ";
    while (!(grafo.EsVerticeNulo(v))) { 
            if (v != ver){
            vl.Agregar(v,numV++);
            if (grafo.ExisteArista(ver, v)) {
                pesos[vl.Indice(v)] = grafo.Peso(ver, v); 
            }
            else {
                pesos[vl.Indice(v)] = maximo;
            }
            verticesPrecedesores[vl.Indice(v)] = ver; 
        }
        if(grafo.Etiqueta(v) != grafo.Etiqueta(ver)){
            cout << "Vertice: " << grafo.Etiqueta(v) << " ";
        }

        v = grafo.SiguienteVertice(v);
    } 
    
    D.Agregar(ver); 
    int menor; int contador; int peso_menor; 
    while (D.numElem() < grafo.NumVertices()) {
        menor = -1; peso_menor = maximo; contador = 0; 
        while (contador < grafo.NumVertices()-1) { 
            if (pesos[contador] <= peso_menor && !D.Pertenece(vl.Vertice(contador))) {
                menor = contador;
                peso_menor = pesos[contador]; 
            }
            contador++; 
        }
        T v = vl.Vertice(menor);
        D.Agregar(v);
        T v_ady = grafo.PrimerVerticeAdyacente(v); 
        while (!(grafo.EsVerticeNulo(v_ady))) {
            if (v_ady != ver){   
                if (pesos[vl.Indice(v_ady)] > grafo.Peso(v,v_ady) + pesos[vl.Indice(v)]) {
                    pesos[vl.Indice(v_ady)] = grafo.Peso(v,v_ady) + pesos[vl.Indice(v)]; 
                    verticesPrecedesores[vl.Indice(v_ady)] = v;
                }       
            }
            v_ady = grafo.SiguienteVerticeAdyacente(v,v_ady);     
        }   
    }
    cout << endl;
    D.Destruir(); 
    vl.Destruir();
}

//---------------------------------------------------------------------------------------

/*

Nombre: Circuito de Hamilton de Menor Costo mediante una búsqueda exhaustiva pura 
Parametros: Etiqueta (tipo elemento), G (tipo grafo) 
G(tipo grafo), v (tipo vertice),pesos* tipo vector de ints,vertices* tipo vector de int
Efecto: Crea una sucesión de aristas adyacentes sin repetir aristas,ni repetir vértices
Requiere: Grafo inicializado 
Modifica: NA 

*/
template<class T, class K>
void CircuitoHamilton(K&grafo, Diccionario<T>&D, T* Sol, T* mejor_Sol, int&costo, int&mejor_costo, int&contador_soluciones,  int indice) {
    D.Agregar(Sol[indice-1]); 
    T v_ady = grafo.PrimerVerticeAdyacente(Sol[indice-1]); 
    while (!grafo.EsVerticeNulo(v_ady)) {
        if (!D.Pertenece(v_ady)) {
            costo+= grafo.Peso(Sol[indice-1], v_ady); 
            Sol[indice] = v_ady; 
            if (indice == grafo.NumVertices()-1) {
                if (grafo.ExisteArista(v_ady, Sol[0])) {
                    ++contador_soluciones; 
                    costo+=  grafo.Peso(v_ady, Sol[0]); 
                    if (costo < mejor_costo) {
                        mejor_costo = costo; 
                        cout << "Solucion factible encontrada" << std::endl; 
                        for (int i = 0; i < grafo.NumVertices(); ++i) {
                            mejor_Sol[i] = Sol[i]; 
                        }
                        costo-= grafo.Peso(v_ady, Sol[0]); 
                    }
                }
                else {
                    CircuitoHamilton(grafo, D, Sol, mejor_Sol, costo, mejor_costo, contador_soluciones, indice); 
                    D.pop(); 
                }
                costo-= grafo.Peso(Sol[indice-1], v_ady); 
            } 
        } 
        v_ady = grafo.SiguienteVerticeAdyacente(Sol[indice-1], v_ady); 
    }
}





//------------------------------------------------------------------------------------------

/*

Nombre: Floyd
Parametros: G(tipo grafo),  matriz de pesos* tipo vector de ints, intermediate vertices* tipo vector de int
Efecto: Encuentra el camino más corto entre todo par de vértices 
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void Floyd(K &grafo, int** MatrizPesos, char** IntermediateVertices, T ver) {
    VL<T> vl; 
    vl.Iniciar(); 
    T v = grafo.PrimerVertice(); int contador_vertice = 0; 
    while (!grafo.EsVerticeNulo(v)) {
        vl.Agregar(v, contador_vertice++); 
        v = grafo.SiguienteVertice(v); 
    }

    for (int i_x = 0; i_x < grafo.NumVertices(); ++i_x) {
        T v_x = vl.Vertice(i_x); 
        for (int i_y = 0; i_y < grafo.NumVertices(); ++i_y) {
            T v_y = vl.Vertice(i_y); 
            if (v_x != v_y) {
                if (grafo.ExisteArista(v_x, v_y)) {
                    MatrizPesos[i_x][i_y] = grafo.Peso(v_x, v_y);
                    IntermediateVertices[i_x][i_y] = '-';        
                }
                else {
                    MatrizPesos[i_x][i_y] = maximo; 
                    IntermediateVertices[i_x][i_y] = '-'; 
                }       
                
            }
            else {
                MatrizPesos[i_x][i_y] = 0; 
                IntermediateVertices[i_x][i_y] = '-'; 
            }       
        }   
    } 

    T vertice_pivote = grafo.PrimerVertice();
    for (int pivote = 0; pivote < grafo.NumVertices(); ++pivote) { 
        for (int origen = 0; origen < grafo.NumVertices(); ++origen) {
            for (int destino = 0; destino < grafo.NumVertices(); ++destino) {
                if (MatrizPesos[origen][destino] > MatrizPesos[origen][pivote] + MatrizPesos[pivote][destino]) {
                    MatrizPesos[origen][destino] = MatrizPesos[origen][pivote] + MatrizPesos[pivote][destino]; 
                    IntermediateVertices[origen][destino] = grafo.Etiqueta(vertice_pivote); 
                }
            }       
        }
        vertice_pivote = grafo.SiguienteVertice(vertice_pivote); 
    }
} 
//---------------------------------------------------------------------------------------

/*

Nombre: Colorear un grafo, usando la menor cantidad de colores posible, mediante una búsqueda exhaustiva pura
Parametros: G(tipo grafo)
Efecto: Asignarle una etiqueta  color a cada vértice del grafo, con la mínima cantidad de colores posible 
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void colorear_grafo(K&grafo, Conjunto<T>&mejor_sol, int&colores, int&menor_cantidad, int&contador_soluciones, bool&found) {
    if (!grafo.Vacio()){
        Conjunto<T> CA; 
        CA.Inicializar(grafo.NumVertices()); 
        Conjunto<T> CB; 
        CB.Inicializar(grafo.NumVertices());
        VL<T> vl;
        vl.Iniciar(); 
        
        int conjuntoX = 0; 
        
        while (conjuntoX < grafo.NumVertices()) {
            CA.AnadirConjunto(conjuntoX);
            CB.AnadirConjunto(conjuntoX); 
            ++conjuntoX;  
        }
        
        T v = grafo.PrimerVertice(); 
        
        int i_v = 0; 
        
        while (!grafo.EsVerticeNulo(v)) {
            vl.Agregar(v, i_v);
            T v_ady = grafo.PrimerVerticeAdyacente(v); 
            while (!grafo.EsVerticeNulo(v_ady)) {
                CB.AgregarAConjunto(v_ady, i_v); 
                v_ady = grafo.SiguienteVerticeAdyacente(v,v_ady); 
            }
            v = grafo.SiguienteVertice(v); 
            ++i_v; 
            
        }
        v = grafo.PrimerVertice(); 
        colorear(grafo, mejor_sol,  CA, CB, v, colores, menor_cantidad, contador_soluciones, vl, found); 
        
    } 
}

template<class T, class K>
void colorear(K&grafo, Conjunto<T>&mejor_sol, Conjunto<T>&CA, Conjunto<T>&CB, T v, int&colores, int&menor_cantidad, int&contador_soluciones, VL<T>&vl, bool&found){

    if (grafo.EsVerticeNulo(v)) {
        ++contador_soluciones; 
        if (colores < menor_cantidad) {
            menor_cantidad = colores;
            found = true; 
            CA.transferirElementos(mejor_sol);
        }
    }
    
    int i = 0; 
    while (i < grafo.NumVertices() && colores < menor_cantidad) {
        int conjunto_c = CA.getConjunto(i); 
        int conjunto_a = CB.getConjunto(vl.Indice(v));
        if (!CA.Interseccion(conjunto_c, CB, conjunto_a)) {
            CA.AgregarAConjunto(v, i); 
            bool new_color = false; 
            if (i >=menor_cantidad) {
                ++colores; 
                new_color = true; 
            }
            colorear(grafo, mejor_sol, CA, CB, grafo.SiguienteVertice(v), colores, menor_cantidad, contador_soluciones, vl, found);
            CA.PopElement(i, v);
            if (new_color) {
                --colores; new_color = false; 
            }   
        } 
        ++i;  
    }       
}



//------------------------------------------------------------------------------------------

/*

Nombre: Averiguar si un grafo es conexo usando un algoritmo basado en Warshall
Parametros: G(tipo grafo), v (tipo vertice)
Efecto: devuelve verdadero si el grafo es conexo o falso si no es conexo
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T, class K>
void WarshallConexo(K&grafo,T ver){
    int cantidadVertices = grafo.NumVertices();
    int MatrizAdyacencia[cantidadVertices][cantidadVertices];
    T vAux = grafo.PrimerVertice();
    T vAux2;

    for(int i = 0; i < cantidadVertices; i++){
        vAux2 = grafo.PrimerVertice();
        for(int j = 0; j < cantidadVertices; j++){
            if(i == j){
                MatrizAdyacencia[i][j] = 0;
            }else{
                if(grafo.ExisteArista(vAux,vAux2)){
                    MatrizAdyacencia[i][j] = 1;
                }else{
                    MatrizAdyacencia[i][j] = 0;
                }
            }
            vAux2 = grafo.SiguienteVertice(vAux2);
        }
    vAux = grafo.SiguienteVertice(vAux);
    }

    cout << "Matiz de adyacencia generada: " << endl;
    for(int i = 0; i < cantidadVertices; i++){
        for(int j = 0; j< cantidadVertices; j++){
            cout << " " << MatrizAdyacencia[i][j];
        }
        cout << endl;
    }

    for(int k = 0; k < cantidadVertices; k++){
        for(int i = 0; i < cantidadVertices; i++){
            for(int j = 0; j< cantidadVertices; j++){
                if(MatrizAdyacencia[i][j] == 0){
                    MatrizAdyacencia[i][j] = MatrizAdyacencia[i][k] & MatrizAdyacencia[k][j];
                }
            }
        } 
    }

    bool conexo = true;
    for(int i = 0; i < cantidadVertices; i++){
        for(int j = 0; j< cantidadVertices; j++){
           if(MatrizAdyacencia[i][j]!= 1 && i!=j){
                conexo = false;
           } 
        }
        
    }

    cout << "\nConexo: " << conexo << endl;


}

//------------------------------------------------------------------------------------------

/*

Nombre: Recorrido en Profundidad Primero para averiguar si el grafo tiene ciclos
Parametros: G(tipo grafo), v (tipo vertice)
Efecto: devuelve verdadero si el grafo tiene ciclos o falso si no tiene ciclos
Requiere: Grafo inicializado 
Modifica: NA 

*/

template<class T>
bool EncontradoEnBusqueda(std::list<T>&L, T ver) {
    bool is_there = false; 
    typename list<T>::iterator current_element;
    current_element = L.begin();  
    for (int iteration = 0; iteration < L.size(); ++iteration) {
        if (*current_element == ver) {
            is_there = true; 
            iteration = L.size(); 
        }
        ++current_element; 
    }
    return is_there;    
}

template<class T, class K>
bool ProfundidadPrimeroCiclos(K&grafo, T ver) {
    ver = grafo.PrimerVertice();
    bool is_there = false; 
     if (!grafo.Vacio()) {
         T v = grafo.PrimerVertice();
         Diccionario<T> D; 
        list<T> L; 
        D.Iniciar();  
        while (!grafo.EsVerticeNulo(v) && !is_there) {
            if (!D.Pertenece(v)) {
                ProfundidadPrimeroCiclosR(grafo, v, grafo.getVerticeNulo(),  D, L, is_there); 
            } 
            v = grafo.SiguienteVertice(v);  
        }   
    }
    return is_there;    
}

template<class T, class K>
void ImprimirVec(std::list <T>&g, T vec, K &grafo){ 
    vec = grafo.PrimerVertice();
    typename list <T> :: iterator it; 
} 

template<class T, class K> 
void ProfundidadPrimeroCiclosR(K&grafo, T ver, T vertice_anterior,  Diccionario<T>&D, list<T>&L, bool&is_there) {
    D.Agregar(ver);
    L.push_back(ver); 
    T v_ady = grafo.PrimerVerticeAdyacente(ver);
    while (!grafo.EsVerticeNulo(v_ady) && !is_there) {
        if (!D.Pertenece(v_ady)) {
            ProfundidadPrimeroCiclosR(grafo, v_ady, ver, D, L, is_there);
            L.pop_back();  
        }
        else {
            if (v_ady != vertice_anterior) { 
                is_there = EncontradoEnBusqueda(L, v_ady); 
            }
            if (is_there) {
                ImprimirVec(L,grafo.PrimerVertice(), grafo);   
            }
        }
        v_ady = grafo.SiguienteVerticeAdyacente(ver, v_ady);  
    }   
}


//------------------------------------------------------------------------------------------

template<class K, class T>
void menu(T vertice, K &grafo,char elemento, char elemento2, int peso){
    int opcion;
    
    do {
        system("cls"); // Para limpiar la pantalla
        
        // Texto del menú que se verá cada vez
        
        cout << "\nMenu de Opciones" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 1. IniciarGrafo" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 2. DestruirGrafo" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 3. VaciarGrafo" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 4. PreguntarVacio" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 5. AgregarVertice" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 6. EliminarVertice" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 7. ModificarEtiqueta" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 8. PrimerVertice" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 9. AgregarArista" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "10. EliminarArista" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "11. ModificarPeso" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "12. Peso" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "13. ExisteArista" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "14. SiguienteVertice" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "15. PrimerVerticeAdyacente" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "16. SiguienteVerticeAdyacente" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "17. NumVertices" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "18. NumVerticesAdyacentes" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "19. NumAristas" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "20. Etiqueta" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "21. EsAdyacente" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "22. EsVerticeNulo" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "23. Menu de Algoritmos" << endl;
        cout << "-------------------------------------"<<endl;
        
        cout << "0. SALIR" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            
            //------------------------------------------------------------
            case 1:
                grafo.Iniciar();

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            case 2:             
                grafo.Destruir();
                grafo.~Grafo();


                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------  
            case 3:           
                grafo.Vaciar();

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa            
                break;
            //------------------------------------------------------------   
            case 4:
                if(grafo.Vacio() == 1){
                    cout << "Grafo se encuentra vacio" << endl;
                }else{
                    cout << "Grafo no vacio" << endl;
                }

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 5: 
                cout<< "Digite el vertice a agregar: " << endl;
                cin >> elemento;
                grafo.AgregarVertice(elemento);            
                

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 6:
                cout<< "Digite que vertice desea borrar:" << endl;
                cin >> elemento;
                
                grafo.EliminarVertice(grafo.traductorNodo(elemento));                               

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 7:
                char newEtiqueta;
                cout<< "Digite a que vertice desea cambiarle la etiqueta:" << endl;
                cin >> elemento;
                cout<< "Digite que elemento desea agregar:" << endl;
                cin >> newEtiqueta;

                grafo.ModificarEtiqueta(grafo.traductorNodo(elemento),newEtiqueta);
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                          
                break;
            //------------------------------------------------------------
            case 8:
                cout<< "Primer Vertice:" << endl;
                             
                cout << grafo.Etiqueta(grafo.PrimerVertice()) << endl;

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                 
                break;
            //------------------------------------------------------------
            case 9:
                //cout << "Agregando Arista" << endl; 
                cout<< "Digite vertice origen:" << endl;
                cin >> elemento;
                cout<< "Digite vertice destino:" << endl;
                cin >> elemento2;
                cout<< "Digite el peso:" << endl;
                cin >> peso;
                
                
                grafo.AgregarArista(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2),peso);
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            
            case 10: 
                cout<< "Digite vertice primero:" << endl;
                cin >> elemento;
                cout<< "Digite vertice segundo:" << endl;
                cin >> elemento2;
                grafo.EliminarArista(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2));
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa               
                break;
            //------------------------------------------------------------
            
            case 11:
                cout<< "Digite vertice primero:" << endl;
                cin >> elemento;
                cout<< "Digite vertice segundo:" << endl;
                cin >> elemento2;
                cout<< "Digite nuevo peso:" << endl;
                cin >> peso;
                grafo.ModificarPeso(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2), peso);
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa               
                break;
            //------------------------------------------------------------                
            
            case 12:
                cout<< "Digite vertice primero:" << endl;
                cin >> elemento;
                cout<< "Digite vertice segundo:" << endl;
                cin >> elemento2;
                cout<< "Peso: ";
                cout << grafo.Peso(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2)) << endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                 
                break;
            //------------------------------------------------------------
           
            case 13:
                cout<< "Digite vertice primero:" << endl;
                cin >> elemento;
                cout<< "Digite vertice segundo:" << endl;
                cin >> elemento2;
                cout << "Existe Arista: ";
                cout<<grafo.ExisteArista(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2))<<endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                                 
                break;
            //------------------------------------------------------------
            
            case 14:
                cout<< "Digite el vertice:" << endl;
                cin >> elemento;
                cout<< "Vertice siguiente es: ";
                if(grafo.SiguienteVertice(grafo.traductorNodo(elemento)) == NULL){
                	cout << "No existe siguiente vertice" << endl;
                }else{
                	cout<< grafo.Etiqueta(grafo.SiguienteVertice(grafo.traductorNodo(elemento))) << endl;
                }
                

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            
            case 15:
                cout<< "Digite el vertice:" << endl;
                cin >> elemento;
                cout<< "Primer Vertice Adyacente es: ";
                cout<< grafo.Etiqueta(grafo.PrimerVerticeAdyacente(grafo.traductorNodo(elemento))) << endl;

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            
            case 16:
                cout<< "Digite el vertice primero:" << endl;
                cin >> elemento;
                cout<< "Digite el vertice segundo:" << endl;
                cin >> elemento2;
                cout<< "Siguiente Vertice Adyacente es: ";
                cout<< grafo.Etiqueta(grafo.SiguienteVerticeAdyacente(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2))) << endl;             

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                             
                break;
            //------------------------------------------------------------
            case 17:
                cout << "Numero de vertices del grafo: ";
                cout << grafo.NumVertices() << endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 18:
                cout<< "Digite el vertice:" << endl;
                cin >> elemento;
                cout << "Numero de vertices adyacentes: ";
                cout << grafo.NumVerticesAdyacentes(grafo.traductorNodo(elemento)) << endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 19:
                cout << "Numero de aristas del grafo: ";
                cout << grafo.NumAristas() << endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 20:
                cout<< "Digite el vertice:" << endl;
                cin >> elemento;
                cout << "Etiqueta: ";
                cout << grafo.Etiqueta(grafo.traductorNodo(elemento)) << endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;
            //------------------------------------------------------------
            case 21:
                cout<< "Digite el vertice primero:" << endl;
                cin >> elemento;
                cout<< "Digite el vertice segundo:" << endl;
                cin >> elemento2;
                cout<< "Es adyacente: ";
                cout<< grafo.EsAdyacente(grafo.traductorNodo(elemento),grafo.traductorNodo(elemento2)) << endl;             

                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                             
                break;
            //------------------------------------------------------------
            case 22:
                cout<< "Digite el vertice:" << endl;
                cin >> elemento;
                cout << "Es vertice nulo: ";
                cout << grafo.EsVerticeNulo(grafo.traductorNodo(elemento)) << endl;
                
                cout<< "Presione enter para continuar..." << endl;
                system("pause>nul"); // Pausa                
                break;

            case 23:
                subMenu(elemento,elemento2,peso,grafo, grafo.PrimerVertice());                              
                break; 
   
        }        
    } while (opcion != 0);      

}




template<class K, class T>
void subMenu(char elemento,char elemento2,int peso,K &grafo, T vertice){
    //K hijo;
    int opcion;
    int* vectorDePesos = (int*)calloc((grafo.NumVertices()-1), sizeof(int));
    T* vectorVerticeAnterior = (T*)calloc((grafo.NumVertices()-1), sizeof(T));
    
    do {
        system("cls");
        
        // Texto del menú que se verá cada vez
        
        cout << "\nMenu de Opciones" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 1. TieneCiclosAnchoPrimero" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 2. CalcularPesos" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 3. AislarVertice" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 4. Prim" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 5. Kruskal" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 6. Dijkstra" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 7. CircuitoHamilton" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 8. Floyd" << endl;
        cout << "-------------------------------------"<<endl;
        cout << " 9. ColorearGrafo" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "10. WarshallConexos" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "11. ProfundidadPrimeroCiclos" << endl;
        cout << "-------------------------------------"<<endl;
        cout << "12. ProfundidadPrimeroConexo" << endl;
        cout << "-------------------------------------"<<endl;
    
        
        cout << "0. SALIR" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            
            //------------------------------------------------------------
            case 1:
                TieneCiclos(grafo.PrimerVertice(),grafo);

                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 2:
                CalcularPesos(grafo.PrimerVertice(),grafo);
                
                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 3:
                cout<< "Digite vertice a aislar: " << endl;
                cin >> elemento;
                AislarVertice(grafo,grafo.traductorNodo(elemento));

                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 4:
                Prim(grafo,grafo.PrimerVertice());

                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 5:
                Kruskal(grafo,grafo.PrimerVertice());

                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 6:
                cout << "Digite el vertice:" << endl;
                cin >> elemento;
                Dijkstra(grafo,grafo.traductorNodo(elemento), vectorDePesos, vectorVerticeAnterior);

                cout << "Informacion de peso de Dijkstra del vertice solicitado : " << endl; 
                    for (int i = 0; i < grafo.NumVertices()-1; ++i) {
                        cout << vectorDePesos[i] << " "; 
                    }
                    cout << endl;

                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 7:
            if(opcion == 7){
                Diccionario<T> diccionario;
                diccionario.Iniciar(); 
                T* soluciones = (T*)calloc(grafo.NumVertices()+1, sizeof(T));
                T* mejorSolucion = (T*)calloc(grafo.NumVertices()+1, sizeof(T));
                int costo = 0; 
                int mejor_costo = maximo; 
                int contador_soluciones = 0; 
                soluciones[0] = grafo.PrimerVertice();

                CircuitoHamilton(grafo, diccionario, soluciones, mejorSolucion, costo, mejor_costo, contador_soluciones, 1);
                cout << "La cantidad de soluciones factibles para el circuito hamilton es: " << contador_soluciones << endl;

                if (contador_soluciones > 0) {
                    stringstream ss; 
                    for (int i = 0; i <= grafo.NumVertices(); ++i) {
                        if (i != grafo.NumVertices()) {
                            ss << mejorSolucion[i] << ", "; 
                        }
                        else {
                            ss << mejorSolucion[i]; 
                        }   
                    }
                    ss << "\n"; 
                    cout << "La mejor solucion al circuito hamilton es la siguiente: " << endl;
                    cout << ss.str() << endl;
                    cout << endl; 
                }
                else {
                   cout << "El grafo no posee un circuito de Hamilton" << endl; 
                }
            }
                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
           
            case 8:
                if(opcion == 8){
                    int** matrizDePesos = (int**)malloc(grafo.NumVertices()*sizeof(int*));
                    char** matrizDeVerticesIntermedios = (char**)malloc(grafo.NumVertices()*sizeof(char*));

                    for (int fila = 0; fila < grafo.NumVertices(); ++fila) {
                        matrizDePesos[fila] = (int*)malloc(grafo.NumVertices()*sizeof(int)); 
                        matrizDeVerticesIntermedios[fila] = (char*)malloc(grafo.NumVertices()*sizeof(char));   
                    } 

                    Floyd(grafo, matrizDePesos, matrizDeVerticesIntermedios, grafo.PrimerVertice()); 

                    
                    cout << "La Matriz con los caminos mas cortos es la siguiente : " << endl; 
                    for (int i = 0; i < grafo.NumVertices(); ++i) {
                        for (int j = 0; j < grafo.NumVertices(); ++j) {
                            cout << matrizDePesos[i][j] << ", "; 
                        }
                        cout << endl; 
                    }
                    cout << "Si el grafo utilizado es el Grafo LSE-LSE la matriz se imprimira al reves" << endl;
                    
                    for (int fila = 0; fila < grafo.NumVertices(); ++fila) {
                        free(matrizDePesos[fila]); 
                        free(matrizDeVerticesIntermedios[fila]);     
                    }
                } 

                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            
            case 9:
                if(opcion == 9){
                    Conjunto<T> mejorSolucion; 
                    mejorSolucion.Inicializar(grafo.NumVertices());
                    int menor_cantidad = maximo; 
                    int colores = 0; 
                    int contador_soluciones = 0; 
                    bool found = false; 
                    colorear_grafo(grafo, mejorSolucion, colores, menor_cantidad, contador_soluciones, found); 
                    if (found) {
                        string resultado = mejorSolucion.printSet();
                        cout << "Cada linea corresponde a un color y los vertices que se agruparon a dicho color" << endl; 
                        cout << "La mejor solucion al algoritmo de coloreo es la siguiente:\n"<< resultado << endl; 

                        T verticeCodificador = grafo.PrimerVertice();
                        cout << "Direccion de cada vertice que aparece en la lista de coloreados, esto es exclusivo para interpretar los elementos de la lista de coloreados para el grafo LSE-LSE: " << endl;
                        while(verticeCodificador!= NULL){
                            cout << "Vertice: " << grafo.Etiqueta(verticeCodificador) << " Direccion del vertice: " << verticeCodificador << endl;
                            verticeCodificador= grafo.SiguienteVertice(verticeCodificador);
                        }
                    }
                    else {
                        cout << "el grafo no pude ser coloreado exitosamente" << std::endl; 
                    }     

                    cout<< "\nPresione enter para continuar..." << endl;
                    system("pause>nul"); // Pausa
                }
                    break;
            //------------------------------------------------------------
            
            case 10:
                
                WarshallConexo(grafo,grafo.PrimerVertice());
                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            case 11:
                cout << "Hay ciclos: " << ProfundidadPrimeroCiclos(grafo,grafo.PrimerVertice()) << endl;
                
                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;
            //------------------------------------------------------------
            case 12:
                profundidadPrimeroConexo(grafo, grafo.PrimerVertice());
      
                cout<< "\nPresione enter para continuar..." << endl;
                system("pause>nul"); // Pausa
                break;

    }  
    
    } while (opcion != 0);     

    
}


//------------------------------------------------------------------------------------------


int main(){
    
    Grafo grafo;
    menu(grafo.PrimerVertice(),grafo,'A','B',1);

    
return 0;   
}


/*int main(){
	Grafo grafo;
    grafo.Iniciar();

   ESTO ESTABA COMENTADO
	grafo.AgregarVertice('1');
    grafo.AgregarVertice('2');
    grafo.AgregarVertice('3');
    grafo.AgregarVertice('4');
    grafo.AgregarArista( grafo.traductorNodo('1'),grafo.traductorNodo('2'),1);
    grafo.AgregarArista(grafo.traductorNodo('2'),grafo.traductorNodo('3'),4);
    grafo.AgregarArista(grafo.traductorNodo('3'),grafo.traductorNodo('4'),2);

    //cout << "Es nulo: " << grafo.EsVerticeNulo(grafo.traductorNodo('8')) << endl;
    ESTO ESTABA COMENTADO


	grafo.AgregarVertice('0');
    grafo.AgregarVertice('1');
    grafo.AgregarVertice('2');
    grafo.AgregarVertice('3');

    grafo.AgregarArista( grafo.traductorNodo('0'),grafo.traductorNodo('1'),1);
    grafo.AgregarArista(grafo.traductorNodo('0'),grafo.traductorNodo('3'),5);
    grafo.AgregarArista(grafo.traductorNodo('1'),grafo.traductorNodo('3'),5);
    grafo.AgregarArista( grafo.traductorNodo('1'), grafo.traductorNodo('2'),4);
    grafo.AgregarArista( grafo.traductorNodo('2'), grafo.traductorNodo('3'),2);

    //cout<< grafo.Etiqueta(grafo.traductorNodo('1')) << endl;
    //cout<< grafo.Etiqueta(grafo.traductorNodo('2')) << endl;
    //cout<< grafo.Etiqueta(grafo.traductorNodo('3')) << endl;
    //cout<< grafo.Etiqueta(grafo.traductorNodo('4')) << endl;
	
    //grafo.imprimirSublistas();

    //CalcularPesos(grafo.traductorNodo('1'), grafo);
    //cout << grafo.Etiqueta(TraductorNodo(grafo.PrimerVertice(),'3', grafo));
	//TieneCiclos(grafo.traductorNodo('1'),grafo);
	//profundidadPrimero(grafo,grafo.traductorNodo('1'));
    Prim(grafo,grafo.traductorNodo('3'));
    //Kruskal(grafo,grafo.traductorNodo('1'));
    //WarshallConexo(grafo,grafo.traductorNodo('1'));

	//AislarVertice(grafo,grafo.traductorNodo('1'));
	//cout<< "Numero de aristas: " << grafo.NumAristas() << endl;
	//grafo.EliminarArista(grafo.traductorNodo('1'),grafo.traductorNodo('3'));
	//grafo.EliminarArista(grafo.traductorNodo('1'),grafo.traductorNodo('2'));

	//grafo.imprimirSublistas();

    cout << "Termine 123" << endl;

	return 0;
}
*/