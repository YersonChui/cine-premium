#include<iostream>
using namespace std;

// Estructura para gestionar productos
struct Producto {
    string nombre;
    int cantidad;
    float precio;
};

// Funciones para manejar productos y ventas
void mostrarProducto(Producto producto) {
    cout << producto.nombre << ": " << producto.cantidad << " unidades, $"
         << producto.precio << " c/u" << endl;
}

void venderProducto(Producto& producto, int cantidad_vendida) {
    if(producto.cantidad >= cantidad_vendida) {
        producto.cantidad -= cantidad_vendida;
        cout << "Vendido " << cantidad_vendida << " de " << producto.nombre
             << ". Total: $" << cantidad_vendida * producto.precio << endl;
    } else {
        cout << "No hay suficientes unidades de " << producto.nombre << " para vender." << endl;
    }
}

int main() {
    Producto palomitas = {"Palomitas", 100, 5.0}; // 100 unidades, $5 c/u
    Producto gaseosa = {"Gaseosa", 50, 3.0};  // 50 unidades, $3 c/u
    Producto maiz = {"Maíz", 200, 1.0};  // 200 unidades, $1 c/u

    int opcion, cantidad_vendida;

    while(true) {
        cout << "\nInventario:\n";
        mostrarProducto(palomitas);
        mostrarProducto(gaseosa);
        mostrarProducto(maiz);

        cout << "\nMenú de opciones:\n";
        cout << "1. Vender palomitas\n";
        cout << "2. Vender gaseosa\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Ingrese la cantidad de palomitas para vender: ";
                cin >> cantidad_vendida;
                venderProducto(palomitas, cantidad_vendida);
                break;
            case 2:
                cout << "Ingrese la cantidad de gaseosas para vender: ";
                cin >> cantidad_vendida;
                venderProducto(gaseosa, cantidad_vendida);
                break;
            case 3:
                cout << "Saliendo del sistema...\n";
                return 0;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}
