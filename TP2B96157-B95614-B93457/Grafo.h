#include<iostream>
#define maximus 30
using namespace std;

class Grafo{
	public: 
		
		/*
			Iniciar 
			Parámetros: ninguno
			Efecto: inicializa el grafo G
			Requiere: grafo no inicializado o destruido 
			Modifica: nada

		*/
		void Iniciar(){
		numElem = 0;	
		}
		//--------------------------------------------------------------------------------------
		/*
			Vaciar
			Parámetros: grafo G
			Efecto: vacía el grafo G
			Requiere: grafo G inicializado
			Modifica: grafo G

		*/
		void Vaciar(){
			numElem=0;
		}
		//--------------------------------------------------------------------------------------
		
		/*
			Vacío?
			Parámetros:grafo G
			Efecto: devuelve falso o verdadero si el grafo G está vacío
			Requiere: grafo G inicializado
			Modifica:nada 

		*/
		bool Vacio(){
			if(numElem == 0){
			return true;
			}else{
			return false;
			}
		}
		//--------------------------------------------------------------------------------------
		/*
			Destruir 
			Parámetros: grafo G
			Efecto: destruye grafo G
			Requiere: grafo G inicializado
			Modifica: nada

		*/
		void Destruir(){
			delete this;
		}
		//--------------------------------------------------------------------------------------
		
		/*
			AgregarVértice?
			Parámetros: e ->tipo elemento
			Efecto: agrega un vértice con el elemento e 
			Requiere: grafo G inicializado y elemento e válido 
			Modifica: grafo G

		*/
		int AgregarVertice(char elemento){
			int vertice = numElem;
			if(numElem<maximus){
				etiquetas[numElem]=elemento;
			numElem++;
			for(int i=0; i<numElem;i++){
				matriz[vertice][i].esta=false;
				matriz[i][vertice].esta=false;
			}	
			}
			
			
			return vertice;

		}
		//--------------------------------------------------------------------------------------
		
