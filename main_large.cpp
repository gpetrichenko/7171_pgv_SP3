#include <iostream>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    long long int n = rand() % 10 + 5;
    long long int arr1[n];
    long long int arr2[n];
    long long int arr3[n];
    cout << "Array 1: \n";
    for(int i = 0; i < n; i++) {
        arr1[i] = rand() % 9 + 1;
        cout << arr1[i] << " ";
    }
    cout << "\nArray 2: \n";
    for(int i = 0; i < n; i++) {
        arr2[i] = rand() % 9 + 1;
        cout << arr2[i] << " ";
    }
    long long *ptr_array1 = &arr1[0];
    long long *end_array1 = &arr1[n-1];
    long long *ptr_array2 = &arr2[0];
    long long *ptr_array3 = &arr3[0];
    asm (
        "mov %[ptr_array1], %%rax\n\t"  // Поместим указатель на начало массива в rax
        "mov %[ptr_array2], %%rbx\n\t"  // Поместим указатель на начало массива в rbx
        "mov %[ptr_array3], %%rcx\n\t"  // Поместим указатель на начало массива в rcx
        "mov (%%rax), %%rdx\n\t"        // Поместим указатель на начало массива в rdx
        "cmp %%rdx, (%%rbx)\n\t"        // Сравним значения rdx к rbx
        "jl first\n\t"                  // Jump Less - Поиск меньшего элемента
        //"jg first\n\t"                  // Jump Greater - Поиск большего элемента
        "push (%%rbx)\n\t"              // Поместить в стек rbx (адрес следующего элемента)
        "pop (%%rcx)\n\t"               // Взять в rcx из стека смещения на следующую строку

        "loop_start:\n\t"
            "add $8, %%rax\n\t"         // Увеличить адрес в rax на 8 (переместили на один элемент вправо)
            "add $8, %%rbx\n\t"         // Увеличить адрес в rbx на 8 (переместили на один элемент вправо)
            "add $8, %%rcx\n\t"         // Увеличить адрес в rcx на 8 (переместили на один элемент вправо)
            "mov (%%rax), %%rdx\n\t"    // Поместим указатель на начало массива в rdx
            "cmp %%rdx, (%%rbx)\n\t"    // Сравним значения rdx и rbx

            "jl first\n\t"              // Jump Less
            //"jg first\n\t"              // Jump Greater - Поиск большего элемента

            "push (%%rbx)\n\t"          // Обмен значений элементов массива через стек
            "pop (%%rcx)\n\t"           // Взять в rcx из стека смещения на следующую строку
            "cmp %%rax, %[end_array1]\n\t" // Проверка что достигнут конец массива
            "je end\n\t"                // Если достигнут - завершение, иначе продолжение
        "jmp loop_start\n\t"            // Переход на loop_start

        "first:\n\t"
            "push (%%rax)\n\t"          // Обмен значений элементов массива через стек
            "pop (%%rcx)\n\t"           // Взять в rcx значение ищ стека смещения на следующую строку
            "cmp %%rax, %[end_array1]\n\t"  // Проверка что достигнут конец массива
            "je end\n\t"                // Если достигнут - завершение, иначе продолжение
        "jmp loop_start\n\t"            // Переход на loop_start

        "end:\n\t"
        :
        :[ptr_array1]"m"(ptr_array1), [ptr_array2]"m"(ptr_array2), [ptr_array3]"m"(ptr_array3), [end_array1]"m"(end_array1)
        :"%rax", "%rbx", "%rcx"
    );

    cout << "\nArray asm: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr3[i] << " ";
    }

    return 0;
}
