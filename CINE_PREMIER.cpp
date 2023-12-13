#include <iostream>
#include <string.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

//Variables globales
int global_horario;
float global_total_bol;
float global_total_prod;
//Estructuras
struct Pelicula{
	char titulo[50];
    char genero[50];
    char actores[50];
    char duracion[20];
    char clasificacion[20];
    char estreno[20];
    char finalizacion[20];
    char idioma[20];
};

struct Sala{
	char nombre[50];
	int fila;
	int columna;
	int capacidad;
	char tipo[10];
};

struct Horario{
	char pelicula[50];
	char sala[50];
	char fecha[20];
	char hora[20];
	float precio;
	int capacidad;
	int disponibilidad;
	int ocupados[100];
};

struct Cliente{
	long int ci;
	char nombre[50];
};

struct Transaccion{
	char fecha_compra[20];
	int cantidad;
	int total;
};

struct Inventario{
	char producto[50];
	float precio;
	int inicial;
	int disponibilidad;
	char fecha_caducidad[20];
};

struct Promocion{
	char nombre_prom[50];
	float porc_descuento;
};

struct Venta{
	char fecha[100];
	int ci;
	float boletos;
	float productos;
};

Sala sala;
Pelicula pelicula;
Horario horario;
Transaccion transaccion;
Inventario inventario;
Promocion promocion;
Cliente cliente;
Venta venta;

//funciones peliculas
void ingresar_pelicula() {
	system("cls");
	cin.clear();
	cin.ignore();
    cout << "Ingrese el titulo: ";
    cin.getline(pelicula.titulo,50,'\n');
    cout << "Ingrese el genero: ";
    cin.getline(pelicula.genero,50,'\n');
    cout << "Ingrese los actores: ";
    cin.getline(pelicula.actores,50,'\n');
    cout << "Ingrese la duracion (HH:MM): ";
    cin>>pelicula.duracion;
    cout << "Ingrese la clasificacion por edades (age): ";
    cin>>pelicula.clasificacion;
    cout << "Ingrese la fecha de estreno (DD-MM-AA): ";
    cin>>pelicula.estreno;
    cout << "Ingrese la fecha de finalizacion (DD-MM-AA): ";
    cin>>pelicula.finalizacion;
    cout << "Ingrese el idioma: ";
    cin>>pelicula.idioma;
}

void mostrar_peliculas(void){
	system("cls");
	cout<<"\nLista de Peliculas disponibles \n"<<endl;
	int n=1;
	fstream f("peliculas.bin",ios::in|ios::binary|ios::app);
	while (f.read((char*)&pelicula,sizeof(pelicula))) {
		cout<<n<<". "<<pelicula.titulo<<endl;
		n++;
	}
	cout<<endl;
	f.close();
}

void eliminar_pelicula(int pos){
	fstream f("peliculas.bin",ios::in|ios::binary|ios::app);
	fstream g("Temporal.bin",ios::out|ios::binary|ios::app);
	int n=1;
	while(f.read((char*)&pelicula,sizeof(pelicula))){
		if(pos!=n){
			g.write((char*)&pelicula,sizeof(pelicula));
		}
		n++;
	}
	f.close();
	g.close();
	remove("peliculas.bin");
	rename("temporal.bin", "peliculas.bin");
}

//funciones salas
void ingresar_sala() {
	system("cls");
	cin.clear();
	cin.ignore();
    cout << "Ingrese el nombre de la sala: ";
    cin.getline(sala.nombre,50,'\n');
    cout << "Ingrese el numero de filas de la sala: ";
    cin>>sala.fila;
    cout << "Ingrese el numero de columnas de la sala: ";
    cin>>sala.columna;
    cin.seekg(0,ios::end);
	cin.clear();
    sala.capacidad=sala.fila*sala.columna;
    cout << "Ingrese el tipo de sala (2D/3D): ";
    cin.getline(sala.tipo,10,'\n');
}

