#include <iostream>
#include <cmath>
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
unsigned int partition(int array[],unsigned int start, unsigned int end) //Lomuto, later Hoare could be implemented
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
//introspective sort
void intro_sort_main(int array[],unsigned int start, unsigned int end,unsigned int max_depth)
{
    if(start>=end) return;
    //if(n<16) insertion_sort(array,size); //could add in the future
    if(max_depth==0) heap_sort_main(array,start,end);
    else 
    {
        unsigned int pivot_index = partition(array,start,end);
        if (pivot_index > start)//in case of pivot_index == 0 
            intro_sort_main(array,start,pivot_index-1,max_depth-1);
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



int main()
{
    int array[10]={8,5,2,0,1,9,3,7,4,6};

    merge_sort(array, sizeof(array)/sizeof(array[0]));
    //quick_sort(array, sizeof(array)/sizeof(array[0]));
    //heap_sort(array, sizeof(array)/sizeof(array[0]));
    //introspective_sort(array, sizeof(array)/sizeof(array[0]));
    for(int i=0;i<10;i++)
    std::cout<<array[i]<<std::endl;
    return 0;
}