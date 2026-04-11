#include <iostream>

//merge sort
void merge(int left_array[], int right_array[], int array[],unsigned int size)
{
    unsigned int leftsize=size/2;
    unsigned int rightsize=size-leftsize;
    int i=0,r=0,l=0;//current indexes of array,right_array,left_array;
    while(l<leftsize && r<rightsize)//merge while left and right are present
    {
        if(left_array[l]<right_array[r])//merge if smaller
        {
            array[i]=left_array[l];
            l++;
            i++;
        }
        else
        {
            array[i]=right_array[r];
            r++;
            i++;
        }
    }
    while(l<leftsize)//merge all that are left
    {
            array[i]=left_array[l];
            i++;
            l++;
    }
    while(r<rightsize)//merge all that are left
    {
            array[i]=right_array[r];
            i++;
            r++;
    }
    return;
}
void merge_sort(int array[],unsigned int size)
{
    if(size<=1) return;
    unsigned int newsize=size/2;
    int* left_array=new int[newsize];
    int* right_array=new int[size-newsize];

    for(int i=0;i<size;i++) //split array in half
    {
        if(i<newsize) left_array[i]=array[i];
        else right_array[i-newsize]=array[i];
    }

    merge_sort(left_array,newsize);
    merge_sort(right_array,size-newsize);
    merge(left_array,right_array,array,size);
    delete [] left_array;
    delete [] right_array;
}

// quick sort
void swap(int array[],unsigned int i, unsigned int j)
{
    int temp=array[i];
    array[i]=array[j];
    array[j]=temp;
    return;
}
unsigned int partition(int array[],unsigned int start, unsigned int end)
{
    int pivot=array[end];
    int j=(int)start,i=(int)start-1;
    while (j!=end)
    {
        if(array[j]<pivot)
        {
            i++;
            swap(array,i,j);
        }
        j++;
    }
    i++;
    swap(array,i,j);
    return (unsigned int)i;
}
void quick_sort_main(int array[],unsigned int start, unsigned int end)
{
    if(start>=end) return;
    unsigned int pivot_index = partition(array,start,end);
    if (pivot_index > start)//in case of pivot_index == 0 
        quick_sort_main(array,start,pivot_index-1);
    quick_sort_main(array,pivot_index+1,end);
}
void quick_sort(int array[], unsigned int size)//built both quick_sort and quick_sort_main for consistency of number of arguments in X_sort functions
{
    if(size==0) return;
    quick_sort_main(array,0,size-1);
}
//introspective sort

//bucket sort



int main()
{
    int array[10]={8,5,2,0,1,9,3,7,4,6};

    //merge_sort(array, sizeof(array)/sizeof(array[0]));
    quick_sort(array, sizeof(array)/sizeof(array[0]));
    for(int i=0;i<10;i++)
    std::cout<<array[i]<<std::endl;
    return 0;
}