void mostrar_salas(void){
	system("cls");
	cout<<"\nLista de Salas disponibles \n"<<endl;
	int n=1;
	fstream f("salas.bin",ios::in|ios::binary|ios::app);
	while (f.read((char*)&sala,sizeof(sala))) {
		cout<<n<<". "<<sala.nombre<<endl;
		n++;
	}
	cout<<endl;
	f.close();
}

//funciones horarios
void confirmar_horario(int index1,int index2){
	int n=1;
	fstream h("peliculas.bin",ios::in|ios::binary|ios::app);
	while (h.read((char*)&pelicula,sizeof(pelicula))) {
		if(n==index1){
		//	strcpy(horario.pelicula,pelicula.titulo);
			strncpy(horario.pelicula, pelicula.titulo, sizeof(horario.pelicula));
			break;
		}
		n++;
	}
	h.close();

	fstream f("salas.bin",ios::in|ios::binary|ios::app);
	n=1;
	while (f.read((char*)&sala,sizeof(sala))) {
		if(n==index2){
			strcpy(horario.sala,sala.nombre);
			horario.disponibilidad=sala.fila*sala.columna;
			horario.capacidad=sala.fila*sala.columna;
			break;
		}
		n++;
	}

	f.close();
	fstream g("horarios.bin",ios::out|ios::binary|ios::app);
	g.write((char*)&horario,sizeof(horario));
	g.close();
}

void ingresar_horario(){
	int index1,index2;
	float precio;
	char fecha[20],hora[20];
	mostrar_peliculas();
	cout<<"Que pelicula desea seleccionar?: ";
	cin>>index1;
	system("cls");
	mostrar_salas();
	cout<<"A que sala desea asignar la pelicula?: ";
	cin>>index2;
	system("cls");
	cout<<"Fecha de la funcion (DD-MM-AA): ";
	cin>>horario.fecha;
	cout<<"Hora de la funcion (HH-MM): ";
	cin>>horario.hora;
	cout<<"Precio de la entrada Bs.: ";
	cin>>horario.precio;
	int opcion;
	cout<<"\nGuardar los datos? 1.Si 2.No ";
	cout<<"\nOpcion: ";
	cin>>opcion;
	if(opcion==1){
		confirmar_horario(index1,index2);
		cout<<"Horario agregado con exito!"<<endl;
		Sleep(1000);
	}
}

//funciones cliente
void sala_matrix(void){
	fstream g("horarios.bin",ios::in|ios::binary|ios::app);
	int n=0;
	while (g.read((char*)&horario,sizeof(horario))) {
		if(strcmp(horario.pelicula,pelicula.titulo)==0){
			n++;
		}
		if(n==global_horario){
			break;
		}
	}
	fstream f("salas.bin",ios::in|ios::binary|ios::app);
	n=1;
	cout<<" Asientos disponibles\n"<<endl;
	while (f.read((char*)&sala,sizeof(sala))) {
		if(strcmp(sala.nombre,horario.sala)==0){
			cout<<"  ";
			for(int i=0;i<sala.columna;i++){
				cout<<i+1<<" ";
			}
			cout<<endl;
			for(int i=0;i<sala.columna;i++){
				cout<<"--";
			}
			cout<<endl;
			for(int i=0;i<sala.fila;i++){
				cout<<i+1<<"|";
				for(int j=0;j<sala.columna;j++){
					bool flag=false;
					for(int k=0;k<=(sala.fila*sala.columna-horario.disponibilidad);k++){
						if(horario.ocupados[k]==n){
							flag=true;
							break;
						}
					}
					if(flag){
						cout<<"1 ";
					}
					else{
						cout<<"0 ";
					}
					n++;
				}
				cout<<endl;
			}
			break;
		}
	}
	f.close();
	g.close();
}

