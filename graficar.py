import matplotlib.pyplot as plt
import pandas as pd
import os
from datetime import datetime
import matplotlib as mpl

# Configuración estética
mpl.style.use('ggplot')  # o usa 'bmh', 'classic', 'default', etc.

mpl.rcParams['figure.figsize'] = [12, 6]
mpl.rcParams['font.size'] = 12
mpl.rcParams['axes.grid'] = True
mpl.rcParams['grid.alpha'] = 0.3

def leer_datos(archivo):
    """Lee archivo CSV y devuelve DataFrame con los datos"""
    try:
        df = pd.read_csv(archivo)
        if not {'time', 'position', 'velocity'}.issubset(df.columns):
            raise ValueError("El archivo no tiene las columnas esperadas")
        return df
    except Exception as e:
        print(f"Error leyendo {archivo}: {str(e)}")
        return None

def graficar_simulacion(df, damping_value, output_dir="graficas"):
    """Genera y guarda gráficas para una simulación"""
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))
    
    # Gráfica de posición
    ax1.plot(df['time'], df['position'], 'b-', linewidth=1.5)
    ax1.set_title(f"Posición vs Tiempo (c = {damping_value} Ns/m)")
    ax1.set_ylabel("Posición (m)")
    
    # Gráfica de velocidad
    ax2.plot(df['time'], df['velocity'], 'r-', linewidth=1.5)
    ax2.set_title(f"Velocidad vs Tiempo (c = {damping_value} Ns/m)")
    ax2.set_xlabel("Tiempo (s)")
    ax2.set_ylabel("Velocidad (m/s)")
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/simulacion_c_{damping_value}.png", dpi=300)
    plt.close()

def graficar_comparativa(archivos):
    """Genera gráfica comparativa de todas las simulaciones"""
    plt.figure(figsize=(12, 6))
    
    for archivo in archivos:
        damping_value = float(archivo.split('_c_')[1].split('.')[0]) / 10
        df = pd.read_csv(archivo)
        plt.plot(df['time'], df['position'], 
                linewidth=1.5,
                label=f'c = {damping_value} Ns/m')
    
    plt.title("Comparación de Posición vs Tiempo")
    plt.xlabel("Tiempo (s)")
    plt.ylabel("Posición (m)")
    plt.legend()
    plt.tight_layout()
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    plt.savefig(f"graficas/comparativa_{timestamp}.png", dpi=300)
    plt.close()

def main():
    archivos_simulacion = sorted([f for f in os.listdir() 
                                if f.startswith('oscillator_data_c_') and f.endswith('.csv')])
    
    if not archivos_simulacion:
        print("No se encontraron archivos de simulación (.csv)")
        return
    
    print(f"Procesando {len(archivos_simulacion)} archivos de simulación...")
    
    # Procesar cada archivo individualmente
    for archivo in archivos_simulacion:
        damping_value = float(archivo.split('_c_')[1].split('.')[0]) / 10
        df = leer_datos(archivo)
        if df is not None:
            graficar_simulacion(df, damping_value)
    
    # Gráfica comparativa
    graficar_comparativa(archivos_simulacion)
    
    print("\nGráficas generadas exitosamente en el directorio 'graficas/'")

if __name__ == "__main__":
    main()