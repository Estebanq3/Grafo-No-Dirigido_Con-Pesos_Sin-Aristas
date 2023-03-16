#include <iostream>
#include <string>
using namespace std;

template <class T>
class NodoD
{
public:
	T m_dato;
	NodoD<T> *m_psig;
public:
	NodoD(T d)
	{
		m_dato = d;
		m_psig = nullptr;
	}
};

template <class T>
class Diccionario
{
public:
	NodoD<T> *m_pHead;
	NodoD<T> *m_pLast;
	int can_elementos = 0;
	public:

	void Iniciar();
	bool Vacio();
	int numElem();
	void Destruir();
	void Vaciar();
	void Agregar(T d);
	void AgregarFrente(T d);
	bool Pertenece(T d);
	bool Eliminar(T d);
	bool PerteneceR(T d, NodoD<T> *p);
	string Imprimir();
};

template <class T>
void Diccionario<T>::Iniciar(){
	m_pHead = m_pLast = nullptr;
}

template <class T>
bool Diccionario<T>::Vacio(){
	if(m_pHead == nullptr && m_pLast == nullptr){
		return true;
	}
	return false;
}

template <class T>
int Diccionario<T>::numElem(){
	return can_elementos;
}

template <class T>
void Diccionario<T>::Destruir(){
	Vaciar();
	delete this;
}

template <class T>
void Diccionario<T>::Vaciar(){
	NodoD<T> *aux1 = m_pHead;
	while(aux1 != NULL){
		Eliminar(aux1->m_dato);
		aux1 = aux1->m_psig;
	}
}

template <class T>
void Diccionario<T>::Agregar(T d)
{
	NodoD<T> *p_Nuevo = new NodoD<T>(d);
	if (m_pHead == 0){
		m_pHead = m_pLast = p_Nuevo;
		can_elementos++;
	}else{
		m_pLast->m_psig = p_Nuevo;
		m_pLast = p_Nuevo;
		can_elementos++;
	}
}

template <class T>
void Diccionario<T>::AgregarFrente(T d)
{
	NodoD<T> *p_Nuevo = new NodoD<T>(d);
	if (m_pHead == 0){
		m_pHead = m_pLast = p_Nuevo;
		can_elementos++;
	}else{
		p_Nuevo->m_psig = m_pHead;
		m_pHead = p_Nuevo;
		can_elementos++;
	}
}

template <class T>
bool Diccionario<T>::Eliminar(T d)
{
    NodoD<T> *aux1 = m_pHead;
    if (aux1 == 0){
        return false;
    }
    if (aux1->m_dato == d && aux1->m_psig == 0){
        delete aux1;
        can_elementos--;
        m_pHead = m_pLast = 0;
        return true;
    }
    NodoD<T> *ant = m_pHead;
    while (aux1 != 0)
    {
        if (aux1->m_dato == d){
            NodoD<T> *aux2 = aux1->m_psig;
            delete aux1;
            ant->m_psig = aux2;
            can_elementos--;
            return true;
        }else{
            ant = aux1;
            aux1 = aux1->m_psig;
        }
    }
    return false;
}

template <class T>
bool Diccionario<T>::Pertenece(T d)
{
	NodoD<T> *aux = m_pHead;
	while (aux != 0)
	{
		if (aux->m_dato == d){
			return true;
		}
		aux = aux->m_psig;
	}
	return false;
}

template <class T>
bool Diccionario<T>::PerteneceR(T d, NodoD<T> *p)
{
	if (p == 0)return false;
	if (p->m_dato == d)return true;
	findR(d, p->m_psig);
}

template<class T>
string Diccionario<T>::Imprimir()
{
	string str = "";
	NodoD<T> *aux = m_pHead;
	while (aux != 0)
	{
		str = str + aux->m_dato;
		aux = aux->m_psig;
	}
	return str;
}

/*
int main(){
	Diccionario<char> diccionario;
	diccionario.Iniciar();
	cout << "se peta? "<< diccionario.Pertenece('4')<<endl;
	cout << diccionario.NumElem()<<endl;
	cout << diccionario.Imprimir()<<endl;
	diccionario.Agregar('5');
	cout << diccionario.Imprimir()<<endl;
	cout << endl;
	diccionario.Agregar('6');
	cout << diccionario.Imprimir()<<endl;
	cout << endl;
	cout << diccionario.Pertenece('5')<< endl;
	cout << diccionario.Imprimir()<<endl;
	cout << endl;
	cout << diccionario.Pertenece('7')<< endl;
	cout << diccionario.Imprimir()<<endl;
	cout << endl;
	diccionario.Agregar('7');
	cout << diccionario.NumElem()<<endl;
	cout << diccionario.Imprimir()<<endl;
	cout << endl;
	diccionario.Eliminar('6');
	cout << diccionario.NumElem()<<endl;
	cout << diccionario.Imprimir()<<endl;
	cout << endl;
	cout << "final" << endl;
	return 0;
};
*/