void mostrar_horarios(){
	system("cls");
	int opcion;
	mostrar_peliculas();
	cout<<"De cual pelicula desea ver los horarios disponibles?: ";
	cin>>opcion;
	int n=1;
	fstream f("peliculas.bin",ios::in|ios::binary|ios::app);
	while (f.read((char*)&pelicula,sizeof(pelicula))) {
		if(n==opcion){
			system("cls");
			cout<<"Pelicula seleccionada: "<<pelicula.titulo<<endl;
			break;
		}
		n++;
	}
	fstream g("horarios.bin",ios::in|ios::binary|ios::app);

	n=1;
	while (g.read((char*)&horario,sizeof(horario))) {
		if(strcmp(pelicula.titulo,horario.pelicula)==0){
			cout<<"\nHorario "<<n<<":"<<endl;
			cout<<"Sala: "<<horario.sala<<endl;
			cout<<"Fecha: "<<horario.fecha<<endl;
			cout<<"Hora: "<<horario.hora<<endl;
			cout<<"Precio Bs. "<<horario.precio<<endl;
			cout<<"Disponibilidad de asientos: "<<horario.disponibilidad<<endl;
			cout<<endl;
			n++;
		}
	}
	f.close();
	g.close();
}

void comprar_boletos(ofstream& out, int cantidad){
	fstream g("horarios.bin",ios::in|ios::binary|ios::app);
	int n=1;
	while (g.read((char*)&horario,sizeof(horario))) {
		if(pelicula.titulo==horario.pelicula){
			n++;
		}
		if(n==global_horario){
			break;
		}
		n++;
	}
	g.close();
	//venta
	if(cantidad<=horario.disponibilidad){
		int fila,columna;
		for(int i=0;i<cantidad;i++){
			system("cls");
			sala_matrix();
			bool disponible=true;
			cout<<"\nBoleto nro. "<<i+1<<endl;
			cout<<"Fila: ";cin>>fila;
			cout<<"Columna: ";cin>>columna;
			for(int j=0;j<sala.capacidad-horario.disponibilidad;j++){
				if(horario.ocupados[j]==(fila-1)*sala.columna+columna){
					disponible=false;
					break;
				}
			}
			if(disponible){
				horario.ocupados[sala.capacidad-horario.disponibilidad]=(fila-1)*sala.columna+columna;
				cout<<"Asiento comprado con exito!"<<endl;
				Sleep(1000);
				horario.disponibilidad--;
			}
			else{
				i--;
				cout<<"Asiento ocupado!"<<endl;
				Sleep(1000);
			}
			//guardar modififaciones
			fstream f("horarios.bin",ios::in|ios::binary|ios::app);
			fstream h("Temporal.bin",ios::out|ios::binary|ios::app);
			Horario horario2;
			int n=0;
			while(f.read((char*)&horario2,sizeof(horario2))){
				if(strcmp(horario2.pelicula,horario.pelicula)==0){
					n++;
					if(n==global_horario){
						h.write((char*)&horario,sizeof(horario));
					}
					else{
						h.write((char*)&horario2,sizeof(horario2));
					}
				}
				else{
					h.write((char*)&horario2,sizeof(horario2));
				}
			}
			f.close();
			h.close();
			remove("horarios.bin");
			rename("temporal.bin", "horarios.bin");
		}
		global_total_bol+=cantidad*horario.precio;
		if(cantidad>0){
			out<<horario.pelicula<<setw(30)<<cantidad<<setw(20)<<cantidad*horario.precio<<endl;
			out<<"Sala: "<<horario.sala<<endl;
			out<<"Fecha: "<<horario.fecha<<endl;
			out<<"Hora: "<<horario.hora<<endl;
		}
	}

	else{
		cout<<"No hay suficientes asientos disponibles!"<<endl;
		Sleep(1000);
	}

}
//Funciones productos
void ingresar_inventario(void){
	system("cls");
	cin.clear();
	cin.ignore();
    cout << "Ingrese el nombre del producto: ";
    cin.getline(inventario.producto,50,'\n');
    cout << "Ingrese el precio del producto (Bs.): ";
    cin>>inventario.precio;
    cout << "Ingrese la cantidad disponible del producto (unidades): ";
    cin>>inventario.disponibilidad;
    inventario.inicial=inventario.disponibilidad;
    cin.seekg(0,ios::end);
	cin.clear();
    cout << "Ingrese la fecha de caducidad del producto (DD-MM-AA): ";
    cin.getline(inventario.fecha_caducidad,20,'\n');
}

