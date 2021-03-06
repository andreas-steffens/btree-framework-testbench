/************************************************************
**
** file:	btreemaptestbench.cpp
** author:	Andreas Steffens
** license:	LGPL v3
**
** description:
**
** This file contains code for the b-tree framework's test bench
** exercising functional, code coverage and regression tests
** for the map application class.
**
************************************************************/

#include "btreemaptestbench.h"

template<class _t_map>
void TestBTreeMapSTLifAssignmentOperator (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typedef typename _t_map::const_iterator			citer_t;
	typedef typename _t_map::key_type				key_type;

	_t_map										sClMM (*pClM);
	key_type									nLastKey = 0;
	citer_t										sIter;
	citer_t										sIterRslt;
	
	::std::cout << "exercises assignment operator compatible to STL interface CBTreeMap<>:: operator= (CBTreeMap<> &)" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	sClMM = *pClM;

	if (sClMM != (*pClM))
	{
		::std::cerr << ::std::endl;
		::std::cerr << "TestBTreeMapSTLifAssignmentOperator<>: ERROR: mismatch after assignment operation" << ::std::endl;

		exit (-1);
	}
}

template<class _t_map>
void TestBTreeMapSTLifInsert (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typename _t_map::key_type	nLastSeed = 0;

	::std::cout << "CBTreeMap::insert (const valuetype &) is exercised" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastSeed, BTREETEST_KEY_GENERATION_RANDOM);
}

template<class _t_map>
void TestBTreeMapSTLifEraseViaIterator (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typedef typename _t_map::const_iterator		citer_t;
	typedef typename _t_map::size_type			size_type;
	typedef typename _t_map::key_type			key_type;

	key_type									nLastKey = 0;
	citer_t										sIter;
	citer_t										sIterRslt;
	size_type									nOffset;
	size_type									nRslt;
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: erase (const_iterator)" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	while (pClM->size () > 0)
	{
		nOffset = generate_rand32 () % pClM->size ();

		sIter = pClM->cbegin ();

		::std::advance (sIter, nOffset);

		sIterRslt = pClM->erase (sIter);

		nRslt = ::std::distance (pClM->cbegin (), sIterRslt);

		if (nOffset != nRslt)
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEraseViaIterator: returned iterator mismatches!" << ::std::endl;

			exit (-1);
		}
	}
}

template<class _t_map>
void TestBTreeMapSTLifEraseViaKey (_t_map *pClM, typename _t_map::size_type nNumEntries, uint32_t nInstances)
{
	typedef typename _t_map::const_iterator		citer_t;
	typedef typename _t_map::size_type			size_type;
	typedef typename _t_map::key_type			key_type;
	
	key_type									nLastKey;
	key_type									nKey;
	citer_t										sIter;
	uint32_t									i;
	size_type									nRslt;
	size_type									nOffset;
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: erase (const keytype &)" << ::std::endl;

	for (i = 0; i < nInstances; i++)
	{
		nLastKey = 0;

		associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);
	}

	while (pClM->size () > 0)
	{
		sIter = pClM->cbegin ();

		nOffset = generate_rand32 () % pClM->size ();

		::std::advance (sIter, nOffset);

		nKey = (*sIter).first;

		nRslt = pClM->erase (nKey);

		if (nRslt != 1)
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEraseViaKey: unexpected number of items deleted!" << ::std::endl;

			exit (-1);
		}
	}
}

