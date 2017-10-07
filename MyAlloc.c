#include "MyAlloc.h"
MemoryNode * memoryNodeInit() {
	MemoryNode * node = (MemoryNode)malloc(sizeof(MemoryNode));
	bzero(node, sizeof(MemoryNode));
	node->taken=FALSE;
	return node;
}

bool isBottom(MemoryNode * node) {
	return !(node->left || node->right);
}
void memoryFree(MemoryNode * node, bool subnodes){
	if(subnodes){
		if(node->left) memoryFree(node->left, subnodes);
		if(node->right) memoryFree(node->right, subnodes);
	}
	free(node);
}
Heap * heapStuff(int totalSize){
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
void * ANMemoreNodeSplitToSize(MemoryNode * node, int size){
	if(node->taken) return NULL;
	if(size == 1) return NULL;
	if(node->size < size) return NULL;
	if(node->size / 2 >= size){
		if(isBottom(MemoryNode * node)){
			MemoryNode * node1 = memoryNodeInit();
			MemoryNode * node2 = memoryNodeInit();
			node1->size = node->size/2;
			node2->size = node->size / 2;
            		node1->ptr = node->ptr;
            		node2->ptr = node->ptr + (node->size / 2);
            		node->left = node1;
            		node->right = node2;
            		node1->parent = node;
            		node2->parent = node;
		}
	void * data = ANMemoryNodeSplitToSize(node->left, size);
	if(data) return data;
	else return ANMemoryNoseSplitToSize(node->right, size);
	} else if (node->size >= size) {
		node->taken = TRUE;
		return node->ptr;
	}
	return NULL;
}
void * ANMemoryHeapGetMemory (Heap * heap, int size){
	return ANMemoryNodeSplitToSize(heap->table, size);
}
void ANMemoryNodeFreeMemory(MemoryNode * node, void * ptr){
	if (node->ptr !- ptr || isBottom(node)){
		if(node->left){
			ANMemoryNodeFreeMemory(node->left, ptr);
		}
		else if(node->right){
			ANMemoryNodeFreeMemory(node->right, ptr);
		}
		else {
			node->taken = FALSE;
			return;
		}
	}
}
void ANMemoryHeapFreeMemory(Heap * heap, void * ptr){
	ANMemoryNodeFreeMemory(heap->table, ptr);
	ANMemoryNodeDefragment(heap);
}


	
