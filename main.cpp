#include <QCoreApplication>
#include <QDebug>
#include <windows.h>
#include <iostream>
#include <fstream>
#define debug123

/*Основные команды для гнуплота
 set logscale x 5

set xlabel "Количество элементов в массиве"

set ylabel "Время(Условные единицы)"

set title "Графики сортировок (обычный масштаб)"

plot "test.dat" u 1:2 lt 32  w lp title "Bubble", "test.dat" u 1:3 lt 26  w lp title "Insertion", "test.dat" u 1:4 lt 31  w lp title "Selection", "test.dat" u 1:5 w l title "Merge", "test.dat" u 1:6 w l title "Quick","test.dat" u 1:7 lt 19 w lp  title "Gnom", "test.dat" u 1:8 w l title "Heap"


*/
using namespace std;
void sort_Bubble(int* arr, int _size);
void sort_Insertion(int* arr, int _size);
void sort_Selection(int* arr, int _size);
void sort_Merge(int* arr, int _size);
void sort_Quick(int* arr, int _size);
void sort_Gnom(int* arr, int _size);
void sort_Heap(int* arr, int _size);

//функции связанные с основными сортировками
void downHeap(int* arr, int k, int n);
void merge(int * arr, int _size, int* Left_arr, int lenL, int* Right_arr, int lenR);

//Вспомогательные функции
void randomFill(int* a, int _size);
void Swap(float &a, float &b);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    long int time1=0;
    long int time2=0;
    long int time3=0;
    long int time4=0;
    long int time5=0;
    long int time6=0;
    long int time7=0;


    FILE* f1;
    f1=fopen("test.dat","w");
    srand(time(NULL));

    int *array;

    for (int size = 0; size < 1001000; size+=1000) {
        array = new int [size];

        randomFill(array, size);
        fprintf(f1,"%d\t",size);

        if(time1>=5500 ){
            fprintf(f1,"%0\t");

        }
        if (time1<5500 ){                      //Bubble
            time1 = GetTickCount64();
            sort_Bubble(array, size);
            time1 = GetTickCount64() - time1;
            fprintf(f1,"%d\t",time1);
        }

        if(time2>=5500){
           fprintf(f1,"%0\t");

        }
        if (time2 <5500 ){                //Insertion
            randomFill(array, size);
            time2 = GetTickCount64();
            sort_Insertion(array, size);
            time2 = GetTickCount64() - time2;
            fprintf(f1,"%d\t",time2);
        }

       if(time3>=5500 ){
            fprintf(f1,"%0\t");

        }
        if (time3 <5500 ){                     // Selection
            randomFill(array, size);
             time3 = GetTickCount64();
            sort_Selection(array, size);
            time3 = GetTickCount64() - time3;
            fprintf(f1,"%d\t",time3);
        }

        if(time4>=5500 ){
            time4=' ';

        }
        if (time4 <5500 ){                        //Merge
            randomFill(array, size);
             time4 = GetTickCount64();
            sort_Merge(array, size);
            time4 = GetTickCount64() - time4;
            fprintf(f1,"%d\t",time4);
       }

        if(time5>=5500 ){
            fprintf(f1,"%0\t");

        }
        if (time5 <5500 ){                           //Quick
            randomFill(array, size);
            time5= GetTickCount64();
            sort_Quick(array,size);
            time5 = GetTickCount64() - time5;
            fprintf(f1,"%d\t",time5);
        }


        if(time6>=5500 ){
           fprintf(f1,"%0\t");

        }
        if(time6<5500 ){
            randomFill(array, size);                              //Gnom
            time6= GetTickCount64();
            sort_Gnom(array,size);
            time6 = GetTickCount64() - time6;
            fprintf(f1,"%d\t",time6);
        }


        if(time7>=5500 ){
            fprintf(f1,"%0\n");

        }
        if (time7<5500 ){
            randomFill(array, size);                              //Heap(Pyramid)
            time7= GetTickCount64();
            sort_Heap(array,size);
            time7 = GetTickCount64() - time7;
            fprintf(f1,"%d\n",time7);
       }



        cout<<size<<endl;
        delete [] array;

        }

    fclose(f1);
 /*
    srand(time(NULL));
    int array[20];
    randomFill(array,20);
    for(int i=0;i<20;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    sort_Heap(array,20);

    for(int i=0;i<20;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;

*/
    cout<<"End"<<endl;
    return a.exec();
}
void sort_Bubble(int* arr,int _size){
    for (int i = 0; i < _size-1 ; i++) {
            for (int j = 0; j < _size -1 ; j++) { //можно добавить _size-1-i но пока что так
                if (arr[j] > arr[j + 1]) {

                    swap(arr[j],arr[j+1]);
                }
            }
        }
}