void mostrar_inventario(bool flag){
	system("cls");
	cout<<"\nLista de productos disponibles \n"<<endl;
	int n=1;
	fstream f("inventario.bin",ios::in|ios::binary|ios::app);
	while (f.read((char*)&inventario,sizeof(inventario))) {
		cout<<n<<". "<<inventario.producto<<endl;
		cout<<"\tPrecio Bs. : "<<inventario.precio<<endl;
		if(flag){
			cout<<"\tCantidad: "<<inventario.disponibilidad<<endl;
			cout<<"\tCaducidad: "<<inventario.fecha_caducidad<<endl;
		}
		n++;
	}
	cout<<endl;
	f.close();
}

void eliminar_inventario(int pos){
	fstream f("inventario.bin",ios::in|ios::binary|ios::app);
	fstream g("Temporal.bin",ios::out|ios::binary|ios::app);
	int n=1;
	while(f.read((char*)&inventario,sizeof(inventario))){
		if(pos!=n){
			g.write((char*)&inventario,sizeof(inventario));
		}
		n++;
	}
	f.close();
	g.close();
	remove("inventario.bin");
	rename("temporal.bin", "inventario.bin");
}

//funciones cliente
void verificar_cliente(long int ci){
	bool flag=false;
	fstream f("clientes.bin",ios::in|ios::binary|ios::app);
	while (f.read((char*)&cliente,sizeof(cliente))) {
		if(cliente.ci==ci){
			flag=true;
			break;
		}
	}
	f.close();

	if(flag){
		cout<<"Nombre: "<<cliente.nombre<<endl;
		cout<<"Cliente registrado\n"<<endl;
	}
	else{
		cout<<"Ingrese su nombre: ";
		cin.clear();
		cin.ignore();
		cin.getline(cliente.nombre,50,'\n');
		cliente.ci=ci;
		fstream g("clientes.bin",ios::out|ios::binary|ios::app);
		g.write((char*)&cliente,sizeof(cliente));
		g.close();
		cout<<"\nCliente nuevo registrado\n"<<endl;
	}
}

void comprar_producto(ofstream& out, int prod_num){
	fstream g("inventario.bin",ios::in|ios::binary|ios::app);
	int n=1;
	while (g.read((char*)&inventario,sizeof(inventario))) {
		if(n==prod_num){
			break;
		}
		n++;
	}
	g.close();
	//venta
	cout<<"Cuantas unidades quiere? : ";
	int cantidad;
	cin>>cantidad;
	if(cantidad<=inventario.disponibilidad){
		inventario.disponibilidad-=cantidad;
		cout<<"Producto añadido a la compra!"<<endl;
		fstream f("inventario.bin",ios::in|ios::binary|ios::app);
		fstream h("Temporal.bin",ios::out|ios::binary|ios::app);
		Inventario inventario2;
		int n=1;
		while(f.read((char*)&inventario2,sizeof(inventario2))){
			if(prod_num!=n){
				h.write((char*)&inventario2,sizeof(inventario2));
			}
			else{
				h.write((char*)&inventario,sizeof(inventario));
			}
			n++;
		}
		f.close();
		h.close();
		remove("inventario.bin");
		rename("temporal.bin", "inventario.bin");
		global_total_prod+=cantidad*inventario.precio;
		if(cantidad>0){
			out<<inventario.producto<<setw(30)<<cantidad<<setw(20)<<cantidad*inventario.precio<<endl;
		}
	}
	else{
		cout<<"No hay suficientes asientos disponibles!"<<endl;
	}

}

//Funciones ventas
void ventas_totales(void){
	cout<<"  REPORTE DE VENTAS\n"<<endl;
	fstream f("ventas.bin",ios::in|ios::binary|ios::app);
	int n=1;
	float boletos=0,productos=0;
	while(f.read((char*)&venta,sizeof(venta))){
		boletos+=venta.boletos;
		productos+=venta.productos;
	}
	f.close();
	cout<<"Ventas totales en boletos (Bs.) : "<<boletos<<endl;
	cout<<"Ventas totales en productos (Bs.) : "<<productos<<endl;
	cout<<"\nINGRESO TOTAL (Bs.) : "<<boletos+productos<<endl;
}

