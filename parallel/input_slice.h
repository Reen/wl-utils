#ifndef INPUT_SLICE_H_DR9TZOE4
#define INPUT_SLICE_H_DR9TZOE4

#include <cstring>
#include "tbb/tbb_allocator.h"

class InputSlice {
  //! Pointer to one past last character in slice
  char* logical_end;
  //! Pionter to one past last available byte in slice.
  char* physical_end;
public:
  //! Allocate a TextSlice object that can hold up to max_size characters.
  static InputSlice* allocate( size_t max_size ) {
      // +1 leaves room for a terminating null character.
      InputSlice* t = (InputSlice*)tbb::tbb_allocator<char>().allocate( sizeof(InputSlice)+max_size+1 );
      t->logical_end = t->begin();
      t->physical_end = t->begin()+max_size;
      return t;
  }
  //! Free a TextSlice object 
  void free() {
      tbb::tbb_allocator<char>().deallocate((char*)this,size());
  }
  //! Pointer to beginning of sequence
  char* begin() {return (char*)(this+1);}
  //! Pointer to one past last character in sequence
  char* end() {return logical_end;}
  //! Length of sequence
  size_t size() const {return logical_end-(char*)(this+1);}
  //! Maximum number of characters that can be appended to sequkence
  size_t avail() const {return physical_end-logical_end;}
  //! Append sequence [first,last) to this sequence.
  void append( char* first, char* last ) {
      memcpy( logical_end, first, last-first );
      logical_end += last-first;
  }
  //! Set end to given value.
  void set_end( char* p ) {logical_end=p;}
};


#endif /* end of include guard: INPUT_SLICE_H_DR9TZOE4 */