template<class _t_map>
void TestBTreeMapSTLifEraseViaIteratorMultiple (_t_map *pClM, typename _t_map::size_type nNumEntries, uint32_t nInstances)
{
	typedef typename _t_map::const_iterator		citer_t;
	typedef typename _t_map::size_type			size_type;
	typedef typename _t_map::key_type			key_type;

	key_type									nLastKey;
	citer_t										sIterBegin;
	citer_t										sIterEnd;
	citer_t										sIterRslt;
	uint32_t									i;
	size_type									nBegin;
	size_type									nRslt;

#if defined (_DEBUG)

	uint32_t									nDebug = 0;

#endif
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: erase (const_iterator, const_iterator)" << ::std::endl;

	for (i = 0; i < nInstances; i++)
	{
		nLastKey = 0;

		associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);
	}

	while (pClM->size () > 0)
	{
		sIterBegin = pClM->cbegin ();
		sIterEnd = pClM->cend ();

		nBegin = 0;

		if (pClM->size () > 1)
		{
			nBegin = generate_rand32 () % (pClM->size () / 2);

			::std::advance (sIterBegin, nBegin);
			::std::advance (sIterEnd, (int) (0 - (generate_rand32 () % (pClM->size () / 2))));
		}

		sIterRslt = pClM->erase (sIterBegin, sIterEnd);

		nRslt = ::std::distance (pClM->cbegin (), sIterRslt);

		if (nRslt != nBegin)
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEraseViaIteratorMultiple: returned iterator mismatches!" << ::std::endl;
			::std::cerr << "expected value: " << nBegin << ::std::endl;
			::std::cerr << "returned value: " << nRslt << ::std::endl;

#if defined (_DEBUG)

			::std::cerr << "iteration: " << nDebug << ::std::endl;

#endif

			exit (-1);
		}

#if defined (_DEBUG)

		nDebug++;

#endif
	}
}

template<class _t_map>
void TestBTreeMapSTLifKeyComp (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typedef typename _t_map::iterator		iter_t;
	typedef typename _t_map::key_type		key_type;
	
	key_type									nLastKey = 0;
	iter_t										sIterBegin;
	iter_t										sIterEnd;
	iter_t										sIter;
	iter_t										sIterUpper;
	key_type									nKey;
	key_type									nNextKey;
	typename _t_map::key_compare				sMComp = pClM->key_comp ();
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: key_comp ()" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	sIterBegin = pClM->begin ();
	sIterEnd = pClM->end ();

	for (sIter = sIterBegin; sIter != sIterEnd; sIter++)
	{
		nKey = get_entry_key (*sIter);

		sIterUpper = pClM->upper_bound (nKey);

		if (sIterUpper != sIterEnd)
		{
			nNextKey = get_entry_key (*sIterUpper);

			if (!sMComp (nKey, nNextKey))
			{
				::std::cerr << ::std::endl;
				::std::cerr << "TestBTreeMapSTLifKeyComp: ERROR: CBTreeMap::key_compare (const keytype &, const keytype &) delivered unexpected result!" << ::std::endl;

				exit (-1);
			}
		}
	}
}

template<class _t_map>
void TestBTreeMapSTLifValueComp (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typedef typename _t_map::iterator			iter_t;
	typedef typename _t_map::key_type			key_type;
	typedef typename _t_map::value_type			value_type;

	key_type									nLastKey = 0;
	iter_t										sIterBegin;
	iter_t										sIterEnd;
	iter_t										sIter;
	iter_t										sIterUpper;
	key_type									nKey;
	typename _t_map::value_compare				sMComp = pClM->value_comp ();
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: value_comp ()" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	sIterBegin = pClM->begin ();
	sIterEnd = pClM->end ();

	for (sIter = sIterBegin; sIter != sIterEnd; sIter++)
	{
		nKey = get_entry_key (*sIter);

		sIterUpper = pClM->upper_bound (nKey);

		if (sIterUpper != sIterEnd)
		{
			if (!sMComp (((value_type)(*sIter)), ((value_type)(*sIterUpper))))
			{
				::std::cerr << ::std::endl;
				::std::cerr << "TestBTreeMapSTLifValueComp: ERROR: CBTreeMap::value_compare (const valuetype &, const valuetype &) delivered unexpected result!" << ::std::endl;

				exit (-1);
			}
		}
	}
}

