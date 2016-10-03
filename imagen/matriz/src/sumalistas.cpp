#include<iostream>
#include<fstream>
#include<cstring>
#include "lista.h"

using namespace std;

int main(){
	Celda listaA;
	Celda listaB;
	Celda listaC;

	listaB.insertar("uno");
	listaC.insertar("dos");

	listaA=listaB+listaC; //equivalente a listaA= operator+(listaB,listaC); 
	
	//cout<<listaA;
}
