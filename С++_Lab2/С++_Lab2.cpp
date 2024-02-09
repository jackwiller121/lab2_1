#include <iostream>

class Cell {
public:
    Cell()
    {

    }
    Cell(int start, int end)
    {
        full_li = new char[1024 * 1024];
        isFree = false;

        startBlock = start;
        endBlock = end;
        dlina = endBlock - startBlock + 1;
    }
    char* full_li;
    int startBlock = -1;
    int endBlock = -1;
    bool isFree = true;
    int dlina;
};

class Stack {
public:
    Cell* massive;
    int top;
    Stack(int size = 10)
    {
        massive = new Cell[size]();
        top = -1;
    }

    void Defrag() {
        int i = 1;
        while (i < 10) {
            if (massive[i].isFree == 0 and massive[i - 1].isFree == 1) {
                massive[i - 1] = massive[i];
                massive[i - 1].endBlock--;
                massive[i - 1].startBlock--;
                massive[i].full_li = NULL;
                delete[] massive[i].full_li;
                massive[i] = Cell();
                i = 1;
            }
            else {
                i++;
            }
        }
        for (int i = 0; i < 10; i++) {
            if (massive[i].isFree == 0) {
                top = i;
            }
        }
    }

    void PrintAll() {
        for (int i = 0; i < 10; i++) {
            std::cout << "| ";
            if (massive[i].isFree == false) {
                std::cout << massive[i].dlina;
            }
            else {
                std::cout << "0";
            }
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }

    void push(int MemSize) {
        system("cls");
        if (isFull())
        {
            std::cout << "ОШИБКА! Недостаточно памяти" << std::endl;
            return;
        }
        if (size() + MemSize > 10) {
            std::cout << "ОШИБКА! Недостаточно памяти" << std::endl;
            return;
        }
        short startBlock = top + 1;
        short endBlock = top + MemSize;
        top = endBlock;
        for (int i = startBlock; i <= endBlock; i++)
        {
            massive[i] = Cell(startBlock, endBlock);
        }
    }

    void Delete(int id) {
        system("cls");
        for (int i = 0; i <= top; i++) {
            if (massive[i].startBlock <= id and massive[i].endBlock >= id) {
                massive[i].full_li = 0;
                delete[] massive[i].full_li;
                massive[i] = Cell();
            }
        }
    }

    int size() {
        return top + 1;
    }

    bool isFull() {
        return size() == 10;
    }

    ~Stack()
    {
        delete[] massive;
    }

};

int main()
{   
    setlocale(LC_ALL, "Russian");
    Stack* MemPage = new Stack();
    int MenuStatus = 0;

    while (MenuStatus != 4) {
        MemPage->PrintAll();
        std::cout << std::endl << std::endl << "Выберете действие" << std::endl << std::endl;
        std::cout << "1. Добавить новую ячейку" << std::endl << "2. Удалить ячейку" << std::endl << "3. Дефрагментировать" << std::endl << "4. Выход" << std::endl << std::endl;
        std::cin >> MenuStatus;
        if (MenuStatus == 1) {
            system("cls");
            MemPage->PrintAll();
            std::cout << "Сколько памяти займет ячейка? (MB)" << std::endl << std::endl;
            int CellSizeNeed = 0;
            std::cin >> CellSizeNeed;
            MemPage->push(CellSizeNeed);
        }
        else if (MenuStatus == 2) {
            system("cls");
            MemPage->PrintAll();
            std::cout << "Какую ячейку вы хотите удалить?" << std::endl << std::endl;
            int CellSizeNeed = 0;
            std::cin >> CellSizeNeed;
            MemPage->Delete(CellSizeNeed);
        }
        else if (MenuStatus == 3) {
            system("cls");
            MemPage->PrintAll();
            MemPage->Defrag();
        }
    }
}