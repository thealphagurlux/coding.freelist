#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM;
  head[0] = size -2;
  head[1] = NULL;

}

long int*
freeList::reserve_space( int size ) {

  long int* current = head;
  
  while (current != NULL) {

    if (size > current[0]) {
      std::cerr << "Memory allocation failed!" << std::endl;

      current = (long int * )current[1];

    }
    else{

      head = current + size + 2;

      head[1] = current[1];

      head[0] = current[0] - size - 2;

      current[0] = size;

    return current;}

  }

  return nullptr; 
  
}

void
freeList::free_space( long int* location ) {
  location[1] = (long int )head;
  head = location;
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
