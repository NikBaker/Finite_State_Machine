#include <iostream>
#include <set>
#include <vector>
#include <fstream>

#include "FSM.h"

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::ofstream;
using std::vector;

FSM::FSM() {
	E = {};
	States = {};
	Start = 1;
	Finish_States = {};
	Matrix = {};
}

void FSM::Input() {
	cout << "Enter the number of characters in the alphabet: ";
	int num_of_ch;
	cin >> num_of_ch;
	while (num_of_ch < 1) {
		cout << "Wrong format, please try again" << endl;
		cout << "Enter the number of characters in the alphabet: ";
		cin >> num_of_ch;
	}
	for (int i = 0; i < num_of_ch; ++i) {
		cout << "Enter the " << i + 1 << " character of the alphabet: ";
		char c;
		cin >> c;
		E.push_back(c);
	}
	cout << "Enter the number of states in the finite state machine: ";
	int n;
	cin >> n;
	while (n< 1) {
		cout << "Wrong format, please try again" << endl;
		cout << "Enter the number of states in the finite state machine: ";
		cin >> n;
	}
	for (int i = 0; i < n; ++i) {
		States.push_back(i + 1);
	}
	cout << "Enter initial state number: ";
	cin >> Start;
	while (Start < 1 || Start > n) {
		cout << "Initial state number can't be more than the number of all states or less than 1! " << endl;
		cout << "Please try again " << endl;
		cout << "Enter initial state number: ";
		cin >> Start;
	}
	cout << "Enter the number of final states in the finite state machine: ";
	int m;
	cin >> m;
	while (m > n || m < 1) {
		cout << "The number of final states can't be more than the number of all states or less than 1! " << endl;
		cout << "Please try again " << endl;
		cout << "Enter the number of final states in the finite state machine: ";
		cin >> m;
	}
	for (int i = 0; i < m; ++i) {
		cout << "Enter " << i + 1 << " final state number: ";
		int final;
		cin >> final;
		while (final < 1 || final > n) {
			cout << "Final state number can't be more than the number of all states or less than 1! " << endl;
			cout << "Please try again " << endl;
			cout << "Enter " << i + 1 << " final state number: ";
			cin >> final;
		}
		Finish_States.push_back(final);
	}

	
	cout << "Entering transition rules (If there is no transition from the state by a given letter, enter \"-1\"): " << endl;
	vector<vector<int>> temp(States.size(), vector <int>(E.size()));
	for (int i = 0; i < States.size(); ++i) {
		for (int j = 0; j < E.size(); ++j) {
			cout << "Enter the state into which the finite state machine passes from state " << i + 1 << " by letter " << E[j] << ": ";
			int to;
			cin >> to;
			while (to < -1 || to == 0 || to > States.size()) {
				cout << "Wrong format, please try again " << endl;
				cout << "Enter the state into which the finite state machine passes from state " << i + 1 << " by letter " << E[j] << ": ";
				cin >> to;
			}
			temp[i][j] = to;
		}
	}
	Matrix = temp;
}

ostream& operator<<(ostream& os, const FSM& F) {
	os << "Alphabet: " << endl;
	for (const auto& c : F.E) {
		os << c << " ";
	}
	os << endl;
	os << "All states: " << endl;
	for (const auto& s : F.States) {
		os << s << " ";
	}
	os << endl;
	os << "Initial state: " << F.Start << endl;
	os << "Final states: " << endl;
	for (const auto& f : F.Finish_States) {
		os << f << " ";
	}
	os << endl;
	os << "Transition rules " << endl;
	os << "In Matrix form: " << endl;
	os << "\t";
	for (const auto& c : F.E) {
		os << c << "\t";
	}
	os << endl;
	for (int  i = 0; i < F.Matrix.size(); ++ i) {
		os << F.States[i] << "\t";
		for (int j = 0; j < F.Matrix[0].size(); ++j) {
			os << F.Matrix[i][j] << "\t";
		}
		os << endl;
	}
	os << "In \"->\" form: " << endl;
	for (int i = 0; i < F.Matrix.size(); ++i) {
		for (int j = 0; j < F.Matrix[0].size(); ++j) {
			os << "delta(" << F.States[i] << ", " << F.E[j] << ") = " << F.Matrix[i][j] << endl;
		}
		os << endl;
	}
	
	// "-1" в матрице и в -> означает, что по данной букве нет перехода

	return os;
}

// конкатенация двух интов
int concat(int n, int m) {
	int res = n;
	for (int i = m; i != 0; i /= 10) {
		res *= 10;
	}
	res += m;
	return res;
}

