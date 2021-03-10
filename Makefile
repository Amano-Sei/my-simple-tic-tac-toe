pvp:tic_tac_toe.h tic_tac_toe.cpp pvp.cpp
	g++ -o pvp.out pvp.cpp tic_tac_toe.cpp
ai:	tic_tac_toe.h tic_tac_toe.cpp ai.cpp pn_search.h pn_search.cpp
	g++ -o ai.out ai.cpp pn_search.cpp tic_tac_toe.cpp

