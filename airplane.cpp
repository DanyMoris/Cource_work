#include "airplane.h"
#include <algorithm>
#include <sstream>

using namespace std::literals;

// ======================================================================
// Implementation of class Airplane
// ======================================================================

Airplane::Airplane() : year(0), seats(0), payload(0.0) {}

Airplane::Airplane(std::string type, int year, int seats, double payload, std::string instructor)
    : type(type), year(year), seats(seats), payload(payload), instructor(instructor) {
}

// Getters
std:: string Airplane::getType() const { return type; }
int Airplane::getYear() const { return year; }
int Airplane::getSeats() const { return seats; }
double Airplane::getPayload() const { return payload; }
std::string Airplane::getInstructor() const { return instructor; }

// Setters
void Airplane::setType(std::string v) { type = v; }
void Airplane::setYear(int v) { year = v; }
void Airplane::setSeats(int v) { seats = v; }
void Airplane::setPayload(double v) { payload = v; }
void Airplane::setInstructor(std::string v) { instructor = v; }

void Airplane::printRow(int index) const {
    std::cout << "|" << std::left << std::setw(W_INDEX) << index
        << "| " << std::left << std::setw(W_TYPE) << type
        << "| " << std::left << std::setw(W_YEAR) << year
        << "| " << std::left << std::setw(W_SEATS) << seats
        << "| " << std::left << std::setw(W_PAYLOAD) << std::fixed << std::setprecision(1) << payload
        << "| " << std:: left << std::setw(W_INSTR) << instructor << "|\n";
}

void Airplane::saveRow(std::ofstream& fout, int index) const {
    fout << "|" << std::left << std::setw(W_INDEX) << index
        << "| " << std::left << std::setw(W_TYPE) << type
        << "| " << std::left << std::setw(W_YEAR) << year
        << "| " << std::left << std::setw(W_SEATS) << seats
        << "| " << std::left << std::setw(W_PAYLOAD) << std::fixed << std::setprecision(1) << payload
        << "| " << std::left << std::setw(W_INSTR) << instructor << "|\n";
}

// ======================================================================
// Implementation of class FleetManager
// ======================================================================

void FleetManager::printSeparator(std::ostream& os) {
    os << std::string(102, '-') << std::endl;
}

void FleetManager::printHeader(std::ostream& os) {
    printSeparator(os);
    os << "|" << std::left << std::setw(W_INDEX) << "№"
        << "| " << std::left << std::setw(W_TYPE) << "Тип"
        << "| " << std::left << std::setw(W_YEAR) << "Год"
        << "| " << std::left << std::setw(W_SEATS) << "Мест"
        << "| " << std::left << std::setw(W_PAYLOAD) << "Груз(т)"
        << "| " << std::left << std::setw(W_INSTR) << "Инструктор" << "|\n";
    printSeparator(os);
}


void FleetManager::printAnyList(const std::vector<Airplane>& list, std::string title) {
    if (list.empty()) {
        std::cout << "\n[" << title << "]: Список пуст." << std::endl;
        return;
    }
    std::cout << "\n=== " << title << " ===" << std::endl;
    printHeader(std::cout);
    for (size_t i = 0; i < list.size(); ++i) {
        list[i].printRow(i + 1);
    }
    printSeparator(std::cout);
}

void FleetManager::showFleet() {
    printAnyList(fleet, "АВИАФЛОТ"s);
}

void FleetManager::loadFromFile() {


    std::string filename;
    std::cout << "Введите имя файла (например, planes.txt): ";
    std::cin >> filename;

    std::ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл!" << std::endl;
        return;
    }

    fleet.clear();
    std::string line;
    int loadedCount = 0;

    while (getline(fin, line)) {
        // Skip empty lines or headers
        if (line.empty() || line.find("---") != std::string::npos || line.find("Тип") != std::string::npos)
            continue;

        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string segment;

        // Split line by '|' delimiter
        while (std::getline(ss, segment, '|')) {
            // Optional: Simple trim to remove potential surrounding spaces
            size_t first = segment.find_first_not_of(" \t");
            if (std::string::npos == first) {
                tokens.push_back("");
            }
            else {
                size_t last = segment.find_last_not_of(" \t");
                tokens.push_back(segment.substr(first, (last - first + 1)));
            }
        }

        // Ensure we parsed enough columns (we expect 5)
        if (tokens.size() < 5) {
            continue; // Skip malformed lines
        }

        try {
            Airplane p;
            p.setType(tokens[0]);                // Type is first
            p.setYear(std::stoi(tokens[1]));     // Year is second
            p.setSeats(std::stoi(tokens[2]));    // Seats
            p.setPayload(std::stod(tokens[3]));  // Payload
            p.setInstructor(tokens[4]);          // Instructor

            fleet.push_back(p);
            loadedCount++;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка парсинга строки: " << line << "\nDetails: " << e.what() << std::endl;
        }
    }
    fin.close();
    std::cout << "Успешно загружено записей: " << loadedCount << std::endl;
}