void sort_Insertion(int* arr, int _size){
    for (int i=1;i<_size;i++){
        for(int j=i;j>0 && (arr[j-1]>arr[j]);j--){
            swap(arr[j],arr[j-1]);
        }
    }
}

void sort_Selection(int* arr, int _size){
    for (int i=0;i<_size-1;i++){
        int tmin=i;
        for(int j=i+1;j<_size;j++){
            if (arr[tmin]>arr[j]){
                tmin=j;
            }

        }
        if (tmin!=i){
            swap(arr[tmin],arr[i]);
        }
    }
}

void sort_Merge(int* arr, int _size)
{
  if(_size>1){
    int middle = _size/2;
    int end = _size-middle;
    int* Left_arr = new int[middle];
    int* Right_arr = new int[end];
    for(int i=0;i<_size;i++){
      if(i<middle){
        Left_arr[i] = arr[i];
      }
      else{
        Right_arr[i-middle] = arr[i];
      }
    }
    sort_Merge(Left_arr,middle);
    sort_Merge(Right_arr,end);
    merge(arr, _size, Left_arr, middle, Right_arr, end);
  }
}

void merge(int * arr, int _size, int* Left_arr, int lenL, int* Right_arr, int lenR){
  int i = 0;
  int j = 0;
  while(i<lenL||j<lenR){
    if (i<lenL & j<lenR){
      if(Left_arr[i]<=Right_arr[j]){
        arr[i+j] = Left_arr[i];
        i++;
      }
      else{
        arr[i+j] = Right_arr[j];
        j++;
      }
    }
    else if(i<lenL){
      arr[i+j] = Left_arr[i];
      i++;
    }
    else if(j<lenR){
      arr[i+j] = Right_arr[j];
      j++;
    }
  }
  delete[] Left_arr;
  delete[] Right_arr;
}

void sort_Quick(int* arr, int _size) {
    int i = 0;
    int j = _size - 1;

    int mid = arr[_size / 2];
    do {

        while(arr[i] < mid) {
            i++;
        }
        while(arr[j] > mid) {
            j--;
        }
        if (i <= j) {
            swap(arr[j],arr[i]);

            i++;
            j--;
        }
    } while (i <= j);
         if(j > 0) {
        sort_Quick(arr, j + 1);
    }
    if (i < _size) {
        sort_Quick(&arr[i], _size - i);
    }
}

void sort_Gnom(int* arr, int _size)
{
    int i = 0;
    while (i < _size)
    {
        if (i == 0)
        {
            i++;
        }
        if (arr[i] >= arr[i-1])
        {
            i++;
        }
        else
        {
            swap(arr[i], arr[i-1]);
            i--;
        }
    }
    return;
}


void downHeap(int* arr, int k, int n)
{

    int new_elem;
    long child;
    new_elem = arr[k];

    while(k <= n/2)
    {
        child = 2*k;

        if( child < n && arr[child] < arr[child+1] )
            child++;
        if( new_elem >= arr[child] )
            break;

        arr[k] = arr[child];
        k = child;
    }
    arr[k] = new_elem;
}


void sort_Heap(int* arr, int _size)
{
    int i;


  // строим пирамиду
    for(i = _size / 2 - 1; i >= 0; --i)
        downHeap(arr, i, _size-1);

  // теперь a[0]...a[size-1] пирамида

    for(i=_size-1; i > 0; --i)
    {
        // меняем первый с последним
        swap(arr[0],arr[i]);
        // восстанавливаем пирамидальность a[0]...a[i-1]
        downHeap(arr, 0, i-1);
    }
}


void randomFill(int*arr, int _size){
    for (int i=0;i<_size;i++){
        arr[i]=rand()%100;
    }
}

void Swap(float &a, float &b){
    float temp;
    temp=a;
    a=b;
    b=temp;
}








