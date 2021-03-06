#ifndef _CALLINSTACK_H_
#define _CALLINSTACK_H_

#include "call_in_stack_config.h"

//1.We have arguments passing stack cost and previous sp pointer saving cost in stack before calling.
//  So we use get_stack_base<cost + 1>(stack_buffer + length) as stack_base.
//2.Some versions of GCC can not support "call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0) > *p = 0"
//  to break overload ambiguous(ambiguous error has higher priority than direct SFINAE?). So we use inner type of call_in_stack_impl::static_asserter instead.
//3.The assert "i == call_in_stack_impl::function_property<T>::arguments_count && (typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)"
//  is to help the overload resolution between "i fixed arguments, j variable arguments" and "i+1 fixed arguments, j-1 variable arguments"

#define CALL_IN_STACK_DEFINE(i, j) \
template <MACRO_JOIN(RECURSIVE_FUNC_, j)(define_typenames_ex_begin, define_typenames_ex, define_typenames_ex) typename T > \
DLL_LOCAL inline typename call_in_stack_impl::function_property<T>::return_type call_in_stack(T dest_func  \
MACRO_JOIN(RECURSIVE_FUNC_,i)(define_typeargs_begin, define_typeargs, define_typeargs) \
MACRO_JOIN(RECURSIVE_FUNC_,j)(define_type_args_ex_begin, define_type_args_ex, define_type_args_ex_end) \
, typename call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)>::type *p = 0){ \
	using namespace call_in_stack_impl; \
	const int default_stack_length = 16*1024; \
	struct auto_stack_buffer{ \
		char* stack_buffer; \
		auto_stack_buffer(unsigned int the_size):stack_buffer(new char[the_size]){} \
		~auto_stack_buffer(){delete []stack_buffer;} \
	}z(default_stack_length); \
	typedef typename function_property<T>::return_type return_type; \
	typedef args_list<MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) void> arg_types;\
    return return_type_adapter<return_type>::forward(do_call< \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) \
		typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments>( \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin, define_args, define_args) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_begin, define_args_ex, define_args_ex) \
		(void*)dest_func, get_stack_base< STACK_COST(arg_types) >(z.stack_buffer + default_stack_length) )); \
} \
template <MACRO_JOIN(RECURSIVE_FUNC_, j)(define_typenames_ex_begin, define_typenames_ex, define_typenames_ex) typename T > \
DLL_LOCAL inline typename call_in_stack_impl::function_property<T>::return_type call_in_stack(unsigned int stack_length, T dest_func  \
MACRO_JOIN(RECURSIVE_FUNC_,i)(define_typeargs_begin, define_typeargs, define_typeargs) \
MACRO_JOIN(RECURSIVE_FUNC_,j)(define_type_args_ex_begin, define_type_args_ex, define_type_args_ex_end) \
, typename call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)>::type *p = 0){ \
	struct auto_stack_buffer{ \
		char* stack_buffer; \
		auto_stack_buffer(unsigned int the_size):stack_buffer(new char[the_size]){} \
		~auto_stack_buffer(){delete []stack_buffer;} \
	}z(stack_length); \
    using namespace call_in_stack_impl; \
	typedef typename function_property<T>::return_type return_type; \
	typedef args_list<MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) void> arg_types;\
    return return_type_adapter<return_type>::forward(do_call< \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) \
		typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments>( \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin, define_args, define_args) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_begin, define_args_ex, define_args_ex) \
		(void*)dest_func, get_stack_base< STACK_COST(arg_types) >(z.stack_buffer + stack_length) )); \
} \
template <MACRO_JOIN(RECURSIVE_FUNC_, j)(define_typenames_ex_begin, define_typenames_ex, define_typenames_ex) typename T > \
DLL_LOCAL inline typename call_in_stack_impl::function_property<T>::return_type call_in_stack(char* stack_buffer, unsigned int stack_length, T dest_func \
MACRO_JOIN(RECURSIVE_FUNC_,i)(define_typeargs_begin, define_typeargs, define_typeargs) \
MACRO_JOIN(RECURSIVE_FUNC_,j)(define_type_args_ex_begin, define_type_args_ex, define_type_args_ex_end) \
, typename call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)>::type *p = 0){ \
    using namespace call_in_stack_impl; \
	typedef typename function_property<T>::return_type return_type; \
	typedef args_list<MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) void> arg_types;\
    return return_type_adapter<return_type>::forward(do_call< \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) \
		typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments>( \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin, define_args, define_args) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_begin, define_args_ex, define_args_ex) \
		(void*)dest_func, get_stack_base< STACK_COST(arg_types) >(stack_buffer + stack_length) )); \
} \
template <MACRO_JOIN(RECURSIVE_FUNC_, j)(define_typenames_ex_begin, define_typenames_ex, define_typenames_ex) typename T, typename B, int N > \
DLL_LOCAL inline typename call_in_stack_impl::function_property<T>::return_type call_in_stack(B (&stack_buffer)[N], T dest_func  \
MACRO_JOIN(RECURSIVE_FUNC_,i)(define_typeargs_begin, define_typeargs, define_typeargs) \
MACRO_JOIN(RECURSIVE_FUNC_,j)(define_type_args_ex_begin, define_type_args_ex, define_type_args_ex_end) \
, typename call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)>::type *p = 0){ \
    using namespace call_in_stack_impl; \
	typedef typename function_property<T>::return_type return_type; \
	typedef args_list<MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) void> arg_types;\
    return return_type_adapter<return_type>::forward(do_call< \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) \
		typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments>( \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin, define_args, define_args) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_begin, define_args_ex, define_args_ex) \
		(void*)dest_func, get_stack_base< STACK_COST(arg_types) >((char*)(&(stack_buffer[N])) ))); \
}
BI_TWO_BATCH_FUNC1(10, CALL_IN_STACK_DEFINE)
//BI_TWO_BATCH_FUNC1 will render 11*10 times and we do not support pure variable argument lists without any fixed argument(comparing printf(...) and printf(char*,...); the previous function does not make sense)
CALL_IN_STACK_DEFINE(0,0)
#undef CALL_IN_STACK_DEFINE

