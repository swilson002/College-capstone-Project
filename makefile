FLAGS = 
OUTFILE =
DESTINATION = NCAATourn.exe

NCAATourn.exe : Loader.o TeamInt.o PickInt.o GameInt.o NCAATourn.cpp \
	AIViewer.o
	g++ NCAATourn.cpp stringconv.o Loader.o GameInt.o PickInt.o TeamInt.o \
Manager.o Player.o Master.o FullBracket.o Bracket.o Team.o ManagerAI.o \
AIcomp.o SeedStorage.o SeedDifStorage.o TeamStorage.o IDUnit.o TeamData.o \
dataUnit.o AIViewer.o $(FLAGS) -o $(DESTINATION)

Team.o : Team.cpp Team.h
	g++ Team.cpp $(FLAGS) -c -o Team.o

TestTeam.o : TestTeamData.cpp TestTeamData.h stringconv.o
	g++ TestTeamData.cpp $(FLAGS) -c -o TestTeam.o

TeamTest.exe : Team.o TeamTest.cpp
	g++ TeamTest.cpp Team.o $(FLAGS) -o TeamTest.exe

Bracket.o : Team.o Bracket.cpp Bracket.h
	g++ Bracket.cpp $(FLAGS) -c -o Bracket.o

BracketTest.exe : Bracket.o TestTeam.o BracketTest.cpp
	g++ BracketTest.cpp stringconv.o TestTeam.o Bracket.o Team.o \
$(FLAGS) -o BracketTest.exe

FullBracket.o : Team.o Bracket.o FullBracket.cpp FullBracket.h
	g++ FullBracket.cpp $(FLAGS) -c -o FullBracket.o

FullBracketTest.exe : TestTeam.o FullBracket.o FullBracketTest.cpp
	g++ FullBracketTest.cpp stringconv.o TestTeam.o FullBracket.o \
Bracket.o Team.o $(FLAGS) -o FullBracketTest.exe

Master.o : Team.o FullBracket.o Master.cpp Master.h
	g++ Master.cpp $(FLAGS) -c -o Master.o

MasterTest.exe : Master.o TestTeam.o MasterTest.cpp
	g++ MasterTest.cpp stringconv.o TestTeam.o Master.o FullBracket.o \
Bracket.o Team.o $(FLAGS) -o MasterTest.exe

Player.o : Team.o FullBracket.o Player.cpp Player.h
	g++ Player.cpp $(FLAGS) -c -o Player.o

PlayerTest.exe : Player.o TestTeam.o PlayerTest.cpp
	g++ PlayerTest.cpp stringconv.o TestTeam.o Player.o FullBracket.o \
Bracket.o Team.o $(FLAGS) -o PlayerTest.exe

Manager.o : Team.o Master.o Player.o Manager.cpp Manager.h
	g++ Manager.cpp $(FLAGS) -c -o Manager.o

ManagerTest.exe : Manager.o stringconv.o ManagerTest.cpp
	g++ ManagerTest.cpp stringconv.o Manager.o Master.o \
Player.o FullBracket.o Bracket.o Team.o $(FLAGS) -o ManagerTest.exe

TeamInt.o : ManagerAI.o TeamInt.cpp TeamInt.h globalConst.h
	g++ TeamInt.cpp $(FLAGS) -c -o TeamInt.o

PickInt.o : ManagerAI.o PickInt.cpp PickInt.h globalConst.h
	g++ PickInt.cpp $(FLAGS) -c -o PickInt.o

GameInt.o : stringconv.o ManagerAI.o GameInt.cpp GameInt.h globalConst.h
	g++ GameInt.cpp $(FLAGS) -c -o GameInt.o

Loader.o : ManagerAI.o Loader.cpp Loader.h globalConst.h
	g++ Loader.cpp $(FLAGS) -c -o Loader.o

LoaderAITest.exe : stringconv.o Loader.o LoaderAITest.cpp
	g++ LoaderAITest.cpp stringconv.o Loader.o Manager.o Master.o \
Player.o FullBracket.o Bracket.o Team.o ManagerAI.o AIcomp.o SeedStorage.o \
SeedDifStorage.o TeamStorage.o IDUnit.o TeamData.o dataUnit.o \
$(FLAGS) -o LoaderAITest.exe

stringconv.o : stringconv.cpp stringconv.h
	g++ stringconv.cpp $(FLAGS) -c -o stringconv.o

