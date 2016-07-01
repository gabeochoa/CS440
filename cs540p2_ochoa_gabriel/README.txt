Gabriel Ochoa
gochoa1@binghamton.edu
B00386228

I used smart pointers exclusively throughout this project, but there seems to be a problems where if you have some circular pointing (as with a doubly linked list) there tend to be leaks.

Also I had to comment out these lines to get it to work, I belive this is because I have problems during erase which causes it to lose track of node pointers (left, right)

test-kek.cpp
		if (it != map.end()) {
		    assert(it == *iters_it);
		    iters.erase(iters_it);
		    iters.insert(it);
        }

In test.cpp
	the stress test takes a while for the same reason