template<class _t_map>
void TestBTreeMapSTLifSwap (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typedef typename _t_map::const_iterator			citer_t;
	typedef typename _t_map::key_type				key_type;

	key_type					nLastKey = 0;
	_t_map						sClMapTarget (*pClM);
	_t_map						sClMapRef (*pClM);
	_t_map						sClMapTargetRef (*pClM);
	citer_t						sCIterBegin;
	citer_t						sCIterEnd;

	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: swap (CBTreeMap &)" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	sClMapRef.insert (pClM->cbegin (), pClM->cend ());

	if ((*pClM) != sClMapRef)
	{
		::std::cerr << "ERROR: Unexpected multimap mismatch!" << ::std::endl;

		exit (-1);
	}

	associative_container_add_primitive (&sClMapTarget, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	sCIterBegin = sClMapTarget.cbegin ();
	sCIterEnd = sClMapTarget.cend ();

	sClMapTargetRef.insert (sCIterBegin, sCIterEnd);

	if (sClMapTarget != sClMapTargetRef)
	{
		::std::cerr << "ERROR: Unexpected target mismatch!" << ::std::endl;

		exit (-1);
	}

	pClM->swap (sClMapTarget);

	if ((*pClM) != sClMapTargetRef)
	{
		::std::cerr << "ERROR: swapped multimap mismatches target reference!" << ::std::endl;

		exit (-1);
	}

	if (sClMapTarget != sClMapRef)
	{
		::std::cerr << "ERROR: target mismatches multimap reference!" << ::std::endl;

		exit (-1);
	}

	sClMapTarget.swap (*pClM);

	if ((*pClM) != sClMapRef)
	{
		::std::cerr << "ERROR: multimap mismatches multimap reference!" << ::std::endl;

		exit (-1);
	}

	if (sClMapTarget != sClMapTargetRef)
	{
		::std::cerr << "ERROR: target mismatches target reference!" << ::std::endl;

		exit (-1);
	}
}

template<class _t_map>
void TestBTreeMapSTLifFind (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	typedef typename _t_map::const_iterator			citer_t;
	typedef typename _t_map::key_type				key_type;

	key_type						nLastKey = 1;
	key_type						nKey;
	citer_t							sCIter;
	citer_t							sCIterRslt;
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: find (const _t_keytype &)" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_ASCEND);

	for (sCIter = pClM->cbegin (); sCIter != pClM->cend (); sCIter++)
	{
		nKey = (*sCIter).first;

		sCIterRslt = pClM->find (nKey);

		if (sCIter != sCIterRslt)
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifFind: ERROR: iterator mismatch!" << ::std::endl;

			exit (-1);
		}
	}

	nKey = 0;

	sCIterRslt = pClM->find (nKey);

	if (sCIterRslt != pClM->cend ())
	{
		::std::cerr << ::std::endl;
		::std::cerr << "TestBTreeMapSTLifFind: ERROR: find () didn't return cend () on lower bound check!" << ::std::endl;

		exit (-1);
	}

	nKey = (key_type) (nNumEntries + 1);

	sCIterRslt = pClM->find (nKey);

	if (sCIterRslt != pClM->cend ())
	{
		::std::cerr << ::std::endl;
		::std::cerr << "TestBTreeMapSTLifFind: ERROR: find () didn't return cend () on upper bound check!" << ::std::endl;

		exit (-1);
	}
}