FSM FSM::operator*(const FSM& F) const {
	FSM result;
	// E = E1 = E2
	if (E != F.E) {
		cout << "Alphabets of finite state machines do not match " << endl;
		cout << "The resul of the operation will be the first operand. " << endl;
		result = *this;
		return result;
	}
	result.E = E;

	// States = States1 x States2
	for (int i = 0; i < States.size(); ++i) {
		for (int j = 0; j < F.States.size(); ++j) {
			result.States.push_back(concat(States[i], F.States[j]));
		}
	}

	// Start = <Start1, Start2>
	result.Start = concat(Start, F.Start);

	// Finish_States = Finish_States1 x Finish_States2
	for (int i = 0; i < Finish_States.size(); ++i) {
		for (int j = 0; j < F.Finish_States.size(); ++j) {
			result.Finish_States.push_back(concat(Finish_States[i], F.Finish_States[j]));
		}
	}

	// delta(<q1,q2>, c) = <delta1(q1,c), delta2(q2,c)>
	vector<vector<int>> temp(result.States.size(), vector <int>(result.E.size()));
	int k = F.Matrix.size();
	for (int i = 0; i < result.States.size(); ++i) {
		for (int j = 0; j < result.E.size(); ++j) {
			// Если не определен какой-то переход в одном из автоматов, то в итоговом автомате этот переход тоже будет не определен
			if (Matrix[i / k][j] == -1 || F.Matrix[i % k][j] == -1) {		
				temp[i][j] = -1;
			}
			else {
				temp[i][j] = concat(Matrix[i / k][j], F.Matrix[i % k][j]);		
			}
		}
	}
	result.Matrix = temp;

	return result;
}

FSM FSM::operator+(const FSM& F) const {	// Finish_States = (Finish_States1 x States2) v (States1 x Finish_States2)
	FSM result = *this * F;
	vector<int> Fin_for_res;

	for (int i = 0; i < Finish_States.size(); ++i) {
		for (int j = 0; j < F.States.size(); ++j) {
			Fin_for_res.push_back(concat(Finish_States[i], F.States[j]));
		}
	}

	for (int i = 0; i < States.size(); ++i) {
		for (int j = 0; j < F.Finish_States.size(); ++j) {
			int temp = concat(States[i], F.Finish_States[j]);
			// Если такого конечного состояния ещё нет:
			if (find(result.Finish_States.begin(), result.Finish_States.end(), temp) == result.Finish_States.end()) {
				Fin_for_res.push_back(concat(States[i], F.Finish_States[j]));
			}
		}
	}
	result.Finish_States = Fin_for_res;

	return result;
}

FSM FSM::operator-() const{
	FSM result = *this;
	vector<int> temp;
	for (const auto& s : States) {
		// Если состояние было неконечным, то добавляем его в temp
		if (find(Finish_States.begin(), Finish_States.end(), s) == Finish_States.end()) {
			temp.push_back(s);
		}
	}
	// Обновляем вектор конечных состояний
	result.Finish_States = temp;

	return result;
}

FSM FSM::operator-(FSM& F) const {
	return *this * -F;
}


void FSM::FSM_to_SVG(const char* Out_File) {
	// Создаем дот файл с описанием автомата
	ofstream out(Out_File);
	out << "digraph {\n";
	out << " rankdir=\"LR\";\n";
	out << " start [style=filled,color=white, label = \"\"];\n";

	for (const auto& s : States) {
		// если состояние является конечным
		if (find(Finish_States.begin(), Finish_States.end(), s) != Finish_States.end()) {
			out << "  " << s << "[shape=doublecircle]" << ";\n";
		}
		else {
			out << "  " << s << "[shape=circle]" << ";\n";
		}
	}

	for (int j = 0; j < States.size(); ++j) {

		if (States[j] == Start) {
			out << "  " << "start -> " << Start << "[label = \"\"]" << ";\n";
		}

		auto it = E.begin();
		for (int k = 0; k < Matrix[j].size(); ++k) {
			if (Matrix[j][k] == -1) {
				continue;
			}
			out << "  " << States[j] << " -> " << Matrix[j][k] << "[label = " << E[k] << "]" << ";\n";
		}
	}
	out << "}\n";

	// Преобразовываем получившийся дот в svg-картику при помощи dot.exe
	char str[100];
	sprintf_s(str, "start debug\\dot\\dot -Tsvg -O %s %s", Out_File, Out_File);
	system(str);
}
