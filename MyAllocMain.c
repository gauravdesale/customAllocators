#import <Foundation/Foundation.h>
#import "ANCustomAllocation.h"

int main (int argc, const char * argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];//make a method 
	
	CFAllocatorRef alloc = AllocatorWithNewHeap();//make the new heap with the new settings 
	
	CFStringRef myString = CFStringCreateWithBytes(alloc, "Hello world!", 12, kCFStringEncodingASCII, FALSE);//new objects that are cf objects with the methods we defined before like the char array
	CFShow(myString);
	
	CFMutableArrayRef array = CFArrayCreateMutable(alloc, 3, NULL);//make an array of smt i dont remember 
	CFArrayAppendValue(array, "Yo");//append values to the newly created values 
	
	CFRelease(array);//not using it anymore
	CFRelease(myString);
	
	CFRelease(alloc);
	
    [pool drain];//idk lol
    return 0;
}
