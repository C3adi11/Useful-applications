#include <iostream>
#include <fstream>

using namespace std;

class Employee {
protected:
    char name[100];
    int employeeID;
    double salary;

public:
    Employee(const char* name = "", int id = 0, double salary = 0.0)
        : employeeID(id), salary(salary) {
        int i = 0;
        while (name[i] != '\0' && i < 99) {
            this->name[i] = name[i];
            i++;
        }
        this->name[i] = '\0';
    }

    virtual ~Employee() {}

    virtual double calculateBonus() const {
        return 0.0;
    }

    virtual void getInfo(char* buffer) const {
        char idStr[20], salaryStr[50];
        intToString(employeeID, idStr);
        doubleToString(salary, salaryStr);

        char temp[300];

        setlocale(LC_ALL, "Russian");
        strCopy(temp, "Сотрудник: ");
        strAppend(temp, name);
        strAppend(temp, " ID: ");
        strAppend(temp, idStr);
        strAppend(temp, " Зарплата: ");
        strAppend(temp, salaryStr);

        strCopy(buffer, temp);
    }

    virtual void serialize(char* buffer) const {
        char idStr[20], salaryStr[50];
        intToString(employeeID, idStr);
        doubleToString(salary, salaryStr);

        char temp[300];
        strCopy(temp, "Employee ");
        strAppend(temp, name);
        strAppend(temp, " ");
        strAppend(temp, idStr);
        strAppend(temp, " ");
        strAppend(temp, salaryStr);

        strCopy(buffer, temp);
    }