		/*
			EliminarVértice
			Parámetros: v tipo vértice
			Efecto: eliminada el vértice v del grafo G
			Requiere:grafo G inicializado y vértice v válido 
			Modifica: grafo V

		*/
		void EliminarVertice(int n){
			bool aislado=true;
			
			//eliminar elemento del arreglo
			if(aislado){
				
				for(int j=n;j<numElem;j++){
					etiquetas[j]=etiquetas[j+1];
				}
				numElem--;
				for(int x=n;x<numElem;x++){
					for(int y=0;y<numElem;y++){
					matriz[x][y].esta=matriz[x+1][y].esta;
					matriz[x][y].peso=matriz[x+1][y].peso;
						
					matriz[y][x].esta=matriz[y+1][x].esta;
					matriz[y][x].peso=matriz[y+1][x].peso;	
					
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
		void ModificarEtiqueta(int vertice,char elemento){
			etiquetas[vertice]=elemento;
		}
		//--------------------------------------------------------------------------------------
		
		/*
			Etiqueta?
			Parámetros: v tipo vértice 
			Efecto:devuelve la etiqueta actual del vértice v 
			Requiere: grafo G inicializado y vértice v válido
			Modifica: nada 
		*/
		char Etiqueta(int vertice){
			if(vertice<numElem){
				return etiquetas[vertice];
			}
		else{
			return NULL;
		}
		}
		//--------------------------------------------------------------------------------------
		
		/*
			AgregarArista
			Parámetros: v1, v2 tipos vértices , p tipo peso
			Efecto: agrega una arista a de peso p entre los vértices v1 y v2
			Requiere: vértices v1,v2 válidos, peso p válido y que no exista una arista entre v1 y v2
			Modifica: grafo G

		*/
		void AgregarArista(int v1,int v2, int p){
			if(v1!=v2&&!matriz[v1][v2].esta&&!matriz[v2][v1].esta&&v1<numElem&&v2<numElem){
			matriz[v1][v2].esta=true;
			matriz[v1][v2].peso=p;
			matriz[v2][v1].esta=true;
			matriz[v2][v1].peso=p;
			}
				
			
		}
		//--------------------------------------------------------------------------------------
		/*
			EliminarArista
			Parámetros: v1,v2 tipo vértices 
			Efecto: elimina la arista a entre los vértices v1 y v2 
			Requiere: arista a entre v1 y v2 existente 
			Modifica: grafo G
		*/

		void EliminarArista(int v1,int v2){
			if(v1<numElem&&v2<numElem){
				matriz[v1][v2].peso=-1;
				matriz[v1][v2].esta=false;
				matriz[v2][v1].peso=-1;
				matriz[v2][v1].esta=false;
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
		void ModificarPeso(int v1,int v2,int p){
			matriz[v1][v2].peso=p;
		}
		//--------------------------------------------------------------------------------------
		/*
			Peso?
			Parámetros:v1,v2 tipo vértices 
			Efecto: devuelve el peso p de la arista entre v1 y v2
			Requiere: vértices v1,v2 válidos, arista existente entre v1 y v2
			Modifica:nada 

		*/
		int Peso(int v1,int v2){
			return matriz[v1][v2].peso;
		}
		//--------------------------------------------------------------------------------------
		/*
			PrimerVértice?
			Parámetros:grafo G
			Efecto:devuelve el primer vértice del grafo G
			Requiere: grafo G inicializado 
			Modifica: nada

		*/
		int PrimerVertice(){
		if(numElem!=0){
			return 0;
		}else{
			return -1;
		}

		}
		//--------------------------------------------------------------------------------------
		int traductorNodo(char nodo){
			bool encontrado=false;
			int buscador = 0;
			while (buscador<numElem&&!encontrado){
				if(etiquetas[buscador]==nodo){
					encontrado =true;
				}else{
					buscador++;
				}
			}
			

			return buscador;
        }
        //--------------------------------------------------------------------------------------
		/*
			SiguienteVértice?
			Parámetros: v tipo vértice
			Efecto:devuelve el siguiente vértice de v dentro del grafo G
			Requiere: grafo G inicializado, vértice v válido
			Modifica: nada

		*/
		int SiguienteVertice(int v) {
			int siguiente=-1;
			if(v+1<numElem){
			siguiente=v+1;
			}
						
			return siguiente;

		}
		//--------------------------------------------------------------------------------------
		/*
			PrimerVérticeAdyacente?
			Parámetros:v tipo vértice 
			Efecto: devuelve el primer vértice adyacente del vértice v 
			Requiere: vértice v válido
			Modifica: nada

		*/
		int PrimerVerticeAdyacente(int vertice){
			int primero=-1;
			for(int i=0;i<numElem;i++){
				if(primero!=i&&matriz[vertice][i].esta==true){
					primero=i;
					i=numElem;
				}
			}
			return primero;

		}
		//--------------------------------------------------------------------------------------
		/*
			SiguienteVérticeAdyacente?
			Parámetros: v1,v2 tipo vértices 
			Efecto:devuelve el siguiente vértice adyacente de v1, después de v2
			Requiere: vértices v1,v2 válidos 
			Modifica: nada 

		*/
		int SiguienteVerticeAdyacente(int v1,int v2){
			int siguiente=-1;
			for(int i= v2+1; i<numElem; i++){
				if(i!=v1&&matriz[v1][i].esta==true){
					siguiente=i;
					i=numElem;
				}
			}
		
			return siguiente;

		}
		//--------------------------------------------------------------------------------------
		/*
			ExisteArista?
			Parámetros:v1,v2 tipo vértices 
			Efecto:devuelve verdadero o falso si existe la arista entre v1 y v2
			Requiere: vértices v1,v2 válidos 
			Modifica: nada

		*/
		bool ExisteArista(int v1,int v2){
			if(v1<numElem&&v2<numElem&&v1!=v2){
			return matriz[v1][v2].esta;	
			}else{
				return false;
			}
			
		}
		//--------------------------------------------------------------------------------------
		int NumAristas(){
			int numero=0;
			for(int i=0;i<=numElem;i++){
				for(int j=0;j<=numElem;j++){
					if(matriz[i][j].esta==true){
						numero++;
					}
				}
			}
			return numero/2;

		}
		//--------------------------------------------------------------------------------------
		/*
			NumVértices?
			Parámetros:grafo G
			Efecto:devuelve la cantidad total de vértices del grafo G
			Requiere:grafo G inicializado 
			Modifica: nada

		*/
		int NumVertices(){
			return numElem;

		}
		//--------------------------------------------------------------------------------------
		/*
			NumVérticesAdyacentes?
			Parámetros: v tipo vértice
			Efecto: devuelve la cantidad de vértices adyacentes del vértice v
			Requiere: vértice v válido 
			Modifica:nada
		*/
		int NumVerticesAdyacentes(int vertice){
			int numAristasAd=0;
			for(int i=0;i<numElem;i++){
				if(i!=vertice){
					if(matriz[vertice][i].esta==true){
						numAristasAd++;	
					}
				}
				
			}
			return numAristasAd;

		}
		//--------------------------------------------------------------------------------------
		bool EsVerticeNulo(int v){
			bool nulo =false;
			if(v>=numElem||v==-1){
				nulo=true;
			}
			return nulo;
		}
		//--------------------------------------------------------------------------------------
		
		int getVerticeNulo(){
			return -1;
		}
		//--------------------------------------------------------------------------------------
		
		bool EsAdyacente(int v1,int v2){
            if(matriz[v1][v2].esta){
                return true;
            }else{
                return false;
            }


        }
        
        
		
		private:
		struct nodo{
		int peso=-1;
		bool esta=false;
			
		};
		int numAristas;
		int numElem;
		int maximusimoVertices=30;
		char etiquetas [maximus];
		nodo matriz[maximus][maximus];
		
			
};

/*
int main(){
	//---------------------------------------------------
	Grafo grafo;
	//---------------------------------------------------
	grafo.Iniciar();//1
	//---------------------------------------------------
	cout<<"EstaVacio->"<<grafo.Vacio()<<endl;//4
	//---------------------------------------------------
	grafo.AgregarVertice('D');//5
	//---------------------------------------------------
	grafo.AgregarVertice('E');//
	//---------------------------------------------------
	grafo.AgregarVertice('A');
	//---------------------------------------------------
	grafo.AgregarVertice('B');
	grafo.AgregarVertice('L');
	//---------------------------------------------------
	cout<<"Esta Vacio->"<<grafo.Vacio()<<endl;//
	//---------------------------------------------------
	cout<<"PrimeroVertice->"<<grafo.Etiqueta(grafo.PrimerVertice())<<endl;//8,14
	//---------------------------------------------------
	cout<<"NumeroDeVertices->"<<grafo.NumVertices()<<endl;
	//---------------------------------------------------
	grafo.ModificarEtiqueta(0,'S');//7
	//---------------------------------------------------
	cout<<"PrimeroVertice->"<<grafo.Etiqueta(grafo.PrimerVertice())<<endl;
	//---------------------------------------------------
	grafo.EliminarVertice(0);//6
	//---------------------------------------------------
	cout<<"PrimeroVertice->"<<grafo.Etiqueta(grafo.PrimerVertice())<<endl;
	//---------------------------------------------------
	grafo.AgregarArista(0,1, 7);//9
	grafo.AgregarArista(0,2, 5);
	grafo.AgregarArista(0,3, 6);
	//---------------------------------------------------
	grafo.ModificarPeso(0,2,4);//11
	//---------------------------------------------------
	cout<<"PesoArista->"<<grafo.Peso(0,1)<<endl;//12
	//---------------------------------------------------
	cout<<"PesoArista->"<<grafo.Peso(0,2)<<endl;//12
	//---------------------------------------------------
	//grafo.EliminarArista(0,1);//10
	//---------------------------------------------------
	cout<<"SiguienteVertice->"<<grafo.Etiqueta(grafo.SiguienteVertice(0))<<endl;//15
	//---------------------------------------------------
	cout<<"PrimerVerticeAdyacente->"<<grafo.PrimerVerticeAdyacente(0)<<endl;//16
	cout<<"PrimerVerticeAdyacente->"<<grafo.PrimerVerticeAdyacente(1)<<endl;
	//---------------------------------------------------
	cout<<"SiguienteVerticeAdya->"<<grafo.SiguienteVerticeAdyacente(0,7)<<endl;//17
	//---------------------------------------------------
	cout<<"Existe la arista->"<<grafo.ExisteArista(0,1)<<endl;//13
	cout<<"Existe la arista->"<<grafo.ExisteArista(8,7)<<endl;
	//---------------------------------------------------
	cout<<"NumeroAristas->"<<grafo.NumAristas()<<endl;//15
	//---------------------------------------------------
	cout<<"NumeroDeVertices->"<<grafo.NumVertices()<<endl;//16
	//---------------------------------------------------
	cout<<"vertices adyacentes->"<<grafo.NumVerticesAdyacentes(0)<<endl;//17
	//---------------------------------------------------
	for(int i=0;i<grafo.NumVertices();i++){
		cout<<grafo.Etiqueta(i);
	}
	cout<<endl;
	for(int i=0;i<grafo.NumVertices();i++){
				for(int j=0;j<grafo.NumVertices();j++){
					if(grafo.ExisteArista(i,j)){
						cout<<"1";
					}else{
						cout<<"0";
					}
				}
				cout<<endl;
			}
	//---------------------------------------------------
	cout<<"holaFINAL"<<endl;
	//---------------------------------------------------
	grafo.Vaciar();//3
	//---------------------------------------------------
	grafo.Destruir();//2
	//---------------------------------------------------
	cout<<"EstaVacio->"<<grafo.Vacio();
	//---------------------------------------------------
	//cout<<arbol.Vacio();
	//---------------------------------------------------
	return 0;
};

*/