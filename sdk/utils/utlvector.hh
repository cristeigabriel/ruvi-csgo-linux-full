//
//  ruvi base
//

#pragma once

template <class t, class m = int>
class utl_memory {
public:
  t &operator[](m i) { return memory[i]; }

protected:
  t * memory;
  int allocation_size;
  int grow_size;
};

template <class t, class a = utl_memory<t>>
class utl_vector {
  typedef a allocator;

public:
  t &operator[](std::size_t index) { return memory[index]; }

  int count() const { return size; }

  void set_size(std::size_t value) { size = value; }

protected:
  allocator memory;
  int       size;
  t *       elements;
};