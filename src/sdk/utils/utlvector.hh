//
//  ruvi base
//

#pragma once

template <class t, class m = int> class utl_memory {
public:
  t &operator[](m i) { return m_memory[i]; }

protected:
  t *m_memory;
  int m_allocation_size;
  int m_grow_size;
};

template <class t, class a = utl_memory<t>> class utl_vector {
  typedef a allocator;

public:
  t &operator[](std::size_t index) { return m_memory[index]; }

  int count() const { return m_size; }

  void set_size(std::size_t value) { m_size = value; }

protected:
  allocator m_memory;
  int m_size;
  t *m_elements;
};