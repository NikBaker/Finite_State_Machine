#pragma once

#include <set>
#include <vector>
#include <iostream>

class FSM
{
private:
    // 1. Алфавит 
    std::vector<char> E;
    // 2. Множество состояний
    std::vector<int> States;
    // 3. Начальное состояние
    int Start;                              // Initial_State
    // 4. Множество конечных состояний
    std::vector<int> Finish_States;            // Final_States        
    // 5. Правила переходов
    std::vector<std::vector<int>> Matrix;   // Rules
public:
    FSM();
    FSM(std::vector<char> E_, std::vector<int> States_, int Start_, std::vector<int> Finish_States_, std::vector<std::vector<int>> Matrix_) :
        E(E_), States(States_), Start(Start_), Finish_States(Finish_States_), Matrix(Matrix_) {};
    void Input();
    friend std::ostream& operator<<(std::ostream& os, const FSM& F);
    // Пересечение двух ДКА
    FSM operator*(const FSM& F) const;
    // Объединение двух ДКА
    FSM operator+(const FSM& F) const;
    // Разность двух ДКА
    FSM operator-(FSM& F) const;
    void FSM_to_SVG(const char* Out_File);

    // для тестов
    std::vector<int> GetFinalStates() {
        return Finish_States;
    }
    std::vector<int> GetAllStates() {
        return States;
    }
    int GetStart() {
        return Start;
    }


private:
    // Отрицание ДКА
    FSM operator-() const;
};

