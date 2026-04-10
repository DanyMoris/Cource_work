#define NOMINMAX 
#include <iostream>
#include <windows.h> 
#include "airplane.h" // Include our header file


int main() {
    // Set console encoding for Russian language
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    FleetManager manager;
    int choice = 0;

    do {
        std::cout << "\n================ МЕНЮ ================\n";
        std::cout << "1.  Загрузка информации из файла\n";
        std::cout << "2.  Просмотр (вывод на экран) базы данных\n";
        std::cout << "3.  Добавление новой записи\n";
        std::cout << "4.  Удаление записи\n";
        std::cout << "5.  Редактирование записи\n";
        std::cout << "6.  Сортировка по числовому полю (Грузоподъемность)\n";
        std::cout << "7.  Сортировка по строковому полю (Тип)\n";
        std::cout << "8.  Структурная сортировка (Тип + Инструктор)\n";
        std::cout << "9.  Сохранение результатов (всей базы) в файл\n";
        std::cout << "10. Поиск (создание Перечня найденных)\n";
        std::cout << "11. Просмотр перечня\n";
        std::cout << "12. Сортировка перечня(по году выпуска)\n";
        std::cout << "13. Сохранение перечня в файл\n";
        std::cout << "0.  Выход\n";
        std::cout << "Ваш выбор: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
        }

        switch (choice) {
        case 1: manager.loadFromFile(); break;
        case 2: manager.showFleet(); break;
        case 3: manager.addRecord(); break;
        case 4: manager.deleteRecord(); break;
        case 5: manager.editRecord(); break;
        case 6: manager.sortByPayload(); break;
        case 7: manager.sortByType(); break;
        case 8: manager.sortStructural(); break;
        case 9: manager.saveToFile(); break;
        case 10: manager.search(); break;
        case 11: manager.showSearchList(); break;
        case 12: manager.sortSearchList(); break;
        case 13: manager.saveSearchList(); break;
        case 0: std::cout << "Завершение работы." << std::endl; break;
        default: std::cout << "Неверный пункт меню." << std::endl; break;
        }

    } while (choice != 0);

    return 0;
}