import matplotlib.pyplot as plt
import numpy as np

# Datos
matrix_size = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
cubic_traditional = [103621, 861440, 3001626, 7490054, 14903851, 25929048, 42539898, 64795352, 104267044, 140780377]
cubic_optimized = [106695, 839696, 2826284, 6673860, 13111699, 22428402, 35668175, 53260019, 76038112, 105222654]
strassen = [2338419, 16404942, 106105710, 115111299, 117690336, 740134172, 775449309, 805853042, 875237307, 823563924]

# Crear el gráfico
plt.figure(figsize=(12, 8))
plt.plot(matrix_size, np.cbrt(cubic_traditional), marker='o', label='Cúbico Tradicional (Escala Cúbica)')
plt.plot(matrix_size, np.cbrt(cubic_optimized), marker='s', label='Cúbico Optimizado (Escala Cúbica)')
plt.plot(matrix_size, np.cbrt(strassen), marker='^', label='Strassen (Escala Cúbica)')

plt.title('Comparación de Algoritmos de Multiplicación de Matrices')
plt.xlabel('Tamaño de Matriz (n x n)')
plt.ylabel('Tiempo (microsegundos) (Escala Cúbica)')
plt.legend()
plt.grid(True)

plt.show()




