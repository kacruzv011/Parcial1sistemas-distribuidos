#include "utilidades.h"
#include "simulacion.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>  // Para std::setprecision

void simulateAndSave(HarmonicOscillator& system, 
                    double dt, int steps, 
                    const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    // Configuración de precisión para el archivo de salida
    outfile << "time,position,velocity\n";
    outfile << std::fixed << std::setprecision(6);

    // Pre-cálculo de valores constantes
    const double inv_mass = 1.0 / system.getMass();
    
    for (int i = 0; i < steps; ++i) {
        system.updateEulerCromer(dt);
        outfile << system.getTime() << ","
               << system.getPosition() << ","
               << system.getVelocity() << "\n";
    }
    outfile.close();
}

void runSimulations() {
    // Encabezado de presentación
    std::cout << "=============================================\n";
    std::cout << "  SIMULACIÓN DE OSCILADOR ARMÓNICO FORZADO\n";
    std::cout << "=============================================\n\n";
    
    // Parámetros constantes
    const double mass = 1.0;
    const double springConstant = 10.0;
    const double forceAmplitude = 2.0;
    const double forceFrequency = 3.0;
    const double dt = 0.01;
    const int simulationSteps = 10000;

    // Valores de amortiguamiento a probar
    std::vector<double> dampingValues = {0.5, 1.0, 2.0};
    
    // Vector para almacenar resultados temporales
    std::vector<std::pair<double, double>> executionTimes; // (damping, time_ms)

    std::cout << "Parámetros de simulación:\n";
    std::cout << "- Masa: " << mass << " kg\n";
    std::cout << "- Constante de resorte: " << springConstant << " N/m\n";
    std::cout << "- Fuerza externa: " << forceAmplitude << " cos(" << forceFrequency << "t) N\n";
    std::cout << "- Paso temporal: " << dt << " s\n";
    std::cout << "- Pasos de simulación: " << simulationSteps << "\n\n";
    
    std::cout << "Iniciando simulaciones...\n";
    std::cout << "---------------------------------------------\n";
    std::cout << std::setw(10) << "c (Ns/m)" << std::setw(20) << "Tiempo (ms)\n";
    std::cout << "---------------------------------------------\n";

    for (double damping : dampingValues) {
        // Inicio de medición de tiempo
        auto start = std::chrono::high_resolution_clock::now();
        
        // Configuración del sistema
        HarmonicOscillator system(mass, damping, springConstant, 
                                forceAmplitude, forceFrequency);

        // Generación de nombre de archivo
        std::string filename = "oscillator_data_c_" + 
                             std::to_string(static_cast<int>(damping*10)) + 
                             ".csv";
        
        // Ejecución de la simulación
        simulateAndSave(system, dt, simulationSteps, filename);
        
        // Fin de medición de tiempo
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double time_ms = duration.count() / 1000.0;
        
        // Almacenamiento de resultados
        executionTimes.emplace_back(damping, time_ms);
        
        // Mostrar resultados en consola
        std::cout << std::setw(10) << damping 
                 << std::setw(20) << std::setprecision(3) << time_ms << "\n";
    }

    // Guardar tiempos en archivo
    std::ofstream timeFile("execution_times.csv");
    timeFile << "damping(Ns/m),time(ms)\n";
    for (const auto& [damping, time] : executionTimes) {
        timeFile << damping << "," << time << "\n";
    }
    timeFile.close();

    // Resumen final
    std::cout << "---------------------------------------------\n";
    std::cout << "Simulaciones completadas correctamente.\n";
    std::cout << "Datos de tiempo guardados en 'execution_times.csv'\n\n";
    
    // Análisis de tiempos
    double totalTime = 0;
    for (const auto& [_, time] : executionTimes) {
        totalTime += time;
    }
    
    std::cout << "Resumen estadístico:\n";
    std::cout << "- Tiempo total: " << totalTime << " ms\n";
    std::cout << "- Tiempo promedio por simulación: " << totalTime/dampingValues.size() << " ms\n";
}