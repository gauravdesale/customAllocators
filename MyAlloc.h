#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef bool
#ifndef bool int
#ifndef TRUE 1
#ifndef FALSE 0
#endif

typedef struct {
	bool taken;
	int size;
	void * ptr;
	void * left;
	void * right;
	void * parent;
} MemoryNode;
typedef struct {
	MemoryNode * newTable;
	int totalBytes;
	void * ptr;
	void * userInfo;
	int retainCount;
} Heap;
MemoryNode * memoryNodeInit();
//memory node functions
bool isBottom(MemoryNode * node);
void memoryFree(MemoryNode * node, bool subnodes);
//memory heap functions
Heap * heapStuff(int totalSize);
void * ANMemoryNodeSplitToSize (ANMemoryNode * node, int size);
void * ANMemoryHeapGetMemory (ANMemoryHeap * heap, int size);
void ANMemoryNodeFreeMemory (ANMemoryNode * node, void * ptr);
void ANMemoryHeapFreeMemory (ANMemoryHeap * heap, void * ptr);
bool ANMemoryNodeDefragment (ANMemoryNode * node);
void ANMemoryHeapDefragment (ANMemoryHeap * heap);
void ANMemoryHeapFree (ANMemoryHeap * heap);
int ANMmeoryNodeGetSize (ANMemoryNode * node, void * ptr);
int ANMemoryHeapGetSize (ANMemoryHeap * heap, void * ptr);


