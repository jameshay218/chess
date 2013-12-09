CXX = g++
CXXFLAGS = -Wall -g
chess: ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o
	$(CXX) $(CXXFLAGS)  ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.hpp Pawn.hpp Rook.hpp Knight.hpp Bishop.hpp Queen.hpp King.hpp
	$(CXX) $(CXXFLAGS) -c  ChessMain.cpp -o ChessMain.o

ChessBoard.o: ChessBoard.cpp ChessBoard.hpp Pawn.hpp Rook.hpp Knight.hpp Bishop.hpp Queen.hpp King.hpp
	$(CXX) $(CXXFLAGS) -c  ChessBoard.cpp -o ChessBoard.o

ChessPiece.o: ChessPiece.cpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  ChessPiece.cpp -o ChessPiece.o

Pawn.o: Pawn.cpp Pawn.hpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  Pawn.cpp -o Pawn.o

Rook.o:	Rook.cpp Rook.hpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  Rook.cpp -o Rook.o

Knight.o: Knight.cpp Knight.hpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  Knight.cpp -o Knight.o

Bishop.o: Bishop.cpp Bishop.hpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  Bishop.cpp -o Bishop.o

Queen.o: Queen.cpp Queen.hpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  Queen.cpp -o Queen.o

King.o: King.cpp King.hpp ChessPiece.hpp
	$(CXX) $(CXXFLAGS) -c  King.cpp -o King.o

clean:
	rm -f enigma *.o