template<class _t_map>
void TestBTreeMapSTLifLowerBoundUpperBound (_t_map *pClM, typename _t_map::size_type nNumEntries, uint32_t nInstance)
{
	typedef typename _t_map::const_iterator			citer_t;
	typedef typename _t_map::key_type				key_type;

	key_type						nLastKey;
	key_type						nKey;
	uint32_t						i;
	citer_t							sCIterLower;
	citer_t							sCIterUpper;
	
	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: lower_bound () upper_bound () count ()" << ::std::endl;
	
	for (i = 0; i < nInstance; i++)
	{
		nLastKey = 1;

		associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_ASCEND);
	}

	for (i = 0; i < nNumEntries; i++)
	{
		nKey = i + 1;

		sCIterLower = pClM->lower_bound (nKey);
		sCIterUpper = pClM->upper_bound (nKey);

		::std::advance (sCIterLower, (int) 1);

		if (sCIterLower != sCIterUpper)
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifLowerBoundUpperBound: ERROR: boundary mismatch!" << ::std::endl;

			exit (-1);
		}

		if (pClM->count (nKey) != 1)
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifLowerBoundUpperBound: ERROR: count () returned with unexpected value!" << ::std::endl;

			exit (-1);
		}
	}

	nKey = 0;

	sCIterLower = pClM->lower_bound (nKey);

	if (sCIterLower != pClM->cbegin ())
	{
		::std::cerr << ::std::endl;
		::std::cerr << "TestBTreeMapSTLifLowerBoundUpperBound: ERROR: lower_bound () didn't return cbegin () when testing for lowest key!" << ::std::endl;

		exit (-1);
	}

	nKey = (key_type) (nNumEntries + 1);

	sCIterUpper = pClM->upper_bound (nKey);

	if (sCIterUpper != pClM->cend ())
	{
		::std::cerr << ::std::endl;
		::std::cerr << "TestBTreeMapSTLifLowerBoundUpperBound: ERROR: upper_bound () didn't return cend () when testing for lowest key!" << ::std::endl;

		exit (-1);
	}
}

template<class _t_map>
void TestBTreeMapSTLifEmplace (_t_map *pClM, typename _t_map::size_type nNumEntries)
{
	uint32_t		nLastKey = 1;

	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: emplace ()" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_EMPLACE);

	nLastKey = 1;

	associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_EMPLACE);
}

template<class _t_map>
void TestBTreeMapSTLifEmplaceHint (_t_map *pClM, typename _t_map::size_type nNumEntries, typename _t_map::size_type nHintVariation)
{
	uint32_t		nLastKey = 1;

	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: emplace_hint () with hint variation set to " << nHintVariation << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_EMPLACE_HINT);

	nLastKey = 1;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_EMPLACE_HINT);
}

template<class _t_map>
void TestBTreeMapSTLifInsertHint (_t_map *pClM, typename _t_map::size_type nNumEntries, typename _t_map::size_type nHintVariation)
{
	uint32_t		nLastKey = 1;

	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: insert (hint) with hint variation set to " << nHintVariation << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_INSERT_HINT);

	nLastKey = 1;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_INSERT_HINT);
}

template<class _t_map>
void TestBTreeMapSTLifEmplaceViaCtor (_t_map *pClM, typename _t_map::size_type nNumEntries, typename _t_map::size_type nHintVariation)
{
	uint32_t		nLastKey = 1;

	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: emplace (ctor)" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_ABSTRACT_EMPLACE);

	nLastKey = 1;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_ABSTRACT_EMPLACE);
}

template<class _t_map>
void TestBTreeMapSTLifEmplaceHintViaCtor (_t_map *pClM, typename _t_map::size_type nNumEntries, typename _t_map::size_type nHintVariation)
{
	uint32_t		nLastKey = 1;

	::std::cout << "exercises method compatible to STL interface CBTreeMap<>:: emplace_hint (ctor)" << ::std::endl;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_ABSTRACT_EMPLACE_HINT);

	nLastKey = 1;

	associative_container_add_primitive (pClM, nNumEntries, nHintVariation, nLastKey, BTREETEST_KEY_GENERATION_RANDOM, ASSOCIATIVE_ADD_METHOD_ABSTRACT_EMPLACE_HINT);
}

