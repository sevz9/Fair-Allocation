FLAGS = -Wall -Werror -Wextra -Iinclude

propm: obj obj/aggregate.o obj/main.o obj/decomposition.o obj/valuation_matrix.o obj/PROPM_alg.o obj/Propm_Checker.o obj/PO_checker.o obj/Generate.o obj/find_bad_matrix.o
	g++ -o propm obj/aggregate.o obj/main.o obj/decomposition.o obj/valuation_matrix.o obj/PROPM_alg.o obj/Propm_Checker.o obj/PO_checker.o obj/Generate.o obj/find_bad_matrix.o

obj/find_bad_matrix.o: src/find_bad_matrix.cpp include/find_bad_matrix.hpp
	g++ -o obj/find_bad_matrix.o -c $(FLAGS) src/find_bad_matrix.cpp

obj/PO_checker.o: src/PO_checker.cpp include/PO_checker.hpp
	g++ -o obj/PO_checker.o -c $(FLAGS) src/PO_checker.cpp

obj/Generate.o: src/Generate.cpp include/Generate.hpp
	g++ -o obj/Generate.o -c $(FLAGS) src/Generate.cpp

obj/Propm_Checker.o: src/Propm_Checker.cpp include/Propm_Checker.hpp
	g++ -o obj/Propm_Checker.o -c $(FLAGS) src/Propm_Checker.cpp

obj/PROPM_alg.o: src/PROPM_alg.cpp include/PROPM_alg.hpp
	g++ -o obj/PROPM_alg.o -c $(FLAGS) src/PROPM_alg.cpp

obj/valuation_matrix.o: src/valuation_matrix.cpp include/valuation_matrix.hpp
	g++ -o obj/valuation_matrix.o -c $(FLAGS) src/valuation_matrix.cpp

obj/aggregate.o: src/aggregate.cpp include/aggregate.hpp
	g++ -o obj/aggregate.o -c $(FLAGS) src/aggregate.cpp

obj/decomposition.o: src/decomposition.cpp include/decomposition.hpp
	g++ -o obj/decomposition.o -c $(FLAGS) src/decomposition.cpp

obj/main.o: src/main.cpp
	g++ -o obj/main.o -c $(FLAGS) src/main.cpp

obj:
	mkdir -p obj

clean:
	rm -rf obj propm

