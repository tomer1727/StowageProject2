COMP = g++-8.3.0

SHARED_OBJS = BaseAlgorithm.so AlgorithmReverse.so
OBJS = ShipPlan.o Floor.o Spot.o Container.o Port.o Route.o Utils.o  WeightBalanceCalculator.o BaseAlgorithm.o AlgorithmReverse.o
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC -I../common
CPP_LINK_FLAG = -shared

all: $(SHARED_OBJS)

BaseAlgorithm.so: $(OBJS)
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^
AlgorithmReverse.so: $(OBJS)
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^

ShipPlan.o: ../common/ShipPlan.cpp ../common/ShipPlan.h ../common/Floor.h ../common/Spot.h ../common/Container.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
Floor.o: ../common/Floor.cpp ../common/Floor.h ../common/Spot.h ../common/Container.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
Spot.o: ../common/Spot.cpp ../common/Spot.h ../common/Container.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
Container.o: ../common/Container.cpp ../common/Container.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
Port.o: ../common/Port.cpp ../common/Port.h ../common/Container.h ../common/Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
Route.o: ../common/Route.cpp ../common/Route.h ../common/Port.h ../common/Container.h ../common/Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
Utils.o: ../common/Utils.cpp ../common/Utils.h
	$(COMP) $(CPP_COMP_FLAG) -c ../common/$*.cpp
WeightBalanceCalculator.o: ../interface/WeightBalanceCalculator.cpp ../interface/WeightBalanceCalculator.h ../common/ShipPlan.h ../common/Floor.h ../common/Spot.h ../common/Container.h
	$(COMP) $(CPP_COMP_FLAG) -c ../interface/$*.cpp
BaseAlgorithm.o: BaseAlgorithm.cpp BaseAlgorithm.h ../common/ShipPlan.h ../common/Floor.h ../common/Spot.h ../common/Container.h ../common/Route.h ../common/Port.h ../common/Utils.h ../interface/WeightBalanceCalculator.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmReverse.o: AlgorithmReverse.cpp AlgorithmReverse.h BaseAlgorithm.h ../common/ShipPlan.h ../common/Route.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(SHARED_OBJS)