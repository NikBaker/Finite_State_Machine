#pragma once

#include <set>
#include <vector>
#include <iostream>

class FSM
{
private:
    // 1. ������� 
    std::vector<char> E;
    // 2. ��������� ���������
    std::vector<int> States;
    // 3. ��������� ���������
    int Start;                              // Initial_State
    // 4. ��������� �������� ���������
    std::vector<int> Finish_States;            // Final_States        
    // 5. ������� ���������
    std::vector<std::vector<int>> Matrix;   // Rules
public:
    FSM();
    FSM(std::vector<char> E_, std::vector<int> States_, int Start_, std::vector<int> Finish_States_, std::vector<std::vector<int>> Matrix_) :
        E(E_), States(States_), Start(Start_), Finish_States(Finish_States_), Matrix(Matrix_) {};
    void Input();
    friend std::ostream& operator<<(std::ostream& os, const FSM& F);
    // ����������� ���� ���
    FSM operator*(const FSM& F) const;
    // ����������� ���� ���
    FSM operator+(const FSM& F) const;
    // �������� ���� ���
    FSM operator-(FSM& F) const;
    void FSM_to_SVG(const char* Out_File);

    // ��� ������
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
    // ��������� ���
    FSM operator-() const;
};

