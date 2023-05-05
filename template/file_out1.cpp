#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;
#include "file_out.h"

void file_out(int res){
	ofstream fout;
	fout.open("record.txt",ios::app);
	time_t now = time(0);
	char* dt = ctime(&now);
	if(res == 0){
		fout << "Game is terminated by player" << " ,  " << dt << endl;
	}
	else if(res == 1){
		fout << "Player1 defeats Boss" << " ,  " << dt << endl;
	}
	else{
		fout << "Player1 was killed by Boss" << " ,  " << dt << endl;
	}
	fout.close();
}
