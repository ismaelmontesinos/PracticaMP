/**
 * lee cualquier imagen indicada por el usuario y un fichero con cadenas 
 * de caracteres y crea ficheros de imagen transformadas, una por cadena
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include "imagen.h"
#include "lista.h"

using namespace std;


const int MAXLONG = 1000000;

int main(int argc, char*argv[]){
    Imagen origen;
    Lista celdas;

   if (argc<3){
	printf("Faltan no componentes del vector\n");
	exit(-1);
   }

    // Leer la imagen desde fichero
    if (!origen.leerImagen(argv[1])){
		cerr << "Error leyendo imagen " << argv[1]<< endl;
		return 1;
    }

	// Leer cadenas desde fichero
	if (celdas.leerLista(argv[2])){	
		// realizar las conversiones
		if (origen.listaAArteASCII(celdas)){
			cout << "Exito en la conversion." << endl;
			cout << "Chequee los ficheros asciiX.txt" << endl;
			cout << endl;
		}else{
			cerr << "La conversion no ha sido posible" << endl;
			cerr << endl;
		}
		//celdas.destruir(); // liberar memoria listas
	}else{
		cerr << "Error lista de grises " /*<< ficheroGrises */<< endl;
	}
	
    //origen.destruir();   // liberar memoria imagen
	
}
