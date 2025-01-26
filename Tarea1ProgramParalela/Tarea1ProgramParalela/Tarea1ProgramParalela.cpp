// Tarea1ProgramParalela.cpp 
//

#include <iostream>
#include <omp.h>                        // Librería para implementar la programación paralela

#define N 1000                          // Cantidad de números a sumar
#define chunk 100                       // Tamaño del bloque a sumar en cada thread paralelo
#define mostrar 10                      // Cantidad de resultados a mostrar en las funciones de impresión

void imprimeArreglo(float* d);          // Función para imprimir los primeros 'mostrar' datos de los arreglos
void imprimeFinArreglo(float* d);       // Función para imprimir los últimos 'mostrar' datos de los arreglos

int main()
{
    #ifdef _OPENMP
        std::cout << "\nCon OPENMP\n";  // Código para verificar que podemos usar  OpenMP
    #endif

    std::cout << "\nSumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)             // Se llenan los arreglos a y b
    {
        a[i] = i * 10;
        //b[i] = i;
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;                // guardo en 'pedazos' la cantidad de números a procesar en cada thread

    // En la definición de los threads, Las variables a,b,c son compartidas, i es privada para cada hilo
    // Divide las iteraciones del for en bloques del tamaño pedazos, y con static les asigna de antemano los pedazos 
    //    a los diferentes hilos
    // Se indica que el procesamiento en paralelo se aplica para el for
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)                 // For en paralelo. En cada thread hace la suma de su parte.
    {
        c[i] = a[i] + b[i];
    }

    //Impresión de los primeros 'mostrar' valores de los 3 arreglos
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    //Impresión de los últimos 'mostrar' valores de los 3 arreglos
    std::cout << "\n";
    std::cout << "Imprimiendo los ultimos " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeFinArreglo(a);
    std::cout << "Imprimiendo los ultimos " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeFinArreglo(b);
    std::cout << "Imprimiendo los ultimos " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeFinArreglo(c);

    return 0;
}

void imprimeArreglo(float* d)
{
    //Imprime los primeros 'mostrar' elementos del arreglo d recibido como parámetro, separados por un guion
    for (int x = 0; x < mostrar; x++)
    {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}

void imprimeFinArreglo(float* d)
{
    //Imprime los ultimos 'mostrar' elementos del arreglo d recibido como parámetro, separados por un guion
    for (int x = N - mostrar; x < N; x++)
    {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}

