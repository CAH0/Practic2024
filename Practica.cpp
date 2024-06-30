#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <iostream>
#include <ctime>

#include <locale.h>

#define SIZE 100

void data()
{
    char buffer[256];
    char elem_str[100][256];
    char info_str[100][256];

    FILE* fp = fopen("time.txt", "r");
    if (fp != NULL) {
        printf("+-------------------------------------------+\n"
               "|                  Количество               |\n"
               "|       Секунд         |       Чисел        |\n"
               "+-------------------------------------------+\n");
        int line_num = 0;
        while (fgets(buffer, 256, fp) != NULL) {
            char* token = strtok(buffer, ",");
            strcpy(info_str[line_num], token);
            token = strtok(NULL, ",");
            strcat(info_str[line_num], ", ");
            strcat(info_str[line_num], token);
            token = strtok(NULL, "\n");
            strcpy(elem_str[line_num], token);

            

            printf("|       %-14s |       %-13s|\n", info_str[line_num], elem_str[line_num]);
            line_num++;
            
        }
        printf("+-------------------------------------------+\n");
        fclose(fp);
    }
    system("pause");
    std::cin.get();
}

void developers()
{
    printf("+---------------------------------------------------------------------------+\n"
        "|   Группа: 23ВВВ1                                                          |\n"
        "|                                                                           |\n"
        "|   Разработка алгоритма                                                    |\n"
        "|   Казаков Александр                                                       |\n"
        "|                                                                           |\n"
        "|   Разработка интерфейса                                                   |\n"
        "|   Власова Адриана                                                         |\n"
        "|                                                                           |\n"
        "|   Тестировка и Работа с файлами                                           |\n"
        "|   Головушкина Алекандра                                                   |\n"
        "|                                                                           |\n"
        "+---------------------------------------------------------------------------+\n");
    system("pause");
    std::cin.get();
}

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
    int left = 0, right = count - 1; 
    int flag = 1;  
    
    clock_t start_time = clock();

    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)  
        {
            if (mass[i] > mass[i + 1]) 
            {             
                double t = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = t;
                flag = 1;    
            }
        }
        right--; 
        for (int i = right; i > left; i--) 
        {
            if (mass[i - 1] > mass[i]) 
            {            
                double t = mass[i];
                mass[i] = mass[i - 1];
                mass[i - 1] = t;
                flag = 1; 
            }
        }
        left++; 
        if (flag == 0) break;
    }
    clock_t end_time = clock(); 
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;


    FILE* fp = fopen("time.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%.3f, %d\n", elapsed_time, count, count);
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
    int none = 0;
    

    while (1) {
        
        printf("Выбор действия:\n");
        printf("1. Ввести размер массива\n");
        printf("2. Создать рандомную последовательность и записать в файл\n");
        printf("3. Прочитать данные из файла\n");
        printf("4. Отсортировать список используя метод Шейкерной сортировки\n");
        printf("5. Загрузить отсортированные данные в файл\n");
        printf("6. База сортировок\n");
        printf("7. Информация о разработчиках\n");
        printf("8. Выход\n");
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
            data();
            break;
        case 7:
            developers();
            break;
        case 8:
            delete[] m;
            return 0;
        default:
            printf("Ошибка.\n Попробуте снова.\n");
        }
        system("cls");
        
    }
    return 0;
}