import matplotlib.pyplot as plt

# Datos de ejemplo
tamanos = [100, 1000, 10000, 100000, 1000000]  # Tamaños de los datos
tiempos_quick_sort = [0.001, 0.005, 0.020, 0.100, 0.500]  # Tiempos de Quick Sort
tiempos_merge_sort = [0.001, 0.004, 0.015, 0.090, 0.400]  # Tiempos de Merge Sort

# Crear el gráfico
plt.figure(figsize=(10, 6))
plt.plot(tamanos, tiempos_quick_sort, label='Quick Sort', marker='o')
plt.plot(tamanos, tiempos_merge_sort, label='Merge Sort', marker='o')

# Configurar el gráfico
plt.title('Comparación de Tiempos de Ejecución')
plt.xlabel('Tamaño del Dataset')
plt.ylabel('Tiempo de Ejecución (s)')
plt.legend()
plt.grid(True)
plt.xscale('log')  # Escala logarítmica en el eje x si los tamaños varían ampliamente
plt.yscale('log')  # Escala logarítmica en el eje y si los tiempos varían ampliamente

# Mostrar el gráfico
plt.show()
