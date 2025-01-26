// Tarea1ProgramParalela.cpp 
//

#include <iostream>
#include <omp.h>

#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);
void imprimeFinArreglo(float* d);

int main()
{
    #ifdef _OPENMP
        std::cout << "\nCon OPENMP\n";
#endif

    std::cout << "\nSumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)         // Se llenan los arreglos
    {
        a[i] = i * 10;
        //b[i] = i;
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;

    // En la definición de los threads, Las variables a,b,c son compartidas, i es privada para cada hilo
    // Divide las iteraciones del for en bloque del tamaño pedazos, y con static les asigna de antemano los pedazos a los diferentes hilos
    // Se indica que el procesamiento en paralelo se aplica para el for
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)                 // For paralelo, en cada thread hace la suma de su parte
    {
        c[i] = a[i] + b[i];
    }

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

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
    //Imprime los primeros 'mostrar' elementos del arreglo d recibido como parámetro
    for (int x = 0; x < mostrar; x++)
    {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}

void imprimeFinArreglo(float* d)
{
    //Imprime los ultimos 'mostrar' elementos del arreglo d recibido como parámetro
    for (int x = N - mostrar; x < N; x++)
    {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
