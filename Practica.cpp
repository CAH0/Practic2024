#define _CRT_SECURE_NO_WARNINGS // для корректной работы scanf()
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <locale.h>

#define SIZE 100

void writeFile(int size)
{
    int min = -1000;
    int max = 1000;
    srand(time(0));

    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d\n", (rand() % (max - min + 1) + min));
    }

    fclose(file);
}

void writeFileData(double* numbers, int size)
{
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%.f\n", numbers[i]);
        
    }
    fclose(file);
}

int readFile(const char* filename, double* numbers, int* count, int size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    *count = 0;

    while (fscanf(file, "%lf", &numbers[*count]) == 1 && *count < size) {
        (*count)++;
    }

    fclose(file);
    return 0;
}

void shakerSort(double* mass, int count)
{
    int left = 0, right = count - 1; // левая и правая границы сортируемой области массива
    int flag = 1;  // флаг наличия перемещений
    clock_t start_time = clock();

    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)  //двигаемся слева направо
        {
            if (mass[i] > mass[i + 1]) // если следующий элемент меньше текущего,
            {             // меняем их местами
                double t = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = t;
                flag = 1;      // перемещения в этом цикле были
            }
        }
        right--; // сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
            if (mass[i - 1] > mass[i]) // если предыдущий элемент больше текущего,
            {            // меняем их местами
                double t = mass[i];
                mass[i] = mass[i - 1];
                mass[i - 1] = t;
                flag = 1;    // перемещения в этом цикле были
            }
        }
        left++; // сдвигаем левую границу на следующий элемент
        if (flag == 0) break;
    }
    clock_t end_time = clock(); // stop timer
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    // Write sorting time to file

    FILE* fp = fopen("time.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%.3f seconds", elapsed_time);
        fclose(fp);
    }
    else {
        printf("Error opening file!\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    int choice;
    int size = 0;
    double* m = nullptr;
    int count;
    char buffer[256];
    

    while (1) {
        FILE* fp = fopen("time.txt", "r");
        if (fp != NULL) { 
            fgets(buffer, 256, fp);
            fclose(fp);
        }
        printf("Выбор действия:\n");
        printf("1. Ввести размер массива\n");
        printf("2. Создать рандомную последовательность и записать в файл\n");
        printf("3. Прочитать данные из файла\n");
        printf("4. Отсортировать список используя метод Шейкерной сортировки\n");
        printf("5. Загрузить отсортированные данные в файл\n");
        printf("6. Выход                                                                   Последняя сортировка заняла: %s\n", buffer);
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1:
            
            printf("Введите размер массива\n");
            std::cin >> size;
            m = new double[size];
            break;
        case 2:
            writeFile(size);
            printf("Данные записанный в файл.\n");
            break;
        case 3:
            readFile("input.txt", m, &count, size);
            printf("Данные прочитанный с файла.\n");
            break;
        case 4:
            shakerSort(m, size);
            printf("Данные отсортированный.\n");
            break;
        case 5:
            writeFileData(m,  size);
            printf("Данные записанны в файл.\n");
            break;
        case 6:
            delete[] m;
            return 0;
        default:
            printf("Ошибка.\n Попробуте снова.\n");
        }
        system("cls");
        
    }
    return 0;
}