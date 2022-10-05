#include <iostream>
using namespace std;

int main()
{   //Заполняю массив числами от 1 до n, n - количество элементов в нем
    const int n = 50;
    int list_of_numbers[n+1];
    for (int i = 0; i <= n; i++) {
        list_of_numbers[i] = i;
    }

    //Первое простое число: simple_number = 2
    int simple_number = 2;
    //Зануляю составные числа в массиве, сначала квадраты
    for (int i = simple_number; i * i <= n; i++) {
        if (list_of_numbers[i] != 0) {
            //Потом прочесываю прибавляя несколько раз простые числа
            for (int j = i * i; j <= n; j += i) {
                list_of_numbers[j] = 0;
            }
        }
    }

    //вывожу не зануленные числа
    cout << "\n";
    for (int i = 0; i < n; i++) {
        if (list_of_numbers[i] != 0) {
            cout << list_of_numbers[i] << "\n";
        }
    }
}