dataUnit.o : dataUnit.h dataUnit.cpp
	g++ dataUnit.cpp $(FLAGS) -c -o dataUnit.o

dataUnitTest.exe : dataUnit.o dataUnitTest.cpp
	g++ dataUnitTest.cpp dataUnit.o $(FLAGS) -o dataUnitTest.exe

TeamData.o : dataUnit.o TeamData.h TeamData.cpp
	g++ TeamData.cpp $(FLAGS) -c -o TeamData.o

SeedDifStorage.o : dataUnit.o SeedDifStorage.h SeedDifStorage.cpp
	g++ SeedDifStorage.cpp $(FLAGS) -c -o SeedDifStorage.o

SeedStorage.o : dataUnit.o SeedStorage.h SeedStorage.cpp
	g++ SeedStorage.cpp $(FLAGS) -c -o SeedStorage.o

IDUnit.o : IDUnit.h IDUnit.cpp
	g++ IDUnit.cpp $(FLAGS) -c -o IDUnit.o

TeamStorage.o : TeamData.o IDUnit.o TeamStorage.cpp TeamStorage.h
	g++ TeamStorage.cpp $(FLAGS) -c -o TeamStorage.o

TeamStorageTest.exe : TeamStorage.o TeamData.o stringconv.o IDUnit.o \
	TeamStorageTest.cpp
	g++ TeamStorageTest.cpp TeamStorage.o TeamData.o stringconv.o \
dataUnit.o IDUnit.o $(FLAGS) -o TeamStorageTest.exe

StorageTest.exe : SeedStorage.o SeedDifStorage.o StorageTest.cpp
	g++ StorageTest.cpp SeedStorage.o SeedDifStorage.o \
dataUnit.o $(FLAGS) -o StorageTest.exe

AIcomp.o : TeamStorage.o TeamData.o SeedStorage.o SeedDifStorage.o \
	Team.o AIcomp.h AIcomp.cpp
	g++ AIcomp.cpp $(FLAGS) -c -o AIcomp.o

AIcompTest.exe : AIcomp.o stringconv.o AIcompTest.cpp
	g++ AIcompTest.cpp AIcomp.o TeamStorage.o TeamData.o IDUnit.o \
SeedStorage.o SeedDifStorage.o dataUnit.o Team.o stringconv.o \
$(FLAGS) -o AIcompTest.exe

ManagerAI.o : Manager.o AIcomp.o ManagerAI.cpp ManagerAI.h
	g++ ManagerAI.cpp $(FLAGS) -c -o ManagerAI.o

ManagerAITest.exe : ManagerAI.o stringconv.o ManagerAITest.cpp
	g++ ManagerAITest.cpp ManagerAI.o AIcomp.o TeamStorage.o TeamData.o \
IDUnit.o SeedStorage.o SeedDifStorage.o dataUnit.o Manager.o Player.o \
Master.o FullBracket.o Bracket.o Team.o stringconv.o \
$(FLAGS) -o ManagerAITest.exe

AIViewer.o : AIViewer.cpp AIViewer.h AIcomp.o Team.o
	g++ AIViewer.cpp $(FLAGS) -c -o AIViewer.o

all : NCAATourn.exe TeamTest.exe BracketTest.exe FullBracketTest.exe \
	MasterTest.exe PlayerTest.exe ManagerTest.exe LoaderTest.exe \
	ManagerAITest.exe AIcompTest.exe StorageTest.exe dataUnitTest.exe

clean :
	rm *.exe *.o

clearCrap :
	rm \#*\#

LineCounter : LineCounter.cpp
	g++ LineCounter.cpp  $(FLAGS) -o LineCounter

lineCount :
	./LineCounter NCAATourn.cpp -c cpp Team Bracket FullBracket Player \
Master Manager dataUnit IDUnit TeamData SeedStorage SeedDifStorage \
TeamStorage AIcomp ManagerAI stringconv Loader TeamInt PickInt GameInt \
AIViewer $(OUTFILE)

backup:
	cp Teams.tm Teams.tm~
	cp Players.brk Players.brk~
	cp Tourn.mbr Tourn.mbr~
	cp Score.set Score.set~
	cp BracketData.ai BracketData.ai~
restore:
	cp Teams.tm~ Teams.tm
	cp Players.brk~ Players.brk
	cp Tourn.mbr~ Tourn.mbr
	cp Score.set~ Score.set
	cp BracketData.ai~ BracketData.ai

