#include <iostream>

using namespace std;

const int MAX_FILAS = 10; // Número máximo de orígenes
const int MAX_COLUMNAS = 10; // Número máximo de destinos

struct Celda {
    int costo;
    int asignado;
};

void imprimirTabla(Celda tabla[MAX_FILAS][MAX_COLUMNAS], int oferta[MAX_FILAS], int demanda[MAX_COLUMNAS], int FILAS, int COLUMNAS) {
    cout << "\033[1;37mTabla de Asignacion:\033[0m\n";
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tabla[i][j].asignado > 0) {
                cout << "\033[1;32m" << tabla[i][j].asignado << "\033[0m\t";
            } else {
                cout << tabla[i][j].asignado << "\t";
            }
        }
        cout << "| \033[1;36m" << oferta[i] << "\033[0m" << endl;
    }
    for (int j = 0; j < COLUMNAS; j++) {
        cout << "\033[1;36m" << demanda[j] << "\033[0m\t";
    }
    cout << endl;
}

void imprimirIteracion(int iteracion, Celda tabla[MAX_FILAS][MAX_COLUMNAS], int oferta[MAX_FILAS], int demanda[MAX_COLUMNAS], int FILAS, int COLUMNAS) {
    cout << "\033[1;34mIteracion " << iteracion << ":\033[0m\n";
    imprimirTabla(tabla, oferta, demanda, FILAS, COLUMNAS);
    cout << "----------------------------------------\n";
}

void asignar(Celda tabla[MAX_FILAS][MAX_COLUMNAS], int oferta[MAX_FILAS], int demanda[MAX_COLUMNAS], int FILAS, int COLUMNAS) {
    int iteracion = 1;
    for (int j = 0; j < COLUMNAS; j++) {
        while (demanda[j] > 0) {
            int minCosto = 999999;
            int minFila = -1;

            for (int i = 0; i < FILAS; i++) {
                if (oferta[i] > 0 && tabla[i][j].costo < minCosto) {
                    minCosto = tabla[i][j].costo;
                    minFila = i;
                }
            }

            if (minFila == -1) break;

            int asignacion = (oferta[minFila] < demanda[j]) ? oferta[minFila] : demanda[j];
            tabla[minFila][j].asignado = asignacion;
            oferta[minFila] -= asignacion;
            demanda[j] -= asignacion;

            imprimirIteracion(iteracion, tabla, oferta, demanda, FILAS, COLUMNAS);
            iteracion++;
        }
    }
}

int main() {
    int FILAS, COLUMNAS;

    // Solicitar el tamaño de la matriz
    cout << "\033[1;33mIngrese el numero de origenes (filas, max 10):\033[0m ";
    cin >> FILAS;
    cout << "\033[1;33mIngrese el numero de destinos (columnas, max 10):\033[0m ";
    cin >> COLUMNAS;

    if (FILAS > MAX_FILAS || COLUMNAS > MAX_COLUMNAS) {
        cout << "\033[1;31mEl tamaño excede el límite permitido.\033[0m" << endl;
        return 1;
    }

    Celda tabla[MAX_FILAS][MAX_COLUMNAS];
    int costos[MAX_FILAS][MAX_COLUMNAS];
    int oferta[MAX_FILAS];
    int demanda[MAX_COLUMNAS];

    // Solicitar costos
    cout << "\033[1;33mIngrese los costos de transporte (solo numeros positivos):\033[0m" << endl;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << "Costo de origen " << i + 1 << " a destino " << j + 1 << ": ";
            cin >> costos[i][j];
            if (costos[i][j] < 0) {
                cout << "\033[1;31mNo se aceptan numeros negativos\033[0m" << endl;
                return 1;
            }
        }
    }

    // Solicitar oferta
    cout << "\033[1;33mIngrese las ofertas de cada origen:\033[0m" << endl;
    for (int i = 0; i < FILAS; i++) {
        cout << "Oferta de origen " << i + 1 << ": ";
        cin >> oferta[i];
    }

    // Solicitar demanda
    cout << "\033[1;33mIngrese las demandas de cada destino:\033[0m" << endl;
    for (int j = 0; j < COLUMNAS; j++) {
        cout << "Demanda de destino " << j + 1 << ": ";
        cin >> demanda[j];
    }

    // Inicializar la tabla de asignaciones con los costos ingresados
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tabla[i][j].costo = costos[i][j];
            tabla[i][j].asignado = 0;
        }
    }

    asignar(tabla, oferta, demanda, FILAS, COLUMNAS);

    imprimirTabla(tabla, oferta, demanda, FILAS, COLUMNAS);

    return 0;
}
