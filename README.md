# Домашняя работа по дисциплине "Теоретические модели вычислений"
## Щучкин Никита А-13а-19
#

### **Задание №5. Реализовать алгоритм.**  
    Ответом на данное задание является работающая программа на выбранном языке программирования.
    В рамках своего выполнения программа должна генерировать текстовый документ с картинками, показывающий процесс построения автомата(к примеру, Markdown с графиками на Graphviz).
    Алгоритм для реализации:  
        Построение прямого произведения двух ДКА, с возможностью построить 
        объединение и разность.

### **2.	Входные данные.**  
    Автоматы задаются при помощи 5 параметров:
    1. Входной алфавит(задается как vector<char>)  
    2. Множество состояний(задается как vector<int>)
    3. Начальное состояние(задается как int)
    4. Множество конечных состояний(задается как vector<int>)
    5. Правила переходов из одного состояния в другие(задается как      vector<vector<int>>)

### **3.	Выходные данные.**  
    На выходе получается md файл с картиками исходных автоматов, построенных в Graphviz, а также картинки с пересечением, объединением и разностью исходных автоматов.
