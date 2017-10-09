#include "MyAlloc.h"
MemoryNode * memoryNodeInit() {//initialize all the parts of the memory node struct
	MemoryNode * node = (MemoryNode)malloc(sizeof(MemoryNode));
	bzero(node, sizeof(MemoryNode));
	node->taken=FALSE;
	return node;
}

bool isBottom(MemoryNode * node) {//check if we are at the bottom if the node is neither left or right
	return !(node->left || node->right);
}
void memoryFree(MemoryNode * node, bool subnodes){//check if the node is free now
	if(subnodes){
		if(node->left) memoryFree(node->left, subnodes);//this is the left integer in the struct and then recurse the function 
		if(node->right) memoryFree(node->right, subnodes);
	}
	free(node);//run the free method 
}
Heap * heapStuff(int totalSize){//make the heap struct with certain values
	Heap * heap = (Heap)malloc(sizeof(Heap));
	bzero(heap, sizeof(Heap));
	heap->totalBytes = totalSize;
	heap->ptr = (void *)malloc(sizeof(Heap));
	heap->table = memoryNodeInit();
		heap->table->size = totalSize;
		heap->table->ptr = node->ptr;
		heap->table->taken = FALSE;
	heap->retainCount = 0;
	heap->userInfo = 0;
	return heap;
}
void * ANMemoreNodeSplitToSize(MemoryNode * node, int size){//this function is supposed to split the heap where specified 
	if(node->taken) return NULL;//check another set of values 
	if(size == 1) return NULL;
	if(node->size < size) return NULL;
	if(node->size / 2 >= size){//if the size is more that the size of the previous node
		if(isBottom(MemoryNode * node)){
			MemoryNode * node1 = memoryNodeInit();
			MemoryNode * node2 = memoryNodeInit();
			node1->size = node->size/2;
			node2->size = node->size / 2;
            		node1->ptr = node->ptr;
            		node2->ptr = node->ptr + (node->size / 2);
            		node->left = node1;//set all the values of the node1 and node2
            		node->right = node2;
            		node1->parent = node;
            		node2->parent = node;
		}
	void * data = ANMemoryNodeSplitToSize(node->left, size);//make a memory variable as the split to size 
	if(data) return data;//check if the data exists
	else return ANMemoryNoseSplitToSize(node->right, size);//recurse the size from the node and the heap node
	} else if (node->size >= size) {
		node->taken = TRUE;//set all the size values 
		return node->ptr;
	}
	return NULL;
}
void * ANMemoryHeapGetMemory (Heap * heap, int size){
	return ANMemoryNodeSplitToSize(heap->table, size);//same function but with a bit different parameters
}
void ANMemoryNodeFreeMemory(MemoryNode * node, void * ptr){//this function checks if the node can free all memory 
	if (node->ptr != ptr || isBottom(node)){
		if(node->left){//if this value exists
			ANMemoryNodeFreeMemory(node->left, ptr);//recurse this function 
		}
		else if(node->right){
			ANMemoryNodeFreeMemory(node->right, ptr);
		}
		else {
			node->taken = FALSE;//break the loop
			return;
		}
	}
}
void ANMemoryHeapFreeMemory(Heap * heap, void * ptr){
	ANMemoryNodeFreeMemory(heap->table, ptr);//same function called for the heap
	ANMemoryNodeDefragment(heap);
}
bool ANMemoryNodeDefragment (ANMemoryNode * node) {
    if (ANMemoryNodeIsBottom(node)) {//this function defragments the node 
        if (node->taken == TRUE) {
			return FALSE;
		}
        return TRUE;  
    } else {
        if (node->left) {
            if (!ANMemoryNodeDefragment(node->left)) {
				//printf("RET FALSE");
				return FALSE;//recurse the function to check if random crap exists
			}
        }
        if (node->right) {
            if (!ANMemoryNodeDefragment(node->right)) {
				//printf("RET FALSE");
				return FALSE;
				
			}
        }
        ANMemoryNodeFree(node->left, TRUE);
        ANMemoryNodeFree(node->right, TRUE);
        node->left = NULL;
        node->right = NULL;
    }
    return TRUE;
}
void ANMemoryHeapDefragment (ANMemoryHeap * heap) {
    ANMemoryNodeDefragment(heap->table);
}
int ANMemoryNodeGetSize (ANMemoryNode * node, void * ptr) {
	// basically recurse each node until we find the ptr.
    // then free it and set taken to FALSE.
    if (node->ptr != ptr || !ANMemoryNodeIsBottom(node)) {
        if (node->left) {
            int i = ANMemoryNodeGetSize(node->left, ptr);
			if (i >= 0) return i;//return the index of the ptr
        }
        if (node->right) {
            int i = ANMemoryNodeGetSize(node->right, ptr);
			if (i >= 0) return i;
        }
    } else {
        //node->taken = FALSE;
        return node->size;
    }
	return -1;
}
int ANMemoryHeapGetSize (ANMemoryHeap * heap, void * ptr) {
	return ANMemoryNodeGetSize(heap->table, ptr);
}//same function as the node
void ANMemoryHeapFree (ANMemoryHeap * heap) {
    free(heap->ptr);//make the previous void function for freeing all the heaps memory
    ANMemoryNodeFree(heap->table, TRUE);
    free(heap);
}

	
