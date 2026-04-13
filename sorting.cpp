#include <iostream>
#include <cmath>    //for floor log2()
#include <cstring> // for memcpy()
#include "sorting.h"
void swap(int array[],unsigned int i, unsigned int j)
{
    int temp=array[i];
    array[i]=array[j];
    array[j]=temp;
    return;
}
//merge sort
void merge(int array[],int buffer[],unsigned int start_left,unsigned int end_left,unsigned int start_right,unsigned int end_right)
{
    memcpy(buffer+start_left,array+start_left,(end_right-start_left+1)*sizeof(array[start_left])); //copy to buffer integers from array that interest us
    int i=start_left,l=start_left,r=start_right;//current indexes of array,right_array,left_array;
    while(l<=end_left && r<=end_right)//merge while left and right are present
    {
        if(buffer[l]<buffer[r])//merge if smaller
        {
            array[i]=buffer[l];
            i++;
            l++;
        }
        else
        {
            array[i]=buffer[r];
            i++;
            r++;
        }
    }
        while(l<=end_left)//merge all that are left
    {
            array[i]=buffer[l];
            i++;
            l++;
    }
    while(r<=end_right)//merge all that are left
    {
            array[i]=buffer[r];
            i++;
            r++;
    }
    return;
}
void merge_sort_impl(int array[],int buffer[], unsigned int start, unsigned int end)
{
    if(end-start+1<=1) return;
    unsigned int half=((start+end-1)/2);
    merge_sort_impl(array,buffer,start,half);
    merge_sort_impl(array,buffer,half+1,end);
    merge(array,buffer,start,half,half+1,end);
}
void merge_sort(int array[],unsigned int size)
{
    if(size<=1) return;
    int* buffer = new int[size];
    merge_sort_impl(array,buffer,0,size-1);
    delete [] buffer;
}
// quick sort
unsigned int median_of_three(int array[], unsigned int start, unsigned int end) {
    unsigned int mid = start + (end - start) / 2;
    
    if (array[start] > array[mid])
        swap(array, start, mid);
    if (array[start] > array[end])
        swap(array, start, end);
    if (array[mid] > array[end])
        swap(array, mid, end);
    swap(array, mid, end);
    return array[end];
}
unsigned int partition(int array[],unsigned int start, unsigned int end) //Hoare
{
    int pivot=median_of_three(array,start,end);
    int i = (int)start - 1;
    int j = (int)end + 1;

    while (true) {
        do { i++; } while (array[i] < pivot);
        do { j--; } while (array[j] > pivot);
        if (i >= j) return (unsigned int)j;
        swap(array, i, j);
    }
}
void quick_sort_main(int array[],unsigned int start, unsigned int end)
{
    if(start>=end) return;
    unsigned int pivot_index = partition(array,start,end);
    quick_sort_main(array,start,pivot_index);
    quick_sort_main(array,pivot_index+1,end);
}
void quick_sort(int array[], unsigned int size)//built both quick_sort and quick_sort_main for consistency of number of arguments in X_sort functions || could later improve pivot selection
{
    if(size==0) return;
    quick_sort_main(array,0,size-1);
}
//heap sort
void heapify(int array[],unsigned int start, unsigned int end,unsigned int index)
{
    unsigned int left = ((2*index)+1)-start;
    unsigned int right= left+1;
    unsigned int max=index;//index of max node, default to starting index
    if(right<=end && array[right]>array[index])
    {
        max=right;
    }
    if(left<=end && array[left]>array[max])
    {
        max=left;
    }
    if(max!=index)
    {
        swap(array,index,max);
        heapify(array,start,end,max);
    }
    return;
}
void create_max_heap(int array[],unsigned int start, unsigned int end)
{
    for(int i=(end-start/*size-1*/)/2;i>=0;i--)
    {
        heapify(array,start,end,i+start);
    }
    return;
}
void heap_sort_main(int array[],unsigned int start, unsigned int end) //built both heap_sort and heap_sort_main for consistency of number of arguments in X_sort functions 
{
    if(end<=start) return;
    create_max_heap(array,start,end);
    for(;end>start;end--)
    {
        swap(array,start,end);
        heapify(array,start,end-1,start);
    }
    return;
}
void heap_sort(int array[],unsigned int size)//heap sort using array indexed from 0
{
    if(size<=1) return;
    heap_sort_main(array,0,size-1);
}
//insertion sort
void insertion_sort_main(int array[],unsigned int start,unsigned int end)
{
    if(end<=start) return;
    for(int i=start+1;i<=end;i++)
    {
        int temp=array[i];
        unsigned int j=i;
            while(j>start && array[j-1]>temp)
            {
                array[j]=array[j-1];
                j--;
            }
            array[j]=temp;
    }
}
void insertion_sort(int array[],unsigned int size)
{
    if(size<=1) return;
    insertion_sort_main(array,0,size-1);
}
//introspective sort
void intro_sort_main(int array[],unsigned int start, unsigned int end,unsigned int max_depth)
{
    if(start>=end) return;
    if(end-start<15) {insertion_sort_main(array,start,end); return;}
    if(max_depth==0) {heap_sort_main(array,start,end); return;}
    else    //quick sort
    {
        unsigned int pivot_index = partition(array,start,end);
        intro_sort_main(array,start,pivot_index,max_depth-1);
        intro_sort_main(array,pivot_index+1,end,max_depth-1);
    }
}
void introspective_sort(int array[],unsigned int size)
{
    if(size<=1) return;
    unsigned int max_depth=2*static_cast<unsigned int>(floor(log2(static_cast<double>(size))));
    intro_sort_main(array,0,size-1,max_depth);
}
//bucket sort
void bucket_sort_recursive(int array[],unsigned int start, unsigned int end)
{
    if(end<=start) return;
    if(end-start<15) //if size less than 15 sort using insertion_sort()
    {
        insertion_sort_main(array,start,end); 
        return;
    }
    unsigned int size = end-start+1;
    //find MAX, MIN
    int MAX=array[start], MIN=array[start];
    for(unsigned int i=start+1;i<=end;i++)
    {
        if(array[i]>MAX) MAX=array[i];
        else if(array[i]<MIN) MIN=array[i]; 
    }
    if(MAX == MIN)
    {
        return;
    }
    //initialize needed lists, we avoid making int[][] list as it generates O(n^2) in terms of space
    unsigned int *counts=new unsigned int[size]();  //how many items in each bucket
    unsigned int *offsets=new unsigned int[size](); //offset of each bucket inside buffer[]
    unsigned int *cursors=new unsigned int[size]; //needed for inserting buckets into buffer without modyfying offsets[]
    int *buffer=new  int[size]; // buffer for storing buckets
    //count elements in each bucket

    //formula for calculating bucket index for each item, normalize to [0,1] then multiply:
    //(unsigned int)floor((((double)(array[i]-MIN)/(MAX-MIN)))*(size-1))

    for(unsigned int i=start;i<=end;i++)
    {
        counts[(unsigned int)floor((((double)(array[i]-MIN)/(MAX-MIN)))*(size-1))]++;
    }
    //calculate offsets,copy it into curosors
    for(unsigned int i=1;i<size;i++)//indexed from 1 because offset [0] is always 0
    {
        offsets[i]=offsets[i-1]+counts[i-1];
    }    
    memcpy(cursors,offsets,size*sizeof(offsets[0]));
    //insert into buckets inside buffer
    for(int i=start;i<=end;i++)
    {
        unsigned int idx=(unsigned int)floor((((double)(array[i]-MIN)/(MAX-MIN)))*(size-1));
        buffer[cursors[idx]]=array[i];
        cursors[idx]++;
    }
    //Sort
    for(int i=0;i<size;i++)
    {
        if(cursors[i]>offsets[i]+1)//if bucket not empty nor with single item
        bucket_sort_recursive(buffer,offsets[i],cursors[i]-1);//sort each bucket indepenently   
    }
    //Copy to array[]
    memcpy(array+start,buffer,size*sizeof(buffer[0]));
    
    delete[] counts;
    delete[] offsets;
    delete[] cursors;
    delete[] buffer;
}
void bucket_sort_main(int array[],unsigned int start, unsigned int end)
{
    if(end<=start) return;
    unsigned int size = end-start+1;
    //find MAX, MIN
    int MAX=array[start], MIN=array[start];
    for(unsigned int i=start+1;i<=end;i++)
    {
        if(array[i]>MAX) MAX=array[i];
        else if(array[i]<MIN) MIN=array[i]; 
    }
    if(MAX == MIN)
    {
        return;
    }
    //initialize needed lists, we avoid making int[][] list as it generates O(n^2) in terms of space
    unsigned int *counts=new unsigned int[size]();  //how many items in each bucket
    unsigned int *offsets=new unsigned int[size](); //offset of each bucket inside buffer[]
    unsigned int *cursors=new unsigned int[size]; //needed for inserting buckets into buffer without modyfying offsets[]
    int *buffer=new  int[size]; // buffer for storing buckets
    //count elements in each bucket

    //formula for calculating bucket index for each item, normalize to [0,1] then multiply:
    //(unsigned int)floor((((double)(array[i]-MIN)/(MAX-MIN)))*(size-1))

    for(unsigned int i=start;i<=end;i++)
    {
        counts[(unsigned int)floor((((double)(array[i]-MIN)/(MAX-MIN)))*(size-1))]++;
    }
    //calculate offsets,copy it into curosors
    for(unsigned int i=1;i<size;i++)//indexed from 1 because offset [0] is always 0
    {
        offsets[i]=offsets[i-1]+counts[i-1];
    }    
    memcpy(cursors,offsets,size*sizeof(offsets[0]));
    //insert into buckets inside buffer
    for(int i=start;i<=end;i++)
    {
        unsigned int idx=(unsigned int)floor((((double)(array[i]-MIN)/(MAX-MIN)))*(size-1));
        buffer[cursors[idx]]=array[i];
        cursors[idx]++;
    }
    //Sort
    for(int i=0;i<size;i++)
    {
        if(cursors[i]>offsets[i]+1)//if bucket not empty nor with single item
        insertion_sort_main(buffer,offsets[i],cursors[i]-1);//sort each bucket indepenently   
    }
    //Copy to array[]
    memcpy(array+start,buffer,size*sizeof(buffer[0]));

    delete[] counts;
    delete[] offsets;
    delete[] cursors;
    delete[] buffer;
}
void bucket_sort(int array[],const unsigned int size)
{
    if(size<=1) return;
    bucket_sort_main(array,0,size-1);
}




// int main()
// {
//     int array[10]={8,5,2,0,1,9,3,7,4,6};

//     //merge_sort(array, sizeof(array)/sizeof(array[0]));
//     //quick_sort(array, sizeof(array)/sizeof(array[0]));
//     //heap_sort(array, sizeof(array)/sizeof(array[0]));
//     //introspective_sort(array, sizeof(array)/sizeof(array[0]));
//     //insertion_sort(array,sizeof(array)/sizeof(array[0]));
//     bucket_sort(array,sizeof(array)/sizeof(array[0]));
//     for(int i=0;i<10;i++)
//     std::cout<<array[i]<<std::endl;
//     return 0;
// }