template<class _t_map>
void TestBTreeMapSTLifEqualRange (_t_map *pClM, typename _t_map::size_type nNumEntries, uint32_t nInstance)
{
	typedef typename _t_map::const_iterator				citer_t;

	typedef typename _t_map::key_type					key_type;
	typedef typename _t_map::size_type					size_type;

	typedef typename _t_map::equal_range_type			equal_range_type;
	typedef typename _t_map::equal_range_const_type		equal_range_const_type;

	key_type								nLastKey;
	key_type								nKey;
	uint32_t								i;
	size_type								j;
	equal_range_type						sEqRange;
	equal_range_const_type					sCEqRange;

	::std::cout << "exercises methods compatible to STL interface CBTreeMap<>:: equal_range ()" << ::std::endl;

	for (i = 0; i < nInstance; i++)
	{
		nLastKey = 1;

		associative_container_add_primitive (pClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_ASCEND);

		for (j = 0; j < nNumEntries; j++)
		{
			nKey = key_type (j + 1);

			sEqRange = pClM->equal_range (nKey);
			sCEqRange = ((const _t_map *) pClM)->equal_range (nKey);

			if (::std::distance (sEqRange.first, sEqRange.second) != size_type (1))
			{
				::std::cerr << ::std::endl;
				::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: rw distance mismatch!" << ::std::endl;

				exit (-1);
			}

			if (::std::distance (sCEqRange.first, sCEqRange.second) != size_type (1))
			{
				::std::cerr << ::std::endl;
				::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: ro distance mismatch!" << ::std::endl;

				exit (-1);
			}
		}

		nKey = 0;

		sEqRange = pClM->equal_range (nKey);
		sCEqRange = ((const _t_map *) pClM)->equal_range (nKey);

		if (sEqRange.first != pClM->begin ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range ().first didn't return begin () when testing for lowest key!" << ::std::endl;

			exit (-1);
		}

		if (sEqRange.second != pClM->begin ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range ().second didn't return begin () when testing for lowest key!" << ::std::endl;

			exit (-1);
		}

		if (sCEqRange.first != pClM->cbegin ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range () const.first didn't return cbegin () when testing for lowest key!" << ::std::endl;

			exit (-1);
		}

		if (sCEqRange.second != pClM->cbegin ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range () const.second didn't return cbegin () when testing for lowest key!" << ::std::endl;

			exit (-1);
		}

		nKey = (key_type) (nNumEntries + 1);

		sEqRange = pClM->equal_range (nKey);
		sCEqRange = ((const _t_map *) pClM)->equal_range (nKey);

		if (sEqRange.first != pClM->end ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range ().first didn't return end () when testing for highest key!" << ::std::endl;

			exit (-1);
		}

		if (sEqRange.second != pClM->end ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range ().second didn't return end () when testing for highest key!" << ::std::endl;

			exit (-1);
		}

		if (sCEqRange.first != pClM->cend ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range () const.first didn't return cend () when testing for highest key!" << ::std::endl;

			exit (-1);
		}

		if (sCEqRange.second != pClM->cend ())
		{
			::std::cerr << ::std::endl;
			::std::cerr << "TestBTreeMapSTLifEqualRange: ERROR: equal_range () const.second didn't return cend () when testing for highest key!" << ::std::endl;

			exit (-1);
		}
	}
}

template<class _t_container>
_t_container TestBTreeMapMoveConstructorAndAssignmentEx (_t_container *pClM, typename _t_container::size_type nNumEntries)
{
	_t_container	sClM (*pClM);

	return (sClM);
}

