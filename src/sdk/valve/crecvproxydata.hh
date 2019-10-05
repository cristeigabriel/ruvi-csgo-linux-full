//
//  ruvi base
//

#pragma once

struct recv_proxy_data_t;
struct recv_table_t;

typedef void (*fn)(recv_proxy_data_t *p_data, void *p_struct, void *p_out);

enum prop_type_t {
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY, // only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,	// an array of the base types (can't be of datatables).
	DPT_DataTable,
};

struct recv_prop_t {
  char *name;
  prop_type_t type;
  int flags;
  int string_buffer_size;
  bool inside_array;
  const void *extra_data;
  recv_prop_t *array_prop;
  void *array_length_alias;
  fn proxy_fn;
  void *data_table_alias_fn;
  recv_table_t *data_table;
  int offset;
  int element_stride;
  int elements;
  const char *parent_array_prop_name;
};

struct recv_table_t {
  recv_prop_t *p_props;
  int num_props;
  void *decoder;
  char *name;
  bool initialized;
  bool in_main_list;
};

class d_variant {
public:
  union {
    float data_float;
    long data_int;
    char *data_string;
    void *p_data;
    float data_vector[3];
  };
};

struct recv_proxy_data_t {
  const recv_prop_t *p_recv_prop;
  d_variant value;
  int element;
  int object_id;
};