[btree-framework-testbench](https://github.com/andreas-steffens/btree-framework-testbench)
=================

The btree-framework-testbench is capable to exercise tests on the [btree-framework](https://github.com/andreas-steffens/btree-framework) in terms of regression, code_coverage and validation. Each of those test categories involves tests that cover basic functionality, API coverage and corner case coverage.
The project is cmake based and is therefore very easy to set up. The two "How to build ..." sections below show how.
<br>
<br>
## Synopsis
```
./btreetest -help | --help | -usage | --usage
./btreetest -type <test type> [-app <app name>] -test <test number> [-sizetype <address space bit width>]

-help, --help, 	prints this help page and exits
-usage, --usage

-type			selects the container type or application test mode

				stl-set			- selects STL interface equivalent set container types
				stl-multiset	- selects STL interface equivalent multiset container types
				stl-map			- selects STL interface equivalent map container types
				stl-multimap	- selects STL interface equivalent multimap container types
				array			- selects array container types
				keysort			- selects keysort container types
				array-iter		- selects array iterators
				keysort-iter	- selects keysort iterators
				app				- switches test bench to application testing mode
				example			- runs the code of an example as it is displayed in the "quick overview" documentation

-app			selects an application name for real world testing
				purposes, in case the application testing mode has
				been selected

				avp				- AVP path find application

-test			selects the test number of the test to be executed

				The test list can be found at the end of this document.

-sizetype		selects the bit width of size_type of the target containers

				32				- size_type is set to uint32_t (default)
				64				- size_type is set to uint64_t (default)

				This setting is ineffective in application testing mode.
```

<br>
<br>
## How to build the test bench under windows for x86 and x86&#95;64 platforms?
--
Via cygwin command execute the following commands:

```
cd .../to/your/projects/location
git clone --recursive https://github.com/andreas-steffens/btree-framework-testbench
cd btree-framework-testbench/src/btreetest
```

Here you can find a number of batch files called msvce201x.x86(&#95;64).bat. These batch files can be executed via command line or the windows explorer. Each of those batch files creates a directory named "cmake" and generates all cmake files as well as the respective visual studio express solution files, set up for the selected platform and visual studio express version, in there. Then it tries to open whatever visual studio express application can be found under the registry key HKEY&#95;CLASSES&#95;ROOT\Applications\WDExpress.exe\shell\open\command. Please see below what versions of visual studio express and target platforms are currently supported:


```
msvce2013.x86.bat    - Visual Studio Express 2013 project for platform Win32
msvce2013.x86_64.bat - Visual Studio Express 2013 project for platform x64
msvce2015.x86.bat    - Visual Studio Express 2015 project for platform Win32
msvce2015.x86_64.bat - Visual Studio Express 2015 project for platform x64
```

If the project needs re-opening at a later point, simply use the same batch file again. In the event that you accidentally select the wrong batch file, cmake will refuse to create new project files and aborts with an error message. As a result your existing project files remain unharmed.
In case you want build the project say for a different platform, then you'll need to close the visual studio instance that has the btree-framework test bench project open. After that, you need to delete or rename the afore mentioned cmake directory and execute a different batch file that generates the project files for the desired platform. However, any modifications that have been made to the project will be lost!

To run regression tests, execute the following command lines in cygwin:

```
cd .../to/your/projects/location
cd btree-framework-testbench/src/btreetest

# use this command line for the debug build -- Warning: This is very slow and may take days to complete!
make -f Makefile.cygwin regression

# use this command line for the release build -- This may take hours to complete!
make -f Makefile.cygwin regression RELEASE=1
```

<br>
<br>
## How to build the test bench under linux?
--
Via command execute the following commands:

```
cd .../to/your/projects/location
git clone --recursive https://github.com/andreas-steffens/btree-framework-testbench
cd btree-framework-testbench/src/btreetest
make debug        # this builds the binary with debug settings
make regression   # this builds the binary with debug settings and runs all regression tests
```

In order to see all build rules, please see section "2.1. Linux" of the [README](https://github.com/andreas-steffens/btree-framework/blob/master/README) file.


<br>
<br>
## Btree-Framework Project on Facebook

If you want to see updates or release on the btree-framework project, then follow this link: [https://www.facebook.com/btreeframework](https://www.facebook.com/btreeframework)<br>
Every release post also contains a brief change log statement, allowing to tell what major changes have been made.
<br>
<br>
## Contact

Please see [README](https://github.com/andreas-steffens/btree-framework/blob/master/README) section "3. Feedback".
<br>
<br>
## License

Licensed under the Lesser GNU Public License, Version 3.0: [http://www.gnu.org/licenses/lgpl-3.0.txt](http://www.gnu.org/licenses/lgpl-3.0.txt)

## Test lists

stl-set, stl-multiset, stl-map and stl-multimap

	0		- test exercises assignment operator of selected container type
	1       - test exercises move constructor and move assignment operator of selected container type

	1000	- test exercises interface method insert (const value_type &)
	1001	- test exercises interface method insert<iterator> (iterator &, iterator &)
	1002	- test exercises interface method erase (const_iterator &) 
	1003	- test exercises interface method erase (const key_value &)
	1004	- test exercises interface method erase (const_iterator &, const_iterator &)
	1005	- test exercises interface method key_comp ()
	1006	- test exercises interface method value_comp ()
	1007	- test exercises interface method swap (container &)
	1008	- test exercises interface method find (const key_type &)
	1009	- test exercises interface methods lower_bound (const key_type &) and upper_bound (const key_type &)
	1010	- test exercises interface method emplace<_t_va_args> (_t_va_args && ...)
	1011	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with perfect hint
	1012	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with near perfect hint
	1013	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with potentially bad hint
	1014	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with terrible hint
	1015	- test exercises interface method insert (const_iterator &, const value_type &) with perfect hint
	1016	- test exercises interface method insert (const_iterator &, const value_type &) with near perfect hint
	1017	- test exercises interface method insert (const_iterator &, const value_type &) with potentially bad hint
	1018	- test exercises interface method insert (const_iterator &, const value_type &) with terrible hint
	1019	- test exercises interface method emplace (const value_type &)
	1020	- test exercises interface method emplace_hint (const_iterator &, const value_type &) with perfect hint
	1021	- test exercises interface method equal_range ()

array

	0		- test adds data at the beginning and removes data at the end
	1		- test adds data at the beginning and removes data at the end on a smaller scale
	2		- test adds data at the end and removes data at the beginning
	3		- test adds data at the end and removes data at the beginning on a smaller scale
	4		- test adds data at a random positions and removes data at random positions
	5		- test adds data at a random positions and removes data at random positions on a smaller scale
	6		- test exercises if container is still ready to operate once interface method clear () has been called
	7		- test exercises scenario where data is rapidly inserted and removed again
	8		- test exercises if container is still ready to operate once interface method unload () has been called
	9		- test exercises if container is still ready to operate once interface debug method show_integrity () has been called
	10		- test exercises copy constructor of container type
	11		- test exercises overloaded assignment operator of container type
	12		- test exercises overloaded subscript operator of container type
	13		- test reads all data from container using method serialize ()
	14		- test reads data from half of a random node using method serialize ()
	15		- test reads data from part of a random node using method serialize ()
	16		- test reads data from from container using method serialize (), while parameters exceeding container size
	17		- test exercises situation where a container is self-referenced using iterators
	18		- test reads no data from container using method serialize () with read length set to zero
	19      - test exercises move constructor and move assignment operator

	1000	- test exercises interface method assign (const size_type, const value_type &)
	1001	- test exercises interface method assign<iterator> (iterator &, iterator &)
	1002	- test exercises interface method push_back () and pop_back ()
	1003	- test exercises interface method insert (const_iterator, const size_type &, const value_type &)
	1004	- test exercises interface method insert<iterator> (const_iterator, iterator &, iterator &)
	1005	- test exercises interface method insert (const_iterator, iterator &, iterator &) on a large container via self-reference
	1006	- test exercises interface method insert (const_iterator, const_iterator &, const_iterator &) on a large container via self-reference
	1007	- test exercises interface method insert (const_iterator, reverse_iterator &, reverse_iterator &) on a large container via self-reference
	1008	- test exercises interface method insert (const_iterator, const_reverse_iterator &, const_reverse_iterator &) on a large container via self-reference
	1009	- test exercises interface method erase (const key_value &)
	1010	- test exercises interface method erase (const_iterator &, const_iterator &)
	1011	- test exercises interface method swap (container &)
	1012	- test exercises interface method emplace<_t_va_args> (const_iterator &, _t_va_args && ...)
	1013	- test exercises interface method emplace_back<_t_va_args> (_t_va_args && ...)

	2000	- code coverage test where data is removed resulting in nodes being merged, while the right node has a lower id than the left node

keysort

	0		- test adds data at the beginning and removes data at the end
	1		- test adds data at the beginning and removes data at the end on a smaller scale
	2		- test adds data at the end and removes data at the beginning
	3		- test adds data at the end and removes data at the beginning on a smaller scale
	4		- test adds data at a random positions and removes data at random positions
	5		- test adds data at a random positions and removes data at random positions on a smaller scale
	6		- test exercises if container is still ready to operate once interface method clear () has been called
	7		- test exercises scenario where data is rapidly inserted and removed again
	8		- test exercises if container is still ready to operate once interface method unload () has been called
	9		- test exercises interface method erase (const_iterator &), while removing specific instance of a key set
	10		- test exercises if container is still ready to operate once interface debug method show_integrity () has been called
	11		- test exercises copy constructor of container type
	12		- test exercises overloaded assignment operator of container type
	13		- test exercises overloaded assignment operator of container type, while making sure key sets remain in order
	14		- test reads all data from container using method serialize ()
	15		- test reads data from half of a random node using method serialize ()
	16		- test reads data from part of a random node using method serialize ()
	17		- test reads data from from container using method serialize (), while parameters exceeding container size
	18		- test reads all data from container using method serialize (), while making sure key sets remain in order
	19		- test reads data from half of a random node using method serialize (), while making sure key sets remain in order
	20		- test reads data from part of a random node using method serialize (), while making sure key sets remain in order
	21      - test exercises move constructor and move assignment operator

	1000	- test exercises interface method insert (const value_type &)
	1001	- test exercises interface method insert<iterator> (iterator &, iterator &)
	1002	- test exercises interface method erase (const_iterator &) 
	1003	- test exercises interface method erase (const key_value &)
	1004	- test exercises interface method erase (const_iterator &, const_iterator &)
	1005	- test exercises interface method swap (container &)
	1006	- test exercises interface method find (const key_type &)
	1007	- test exercises interface methods lower_bound (const key_type &) and upper_bound (const key_type &)
	1008	- test exercises interface method emplace<_t_va_args> (_t_va_args && ...)
	1009	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with perfect hint
	1010	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with near perfect hint
	1011	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with potentially bad hint
	1012	- test exercises interface method emplace_hint<_t_va_args> (const_iterator &, _t_va_args && ...) with terrible hint
	1013	- test exercises interface method insert (const_iterator &, const value_type &) with perfect hint
	1014	- test exercises interface method insert (const_iterator &, const value_type &) with near perfect hint
	1015	- test exercises interface method insert (const_iterator &, const value_type &) with potentially bad hint
	1016	- test exercises interface method insert (const_iterator &, const value_type &) with terrible hint
	1017	- test exercises interface method emplace (const value_type &)
	1018	- test exercises interface method emplace_hint (const_iterator &, const value_type &) with perfect hint
	1019	- test exercises interface method equal_range ()

	2000	- code coverage test which exercises corner cases in method determine_position ()
	2001	- code coverage test which exercises corner cases in method find_first_key ()
	2002	- code coverage test which exercises corner cases in method get_init_pos_of_key () on leaf node
	2003	- code coverage test which exercises corner cases in overloaded method set_iter_data ()
	2004	- code coverage test which exercises corner cases in overloaded compare operator

array-iter

	0		- test exercises increment operator
	1		- test exercises increment operator on a small scale
	2		- test exercises decrement operator
	3		- test exercises decrement operator on a small scale
	4		- test exercises arithmetic operator+ with one of the operands being the result instance (a = a + n)
	5		- test exercises arithmetic operator+ with one of the operands being the result instance on a small scale
	6		- test exercises arithmetic operator- with one of the operands being the result instance (a = a - n)
	7		- test exercises arithmetic operator- with one of the operands being the result instance on a small scale
	8		- test exercises arithmetic operator+ with different step sizes versus different node sizes
	9		- test exercises arithmetic operator- with different step sizes versus different node sizes
	10		- test exercises dereference operator*
	11		- test exercises subscript operator[size_type]
	12		- test exercises subscript operator[int]
	13		- test exercises compound operator+= (size_type)
	14		- test exercises compound operator+= (int)
	15		- test exercises compound operator+= (iterator)
	16		- test exercises arithmetic operator+ and operator- with none of the operands being the result instance (r = a + b) or (r = a - b)
	17		- test exercises all compare operators (<, >, <=, >=, ==, !=)
	18		- test exercises interface method swap (iterator &) with parameter from a different container
	19		- test exercises interface method swap (iterator &) with parameter from the same different container

	2000	- code coverage test exercises compare operator with same instance as an input
	2001	- code coverage test exercises situation where the time stamp is up to date after a re-assignment
	2002	- code coverage test exercises situation where the time stamp is up to date after a re-register
	2003	- code coverage test exercises situation where an uninitialised iterator is assigned to another instance
	2004	- code coverage test exercises all begin () and end () methods

keysort-iter

	0		- test exercises increment operator
	1		- test exercises increment operator on a small scale
	2		- test exercises decrement operator
	3		- test exercises decrement operator on a small scale
	4		- test exercises arithmetic operator+ with one of the operands being the result instance (a = a + n)
	5		- test exercises arithmetic operator+ with one of the operands being the result instance on a small scale
	6		- test exercises arithmetic operator- with one of the operands being the result instance (a = a - n)
	7		- test exercises arithmetic operator- with one of the operands being the result instance on a small scale
	8		- test exercises arithmetic operator+ with different step sizes versus different node sizes
	9		- test exercises arithmetic operator- with different step sizes versus different node sizes
	10		- test exercises subscript operator[size_type]
	11		- test exercises subscript operator[int]
	12		- test exercises compound operator+= (size_type)
	13		- test exercises compound operator+= (int)
	14		- test exercises compound operator+= (iterator)
	15		- test exercises arithmetic operator+ and operator- with none of the operands being the result instance (r = a + b) or (r = a - b)
	16		- test exercises all compare operators (<, >, <=, >=, ==, !=)
	17		- test exercises interface method swap (iterator &) with parameter from the same different container

example

	0		- run polymorphic calls example
	1		- run simple database example

app

avp-application

	0		- full path resolution
	1		- speed run full path resolution
	2		- parallel / part path resolution

