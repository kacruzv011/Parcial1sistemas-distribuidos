# Parcial 1 - Sistemas Distribuidos  
**Programa de Física**  
*Universidad Distrital Francisco José de Caldas*

## 1. Descripción del Proyecto

Este repositorio contiene la solución al primer parcial de Sistemas Distribuidos, donde se implementa una simulación numérica de un oscilador armónico amortiguado con fuerza externa periódica:
mẍ + cẋ + kx = F₀cos(ωt)

El proyecto demuestra:
- Implementación de métodos numéricos (Euler-Cromer)
- Técnicas de optimización de código
- Generación automatizada de resultados
- Análisis físico de sistemas dinámicos

## 2. Tecnologías Utilizadas

- **Lenguaje**: C++17 (simulación núcleo)
- **Visualización**: Python 3 con Matplotlib
- **Build System**: Makefile
- **Documentación**: LaTeX (informe científico)

## 3. Estructura del Proyecto
/proyecto_parcial/

├── include/ # Headers (.h)

├── src/ # Código fuente (.cpp)

├── graficas/ # Resultados gráficos

├── informe/ # Documentación LaTeX

├── Makefile # Sistema de construcción

└── graficar.py # Script de visualización

## 4. Instalación y Ejecución

1. Clonar repositorio:
   ```bash
   git clone [URL_DEL_REPOSITORIO]
   cd proyecto_parcial
   make full  # Compila, ejecuta y genera gráficas
   make       # Solo compilación
   make run   # Ejecutar simulación
   make clean # Limpiar archivos generados