void ranking(void){
	cout<<"Ingresos por peliculas: \n"<<endl;
	fstream f("peliculas.bin",ios::in|ios::binary|ios::app);
	int n=1;
	float min=10000000,max=0;
	char min_t[50],max_t[50];
	while(f.read((char*)&pelicula,sizeof(pelicula))){
		float total=0;
		fstream g("horarios.bin",ios::in|ios::binary|ios::app);
		while(g.read((char*)&horario,sizeof(horario))){
			if(strcmp(pelicula.titulo,horario.pelicula)==0){
				total+=horario.precio*(horario.capacidad-horario.disponibilidad);
			}
		}
		if(total<=min){
			min=total;
			strcpy(min_t,pelicula.titulo);
		}
		if(total>=max){
			max=total;
			strcpy(max_t,pelicula.titulo);
		}
		cout<<n<<". "<<pelicula.titulo<<": "<<total<<" Bs."<<endl;
		g.close();
		n++;
	}
	cout<<"\nPelicula mas vendida: "<<max_t<<endl;
	cout<<"Pelicula menos vendida: "<<min_t<<endl;
	f.close();
}

void proyeccion(){
	fstream f("ventas.bin",ios::in|ios::binary|ios::app);
	int n=0;
	char fecha[100];
	float total1=0,total2=0;
	while(f.read((char*)&venta,sizeof(venta))){
		if(strcmp(fecha,venta.fecha)!=0){
			strcpy(fecha,venta.fecha);
			n++;
		}
		total1+=venta.boletos;
		total2+=venta.productos;
	}
	if(n!=0){
		cout<<"PROYECCIONES\n"<<endl;
		cout<<"Promedio venta diaria de boletos Bs. "<<total1/n<<endl;
		cout<<"Promedio venta diaria de productos Bs. "<<total2/n<<endl;
		fstream g("inventario.bin",ios::in|ios::binary|ios::app);
		while(g.read((char*)&inventario,sizeof(inventario))){
			int prom=(inventario.inicial-inventario.disponibilidad)/n;
			if(prom>0){
				cout<<"\nPromedio venta diaria de unidades de "<<inventario.producto<<": "<<prom<<endl;
				cout<<"Se estima que en "<<int(inventario.disponibilidad/prom)<<" dias se acabara el producto"<<endl;
			}
		}
		g.close();
	}
	else{
		cout<<"No hay datos!"<<endl;
	}
	f.close();
}

