//
//  Ruvi - @special-parakeet.git
//

#pragma once

// includes
#include <cstring>
#include <cassert>
#include <stdint.h>

class dynamic_table {
public:
	constexpr dynamic_table()
			: m_new_vmt{nullptr}
			, m_old_vmt{nullptr} {}

	~dynamic_table() {
		if(m_new_vmt)
			delete[] (m_new_vmt - 1);
	}

protected:
	auto initialize(void** original_table) -> void {
		m_old_vmt = original_table;

		size_t size = 0;
		while(m_old_vmt[size])
			++size;

		m_new_vmt = (new void*[size + 1]) + 1;
		std::memcpy(m_new_vmt - 1, m_old_vmt - 1, sizeof(void*) * (size + 1));
	}

	auto initialize_and_hook_instance(void* inst) -> bool {

		auto& vtbl = *reinterpret_cast<void***>(inst);
		auto initialized = false;

		if(!m_old_vmt) {
			initialized = true;
			initialize(vtbl);
		}

		hook_instance(inst);
		return initialized;
	}

	constexpr auto leak_table() -> void {
		m_new_vmt = nullptr;
	}

	auto hook_instance(void* inst) const -> void {
		auto& vtbl = *reinterpret_cast<void***>(inst);
		assert(vtbl == m_old_vmt || vtbl == m_new_vmt);
		vtbl = m_new_vmt;
	}

	auto unhook_instance(void* inst) const -> void {
		auto& vtbl = *reinterpret_cast<void***>(inst);
		assert(vtbl == m_old_vmt || vtbl == m_new_vmt);
		vtbl = m_old_vmt;
	}

	template <typename fn>
	auto hook_function( fn hooked_fn, const std::size_t index ) -> fn {
		m_new_vmt[index] = (void*)(hooked_fn);
		return (fn)(m_old_vmt[index]);
	}

	template<typename fn>
	auto apply_hook(std::size_t index) -> void {
		fn::original = hook_function(&fn::hooked, index);
	}

	template <typename fn = uintptr_t>
	auto get_original_function(const int index) -> fn {
		return (fn)(m_old_vmt[index]);
	}
private:
	void** m_new_vmt = nullptr;
	void** m_old_vmt = nullptr;
};

class vmt_smart_hook : dynamic_table
{
public:
	vmt_smart_hook(void* class_base) : m_class{class_base} {
		initialize_and_hook_instance(class_base);
	}

	~vmt_smart_hook() {
		unhook_instance(m_class);
	}

	auto rehook() const -> void {
		hook_instance(m_class);
	}

	auto unhook() const -> void {
		unhook_instance(m_class);
	}

	using dynamic_table::apply_hook;
	using dynamic_table::get_original_function;
	using dynamic_table::hook_function;

private:
	void* m_class = nullptr;
};

class vmt_hook : dynamic_table {
public:
	constexpr vmt_hook() {}

	~vmt_hook() {
		leak_table();
	}

	using dynamic_table::apply_hook;
	using dynamic_table::get_original_function;
	using dynamic_table::hook_function;
	using dynamic_table::hook_instance;
	using dynamic_table::unhook_instance;
	using dynamic_table::initialize;
	using dynamic_table::initialize_and_hook_instance;
};