    const char* getName() const { return name; }
    int getID() const { return employeeID; }
    double getSalary() const { return salary; }
    void setSalary(double salary) { this->salary = salary; }

protected:
    static void strCopy(char* dest, const char* src) {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    static void strAppend(char* dest, const char* src) {
        int len = 0;
        while (dest[len] != '\0') len++;

        int i = 0;
        while (src[i] != '\0') {
            dest[len + i] = src[i];
            i++;
        }
        dest[len + i] = '\0';
    }
    static void intToString(int value, char* buffer) {
        if (value == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        char temp[20];
        int i = 0;
        bool negative = false;

        if (value < 0) {
            negative = true;
            value = -value;
        }

        while (value > 0) {
            temp[i++] = '0' + (value % 10);
            value /= 10;
        }

        int j = 0;
        if (negative) {
            buffer[j++] = '-';
        }

        while (i > 0) {
            buffer[j++] = temp[--i];
        }
        buffer[j] = '\0';
    }

    static void doubleToString(double value, char* buffer) {
        int intPart = (int)value;
        char intBuffer[20];
        intToString(intPart, intBuffer);

        double fractional = value - intPart;
        if (fractional < 0) fractional = -fractional;

        char fracBuffer[20];
        int fracPart = (int)(fractional * 1000);
        intToString(fracPart, fracBuffer);

        strCopy(buffer, intBuffer);
        strAppend(buffer, ".");

        if (fracPart < 10) {
            strAppend(buffer, "00");
        }
        else if (fracPart < 100) {
            strAppend(buffer, "0");
        }
        strAppend(buffer, fracBuffer);
    }
};

class Manager : public Employee {
private:
    int teamSize;
    char departmentName[100];

public:
    Manager(const char* name = "", int id = 0, double salary = 0.0,
        int teamSize = 0, const char* department = "")
        : Employee(name, id, salary), teamSize(teamSize) {
        int i = 0;
        while (department[i] != '\0' && i < 99) {
            this->departmentName[i] = department[i];
            i++;
        }
        this->departmentName[i] = '\0';
    }

    double calculateBonus() const override {
        return salary * 0.1 + teamSize * 500;
    }

    void getInfo(char* buffer) const override {
        char idStr[20], salaryStr[50], teamStr[20];
        intToString(employeeID, idStr);
        doubleToString(salary, salaryStr);
        intToString(teamSize, teamStr);

        char temp[400];
        strCopy(temp, "Менеджер: ");
        strAppend(temp, name);
        strAppend(temp, " ID: ");
        strAppend(temp, idStr);
        strAppend(temp, " Зарплата: ");
        strAppend(temp, salaryStr);
        strAppend(temp, " Отдел: ");
        strAppend(temp, departmentName);
        strAppend(temp, " Размер команды: ");
        strAppend(temp, teamStr);

        strCopy(buffer, temp);
    }

    void serialize(char* buffer) const override {
        char idStr[20], salaryStr[50], teamStr[20];
        intToString(employeeID, idStr);
        doubleToString(salary, salaryStr);
        intToString(teamSize, teamStr);

        char temp[400];
        strCopy(temp, "Manager ");
        strAppend(temp, name);
        strAppend(temp, " ");
        strAppend(temp, idStr);
        strAppend(temp, " ");
        strAppend(temp, salaryStr);
        strAppend(temp, " ");
        strAppend(temp, teamStr);
        strAppend(temp, " ");
        strAppend(temp, departmentName);

        strCopy(buffer, temp);
    }
};

class Developer : public Employee {
private:
    char programmingLanguage[100];
    int completedProjects;

public:
    Developer(const char* name = "", int id = 0, double salary = 0.0,
        const char* language = "", int projects = 0)
        : Employee(name, id, salary), completedProjects(projects) {
        int i = 0;
        while (language[i] != '\0' && i < 99) {
            this->programmingLanguage[i] = language[i];
            i++;
        }
        this->programmingLanguage[i] = '\0';
    }

    double calculateBonus() const override {
        return salary * 0.05 + completedProjects * 1000;
    }

    void getInfo(char* buffer) const override {
        char idStr[20], salaryStr[50], projectsStr[20];
        intToString(employeeID, idStr);
        doubleToString(salary, salaryStr);
        intToString(completedProjects, projectsStr);

        char temp[400];
        strCopy(temp, "Разработчик: ");
        strAppend(temp, name);
        strAppend(temp, " ID: ");
        strAppend(temp, idStr);
        strAppend(temp, " Зарплата: ");
        strAppend(temp, salaryStr);
        strAppend(temp, " Язык программирования: ");
        strAppend(temp, programmingLanguage);
        strAppend(temp, " Завершенные проекты: ");
        strAppend(temp, projectsStr);

        strCopy(buffer, temp);
    }

    void serialize(char* buffer) const override {
        char idStr[20], salaryStr[50], projectsStr[20];
        intToString(employeeID, idStr);
        doubleToString(salary, salaryStr);
        intToString(completedProjects, projectsStr);

        char temp[400];
        strCopy(temp, "Developer ");
        strAppend(temp, name);
        strAppend(temp, " ");
        strAppend(temp, idStr);
        strAppend(temp, " ");
        strAppend(temp, salaryStr);
        strAppend(temp, " ");
        strAppend(temp, programmingLanguage);
        strAppend(temp, " ");
        strAppend(temp, projectsStr);

        strCopy(buffer, temp);
    }
};

class CompanyAnalytics {
public:
    static double calculateTotalExpenses(Employee** employees, int count) {
        double total = 0.0;
        for (int i = 0; i < count; i++) {
            total += employees[i]->getSalary() + employees[i]->calculateBonus();
        }
        return total;
    }

    static void getManagerStatistics(Employee** employees, int count,
        int& managerCount, double& averageTeamSize) {
        managerCount = 0;
        double totalTeamSize = 0.0;

        for (int i = 0; i < count; i++) {
            Manager* manager = dynamic_cast<Manager*>(employees[i]);
            if (manager) {
                managerCount++;
                totalTeamSize += 5;
            }
        }

        averageTeamSize = managerCount > 0 ? totalTeamSize / managerCount : 0.0;
    }
};

double calculateTotalSalary(Employee** employees, int count) {
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += employees[i]->getSalary();
    }
    return total;
}

double calculateAverageSalary(Employee** employees, int count) {
    if (count == 0) return 0.0;
    return calculateTotalSalary(employees, count) / count;
}

Employee* findEmployeeWithMaxSalary(Employee** employees, int count) {
    if (count == 0) return nullptr;

    Employee* maxEmployee = employees[0];
    for (int i = 1; i < count; i++) {
        if (employees[i]->getSalary() > maxEmployee->getSalary()) {
            maxEmployee = employees[i];
        }
    }
    return maxEmployee;
}

void sortEmployeesBySalary(Employee** employees, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (employees[j]->getSalary() > employees[j + 1]->getSalary()) {
                Employee* temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void saveEmployeesToFile(Employee** employees, int count, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи: " << filename << endl;
        return;
    }

    char buffer[400];
    for (int i = 0; i < count; i++) {
        employees[i]->serialize(buffer);
        file << buffer << endl;
    }
    file.close();
}

int stringToInt(const char* str) {
    int result = 0;
    int i = 0;
    bool negative = false;

    if (str[0] == '-') {
        negative = true;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        i++;
    }

    return negative ? -result : result;
}

double stringToDouble(const char* str) {
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 1.0;
    bool decimalPoint = false;
    bool negative = false;

    int i = 0;
    if (str[0] == '-') {
        negative = true;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] == '.') {
            decimalPoint = true;
            i++;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            if (!decimalPoint) {
                result = result * 10 + (str[i] - '0');
            }
            else {
                fraction = fraction * 10 + (str[i] - '0');
                divisor *= 10;
            }
        }
        i++;
    }

