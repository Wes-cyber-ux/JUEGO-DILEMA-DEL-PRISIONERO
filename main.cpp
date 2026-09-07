#include <iostream>
#include "prisionero.h"
using namespace std;

int main() {

    int op;

    do {

        system("clear");

        cout << "====== JUEGO DILEMA DEL PRISIONERO ======\n\n";
        cout << "1.- Opcion 1\n";
        cout << "2.- Opcion 2\n";
        cout << "3.- Opcion 3\n";
        cout << "4.- Opcion 4\n";
        cout << "5.- Opcion 5\n";
        cout << "6.- Opcion 6\n";
        cout << "0.- SALIR DEL JUEGO\n";

        cout << "\nIngrese la opcion: ";
        cin >> op;

        cin.ignore();

        system("clear");

        switch(op) {

            case 1:
                cout << "====================\n";
                cout << "    ESTRATEGIA 1\n";
                cout << "====================\n";
                break;

            case 2:
                cout << "====================\n";
                cout << "    ESTRATEGIA 2\n";
                cout << "====================\n";
                break;

            case 3:
                cout << "====================\n";
                cout << "    ESTRATEGIA 3\n";
                cout << "====================\n";
                break;

            case 4:
                cout << "====================\n";
                cout << "    ESTRATEGIA 4\n";
                cout << "====================\n";
                break;

            case 5:
                cout << "====================\n";
                cout << "    ESTRATEGIA 5\n";
                cout << "====================\n";
                break;

            case 6:
                cout << "====================\n";
                cout << "    ESTRATEGIA 6\n";
                cout << "====================\n";
                break;

            case 0:
                cout << "Saliendo del juego...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

        if (op != 0) {
            cout << "\nPresiona ENTER para volver al menu...";
            cin.get();
        }

    } while (op != 0);

    return 0;
}