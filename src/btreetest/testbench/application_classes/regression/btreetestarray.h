/************************************************************
**
** file:	btreetestarray.h
** author:	Andreas Steffens
** license:	LGPL v3
**
** description:
**
** This file contains array application class code derived
** from the b-tree framework's array data class to allow
** for the array data class being tested by having
** the array application class act as a wrapper.
**
************************************************************/

#ifndef	BTREETESTARRAY_H
#define	BTREETESTARRAY_H

#include <stdint.h>

#include <list>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "testbench/application_classes/regression/base/btreetestbaselinear.h"

#include <btreearray.h>

template<class _t_datalayerproperties>
class CBTreeArrayTestSubscriptAccessWrapper;

typedef struct arrayEntry_s
{
	arrayEntry_s ()
	{
		nData;
		nDebug;
	}
	
	arrayEntry_s (uint32_t _nData, uint32_t _nDebug)
	{
		nData = _nData;
		nDebug = _nDebug;
	}

	uint32_t		nData;
	uint32_t		nDebug;

	bool			operator== (const struct arrayEntry_s sOperand) const
	{
		return ((nData == sOperand.nData) && (nDebug == sOperand.nDebug));
	}

	bool			operator!= (const struct arrayEntry_s sOperand) const
	{
		return ((nData != sOperand.nData) || (nDebug != sOperand.nDebug));
	}
} arrayEntry_t;

template<class _t_datalayerproperties = CBTreeIOpropertiesRAM <> >
class CBTreeTestArray
	:	public CBTreeTestBaseLinear
				<
					CBTreeArray <arrayEntry_t, _t_datalayerproperties>, 
					::std::list<arrayEntry_t>, 
					arrayEntry_t, 
					_t_datalayerproperties
				>
{
public:

	typedef CBTreeTestArray											CBTreeTestArray_t;

	typedef CBTreeTestBaseLinear<
									CBTreeArray <arrayEntry_t, _t_datalayerproperties>, 
									::std::list<arrayEntry_t>, 
									arrayEntry_t, 
									_t_datalayerproperties
								>									CBTreeTestBaseLinear_t;

	typedef arrayEntry_t											value_type;
	typedef typename _t_datalayerproperties::size_type				size_type;
	typedef typename _t_datalayerproperties::node_iter_type			node_iter_type;
	typedef typename _t_datalayerproperties::sub_node_iter_type		sub_node_iter_type;
	typedef _t_datalayerproperties									data_layer_properties_type;
	typedef typename _t_datalayerproperties::data_layer_type		data_layer_type;
	
	typedef value_type&												reference;
	typedef const value_type&										const_reference;
	typedef value_type*												pointer;
	typedef const value_type*										const_pointer;
	typedef	typename ::std::make_signed<size_type>::type			difference_type;

	typedef CBTreeArray<value_type, _t_datalayerproperties>			CBTreeArray_t;

	typedef typename CBTreeArray_t::CBTreeBaseDefaults_t			CBTreeBaseDefaults_t;

	typedef typename CBTreeArray_t::iterator						iterator;
	typedef typename CBTreeArray_t::const_iterator					const_iterator;
	typedef typename CBTreeArray_t::reverse_iterator				reverse_iterator;
	typedef typename CBTreeArray_t::const_reverse_iterator			const_reverse_iterator;

	typedef std::list<value_type>									reference_t;
	
						CBTreeTestArray<_t_datalayerproperties>
													(_t_datalayerproperties &rDataLayerProperties, sub_node_iter_type nNodeSize, reference_t *pClRef);

						CBTreeTestArray<_t_datalayerproperties>
													(const CBTreeTestArray<_t_datalayerproperties> &rContainer, const bool bAssign = true);

						CBTreeTestArray<_t_datalayerproperties>
													(CBTreeTestArray<_t_datalayerproperties> &&rRhsContainer);

						~CBTreeTestArray<_t_datalayerproperties>
													();

	template<class _t_iterator>
	void				assign						(_t_iterator sItFirst, _t_iterator sItLast);
	void				assign						(const size_type nNewSize, const value_type& rVal);

	void				push_back					(const value_type& rData);

	void				pop_back					();

	template<class _t_iterator>
	iterator			insert						(const_iterator sCIterPos, _t_iterator sItFirst, _t_iterator sItLast);

	iterator			insert						(const_iterator sCIterPos, const value_type& rData);
	iterator			insert						(const_iterator sCIterPos, const size_type nLen, const value_type& rData);

	iterator			erase						(const_iterator sCIterPos);
	iterator			erase						(const_iterator sCIterFirst, const_iterator sCIterLast);

	void				swap						(CBTreeTestArray &rArray);

	void				clear						();

	bool				operator==					(const CBTreeTestArray &rArray) const;
	bool				operator!=					(const CBTreeTestArray &rArray) const;

	CBTreeTestArray<_t_datalayerproperties>
						&operator=					(const CBTreeTestArray<_t_datalayerproperties> &rContainer);

	CBTreeTestArray<_t_datalayerproperties>
						&operator=					(CBTreeTestArray<_t_datalayerproperties> &&rRhsContainer);

protected:

	bool				show_data					(std::ofstream &ofs, std::stringstream &rstrData, std::stringstream &rszMsg, const node_iter_type nNode, const sub_node_iter_type nSubPos) const;

	bool				set_at						(const size_type nPos, const value_type &rData);
	bool				get_at						(const size_type nPos, value_type &rData) const;

	void		_swap								(CBTreeTestArray<_t_datalayerproperties> &rContainer);
};

#endif // BTREETESTARRAY_H

#include "btreetestarray.cpp"
