#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

void saveWorld(vector<char> world, vector<int> iC, vector<int> state, bool eV) {
	// iC == item Count
	// eV == expandedVision
	//state: health, energy, every3SecondEnergy, energyLoop, energyLoop2 (every3Second), expandedVisionLoop, speed, speedLoop
	ofstream file(".state.txt");
	string theState = "";
	for(auto a : world) {
		theState += string(1, a) + " ";
	}
	theState += "\n";
	for(auto a : iC) {
		theState += to_string(a) + " ";
	}
	theState += "\n";
	for(auto a : state) {
		theState += to_string(a) + " ";
	}
	theState += string("\n") + (eV ? "true" : "false") + string("\n");
	file << theState;
	file.close();
}

void loadWorld(vector<char>& world, vector<int>& iC, vector<int*> state, bool& eV) {
	ifstream file(".state.txt");
	vector<string> theStatePL; //per line
	string theStateL; //line

	while(getline(file, theStateL)) {
		theStatePL.push_back(theStateL);
	}
	int j = 0; // untuk state nanti
	for(int i = 0; i < 4; i++) {
	stringstream theStatePLPW; //per word per line
    	theStatePLPW << theStatePL[i];
	string data;
		while(theStatePLPW >> data) {
			switch(i) {
				case 0:
					world.push_back(data[0]);
					break;
				case 1:
					iC.push_back(stoi(data));
					break;
				/*case 2:
					while(j < 8) {
						*state[j] = stoi(data);
						j++;
					}
					break;*/
					case 2: {
    stringstream ss(theStatePL[i]);
    string token;
    size_t j = 0;
    while (ss >> token) {
        if (j >= state.size()) {
            cerr << "[loadWorld] Error: terlalu banyak nilai state\n";
            break;
        }
        try {
            *state[j] = stoi(token);
        } catch (...) {
            cerr << "[loadWorld] Warning: token invalid: '" << token << "'\n";
            *state[j] = 0;
        }
        j++;
    }
    if (j < state.size()) {
        cerr << "[loadWorld] Warning: hanya " << j << " nilai state ditemukan, sisanya diisi default\n";
        for (; j < state.size(); ++j) *state[j] = 0;
    }
    break;
}
				case 3:
					eV = (data == "true" ? true : false);
					break;
			}
		}
	}
	file.close();
	
}