//MENUS
void menu6(void){
	fstream h("ventas.bin",ios::out|ios::binary|ios::app);
	global_total_bol=0;
	global_total_prod=0;
	ofstream out;
	remove("Factura.txt");
	out.open("Factura.txt",ios::app);
	out<<setw(30)<<"FACTURA"<<endl;
	out<<setw(30)<<"CINE PREMIER"<<endl;
	//Tiempo actual
	auto tiempoActual = chrono::system_clock::to_time_t(chrono::system_clock::now());
	char fechaHora[100];
    strftime(fechaHora, sizeof(fechaHora), "%Y-%m-%d %H:%M:%S", localtime(&tiempoActual));
    strftime(venta.fecha, sizeof(venta.fecha), "%Y-%m-%d", localtime(&tiempoActual));

    out<<endl<<fechaHora<<endl;
	out<<"\nProductos"<<setw(30)<<"Cantidad"<<setw(20)<<"Total (Bs)"<<endl;
	bool salir=false;
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Comprar boletos"<<endl;
		cout<<"2. Comprar produtos"<<endl;
		cout<<"3. Generar factura"<<endl;
		int opcion;
		cout<<"\nOpcion:  ";
		cin>>opcion;
		switch (opcion){
			case 1: {
				mostrar_horarios();
				cout<<"Cual horario desea elegir? : ";
				cin>>global_horario;
				system("cls");
				sala_matrix();
				cout<<"\nCuantos boletos desea comprar?"<<endl;
				cin>>opcion;
				comprar_boletos(out, opcion);
				system("cls");
				cout<<"Las compras fueron registradas en la factura exitosamente!"<<endl;
				Sleep(2000);
				break;
			}
			case 2:{
				mostrar_inventario(false);
				cout<<"\nDesea comprar algun producto? "<<endl;
				cout<<"1.Si 2.No"<<endl;
				cin>>opcion;
				while(opcion==1){
					int prod_num;
					system("cls");
					mostrar_inventario(false);
					cout<<"Cual producto quiere comprar? : ";
					cin>>prod_num;
					comprar_producto(out,prod_num);
					cout<<"\nQuiere comprar mas productos?"<<endl;
					cout<<"1.Si 2.No"<<endl;
					cin>>opcion;
				}
				system("cls");
				cout<<"Las compras fueron registradas en la factura exitosamente!"<<endl;
				Sleep(3000);
				break;
			}
			case 3:{
				long int ci;
				system("cls");
				cout<<"Ingrese su CI: ";
				cin>>ci;
				verificar_cliente(ci);
				out<<"Total (Bs.)"<<setw(50)<<global_total_prod+global_total_bol<<setw(20)<<endl;
				out<<"\nNombre: "<<cliente.nombre<<endl;
				out<<"CI/NIT: "<<cliente.ci<<endl;
				cout<<"Factura Generada!"<<endl;
				Sleep(3000);
				out.close();
				//registrar venta
				venta.ci=cliente.ci;
				venta.boletos=global_total_bol;
				venta.productos=global_total_prod;
				h.write((char*)&venta,sizeof(venta));
				h.close();
				salir=true;
				break;
			}
			default: {
				cout<<"Opcion incorrecta!";
				Sleep(1000);
				break;
			}

		}
		if(salir){
			break;
		}
	}
}

void menu5(void){
	bool salir=false;
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Ver Cartelera y horarios"<<endl;
		cout<<"2. Comprar produtos"<<endl;
		cout<<"3. Salir"<<endl;
		int opcion;
		cout<<"\nOpcion:  ";
		cin>>opcion;
		switch (opcion){
			case 1: {
				mostrar_horarios();
				system("pause");
				break;
			}
			case 2:{
				menu6();
				break;
			}
			case 3:{
				salir=true;
				break;
			}
			default: {
				cout<<"Opcion incorrecta!";
				Sleep(1000);
				break;
			}

		}
		if(salir){
			break;
		}
	}
}

void menu4(void){
	bool salir=false;
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Ver ingresos totales"<<endl;
		cout<<"2. Ver ranking de peliculas"<<endl;
		cout<<"3. Ver proyecciones"<<endl;
		cout<<"4. Salir"<<endl;
		int opcion;
		cout<<"\nOpcion:  ";
		cin>>opcion;
		switch (opcion){
			case 1:{
				system("cls");
				ventas_totales();
				cout<<endl;
				system("pause");
				break;
			}
			case 2:{
				system("cls");
				ranking();
				cout<<endl;
				system("pause");
				break;
			}
			case 3:{
				system("cls");
				proyeccion();
				cout<<endl;
				system("pause");
				break;
			}
			case 4:{
				salir=true;
				break;
			}
			default:{

				break;
			}
		}
		if(salir){
			break;
		}
	}
}

void menu3(void){
	bool salir=false;
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Ver productos disponibles"<<endl;
		cout<<"2. Agregar producto"<<endl;
		cout<<"3. Eliminar producto"<<endl;
		cout<<"4. Salir"<<endl;
		int opcion;
		cout<<"\nOpcion:  ";
		cin>>opcion;
		switch (opcion){
			case 1:{
				mostrar_inventario(true);
				system("pause");
				break;
			}
			case 2:{
				ingresar_inventario();
				cout<<"\nGuardar los datos? 1.Si 2.No ";
				cout<<"\nOpcion: ";
				cin>>opcion;
				if(opcion==1){
					fstream g("inventario.bin",ios::out|ios::binary|ios::app);
					g.write((char*)&inventario,sizeof(inventario));
					g.close();
					cout<<"Producto agregado con exito!"<<endl;
					Sleep(1000);
					break;
				}
			}
			case 3:{
				mostrar_inventario(true);
				cout<<"Cual producto desea eliminar?"<<endl;
				cout<<"\nopcion: ";
				cin>>opcion;
				eliminar_inventario(opcion);
				cout<<"Producto eliminado con exito!"<<endl;
				Sleep(1000);
				break;
			}
			case 4:{
				salir=true;
				break;
			}
		}

		if(salir){
			break;
		}
	}
}