void FleetManager::addRecord() {
    Airplane p;
    std::string tempS; // temporary string
    int tempI; // temporary integer
    double tempD; // temporary double 

    std::cin.ignore(10000, '\n');

    std::cout << "Введите тип самолета: "; std:getline(std::cin, tempS); p.setType(tempS);

    std::cout << "Введите год выпуска: ";
    while (!(std::cin >> tempI)) { std::cout << "Ошибка! Введите число: "; std::cin.clear(); std::cin.ignore(10000, '\n'); }
    p.setYear(tempI);

    std::cout << "Введите кол-во кресел: ";
    while (!(std::cin >> tempI)) { std::cout << "Ошибка! Введите число: "; std::cin.clear(); std::cin.ignore(10000, '\n'); }
    p.setSeats(tempI);

    std::cout << "Введите грузоподъемность: ";
    while (!(std::cin >> tempD)) { std::cout << "Ошибка! Введите число: "; std::cin.clear(); std::cin.ignore(10000, '\n'); }
    p.setPayload(tempD);

    std::cout << "Введите фамилию инструктора: "; std::getline(std::cin >> std::ws, tempS); p.setInstructor(tempS);

    fleet.push_back(p);
    std::cout << "Запись добавлена!" << std::endl;
}

void FleetManager::deleteRecord() {
    if (fleet.empty()) { std::cout << "База пуста." << std::endl; return; }
    showFleet();

    int idx;
    std::cout << "Введите номер записи для удаления: ";
    std::cin >> idx;

    if (idx < 1 || idx >(int)fleet.size()) {
        std::cout << "Неверный номер!" << std::endl;
        return;
    }

    fleet.erase(fleet.begin() + idx - 1);
    std::cout << "Запись удалена." << std::endl;
}

void FleetManager::editRecord() {
    if (fleet.empty()) { std::cout << "База пуста." << std::endl; return; }
    showFleet();

    int idx;
    std::cout << "Введите номер записи для редактирования: ";
    std::cin >> idx;

    if (idx < 1 || idx >(int)fleet.size()) {
        std::cout << "Неверный номер!" << std::endl;
        return;
    }

    Airplane& p = fleet[idx - 1];
    std::string buf;
    std::cin.ignore(10000, '\n');

    std::cout << "--- Редактирование (введите '-', чтобы оставить старое) ---\n";

    std::cout << "Тип [" << p.getType() << "]: "; std::getline(std::cin, buf);
    if (buf != "-") { p.setType(buf); }

    std::cout << "Год [" << p.getYear() << "]: "; std::cin >> buf;
    if (buf != "-" && !buf.empty()) { p.setYear(stoi(buf)); }

    std::cout << "Кресла [" << p.getSeats() << "]: "; std::cin >> buf;
    if (buf != "-" && !buf.empty()) { p.setSeats(stoi(buf)); }

    std::cout << "Груз [" << p.getPayload() << "]: "; std::cin >> buf;
    if (buf != "-" && !buf.empty()) { p.setPayload(stod(buf)); }

    std::cout << "Инструктор [" << p.getInstructor() << "]: "; std::getline(std::cin >> std::ws, buf);
    if (buf != "-") { p.setInstructor(buf); }

    std::cout << "Запись обновлена!" << std::endl;
}

