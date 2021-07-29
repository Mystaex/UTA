***********************************
Description:
Implements malloc with own memory allocation rules such as best, worst, next, and first fit.
***********************************
compilation instructions:
	make
run instructions:
	Template: 	env LD_PRELOAD=lib/libmalloc-<fit.so> <program>
	Example: 	env LD_PRELOAD=lib/libmalloc-ff.so tests/test1
	<fit.so> can be bf.so, wf.so, ff.so, or nf.so for best, worst, first, and next fit.
	all test programs are stored in the "tests/" folder
***********************************