//call_in_stack_safe is safe for recursively call_in_stack with same stack_buffer(maybe it is a global variable?) as stack.
#define IS_IN_CALL_STACK(dest, stack_begin, stack_end) \
	(((word_int_t)(((word_int_t)(dest) - (word_int_t)(stack_begin)) ^ ((word_int_t)(stack_end) - (word_int_t)dest))) > 0)

#define CALL_IN_STACK_SAFE_DEFINE(i, j) \
template <MACRO_JOIN(RECURSIVE_FUNC_, j)(define_typenames_ex_begin, define_typenames_ex, define_typenames_ex) typename T > \
DLL_LOCAL inline typename call_in_stack_impl::function_property<T>::return_type call_in_stack_safe( char* stack_buffer, unsigned int stack_length, T dest_func \
MACRO_JOIN(RECURSIVE_FUNC_,i)(define_typeargs_begin, define_typeargs, define_typeargs) \
MACRO_JOIN(RECURSIVE_FUNC_,j)(define_type_args_ex_begin, define_type_args_ex, define_type_args_ex_end) \
, typename call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)>::type *p = 0){ \
	using namespace call_in_stack_impl; \
	DEF_SP(sp_value);\
	if(IS_IN_CALL_STACK(sp_value, stack_buffer, stack_buffer + stack_length)){ \
		return dest_func( \
			MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin_org, define_args_org, define_args_end_org) \
			MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_c_begin, define_args_ex_c, define_args_ex_c_end) \
		); \
	} \
	else{ \
        typedef typename function_property<T>::return_type return_type; \
		typedef args_list<MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
			MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) void> arg_types;\
		return return_type_adapter<return_type>::forward(do_call< \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) \
		typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments>( \
			MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin, define_args, define_args) \
			MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_begin, define_args_ex, define_args_ex) \
			(void*)dest_func, get_stack_base< STACK_COST(arg_types) >(stack_buffer + stack_length) )); \
	} \
} \
template <MACRO_JOIN(RECURSIVE_FUNC_, j)(define_typenames_ex_begin, define_typenames_ex, define_typenames_ex) typename T, typename B, int N > \
DLL_LOCAL inline typename call_in_stack_impl::function_property<T>::return_type call_in_stack_safe(B (&stack_buffer)[N], T dest_func \
MACRO_JOIN(RECURSIVE_FUNC_,i)(define_typeargs_begin, define_typeargs, define_typeargs) \
MACRO_JOIN(RECURSIVE_FUNC_,j)(define_type_args_ex_begin, define_type_args_ex, define_type_args_ex_end) \
, typename call_in_stack_impl::static_asserter< i == call_in_stack_impl::function_property<T>::arguments_count && (call_in_stack_impl::function_property<T>::has_variable_arguments || j == 0)>::type *p = 0){ \
	using namespace call_in_stack_impl; \
	DEF_SP(sp_value);\
	if(IS_IN_CALL_STACK(sp_value, &stack_buffer, &(stack_buffer[N]))){ \
		return dest_func( \
			MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin_org, define_args_org, define_args_end_org) \
			MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_c_begin, define_args_ex_c, define_args_ex_c_end) \
		); \
	} \
	else{ \
        typedef typename function_property<T>::return_type return_type; \
		typedef args_list<MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
			MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) void> arg_types;\
		return return_type_adapter<return_type>::forward(do_call< \
		MACRO_JOIN(RECURSIVE_FUNC_,i)(define_rtypes_begin, define_rtypes, define_rtypes) \
		MACRO_JOIN(RECURSIVE_FUNC_,j)(define_rtype_ex_begin, define_rtype_ex, define_rtype_ex) \
		typename return_type_adapter<return_type>::forward_type, call_in_stack_impl::function_property<T>::has_variable_arguments>( \
			MACRO_JOIN(RECURSIVE_FUNC_,i)(define_args_begin, define_args, define_args) \
			MACRO_JOIN(RECURSIVE_FUNC_,j)(define_args_ex_begin, define_args_ex, define_args_ex) \
			(void*)dest_func, get_stack_base< STACK_COST(arg_types) >((char*)(&(stack_buffer[N])) ))); \
	} \
}