void menu2(void){
	bool salir=false;
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Mostrar salas de cine"<<endl;
		cout<<"2. Agregar sala de cine"<<endl;
		cout<<"3. Asignar horario a pelicula"<<endl;
		cout<<"4. Salir"<<endl;
		int opcion;
		cout<<"\nOpcion:  ";
		cin>>opcion;
		switch (opcion){
			case 1:{
				mostrar_salas();
				cout<<endl;
				system("pause");
				break;
			}
			case 2: {
				ingresar_sala();
				cout<<"\nGuardar los datos? 1.Si 2.No ";
				cout<<"\nOpcion: ";
				cin>>opcion;
				if(opcion==1){
					fstream g("salas.bin",ios::out|ios::binary|ios::app);
					g.write((char*)&sala,sizeof(sala));
					g.close();
					cout<<"Sala agregada con exito!"<<endl;
					Sleep(1000);
				}
				break;
			}
			case 3:{
				ingresar_horario();
				break;
			}
			case 4:{
				salir=true;
				break;
			}
			default: {
				cout<<"Opcion incorrecta!";
				Sleep(1000);
				break;
			}

		}
		if(salir){
			break;
		}
	}
}

void menu1(void){
	bool salir=false;
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Mostrar peliculas disponibles"<<endl;
		cout<<"2. Agregar pelicula"<<endl;
		cout<<"3. Eliminar pelicula"<<endl;
		cout<<"4. Salir"<<endl;
		int opcion;
		cout<<"\nOpcion: ";
		cin>>opcion;
		switch (opcion){
			case 1:{
				mostrar_peliculas();
				cout<<endl;
				system("pause");
				break;
			}
			case 2: {
				ingresar_pelicula();
				cout<<"\nGuardar los datos? 1.Si 2.No ";
				cout<<"\nOpcion: ";
				cin>>opcion;
				if(opcion==1){
					fstream g("peliculas.bin",ios::out|ios::binary|ios::app);
					g.write((char*)&pelicula,sizeof(pelicula));
					g.close();
					cout<<"Pelicula agregada con exito!"<<endl;
					Sleep(1000);
				}
				break;
			}
			case 3:{
				mostrar_peliculas();
				cout<<"Cual pelicula desea eliminar?"<<endl;
				cout<<"\nopcion: ";
				cin>>opcion;
				eliminar_pelicula(opcion);
				cout<<"Pelicula eliminada con exito!"<<endl;
				Sleep(1000);
				break;
			}
			case 4:{
				salir=true;
				break;
			}
			default: {
				cout<<"Opcion incorrecta!";
				Sleep(1000);
				break;
			}

		}
		if(salir){
			break;
		}
	}
}

int main(){
	for(;true;){
		system("cls");
		cout<<"CINE PREMIER :\n"<<endl;
		cout<<"1. Gestionar peliculas"<<endl;
		cout<<"2. Gestionar salas de cine"<<endl;
		cout<<"3. Gestionar inventario"<<endl;
		cout<<"4. Gestionar finanzas"<<endl;
		cout<<"5. Venta a cliente"<<endl;
		cout<<"6. Salir "<<endl;
		int opcion;
		cout<<"\nOpcion: ";
		cin>>opcion;
		switch (opcion){
			case 1:{
				menu1();
				break;
			}
			case 2:{
				menu2();
				break;
			}
			case 3:{
				menu3();
				break;
			}
			case 4:{
				menu4();
				break;
			}
			case 5:{
				menu5();
				break;
			}
			case 6:{
				exit(0);
			}
			default: {
				cout<<"Opcion incorrecta!";
				Sleep(1000);
				break;
			}
		}
	}
	return 0;
}
