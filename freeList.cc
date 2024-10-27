#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  long int * head = inRAM;

  int Msize = size;

}

long int*
freeList::reserve_space( int size ) {
  
  long int* reservedMemory = (long int*)malloc((size + 2) * sizeof(long int));
  if (!reservedMemory) {
    std::cerr << "Memory allocation failed!" << std::endl;
    return nullptr; 
   }
  head = reservedMemory + 2;

  reservedMemory[0] = size;
  reservedMemory[1] = 0;

  return head; 
}

void
freeList::free_space( long int* location ) {
  long int* header = location - 2;
  header[1] = (long int)head; 
  head = header; 
}

void
freeList::coalesce_forward() {
long int* current = head;

while (current) {
            
  int size = current[0];

  
  long int* nextChunk = (long int*)((char*)current + (size + 2) * sizeof(long int));

  
  if (nextChunk[0] > 0) {
                
    current[0] += nextChunk[0] + 2; 
    current[1] = nextChunk[1]; 
  } else {
    
    current = nextChunk;
   }
  }


}


void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