void FleetManager::sortByPayload() {
    if (fleet.empty()) return;
    sort(fleet.begin(), fleet.end(), [](const Airplane& a, const Airplane& b) {
        return a.getPayload() < b.getPayload();
        });
    std::cout << "Отсортировано по грузоподъемности." << std::endl;
    showFleet();
}

void FleetManager::sortByType() {
    if (fleet.empty()) return;
    sort(fleet.begin(), fleet.end(), [](const Airplane& a, const Airplane& b) {
        return a.getType() < b.getType();
        });
    std::cout << "Отсортировано по тип самолета." << std::endl;
    showFleet();
}

void FleetManager::sortStructural() {
    if (fleet.empty()) return;
    sort(fleet.begin(), fleet.end(), [](const Airplane& a, const Airplane& b) {
        if (a.getType() != b.getType()) {
            return a.getType() < b.getType();
        }
        return a.getInstructor() < b.getInstructor();
        });
    std::cout << "Выполнена структурная сортировка (Тип + Инструктор)." << std::endl;
    showFleet();
}

void FleetManager::saveToFile() {
    if (fleet.empty()) { std::cout << "Нет данных для сохранения." << std::endl; return; }

    std::string filename;
    std::cout << "Введите имя файла для сохранения: ";
    std::cin >> filename;

    std::ofstream fout(filename.c_str());
    if (!fout.is_open()) { std::cout << "Ошибка записи!" << std::endl; return; }

    printHeader(fout);
    for (size_t i = 0; i < fleet.size(); ++i) {
        fleet[i].saveRow(fout, i + 1);
    }
    printSeparator(fout);
    fout.close();
    std::cout << "База успешно сохранена в " << filename << std::endl;
}

void FleetManager::search() {
    if (fleet.empty()) { std::cout << "База пуста." << std::endl; return; }

    searchList.clear();
    int mode;
    std::cout << "\n--- РЕЖИМ ПОИСКА ---\n";
    std::cout << "1. По одному признвку(Фамилия инструктора)\n";
    std::cout << "2. По двум признакам (Фамилия и Тип самолёта)\n";
    std::cout << "Выбор: ";
    std::cin >> mode;

    std::string instr, type;
    std::cout << "Введите фамилию(или часть): "; std::getline(std::cin >> std::ws, instr);

    if (mode == 2) {
        std::cout << "Введите тип самолёта(или часть): "; std::getline(std::cin >> std::ws, type);
    }

    for (const auto& plane : fleet) {
        bool matchInstr = (plane.getInstructor().find(instr) != std::string::npos);
        bool matchType = true;

        if (mode == 2) {
            matchType = (plane.getType().find(type) != std::string::npos);
        }

        if (matchInstr && matchType)
            searchList.push_back(plane);
    }

    if (searchList.empty())
        std::cout << "Поиск не дал результатов. Перечень пуст." << std::endl;
    else {
        std::cout << "Найдено записей: " << searchList.size() << std::endl;
        printAnyList(searchList, "ПЕРЕЧЕНЬ (резльтаты поиска)");
    }
}

void FleetManager::showSearchList() {
    printAnyList(searchList, "ТЕКУЩИЙ ПЕРЕЧЕНЬ");
}

void FleetManager::sortSearchList() {
    if (searchList.empty()) { std::cout << "Перечень пуст.\n"; return; }

    sort(searchList.begin(), searchList.end(), [](const Airplane& a, const Airplane& b) {
        return a.getYear() < b.getYear();
        });

    std::cout << "Перечень отсортированан по году выпуска.\n";
    showSearchList();
}

void FleetManager::saveSearchList() {
    if (searchList.empty()) { std::cout << "Перечень пуст." << std::endl; return; }

    std::string filename;
    std::cout << "Введите имя файла для сохранения отчёта: ";
    std::cin >> filename;

    std::ofstream fout(filename.c_str());
    if (!fout.is_open()) { std::cout << "Ошмбка: не получается открыть файл.\n"; return; }

    fout << "ОТЧЁТ ПО РЕЗУЛЬТАТАМ ПОИСКА\n";
    printHeader(fout);
    for (std::size_t i = 0; i < searchList.size(); ++i) {
        searchList[i].saveRow(fout, i + 1);
    }
    printSeparator(fout);
    fout.close();
    std::cout << "Перечень сохранён в " << filename << std::endl;
}