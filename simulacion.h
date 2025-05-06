#ifndef SIMULACION_H
#define SIMULACION_H

class HarmonicOscillator {
public:
    HarmonicOscillator(double mass, double damping, double springConstant, 
                      double forceAmplitude, double forceFrequency);

    void updateEulerCromer(double dt);
    void reset();

    // Métodos de acceso
    double getPosition() const { return x; }
    double getVelocity() const { return v; }
    double getTime() const { return t; }
    double getDamping() const { return c; }
    double getMass() const { return m; }

private:
    double m;    // Masa (kg)
    double c;    // Coeficiente de amortiguamiento (Ns/m)
    double k;    // Constante del resorte (N/m)
    double F0;   // Amplitud de la fuerza externa (N)
    double w;    // Frecuencia angular de la fuerza externa (rad/s)
    double x;    // Posición (m)
    double v;    // Velocidad (m/s)
    double t;    // Tiempo actual (s)
};

#endif // SIMULACION_H