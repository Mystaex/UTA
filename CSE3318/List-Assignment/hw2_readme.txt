Ethan Chase  |  EGC7646  |  1001457646
CSE 3318-001

Compilation instructions to run my code:
gcc gcc hw2_list.c list.h list.c
	to run: ./a.out

I ran my code on:
- VM (The Xubuntu VM posted on the CSE 13xx page)

I ran my code with Valgrind: 
- Yes

My code runs with the input files (select what applies to you):
- Unix version  


For the answers below assume L1 has size N1 and L2 has size N2.
If you call any of the functions from the provided list.c (e.g. destroy_list), give the time complexity for them.

merge(L1, L2) 
	time: O(  N1+N2  )
	space: O( 1 ), if not, fill in O(   ) and justify: 

check_sorted(L1) 
	time: O(  N1  )
	space: O( 1 ), if not, fill in O(   ) and justify: 

print_list_with_addresses(L1) 
	time: O(  N1  )
	space: O( 1 ), if not, fill in O(   ) and justify:
	
remove_duplicates(L1) 
	time: O( N1^2 )
	space: O( 1 ), if not, fill in O(   ) and justify:

destroy_list(L1) 
	time: O(  N1  )
	space: O( 1 ), if not, fill in O(   ) and justify:


