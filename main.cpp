#include "utilidades.h"
#include <iostream>

int main() {
    std::cout << "Iniciando simulaciones con diferentes valores de amortiguamiento...\n\n";
    
    runSimulations();

    std::cout << "\nTodas las simulaciones han sido completadas.\n";
    std::cout << "Puedes visualizar los resultados importando los archivos CSV generados\n";
    std::cout << "o ejecutando 'make graficar' para generar gráficas automáticamente.\n";

    return 0;
}