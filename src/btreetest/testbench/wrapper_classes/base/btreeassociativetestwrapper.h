/************************************************************
**
** file:	btreeassociativetestwrapper.h
** author:	Andreas Steffens
** license:	LGPL v3
**
** description:
**
** This file contains the declaration of the associative container
** test class wrapping abstract accesses to associative container test class
** and a templatebased reference container instance, while making sure the
** associative container instance acts the same way as the abstract reference.
**
************************************************************/

#ifndef BTREEASSOCIATIVETESTWRAPPER_H
#define BTREEASSOCIATIVETESTWRAPPER_H

#include <stdint.h>

#include <sstream>

#include "abstract_data_classes/btreeassociative.h"

#include "testbench/application_classes/regression/btreetestkeysort.h"
#include "testbench/primitives/btreekeysorttestprimitive.h"

template<class _t_data, class _t_value, class _t_sizetype, class _t_ref_container>
class CBTreeAssociativeTestWrapper
{
public:

	typedef CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_sizetype, _t_ref_container>
																CBTreeAssociativeTestWrapper_t;
	
	typedef _t_ref_container									reference_t;

	typedef typename reference_t::iterator						iterator;
	typedef typename reference_t::const_iterator				const_iterator;
	typedef typename reference_t::reverse_iterator				reverse_iterator;
	typedef typename reference_t::const_reverse_iterator		const_reverse_iterator;

	typedef typename ::std::pair<iterator, iterator>				equal_range_type;
	typedef typename ::std::pair<const_iterator, const_iterator>	equal_range_const_type;

	typedef typename reference_t::value_type					value_type;
	typedef typename reference_t::key_type						key_type;
	typedef typename reference_t::size_type						size_type;

	typedef typename ::std::make_signed<size_type>::type		signed_size_type;

	typedef _t_data												value_test_type;
	typedef uint32_t											key_test_type;
	typedef _t_sizetype											size_test_type;

	typedef CBTreeAssociativeIf<_t_value, key_test_type, size_test_type>
																CBTreeAssociativeIf_t;

	typedef typename CBTreeAssociativeIf_t::iterator			test_iterator;

	typedef typename CBTreeAssociativeIf_t::const_iterator		test_const_iterator;

	typedef typename CBTreeAssociativeIf_t::reverse_iterator	test_reverse_iterator;

	typedef typename CBTreeAssociativeIf_t::const_reverse_iterator
																test_const_reverse_iterator;

								CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_sizetype, _t_ref_container>
																	(const uint32_t nNodeSize, const uint32_t nPageSize);

								CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_sizetype, _t_ref_container>
																	(const CBTreeAssociativeTestWrapper &rContainer);

								CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_sizetype, _t_ref_container>
																	(CBTreeAssociativeTestWrapper &&rRhsContainer);

	virtual						~CBTreeAssociativeTestWrapper<_t_data, _t_value, _t_sizetype, _t_ref_container>
																	();

	size_type					size								() const;

	void						clear								();

	iterator					begin								();
	iterator					end									();
	
	reverse_iterator			rbegin								();
	reverse_iterator			rend								();

	const_iterator				cbegin								() const;
	const_iterator				cend								() const;

	const_reverse_iterator		crbegin								() const;
	const_reverse_iterator		crend								() const;

	void						swap								(CBTreeAssociativeTestWrapper &rContainer);

	iterator					insert								(const value_type &rData, const bool bInsertNotEmplace = true);

	void						insert_hint							(const value_type &rData, const bool bInsertNotEmplace = true);

	iterator					erase								(const_iterator sCIterPos);
	size_type					erase								(key_type &rKey);
	iterator					erase								(const_iterator sCIterFirst, const_iterator sCIterLast);

	iterator					find								(key_type &rKey);
	const_iterator				find								(key_type &rKey) const;

	iterator					lower_bound							(key_type &rKey);
	const_iterator				lower_bound							(key_type &rKey) const;

	iterator					upper_bound							(key_type &rKey);
	const_iterator				upper_bound							(key_type &rKey) const;

	equal_range_type			equal_range							(key_type &rKey);
	equal_range_const_type		equal_range							(key_type &rKey) const;

	size_type					count								(key_type &rKey) const;

	size_type					serialize							(const size_type nStart, const size_type nLen, value_type *pData) const;

	void						set_iter_data						(const_iterator sCIter, const value_type &rData);

	void						unload								();

	bool						compare_individual_containers		(const CBTreeAssociativeTestWrapper &rContainer) const;

	void						set_hint_variation					(const size_type nHintVariation);

	CBTreeAssociativeTestWrapper &
								operator=							(const CBTreeAssociativeTestWrapper &rContainer);

	CBTreeAssociativeTestWrapper &
								operator=							(CBTreeAssociativeTestWrapper &&rRhsContainer);

	bool						operator==							(const CBTreeAssociativeTestWrapper &rContainer) const;
	bool						operator!=							(const CBTreeAssociativeTestWrapper &rContainer) const;

	void						show_integrity						(const char *pszPrefix);

protected:

	void						test								() const;

	void						disable_atomic_testing				() const;
	void						enable_atomic_testing				() const;

	void						instantiate_container_array			();

	uint32_t					get_num_containers					() const;

	virtual void				init_containers						(const uint32_t nNodeSize, const uint32_t nPageSize) = 0;

	virtual void				init_containers						(const CBTreeAssociativeTestWrapper &rWrapper, const bool bAssign = true) = 0;

	virtual void				transfer_containers					() = 0;

	template<class _t_test_iterator, class _t_test_call_type>
	const_iterator				_bound								(key_type &rKey, const bool bLowerNotUpper) const;

	template<class _t_test_iterator, class _t_test_call_type>
	equal_range_const_type		_equal_range						(key_type &rKey) const;

	template<class _t_container>
	_t_container				generate_move_construction			(_t_container *pContainer, _t_ref_container *pReference) const;

	size_type					m_nHintVariation;

	uint32_t					m_nNodeSize;
	uint32_t					m_nPageSize;

	uint32_t					m_nNumContainers;
	CBTreeAssociativeIf_t		**m_ppContainers;

	reference_t					*m_pReference;
};

#include "btreeassociativetestwrapper.cpp"

#endif // BTREEASSOCIATIVETESTWRAPPER_H
