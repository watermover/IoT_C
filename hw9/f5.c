int find_max_array(int size, int a[])
{
    int i;
    int mx = a[0];

    for (i = 1; i < size; i++)
        if (a[i] > mx)
            mx = a[i];

    return mx;
}
