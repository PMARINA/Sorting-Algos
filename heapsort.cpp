using namespace std;

void makesubheap(int a[], int i, int n) {
    int temp;

    if ((i >= n) or ((2*i) >= n)) {
        return;
    }
    if (((2*i) + 1) >= n) {
        if (a[2*i] > a[i]) {
            temp = a[2*i];
            a[2*i] = a[i];
            a[i] = temp;
        }
    } else {
        if (a[2*i] > a[(2*i) + 1]) {
            if (a[2*i] > a[i]) {
                temp = a[2*i];
                a[2*i] = a[i];
                a[i] = temp;
            }
        } else {
            if (a[(2*i) + 1] > a[i]) {
                temp = a[(2*i) + 1];
                a[(2*i) + 1] = a[i];
                a[i] = temp;                
            }
        }
    }
};

void makeheap(int a[]) {
    for (int i = 1; i <= (sizeof(a) / 2); i++) {
        makesubheap(a, i, sizeof(a));
    }
};

void rebuildheap(int a[]) {
    int temp;
    for (int i = 2; i <= (sizeof(a) - 1); i++) {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
    }
};

void heapsort(int a[]) {
    makeheap(a);
    rebuildheap(a);
}