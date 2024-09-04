#include <assert.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32,4,5,5> AXI_VAL;

// --------------------------------------------------------
// functions to insert and extract elements from an axi stream
// includes conversion to correct data type

/*
ap_axi_sdata.h::

#include "ap_int.h"

template<int D,int U,int TI,int TD>
struct ap_axis{
 ap_int<D>    data;
 ap_uint<D/8> keep;
 ap_uint<D/8> strb;
 ap_uint<U>   user;
 ap_uint<1>   last;
 ap_uint<TI>  id;
 ap_uint<TD>  dest;
};
 */

template <typename T>
T pop_stream(ap_axiu <sizeof(T)*8,4,5,5> const &e)
{
#pragma HLS INLINE

	assert(sizeof(T) == sizeof(int)); // It will only support a dtype of 32bits (4bytes)
	union
	{
		int ival;
		T oval;
	} converter;
	converter.ival = e.data;
	T ret = converter.oval;

	volatile ap_uint<sizeof(T)> strb = e.strb;
	volatile ap_uint<sizeof(T)> keep = e.keep;
	volatile ap_uint<4> user = e.user;
	volatile ap_uint<1> last = e.last;
	volatile ap_uint<5> id = e.id;
	volatile ap_uint<5> dest = e.dest;

	return ret;
}

template <typename T> ap_axiu <sizeof(T)*8,4,5,5> push_stream(T const &v, bool last = false)
{
#pragma HLS INLINE
	ap_axiu<sizeof(T)*8,4,5,5> e;

	assert(sizeof(T) == sizeof(int));
	union
	{
		int oval;
		T ival;
	} converter;
	converter.ival = v;
	e.data = converter.oval;

	// set it to sizeof(T) ones
	e.strb = -1;
	e.keep = 15; //e.strb;
	e.user = 0;
	e.last = last ? 1 : 0;
	e.id = 0;
	e.dest = 0;
	return e;
}

// you can use the template as follows.
// in_matrix[i][j] = pop_stream<float>(in_matrix[k]);
