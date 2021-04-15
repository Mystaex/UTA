Implements malloc with own allocation rules.

to build:
	make
to run:
	Template: 	env LD_PRELOAD=lib/libmalloc-<fit.so> <program>
	Example: 	env LD_PRELOAD=lib/libmalloc-ff.so tests/test1
	fit.so can be bf.so, wf.so, ff.so, or nf.so for best, worst, first, and next fit.