BI_TWO_BATCH_FUNC1(10, CALL_IN_STACK_SAFE_DEFINE)
//BI_TWO_BATCH_FUNC1 will render 10*11 times and we do not support pure variable argument lists without any fixed argument(comparing printf(...) and printf(char*,...); the previous function does not make sense)
CALL_IN_STACK_SAFE_DEFINE(0,0)
#undef CALL_IN_STACK_SAFE_DEFINE


//from_member_fun(class_obj, member_name,...): casting member function(either virtual or non-virtual) to function pointer
//from_nonvirtual_member_fun(class_obj, member_name,...): casting non-virtual member function to function pointer, faster than from_member_fun
//from_virtual_member_fun(class_obj, member_name,...): casting virtual member function to function pointer, faster than from_member_fun
//from_functor(class_obj,...): casting functor to function pointer

#define MEMBER_FUN_PTR(class_obj, member_name) (&call_in_stack_impl::change_ref_to_pointer<__typeof__(class_obj)>::content_type::member_name)

#define from_member_fun_impl(wrapper, class_obj, member_name,...) \
    &wrapper<__typeof__(MEMBER_FUN_PTR(class_obj, member_name))>::exec, \
    wrapper<__typeof__(MEMBER_FUN_PTR(class_obj, member_name))> (class_obj, MEMBER_FUN_PTR(class_obj, member_name)), \
    ##__VA_ARGS__

// adapter of member function
#define from_member_fun(class_obj, member_name,...) from_member_fun_impl(call_in_stack_impl::member_function_wrapper, class_obj, member_name,##__VA_ARGS__)

#define ENABLE_FROM_MEMBER_FUN_FAST

#if defined ENABLE_FROM_MEMBER_FUN_FAST

    #define from_nonvirtual_member_fun(class_obj, member_name,...) from_nonvirtual_member_fun_fast(class_obj, member_name,##__VA_ARGS__)

    #if defined DISABLE_VTABLE_EXPANSION
        #define from_virtual_member_fun(class_obj, member_name,...) from_member_fun_impl(call_in_stack_impl::virtual_member_function_wrapper, class_obj, member_name,##__VA_ARGS__)
    #else
        #define from_virtual_member_fun(class_obj, member_name,...) from_virtual_member_fun_fast(class_obj, member_name,##__VA_ARGS__)
    #endif // DISABLE_VTABLE_EXPANSION

#else
    #define from_nonvirtual_member_fun(class_obj, member_name,...) from_member_fun_impl(call_in_stack_impl::nonvirtual_member_function_wrapper, class_obj, member_name,##__VA_ARGS__)
    #define from_virtual_member_fun(class_obj, member_name,...) from_member_fun_impl(call_in_stack_impl::virtual_member_function_wrapper, class_obj, member_name,##__VA_ARGS__)
#endif // ENABLE_FROM_MEMBER_FUN_FAST

#define from_nonvirtual_member_fun_fast(class_obj, member_name,...) \
    ((call_in_stack_impl::member_function_fast<__typeof__(MEMBER_FUN_PTR(class_obj, member_name))>)\
        (MEMBER_FUN_PTR(class_obj, member_name))).un.st.function_ptr, \
    &class_obj, \
    ##__VA_ARGS__

#define GET_FUNCTION_PTR_VIRTUAL(class_obj, instance, instance_type)  (*(instance_type::funtion_ptr_t*)(((char**)(instance_type::class_type*)(&class_obj))[0] + instance.un.vst.vtable_offset_1 - 1 ))

#define from_virtual_member_fun_fast(class_obj, member_name,...) \
    GET_FUNCTION_PTR_VIRTUAL(class_obj, ((call_in_stack_impl::member_function_fast<__typeof__(MEMBER_FUN_PTR(class_obj, member_name))>)\
        (MEMBER_FUN_PTR(class_obj, member_name))), call_in_stack_impl::member_function_fast<__typeof__(MEMBER_FUN_PTR(class_obj, member_name))>), \
    &class_obj, \
    ##__VA_ARGS__

// adapter of functor or lambda
#define from_functor(class_obj,...) from_nonvirtual_member_fun(class_obj, operator(), ##__VA_ARGS__)

#endif
