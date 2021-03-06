#include<iostream>
#include<fstream>
#include<cstring>
#include "imagen.h"
#include "lista.h"

using namespace std;

int main(int argc, char*argv[]){
	Imagen imgA;
	Imagen imgB;
	Imagen imgC;

	if (argc<5){
		printf("Faltan no componentes del vector\n");
		exit(-1);
   	}

	if (!imgB.leerImagen(argv[1])){
		cerr << "Error leyendo imagen" << argv[1]<< endl;
		return 1;
    	}

	if (!imgC.leerImagen(argv[2])){
		cerr << "Error leyendo imagen" <<argv[2]<< endl;
		return 1;
    	}

	imgA=imgB+imgC; //equivalente a imgA= operator+(imgB,imgC); 

	if(strcmp(argv[4],"t")==0){
		//guarda en texto
		imgA.escribirImagen(argv[3],false);
	}else{
		//guarda en binario
		imgA.escribirImagen(argv[3],true);
	}
}
