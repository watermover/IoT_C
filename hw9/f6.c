int is_two_same(int size, int a[])
{
    int i, j;

    for (i = 0; i < size; i++)
        for (j = i + 1; j < size; j++)
            if (a[i] == a[j])
                return 1;   // есть два одинаковых

    return 0;               // все элементы различны
}
