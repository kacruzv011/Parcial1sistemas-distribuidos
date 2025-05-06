#include "utilidades.h"
#include "simulacion.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>

void simulateAndSave(HarmonicOscillator& system, 
                    double dt, int steps, 
                    const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    // Pre-cálculo de valores constantes
    const double inv_mass = 1.0 / system.getMass();
    
    // Reservar espacio aproximado
    outfile << "time,position,velocity\n";
    outfile.precision(6);
    outfile.setf(std::ios::fixed);
    
    for (int i = 0; i < steps; ++i) {
        system.updateEulerCromer(dt);
        outfile << system.getTime() << ","
               << system.getPosition() << ","
               << system.getVelocity() << "\n";  // Usamos \n en lugar de endl
    }
    outfile.close();
}

void runSimulations() {
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // Parámetros constantes
    const double mass = 1.0;
    const double springConstant = 10.0;
    const double forceAmplitude = 2.0;
    const double forceFrequency = 3.0;
    const double dt = 0.01;
    const int simulationSteps = 3000;

    std::vector<double> dampingValues = {0.5, 1.0, 2.0};

    for (double damping : dampingValues) {
        HarmonicOscillator system(mass, damping, springConstant, 
                                forceAmplitude, forceFrequency);

        std::string filename = "oscillator_data_c_" + 
                              std::to_string(static_cast<int>(damping*10)) + 
                              ".csv";
        
        simulateAndSave(system, dt, simulationSteps, filename);

        std::cout << "Simulación completada para c = " << damping << " Ns/m\n";
        std::cout << "Datos guardados en: " << filename << "\n\n";
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "\nTiempo total de simulación: " << duration.count() << " ms\n";
}