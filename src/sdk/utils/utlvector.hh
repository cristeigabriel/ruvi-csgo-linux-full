//
//  ruvi base
//

#pragma once

template <class t, class m = int>
class utl_memory {
public:
  t &operator[](m index) { return memory[index]; }

protected:
  t * memory;
  int allocation_count;
  int grow_size;
};

template <class t, class a = utl_memory<t>>
class utl_vector {
  typedef a allocator;

public:
  t &operator[](int index) { return memory[index]; }

  int count() const { return size; }

  void set_size(int value) { size = value; }

protected:
  allocator memory;
  int       size;
  t *       elements;
};