    result += fraction / divisor;
    return negative ? -result : result;
}

void parseLine(const char* line, char* type, char* name, char* idStr, char* salaryStr, char* extra1, char* extra2) {
    type[0] = name[0] = idStr[0] = salaryStr[0] = extra1[0] = extra2[0] = '\0';

    int field = 0;
    int pos = 0;
    int start = 0;
    int len = 0;

    while (line[pos] != '\0' && field < 6) {
        if (line[pos] == ' ' || line[pos] == '\n' || line[pos] == '\0') {
            len = pos - start;
            if (len > 0) {
                switch (field) {
                case 0:
                    for (int i = 0; i < len && i < 19; i++) type[i] = line[start + i];
                    type[len < 20 ? len : 19] = '\0';
                    break;
                case 1:
                    for (int i = 0; i < len && i < 99; i++) name[i] = line[start + i];
                    name[len < 100 ? len : 99] = '\0';
                    break;
                case 2:
                    for (int i = 0; i < len && i < 19; i++) idStr[i] = line[start + i];
                    idStr[len < 20 ? len : 19] = '\0';
                    break;
                case 3:
                    for (int i = 0; i < len && i < 49; i++) salaryStr[i] = line[start + i];
                    salaryStr[len < 50 ? len : 49] = '\0';
                    break;
                case 4:
                    for (int i = 0; i < len && i < 99; i++) extra1[i] = line[start + i];
                    extra1[len < 100 ? len : 99] = '\0';
                    break;
                case 5:
                    for (int i = 0; i < len && i < 99; i++) extra2[i] = line[start + i];
                    extra2[len < 100 ? len : 99] = '\0';
                    break;
                }
            }
            start = pos + 1;
            field++;
        }
        pos++;
    }

    if (field < 6 && pos > start) {
        len = pos - start;
        if (len > 0) {
            switch (field) {
            case 4:
                for (int i = 0; i < len && i < 99; i++) extra1[i] = line[start + i];
                extra1[len < 100 ? len : 99] = '\0';
                break;
            case 5:
                for (int i = 0; i < len && i < 99; i++) extra2[i] = line[start + i];
                extra2[len < 100 ? len : 99] = '\0';
                break;
            }
        }
    }
}

bool myStrcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return str1[i] == str2[i];
}

