#import <CoreFoundation/CoreFoundation.h>
#import "ANBuddyAlloc.h"

const void * CustomAllocatorRetainCall(const * void info);//making a function that returns a memory allocator type to retain the information of the call to the memory allocator
void customAllocatorReleaseCall(const void * info);//making a function that releases the call and this means it gets rid od it instead of remembering it
CFSringRef CustomAllocatorCreateDescription(const void * info);//making a function that returns a string rf object that describes the object being allocated
void * CustomAllocatorAllocate (CFIndex allocSize, CFOptionFlags hint, void * info);//making an allocator function that is the main one to allocate memory according to the size of the object, the flags hint, and the information of the allocation 
void * CustomAllocatorReallocate (void * ptr, CFIndex newsize, CFOptionFlags hint, void * info);//allocate the thing again if the first one didnt work and another one cokpletely is unnecessary 
void CustomAllocatorDeallocate(void * ptr, void * info);//remove the allocation of the object and the other info should already be there 
CFIndex CustomAllocatorPreferredSize(CFIndex size, CFOptionFlags hint, void * info);//specify a size of the allocaition for the other functions using the size of the object and flags and the info pointer to the memory available 
CFAllocatorRef AllocatorWithBuddyHeap(Heap * heap );//using the heap struct we made last time to allocate with the same manner as the heap variable 
CFAllocatorRef ANMemoryWithNewHeap();//make a new heap object that the previous method uses

