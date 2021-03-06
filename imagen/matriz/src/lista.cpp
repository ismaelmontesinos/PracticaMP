#include <string>
#include <fstream>
#include <iostream>
#include "lista.h"

using namespace std;

Lista::Lista(){
	cabecera=0;
}
   
Lista::Lista(string valor){
	cabecera=0;
	insertar(valor);
}
	

void Lista::destruir(){
	if(cabecera!=0){
		Celda *p=cabecera;
		while(cabecera->siguiente != 0){
			cabecera = cabecera->siguiente;
			delete p;
			p = cabecera;
		}
		delete cabecera;
	}
}  

//destructor
Lista::~Lista(){
		destruir();
	}

//constructor de copia??????????'
Lista::Lista(const Lista &otra){
	Celda *aux=otra.cabecera;
	cabecera=0;
	while (aux!=0){
		insertar(aux->datos);
		aux=aux->siguiente;
	}
}	



void Lista::insertar(string valor){
	if(cabecera==0){
		cabecera = new Celda;
		cabecera->datos=valor;
		cabecera->siguiente=0;
	}
	else{
		Celda *p=cabecera;
		while(p->siguiente!=0)
			p=p->siguiente;

		p->siguiente = new Celda;
		p=p->siguiente;
		p->datos=valor;
		p->siguiente=0;
	}
}

//sobrecarga operador=
Lista& Lista::operator=(const Lista &l){
		if(this!=&l){//??????????constructor de copia
			this->cabecera= l.cabecera;
		}
		return (*this);
	}

//Sobrecarga de operador de suma
	Lista Lista::operator+(const string dato){
		Lista nueva(*this);
		nueva.insertar(dato);
		return nueva;
	}

string Lista::getCelda(int pos) const{
	Celda *p = cabecera;
	string devuelve="";
	int lon=longitud();
	if(pos<=lon){
		for(int i=0;i<pos;i++){
			p=p->siguiente;
		}
		devuelve=p->datos; 
	}
	return devuelve;

}

int Lista::longitud() const{
	int k=0;
	if(cabecera!=0){
		Celda *p=cabecera;
		while(p){
			p=p->siguiente;
			k++;
		}
	}
	return k;
}

/**
 * @brief Construye una lista de celdas enlazadas a partir de la informacion 
 * contenida en un fichero.
 * @param nombreFichero ruta del fichero de texto con el contenido de las datoss
 * a insertar en la lista
 * @retval true si ha tenido éxito en la lectura y el formato es el correcto
 * @retval false si se ha producido algún error en la lectura 
 * 
 * Lee desde disco los elementos almacenados en @a nombreFichero y los guarda 
 * en la lista. La función debe asegurarse de que la estructura sigue un patron 
 * determinado, y se ha de crear la lista con el numero de elementos que contenga. 
 */
bool Lista::leerLista(const char nombrefichero[]){
	ifstream fin;
	fin.open(nombrefichero);
	if(!fin){
		return false;
	}else{
		string grises;
		int lineas;
		getline(fin,grises); //la primera linea se ignora
		fin >> lineas; //leo el numero de datos de grises
		getline(fin,grises); //leer salto de linea
		if (!fin){
			return false;
		}else {
			int i = 0;
			getline(fin,grises); //leer cadena de caracteres
			while ((i < lineas)&&(fin)){
				if (grises != ""){
					insertar(grises);
					i++;
				}
				getline(fin,grises); //leer cadena de caracteres
			}
		}
		fin.close();
	}
	return true;
}