int loadEmployeesFromFile(Employee** employees, int maxCount, const char* filename) {
    ifstream file(filename);
    int loadedEmployees = 0;

    if (!file.is_open()) {
        cout << "Ошибка открытия файла для чтения: " << filename << endl;
        return 0;
    }

    char line[400];
    while (file.getline(line, 400) && loadedEmployees < maxCount) {
        if (line[0] == '\0') continue;

        char type[20], name[100], idStr[20], salaryStr[50], extra1[100], extra2[100];
        parseLine(line, type, name, idStr, salaryStr, extra1, extra2);

        int id = stringToInt(idStr);
        double salary = stringToDouble(salaryStr);

        if (myStrcmp(type, "Manager")) {
            int teamSize = stringToInt(extra1);
            employees[loadedEmployees++] = new Manager(name, id, salary, teamSize, extra2);
        }
        else if (myStrcmp(type, "Developer")) {
            int projects = stringToInt(extra2);
            employees[loadedEmployees++] = new Developer(name, id, salary, extra1, projects);
        }
        else {
            employees[loadedEmployees++] = new Employee(name, id, salary);
        }
    }

    file.close();
    return loadedEmployees;
}

void recalculateSalaries(Employee** employees, int count) {
    if (count == 0) {
        cout << "Нет сотрудников для пересчета зарплаты." << endl;
        return;
    }

    cout << "Введите процент увеличения зарплаты (например, 10 для 10%): ";
    double percentage;
    cin >> percentage;

    if (percentage <= 0) {
        cout << "Процент должен быть положительным числом." << endl;
        return;
    }

    double multiplier = 1.0 + percentage / 100.0;

    for (int i = 0; i < count; i++) {
        double newSalary = employees[i]->getSalary() * multiplier;
        employees[i]->setSalary(newSalary);
    }

    cout << "Зарплаты всех сотрудников увеличены на " << percentage << "%" << endl;
}

bool deleteEmployeeByID(Employee** employees, int& count, int id) {
    int indexToDelete = -1;

    for (int i = 0; i < count; i++) {
        if (employees[i]->getID() == id) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1) {
        cout << "Сотрудник с ID " << id << " не найден." << endl;
        return false;
    }

    delete employees[indexToDelete];

    for (int i = indexToDelete; i < count - 1; i++) {
        employees[i] = employees[i + 1];
    }

    count--;
    cout << "Сотрудник с ID " << id << " удален." << endl;
    return true;
}

void addNewEmployeeInteractive(Employee** employees, int& count, int maxCount) {
    if (count >= maxCount) {
        cout << "Достигнут максимальный лимит сотрудников." << endl;
        return;
    }

    cout << "\nДобавление нового сотрудника:" << endl;

    char name[100];
    int id;
    double salary;
    int typeChoice;

    cout << "Введите имя сотрудника: ";
    cin.ignore();
    cin.getline(name, 100);

    cout << "Введите ID сотрудника: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (employees[i]->getID() == id) {
            cout << "Сотрудник с таким ID уже существует." << endl;
            return;
        }
    }

    cout << "Введите зарплату сотрудника: ";
    cin >> salary;

    cout << "Выберите тип сотрудника:" << endl;
    cout << "1. Обычный сотрудник" << endl;
    cout << "2. Менеджер" << endl;
    cout << "3. Разработчик" << endl;
    cout << "Ваш выбор: ";
    cin >> typeChoice;

    switch (typeChoice) {
    case 1: {
        employees[count++] = new Employee(name, id, salary);
        cout << "Обычный сотрудник добавлен." << endl;
        break;
    }
    case 2: {
        int teamSize;
        char department[100];
        cout << "Введите размер команды менеджера: ";
        cin >> teamSize;
        cout << "Введите название отдела: ";
        cin.ignore();
        cin.getline(department, 100);
        employees[count++] = new Manager(name, id, salary, teamSize, department);
        cout << "Менеджер добавлен." << endl;
        break;
    }
    case 3: {
        char language[100];
        int projects;
        cout << "Введите язык программирования: ";
        cin.ignore();
        cin.getline(language, 100);
        cout << "Введите количество завершенных проектов: ";
        cin >> projects;
        employees[count++] = new Developer(name, id, salary, language, projects);
        cout << "Разработчик добавлен." << endl;
        break;
    }
    default:
        cout << "Неверный выбор типа сотрудника." << endl;
        return;
    }
}

