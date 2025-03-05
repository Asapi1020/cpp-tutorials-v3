#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

enum GameLength { SHORT, MEIDUM, LONG };
enum Difficulty { NORMAL, HARD, SUICIDAL, HOE };

float calcMultiplier(int waveSizeFakes) {
	const vector<float> defaultMultiplier = {1.f, 2.f, 2.75f, 3.5f, 4.0f, 4.5f};
	if (waveSizeFakes < 1) {
		cerr << "Wave Size Fakes is must be positive but " << waveSizeFakes << endl;
		return 0.f;
	}

	if (waveSizeFakes <= 6) {
		return defaultMultiplier[waveSizeFakes - 1];
	}

	return defaultMultiplier[5] + (waveSizeFakes - 6) * 0.211718f;
}

int calcWaveSize(int waveNum, GameLength gameLength, Difficulty difficulty, int waveSizeFakes) {
	const vector<vector<int>> defaultBaseNum = {
		{25, 32, 35, 42}, {25, 28, 32, 32, 35, 40, 42}, {25, 28, 32, 32, 35, 35, 35, 40, 42, 42}};
	const vector<float> defaultDifficultyMod = {0.85f, 1.f, 1.3f, 1.7f};
	const float multiplier = calcMultiplier(waveSizeFakes);

	if (waveNum < 0 || waveNum >= defaultBaseNum[gameLength].size()) {
		cerr << "Wave number is out of range" << endl;
		return 0;
	}

	const int baseNum = defaultBaseNum[gameLength][waveNum];
	const float difficultyMod = defaultDifficultyMod[difficulty];
	return static_cast<int>(floor(multiplier * baseNum * difficultyMod));
}

vector<string> split(const string& s, char delim) {
	vector<string> result;
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}

int main() {
	string command;
	int waveSizeFakes = 1;
	const int waveNum = 9;
	const GameLength gameLength = LONG;
	const Difficulty difficulty = HOE;

	while (true) {
		cout << "Enter command: ";
		getline(cin, command);
		const vector<string> splitCommands = split(command, ' ');
		if (splitCommands.empty()) {
			cout << "Invalid command" << endl;
			continue;
		}

		const string key = splitCommands[0];
		const bool hasValue = splitCommands.size() > 1;

		if (key == "!cdws") {
			const int result = calcWaveSize(waveNum, gameLength, difficulty, waveSizeFakes);
			cout << "Wave Size: " << result << endl;
			continue;
		}

		if (key == "!cdwsf") {
			if (hasValue) {
				waveSizeFakes = stoi(splitCommands[1]);
			}
			cout << "WaveSizeFakes: " << waveSizeFakes << endl;
			continue;
		}

		if (command == "exit") {
			break;
		}

		cout << "Invalid command" << endl;
	}
	return 0;
}
