/************************************************************
**
** file:	btreetestmultiset.h
** author:	Andreas Steffens
** license:	LGPL v3
**
** description:
**
** This file contains multi set application class code derived
** from the b-tree framework's multi set class to allow
** for the multi set class being tested by having
** the multi set application class act as a wrapper.
**
************************************************************/

#ifndef BTREETESTMULTISET_H
#define	BTREETESTMULTISET_H

#include <stdint.h>

#include <set>
#include <utility>
#include <sstream>

#include "testbench/common/btreetestcommon.h"
#include "testbench/application_classes/regression/base/btreetestbaseset.h"

#include "specific_data_classes/btreemultiset.h"

template<class _t_datalayerproperties>
class CBTreeTestMultiSet
	:	public CBTreeTestBaseSet
				<
					CBTreeMultiSet<uint32_t, _t_datalayerproperties>, 
					::std::multiset<uint32_t>, 
					uint32_t, 
					_t_datalayerproperties
				>
{
public:

	typedef CBTreeTestMultiSet											CBTreeTestMultiSet_t;

	typedef CBTreeTestBaseSet
		<
			CBTreeMultiSet<uint32_t, _t_datalayerproperties>, 
			::std::multiset<uint32_t>, 
			uint32_t, 
			_t_datalayerproperties
		>																CBTreeTestBaseSet_t;

	typedef uint32_t													value_type;
	typedef uint32_t													key_type;
	typedef typename _t_datalayerproperties::size_type					size_type;
	typedef typename _t_datalayerproperties::node_iter_type				node_iter_type;
	typedef typename _t_datalayerproperties::sub_node_iter_type			sub_node_iter_type;
	typedef _t_datalayerproperties										data_layer_properties_type;
	typedef typename _t_datalayerproperties::data_layer_type			data_layer_type;

	typedef value_type&													reference;
	typedef const value_type&											const_reference;
	typedef value_type*													pointer;
	typedef const value_type*											const_pointer;
	typedef	typename ::std::make_signed<size_type>::type				difference_type;

	typedef CBTreeMultiSet<key_type, _t_datalayerproperties>			CBTreeMultiSet_t;

	typedef typename CBTreeMultiSet_t::CBTreeAssociativeIf_t			CBTreeAssociativeIf_t;

	typedef typename CBTreeMultiSet_t::CBTreeIf_t						CBTreeIf_t;

	typedef typename CBTreeMultiSet_t::CBTreeDefaults_t					CBTreeDefaults_t;

	typedef typename CBTreeMultiSet_t::CBTreeBaseIf_t					CBTreeBaseIf_t;

	typedef typename CBTreeMultiSet_t::CBTreeBaseDefaults_t				CBTreeBaseDefaults_t;

	typedef typename CBTreeMultiSet_t::iterator							iterator;
	typedef typename CBTreeMultiSet_t::const_iterator					const_iterator;
	typedef typename CBTreeMultiSet_t::reverse_iterator					reverse_iterator;
	typedef typename CBTreeMultiSet_t::const_reverse_iterator			const_reverse_iterator;

	typedef	typename CBTreeMultiSet_t::key_compare						key_compare;
	typedef typename CBTreeMultiSet_t::value_compare					value_compare;

	struct data_s
	{
		key_type			nKey;
	};

	typedef ::std::multiset<key_type>									reference_t;

							CBTreeTestMultiSet<_t_datalayerproperties>
								(_t_datalayerproperties &rDataLayerProperties, sub_node_iter_type nNodeSize, reference_t *pClRefData);

							CBTreeTestMultiSet<_t_datalayerproperties>
								(const CBTreeTestMultiSet<_t_datalayerproperties> &rContainer, const bool bAssign = true);

							CBTreeTestMultiSet<_t_datalayerproperties>
								(CBTreeTestMultiSet<_t_datalayerproperties> &&rRhsContainer);

							~CBTreeTestMultiSet<_t_datalayerproperties>
								();

	CBTreeTestMultiSet_t &	operator=				(const CBTreeTestMultiSet_t &rContainer);
	CBTreeTestMultiSet_t &	operator=				(CBTreeTestMultiSet_t &&rRhsContainer);

	template<class _t_iterator>
	void					insert					(_t_iterator sItFirst, _t_iterator sItLast);
	
	template<class _t_iterator, class _t_ref_iterator>
	void					insert					(_t_iterator sItFirst, _t_iterator sItLast);
	
	iterator				insert					(const value_type &rData);

	template<class ..._t_va_args>
	iterator				insert					(const_iterator sCIterHint, _t_va_args && ... rrArgs);

	iterator				erase					(const_iterator sCIterPos);
	size_type				erase					(const key_type &rKey);
	iterator				erase					(const_iterator sCIterFirst, const_iterator sCIterLast);

	void					swap					(CBTreeTestMultiSet &rContainer);

	void					clear					();

	bool					operator==				(const CBTreeTestMultiSet &rTMM) const;
	bool					operator!=				(const CBTreeTestMultiSet &rTMM) const;

protected:

	void					_swap					(CBTreeTestMultiSet_t &rContainer);

	bool					show_data				(std::ofstream &ofs, std::stringstream &rstrData, std::stringstream &rszMsg, const node_iter_type nNode, const sub_node_iter_type nSubPos) const;
	
public:

	friend class CBTreeIterator<CBTreeIf_t>;
	friend class CBTreeConstIterator<CBTreeIf_t>;
	friend class CBTreeReverseIterator<iterator>;
	friend class CBTreeConstReverseIterator<const_iterator>;
};

#endif // !BTREETESTMULTISET_H

#include "btreetestmultiset.cpp"
