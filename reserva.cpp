#include <iostream>
#include <iomanip> // Para usar setw()
using namespace std;

const int num_filas = 5;
const int num_asientos = 5;

void mostrarSala(char sala[num_filas][num_asientos]) {
    cout << "\n   Pantalla\n";
    cout << "  ";
    for(int j = 0; j < num_asientos; j++) {
        cout << " " << j + 1 << " ";
    }
    cout << "\n";
    for(int i = 0; i < num_filas; i++) {
        cout << i + 1 << " ";
        for(int j = 0; j < num_asientos; j++) {
            cout << "[" << sala[i][j] << "]";
        }
        cout << "\n";
    }
    cout << "\nD = Asiento Disponible, R = Asiento Reservado\n";
}

bool reservarAsiento(char sala[num_filas][num_asientos], int fila, int asiento) {
    if(sala[fila][asiento] == 'D') {
        char confirmar;
        cout << "¿Desea confirmar la reserva del asiento " << fila + 1 << "-" << asiento + 1 << "? (y/n): ";
        cin >> confirmar;
        if(confirmar == 'y' || confirmar == 'Y') {
            sala[fila][asiento] = 'R';
            cout << "¡Reserva completada con éxito!\n";
            return true;
        } else {
            cout << "Reserva cancelada.\n";
            return false;
        }
    } else {
        cout << "Asiento ya reservado o no existente, por favor elige otro.\n";
        return false;
    }
}

int main() {
    char sala[num_filas][num_asientos] = { {'D', 'D', 'D', 'D', 'D'},
                                           {'D', 'D', 'D', 'D', 'D'},
                                           {'D', 'D', 'D', 'D', 'D'},
                                           {'D', 'D', 'D', 'D', 'D'},
                                           {'D', 'D', 'D', 'D', 'D'}};

    int n;

    cout << "¡Bienvenido al sistema de reserva de asientos del Cine!\n";
    mostrarSala(sala);

    cout << "Ingrese el número de personas que desean reservar un asiento: ";
    cin >> n;

    if(n <= 0 || n > num_filas * num_asientos) {
        cout << "Número de personas no válido.\n";
        return 1;
    }

    for(int i = 0; i < n; i++) {
        int fila, asiento;
        cout << "\nReserva para la persona " << i + 1 << ":\n";
        cout << "Ingrese la fila del asiento que desea reservar: ";
        cin >> fila;
        cout << "Ingrese el número del asiento que desea reservar: ";
        cin >> asiento;

        fila--;
        asiento--;

        if(reservarAsiento(sala, fila, asiento)) {
            mostrarSala(sala);
        } else {
            i--; // Intenta de nuevo con la misma persona
        }
    }

    cout << "Gracias por utilizar nuestro sistema de reservas.\n";
    return 0;
}
