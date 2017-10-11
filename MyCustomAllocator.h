
#include "ANCustomAllocation.h"

const void * CustomAllocatorRetainCall (const void * info) {
	((Heap *)info)->retainCount += 1;//casting the values to the memory heap and assigned the retainCount to adding it by one
	return info;
}

void CustomAllocatorReleaseCall (const void * info) {
	((Heap *)info)->retainCount -= 1;//make the values different again
	if (((Heap *)info)->retainCount == 0) {//if this value is unchanged 
		ANMemoryHeapFree((ANMemoryHeap *)info);//call the free memory method 
	}
}

CFStringRef CustomAllocatorCreateDescription (const void * info) {
	char myBytes[512];//make a character array of size 512 
	printf(myBytes, "BuddyAllocator: %p", ((Heap *)info)->userInfo);//make a string of the character arrays and the info of the user info in the struct of heap
	return CFStringCreateWithBytes(kCFAllocatorDefault, (const UInt8 *)myBytes, strlen(myBytes),//call the method with the uint object of mybytes and the string length of mybytes and the encoded ascii value
								   kCFStringEncodingASCII,
								   FALSE);
}

void * CustomAllocatorAllocate (CFIndex allocSize, CFOptionFlags hint, void * info) {//this is the method to allocate memory on the heap 
	ANMemoryHeap * heap = (ANMemoryHeap *)info;//make a heap value equal to the info pointer 
	void * data = ANMemoryHeapGetMemory(heap, allocSize);//this is setting the output of the get memory of the value we want 
	return data;
}

void * CustomAllocatorReallocate (void * ptr, CFIndex newsize, 
								  CFOptionFlags hint, void * info) {//method to make allocation modifications after it is done
	ANMemoryHeap * heap = (ANMemoryHeap *)info;
	void * nptr = ANMemoryHeapGetMemory(heap, newsize);//new pointer points to memory of the new size in the heap 
	memcpy(nptr, ptr, ANMemoryHeapGetSize(heap, ptr));//copy the memory of the heap of the old pointer 
	ANMemoryHeapFreeMemory(heap, ptr);//free all the memory of the old heap 
	return nptr;
}

void CustomAllocatorDeallocate (void * ptr, void * info) {//remove all the previous allocations to the heap 
	ANMemoryHeap * heap = (ANMemoryHeap *)info;//make a new heap object 
	ANMemoryHeapFreeMemory(heap, ptr);//remove the heap memory fully
}

CFIndex CustomAllocatorPreferedSize (CFIndex size, CFOptionFlags hint, void * info) {//set the user defined size 
	// basically buddy allocation method.
	ANMemoryHeap * heap = (ANMemoryHeap *)info;
	int i = heap->totalBytes;//the total size from the heap struct
	while (i >= size) {
		i /= 2;//go until the total size is greater than the size 
	}
	return (CFIndex)(i * 2);//return the cf object with the totalbyte of 2 times the total bytes 
}

CFAllocatorRef AllocatorWithBuddyHeap (ANMemoryHeap * heap) {//method to use the struct and its values to set different values and modify the settings of the struct 
	CFAllocatorContext * context = (CFAllocatorContext *)malloc(sizeof(CFAllocatorContext));
	context->info = heap;
	context->version = 0;
	context->retain = CustomAllocatorRetainCall;//use all the methods we have made so far to set the new struct values 
	context->release = CustomAllocatorReleaseCall;
	context->copyDescription = CustomAllocatorCreateDescription;
	context->allocate = CustomAllocatorAllocate;
	context->reallocate = CustomAllocatorReallocate;
	context->deallocate = CustomAllocatorDeallocate;
	context->preferredSize = CustomAllocatorPreferedSize;
	CFAllocatorRef allocator = CFAllocatorCreate(kCFAllocatorDefault, context);
	heap->userInfo = (void *)allocator;
	return allocator;
}

CFAllocatorRef AllocatorWithNewHeap () {//make a new heap object 
	int buddyHeapSize = (1024*1024) * 10; // 10mb
	ANMemoryHeap * heap = ANMemoryHeapCreate(buddyHeapSize);//create the heap into the heap object 
	heap->userInfo = nil;//no user in
	return AllocatorWithBuddyHeap(heap);//this shows it is the main object that creates and uses all the methods
}