void displayMenu() {
    cout << "\n=== Меню управления сотрудниками ===" << endl;
    cout << "1. Показать всех сотрудников" << endl;
    cout << "2. Добавить нового сотрудника" << endl;
    cout << "3. Удалить сотрудника по ID" << endl;
    cout << "4. Пересчитать зарплаты всех сотрудников" << endl;
    cout << "5. Сохранить сотрудников в файл" << endl;
    cout << "6. Загрузить сотрудников из файла" << endl;
    cout << "7. Показать аналитику компании" << endl;
    cout << "8. Отсортировать сотрудников по зарплате" << endl;
    cout << "9. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int MAX_EMPLOYEES = 100;
    Employee* employees[MAX_EMPLOYEES];
    int employeeCount = 0;

    employees[employeeCount++] = new Manager("Иван", 1, 50000, 5, "ИТ");
    employees[employeeCount++] = new Developer("Петр", 2, 60000, "C++", 3);
    employees[employeeCount++] = new Employee("Сергей", 3, 40000);

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\nИнформация о сотрудниках:" << endl;
            if (employeeCount == 0) {
                cout << "Нет сотрудников для отображения." << endl;
            }
            else {
                char buffer[400];
                for (int i = 0; i < employeeCount; i++) {
                    employees[i]->getInfo(buffer);
                    cout << buffer << endl;
                }
            }
            break;
        }
        case 2: {
            addNewEmployeeInteractive(employees, employeeCount, MAX_EMPLOYEES);
            break;
        }
        case 3: {
            if (employeeCount == 0) {
                cout << "Нет сотрудников для удаления." << endl;
                break;
            }
            int idToDelete;
            cout << "Введите ID сотрудника для удаления: ";
            cin >> idToDelete;
            deleteEmployeeByID(employees, employeeCount, idToDelete);
            break;
        }
        case 4: {
            recalculateSalaries(employees, employeeCount);
            break;
        }
        case 5: {
            saveEmployeesToFile(employees, employeeCount, "employees.txt");
            cout << "Сотрудники сохранены в файл employees.txt" << endl;
            break;
        }
        case 6: {
            for (int i = 0; i < employeeCount; i++) {
                delete employees[i];
            }
            employeeCount = 0;

            employeeCount = loadEmployeesFromFile(employees, MAX_EMPLOYEES, "employees.txt");
            cout << "Загружено сотрудников: " << employeeCount << endl;
            break;
        }
        case 7: {
            cout << "\nАналитика компании:" << endl;
            if (employeeCount == 0) {
                cout << "Нет сотрудников для анализа." << endl;
                break;
            }

            double totalExpenses = CompanyAnalytics::calculateTotalExpenses(employees, employeeCount);
            cout << "Общие расходы на зарплаты и бонусы: " << totalExpenses << endl;

            double avgSalary = calculateAverageSalary(employees, employeeCount);
            cout << "Средняя зарплата: " << avgSalary << endl;

            Employee* maxSalaryEmployee = findEmployeeWithMaxSalary(employees, employeeCount);
            if (maxSalaryEmployee) {
                cout << "Сотрудник с максимальной зарплатой: " << maxSalaryEmployee->getName()
                    << " (" << maxSalaryEmployee->getSalary() << ")" << endl;
            }

            int managerCount;
            double averageTeamSize;
            CompanyAnalytics::getManagerStatistics(employees, employeeCount, managerCount, averageTeamSize);
            cout << "Количество менеджеров: " << managerCount << endl;
            cout << "Средний размер команды менеджеров: " << averageTeamSize << endl;
            break;
        }
        case 8: {
            if (employeeCount == 0) {
                cout << "Нет сотрудников для сортировки." << endl;
                break;
            }
            sortEmployeesBySalary(employees, employeeCount);
            cout << "Сотрудники отсортированы по зарплате." << endl;
            break;
        }
        case 9: {
            running = false;
            cout << "Выход из программы." << endl;
            break;
        }
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
    for (int i = 0; i < employeeCount; i++) {
        delete employees[i];
    }

    return 0;
}
