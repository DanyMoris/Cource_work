#pragma once // Prevents the file from being included twice
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

// --- Constants for table column widths ---
const int W_INDEX = 5;
const int W_TYPE = 25;
const int W_YEAR = 10;
const int W_SEATS = 10;
const int W_PAYLOAD = 15;
const int W_INSTR = 25;

// ======================================================================
// CLASS: Airplane (Data Model)
// ======================================================================
class Airplane {
private:
    std::string type;        // Type
    int year;           // Year
    int seats;          // Seats
    double payload;     // Payload (tons)
    std::string instructor;  // Instructor name

public:
    // Constructors
    Airplane();
    Airplane(std::string type, int year, int seats, double payload, std::string instructor);

    // Getters
    std::string getType() const;
    int getYear() const;
    int getSeats() const;
    double getPayload() const;
    std::string getInstructor() const;

    // Setters
    void setType(std::string v);
    void setYear(int v);
    void setSeats(int v);
    void setPayload(double v);
    void setInstructor(std::string v);

    // Output methods
    void printRow(int index) const;
    void saveRow(std::ofstream& fout, int index) const;
};

// ======================================================================
// CLASS: FleetManager (Logic / Controller)
// ======================================================================
class FleetManager {
private:
    std::vector<Airplane> fleet;          // Main database
    std::vector<Airplane> searchList;     // Search results list

    // Helper methods
    void printSeparator(std::ostream& os);
    void printHeader(std::ostream& os);
    void printAnyList(const std::vector<Airplane>& list, std::string title);

public:
    
    void showFleet();
    void addRecord();
    void deleteRecord();
    void editRecord();

    // Sorting
    void sortByPayload();
    void sortByType();
    void sortStructural();

    // File operations
    void loadFromFile();
    void saveToFile();

    // Search and List operations
    void search();
    void showSearchList();
    void sortSearchList();
    void saveSearchList();
};