#include <iostream>
#include <cstring>
#include <fstream>
#include "imagen.h"
#include "pgm.h"
#include "byte.h"
#include "lista.h"
using namespace std;
	
// Construye una imagen vacía (0 filas, 0 columnas)
	Imagen::Imagen(){
		nfilas=0;
		ncolumnas=0;
		datos=0;
	}
   

//Construye una imagen negra de tamaño filas x columnas
	Imagen::Imagen(int filas, int columnas){
		datos=0;
		crear(filas,columnas);
	}


//Crea una imagen negra de tamaño filas x columnas
	void Imagen::crear(int filas, int columnas){
		if(datos!=0)
			destruir();
		nfilas=filas;
		ncolumnas=columnas;
		datos = new byte*[nfilas];
		datos[0]= new byte[nfilas*ncolumnas];

		for(int i=1;i<nfilas;i++){
			datos[i]=datos[i-1]+ncolumnas;
		}
	}

//Destructor
	Imagen::~Imagen(){
		destruir();
	}

//
	void Imagen::destruir(){
		nfilas=ncolumnas=0;
		if(datos!=0){
			delete [] datos[0];
			delete [] datos;
			datos=0;
		}
	}	

//Constructor de copia
	Imagen::Imagen(const Imagen &otra){
		nfilas= otra.nfilas;
		ncolumnas= otra.ncolumnas;
		datos= new byte*[nfilas];
		datos[0]= new byte[nfilas*ncolumnas];
		for(int i=1;i<nfilas;i++){
			datos[i]=datos[i-1]+ncolumnas;
		}
		for(int i=0;i<nfilas;i++){
			for(int j=0;j<ncolumnas;j++){
				 datos[i][j]=otra.get(i,j);
			}	
		}
	}	

//Devuelve el numero de filas de la imagen
	int Imagen::filas(){
		return nfilas;
	}


//Devuelve el numero de columnas de la imagen
	int Imagen::columnas(){
		return ncolumnas;
	}
   

//Asign el valor v a la posicion (x,y) de la imagen
	void Imagen::set(int y, int x, byte v){		
		datos[y][x]=v;
	}
   

//Devuelve el valor v de la posicion (x,y) de la imagen
	byte Imagen::get(int y, int x) const{
		return datos[y][x];
	}
   
   
//Asigna el valor v a la posicion i de la imagen considerada como vector
	void Imagen::setPos(int i, byte v){
		datos[0][i]=v;
	}
   
 
//Devuelve el valor de la posicion i de la imagen considerada como vector
	byte Imagen::getPos(int i){
		return datos[0][i];
	}

//Sobrecarga de operador de asignación
	Imagen& Imagen::operator=(const Imagen &im){
		if(this!=&im){//??????????constructor de copia
			destruir();
			nfilas=im.nfilas;
			ncolumnas=im.ncolumnas;
			crear(nfilas, ncolumnas);
			for(int i=0;i<nfilas;i++){
				for(int j=0;j<ncolumnas;j++){
					set(i,j,im.get(i,j));
				}
			}
		}
		return (*this);
	}

//Sobrecarga de operador de suma
	Imagen Imagen::operator+(const Imagen &img){
		int col= ncolumnas+img.ncolumnas;		
		int row= (nfilas>img.nfilas)?nfilas:img.nfilas;
		Imagen imgsalida(row,col);
		//Ponemos toda la imagen negra
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				imgsalida.set(i,j,0x00);
			}
		}		
		//Ahora introducimos la imagen B	
		for(int i=0;i<nfilas;i++){
			for(int j=0;j<ncolumnas;j++){
				imgsalida.set(i,j,get(i,j));
			}
		}
		//Ahora introducimos la imagen C
		for(int i=0;i<img.nfilas;i++){
			for(int j=0;j<img.ncolumnas;j++){
				imgsalida.set(i,j+ncolumnas,img.get(i,j));
			}
		}
		return imgsalida;
	}


//Carga una imagen desde fichero 
	bool Imagen::leerImagen(const char nombreFichero[]){
		int filas, columnas;

		if (infoPGM(nombreFichero, filas, columnas) == IMG_PGM_BINARIO){
			crear(filas,columnas);
			return leerPGMBinario(nombreFichero, datos[0], nfilas, ncolumnas);
		}
			
		else if(infoPGM(nombreFichero,filas,columnas)==IMG_PGM_TEXTO){
			crear(filas,columnas);
			return leerPGMTexto (nombreFichero, datos[0], nfilas, ncolumnas);
		}
		return false;
	}
   

//Guarda la imagen en fichero.
	bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
		if(esBinario)
			return escribirPGMBinario(nombreFichero,datos[0],nfilas,ncolumnas);
		else
			return escribirPGMTexto(nombreFichero,datos[0],nfilas,ncolumnas);
	} 
//

	Imagen Imagen::plano (int k){
		Imagen plano(nfilas,ncolumnas);
		for(int i=0;i<nfilas*ncolumnas;i++){
			if(getbit(getPos(i),k)){//si el bit de la posicion k = 1, mete la constante 0x80, msb a 1 y el resto a 0
				plano.setPos(i, 0x80);//0b1000 0000
			}
			else{
				plano.setPos(i,0);//si k=0, pone todo a 0

			}
		}
		return plano;
	}

	bool Imagen::aArteASCII(const char grises[], char arteascii[], int maxlong){
		int cardinal = strlen(grises);
		int contador_char=0;
		if((filas()*columnas())+1>maxlong)
			return false;
		else{
			for (int i=0;i<filas();i++){
				for(int j=0;j<columnas();j++){
					arteascii[contador_char++]=grises[(get(i,j)*cardinal)/256];
				}
				arteascii[contador_char++] ='\n';
			}
			arteascii [contador_char] ='\0';
			return true;
		}
	}


	bool Imagen::listaAArteASCII(const Lista celdas){
		ofstream fsalida;
		const int MAXLONG = 1000000;
		char *arteascii = new char [MAXLONG];
		string cadena;
		int lon = celdas.longitud();
		if(fsalida){
			for(int i=0;i<lon;i++){

				char *grises = new char [100];
				cadena=celdas.getCelda(i);
				strcpy(grises,cadena.c_str());

				string nombre= "ArteASCII"+to_string(i+1)+".txt";

				fsalida.open(nombre);
				if(aArteASCII(grises,arteascii,MAXLONG))
					fsalida<<arteascii;

				fsalida.close();
				delete [] grises;

			}
			delete [] arteascii;
			return true;
		}
		else{
			delete[]arteascii;
			return false;
		}
	}