template<class _t_container>
void TestBTreeMapMoveConstructorAndAssignment (_t_container *pClM, typename _t_container::size_type nNumEntries)
{
	typedef typename _t_container::key_type					key_type;

	key_type								nLastKey;

	_t_container							sClM (*pClM);

	::std::cout << "exercises CBTreeMap<>:: CBTreeMap (CBTreeMap<> &&) and operator= (CBTreeMap<> &&)" << ::std::endl;

	associative_container_add_primitive (&sClM, nNumEntries, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	*pClM = TestBTreeMapMoveConstructorAndAssignmentEx (&sClM, nNumEntries);

	pClM->clear ();

	nLastKey = 1;

	associative_container_add_primitive (pClM, 1, 0, nLastKey, BTREETEST_KEY_GENERATION_RANDOM);

	*pClM = TestBTreeMapMoveConstructorAndAssignmentEx (&sClM, nNumEntries);
}

template<class _t_container>
void TestBTreeSTLmap (uint32_t nTestNum, uint32_t nNodeSize, uint32_t nPageSize, _t_container *pMapWrapper)
{
	typename _t_container::size_test_type		sTypeSelect;
	::std::string								sTypeStr;

	get_typename (sTypeSelect, sTypeStr);

	::std::cout << "b-tree map test bench selected using type " << sTypeStr << ::std::endl;

	pMapWrapper = new _t_container (nNodeSize, nPageSize);

	if (pMapWrapper == NULL)
	{
		::std::cerr << "insufficient memory!" << ::std::endl;

		exit (-1);
	}

	switch (nTestNum)
	{
	case BTREETEST_MAP_ASSIGNMENT_OPERATOR	:
		{
			TestBTreeMapSTLifAssignmentOperator (pMapWrapper, 64);

			break;
		}

	case BTREETEST_MAP_MOVE_CONSTRUCTOR_AND_ASSIGNMENT:
		{
			TestBTreeMapMoveConstructorAndAssignment (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_INSERT	:
		{
			TestBTreeMapSTLifInsert (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_INSERT_VIA_ITERATOR	:
		{
			TestBTreeMapSTLifInsertViaIterator (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_ERASE_VIA_ITERATOR	:
		{
			TestBTreeMapSTLifEraseViaIterator (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_ERASE_VIA_KEY	:
		{
			TestBTreeMapSTLifEraseViaKey (pMapWrapper, 64, 2);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_ERASE_VIA_ITERATOR_MULTIPLE	:
		{
			TestBTreeMapSTLifEraseViaIteratorMultiple (pMapWrapper, 64, 2);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_KEY_COMP	:
		{
			TestBTreeMapSTLifKeyComp (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_VALUE_COMP	:
		{
			TestBTreeMapSTLifValueComp (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_SWAP	:
		{
			TestBTreeMapSTLifSwap (pMapWrapper, 128);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_FIND	:
		{
			TestBTreeMapSTLifFind (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_LOWER_BOUND_UPPER_BOUND	:
		{
			TestBTreeMapSTLifLowerBoundUpperBound (pMapWrapper, 64, 5);

			break;
		}
	
		
	case BTREETEST_MAP_STL_IF_EMPLACE	:
		{
			TestBTreeMapSTLifEmplace (pMapWrapper, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_EMPLACE_HINT	:
		{
			TestBTreeMapSTLifEmplaceHint (pMapWrapper, 64, 0);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_EMPLACE_HINT_MINOR	:
		{
			TestBTreeMapSTLifEmplaceHint (pMapWrapper, 64, 1);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_EMPLACE_HINT_SIGNIFICANT	:
		{
			TestBTreeMapSTLifEmplaceHint (pMapWrapper, 64, 6);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_EMPLACE_HINT_LARGE	:
		{
			TestBTreeMapSTLifEmplaceHint (pMapWrapper, 64, 64);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_INSERT_HINT	:
		{
			TestBTreeMapSTLifInsertHint (pMapWrapper, 64, 0);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_INSERT_HINT_MINOR	:
		{
			TestBTreeMapSTLifInsertHint (pMapWrapper, 64, 1);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_INSERT_HINT_SIGNIFICANT	:
		{
			TestBTreeMapSTLifInsertHint (pMapWrapper, 64, 6);

			break;
		}
	
	case BTREETEST_MAP_STL_IF_INSERT_HINT_LARGE	:
		{
			TestBTreeMapSTLifInsertHint (pMapWrapper, 64, 64);

			break;
		}

	case BTREETEST_MAP_STL_IF_EMPLACE_VIA_CTOR	:
		{
			TestBTreeMapSTLifEmplaceViaCtor (pMapWrapper, 64, 0);
	
			break;
		}
	
	case BTREETEST_MAP_STL_IF_EMPLACE_HINT_VIA_CTOR	:
		{
			TestBTreeMapSTLifEmplaceHintViaCtor (pMapWrapper, 64, 0);

			break;
		}

	case BTREETEST_MAP_STL_IF_EQUAL_RANGE	:
		{
			TestBTreeMapSTLifEqualRange (pMapWrapper, 64, 5);

			break;
		}
	
	default:
		{
			::std::cerr << "ERROR: TestBTreeSTLmap: Unknown test or test not specified!" << ::std::endl;

			exit (-1);

			break;
		}
	}

	delete pMapWrapper;
}
