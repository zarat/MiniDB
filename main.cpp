#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <vector>
#include <utility>

enum DataType { INT, STRING };

struct Column {
    std::string name;
    DataType type;

    Column(const std::string& name, DataType type) : name(name), type(type) {}
};

class Table {
private:
    std::vector<Column> columns;
    std::vector<std::unordered_map<std::string, std::string>> rows;
    std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>> index; // Index für schnelle Suchen

public:
    Table(const std::vector<Column>& cols) : columns(cols) {}

    void insertRow(const std::unordered_map<std::string, std::string>& row) {
        rows.push_back(row);
        for (const auto& col : columns) {
            if (row.find(col.name) != row.end()) {
                index[col.name][row.at(col.name)].insert(row.at(col.name)); // Index bauen
            }
        }
    }

    void showRows() const {
        for (const auto& row : rows) {
            for (const auto& col : columns) {
                std::cout << col.name << "=" << row.at(col.name) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Liefert die Zeilen der Tabelle
    const std::vector<std::unordered_map<std::string, std::string>>& getRows() const {
        return rows;
    }

    bool hasColumn(const std::string& columnName) const {
        for (const auto& col : columns) {
            if (col.name == columnName) {
                return true;
            }
        }
        return false;
    }

    // Indizierte Suche für eine Spalte
    std::pair<bool, std::unordered_set<std::string>> searchIndex(const std::string& columnName, const std::string& value) const {
        if (index.find(columnName) != index.end()) {
            auto& columnIndex = index.at(columnName);
            if (columnIndex.find(value) != columnIndex.end()) {
                return {true, columnIndex.at(value)};
            }
        }
        return {false, {}}; // Keine Übereinstimmung
    }
};

enum JoinType { INNER, LEFT, RIGHT, FULL };

// JOINS: INNER, LEFT, RIGHT, FULL
void joinTables(
    const Table& table1, const std::string& column1,
    const Table& table2, const std::string& column2,
    const JoinType joinType,
    const std::vector<std::pair<std::string, std::string>>& whereConditions
) {
    const auto& rows1 = table1.getRows();
    const auto& rows2 = table2.getRows();
    
    auto satisfiesWhere = [&whereConditions](const std::unordered_map<std::string, std::string>& row) -> bool {
        for (const auto& condition : whereConditions) {
            const auto& column = condition.first;
            const auto& value = condition.second;
            if (row.find(column) == row.end() || row.at(column) != value) {
                return false;
            }
        }
        return true;
    };

    for (const auto& row1 : rows1) {
        bool matched = false;
        for (const auto& row2 : rows2) {
            if (row1.at(column1) == row2.at(column2)) {
                if (satisfiesWhere(row1) && satisfiesWhere(row2)) {
                    matched = true;
                    for (auto it = row1.begin(); it != row1.end(); ++it) {
                        std::cout << it->first << "=" << it->second << " ";
                    }
                    for (auto it = row2.begin(); it != row2.end(); ++it) {
                        std::cout << it->first << "=" << it->second << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }

        if (joinType == LEFT && !matched) {
            if (satisfiesWhere(row1)) {
                for (auto it = row1.begin(); it != row1.end(); ++it) {
                    std::cout << it->first << "=" << it->second << " ";
                }
                for (const auto& col : table2.getRows()[0]) { 
                    std::cout << col.first << "=NULL ";
                }
                std::cout << std::endl;
            }
        }
    }

    if (joinType == RIGHT) {
        for (const auto& row2 : rows2) {
            bool matched = false;
            for (const auto& row1 : rows1) {
                if (row1.at(column1) == row2.at(column2)) {
                    if (satisfiesWhere(row1) && satisfiesWhere(row2)) {
                        matched = true;
                        for (auto it = row1.begin(); it != row1.end(); ++it) {
                            std::cout << it->first << "=" << it->second << " ";
                        }
                        for (auto it = row2.begin(); it != row2.end(); ++it) {
                            std::cout << it->first << "=" << it->second << " ";
                        }
                        std::cout << std::endl;
                    }
                }
            }
            if (!matched && satisfiesWhere(row2)) {
                for (const auto& col : table1.getRows()[0]) { 
                    std::cout << col.first << "=NULL ";
                }
                for (auto it = row2.begin(); it != row2.end(); ++it) {
                    std::cout << it->first << "=" << it->second << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    // FULL OUTER JOIN
    if (joinType == FULL) {
        for (const auto& row1 : rows1) {
            bool matched = false;
            for (const auto& row2 : rows2) {
                if (row1.at(column1) == row2.at(column2)) {
                    if (satisfiesWhere(row1) && satisfiesWhere(row2)) {
                        matched = true;
                        for (auto it = row1.begin(); it != row1.end(); ++it) {
                            std::cout << it->first << "=" << it->second << " ";
                        }
                        for (auto it = row2.begin(); it != row2.end(); ++it) {
                            std::cout << it->first << "=" << it->second << " ";
                        }
                        std::cout << std::endl;
                    }
                }
            }
            if (!matched && satisfiesWhere(row1)) {
                for (auto it = row1.begin(); it != row1.end(); ++it) {
                    std::cout << it->first << "=" << it->second << " ";
                }
                for (const auto& col : table2.getRows()[0]) { // Rechte Tabelle ist leer
                    std::cout << col.first << "=NULL ";
                }
                std::cout << std::endl;
            }
        }

        for (const auto& row2 : rows2) {
            bool matched = false;
            for (const auto& row1 : rows1) {
                if (row1.at(column1) == row2.at(column2)) {
                    if (satisfiesWhere(row1) && satisfiesWhere(row2)) {
                        matched = true;
                        for (auto it = row1.begin(); it != row1.end(); ++it) {
                            std::cout << it->first << "=" << it->second << " ";
                        }
                        for (auto it = row2.begin(); it != row2.end(); ++it) {
                            std::cout << it->first << "=" << it->second << " ";
                        }
                        std::cout << std::endl;
                    }
                }
            }
            if (!matched && satisfiesWhere(row2)) {
                for (const auto& col : table1.getRows()[0]) { // Linke Tabelle ist leer
                    std::cout << col.first << "=NULL ";
                }
                for (auto it = row2.begin(); it != row2.end(); ++it) {
                    std::cout << it->first << "=" << it->second << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

int main() {
	
    Table users({
        Column("id", INT),
        Column("name", STRING),
        Column("age", INT)
    });

    Table orders({
        Column("order_id", INT),
        Column("user_id", INT),
        Column("amount", INT)
    });

    users.insertRow({{"id", "1"}, {"name", "Alice"}, {"age", "30"}});
    users.insertRow({{"id", "2"}, {"name", "Bob"}, {"age", "25"}});
    users.insertRow({{"id", "3"}, {"name", "Charlie"}, {"age", "35"}});

    orders.insertRow({{"order_id", "1"}, {"user_id", "1"}, {"amount", "50"}});
    orders.insertRow({{"order_id", "2"}, {"user_id", "2"}, {"amount", "60"}});
    orders.insertRow({{"order_id", "3"}, {"user_id", "3"}, {"amount", "70"}});
	orders.insertRow({{"order_id", "4"}, {"user_id", "1"}, {"amount", "80"}});

    std::cout << "Users Table:\n";
    users.showRows();

    std::cout << "\nOrders Table:\n";
    orders.showRows();

    std::cout << "\nINNER JOIN:\n";
    joinTables(users, "id", orders, "user_id", INNER, {});

    std::cout << "\nLEFT JOIN:\n";
    joinTables(users, "id", orders, "user_id", LEFT, {});

    std::cout << "\nRIGHT JOIN:\n";
    joinTables(users, "id", orders, "user_id", RIGHT, {});

    std::cout << "\nFULL OUTER JOIN:\n";
    joinTables(users, "id", orders, "user_id", FULL, {});

    return 0;
}
