#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For atoi
#include <vector>
#include "generator_ETHZ.cu" 
#include "generator_ETHZ.cuh" 
 
// Function to write data to CSV
void writeToCSV(const std::string &csv_filename, int *data, uint64_t num_entries) {
    std::ofstream csv_file(csv_filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open " << csv_filename << " for writing\n";
        return;
    }
    for (uint64_t i = 0; i < num_entries; i++) {
        csv_file << data[i] << "\n";
    }
    csv_file.close();
}
 
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <num_tuples> <max_id>\n";
        return 1;
    }
 
    // Parse command line arguments
    uint64_t num_tuples = std::atoi(argv[1]);
    int64_t max_id = std::atoi(argv[2]);
 
    // Allocate memory for the primary key relation
    std::vector<int> relation(num_tuples);
 
    // Create a unique primary key relation
    create_relation_unique("primary_key.dat", relation.data(), num_tuples, max_id);
 
    // Write primary key relation to a CSV file
    writeToCSV("primary_key_relation.csv", relation.data(), num_tuples);
    std::cout << "Primary key relation saved to primary_key_relation.csv\n";
 
    // Allocate memory for the foreign key relation
    // std::vector<int> fk_relation(num_tuples);
 
    // Create a foreign key relation based on the primary key relation
    // create_relation_fk_from_pk("foreign_key.dat", fk_relation.data(), num_tuples, relation.data(), num_tuples);
 
    // // Write foreign key relation to a CSV file
    // writeToCSV("foreign_key_relation.csv", fk_relation.data(), num_tuples);
    // std::cout << "Foreign key relation saved to foreign_key_relation.csv\n";
 
    // Normal shuffle on primary key relation
    // knuth_shuffle(relation.data(), num_tuples);
    // writeToCSV("primary_key_knuth_shuffle.csv", relation.data(), num_tuples);
    // std::cout << "Primary key relation (normal shuffle) saved to primary_key_knuth_shuffle.csv\n";
 
    // // Create foreign key relation based on the shuffled primary key
    // create_relation_fk_from_pk("foreign_key_knuth_shuffle.dat", fk_relation.data(), num_tuples, relation.data(), num_tuples);
    // writeToCSV("foreign_key_knuth_shuffle.csv", fk_relation.data(), num_tuples);
    // std::cout << "Foreign key relation (normal shuffle) saved to foreign_key_knuth_shuffle.csv\n";
 
    // 48-bit shuffle on primary key relation
    // unsigned short state[3] = {0, 0, 0}; // Initialize state for nrand48
    // knuth_shuffle48(relation.data(), num_tuples, state);
    // writeToCSV("primary_key_knuth_shuffle48.csv", relation.data(), num_tuples);
    // std::cout << "Primary key relation (48-bit shuffle) saved to primary_key_knuth_shuffle48.csv\n";
 
    // Create foreign key relation based on the 48-bit shuffled primary key
    // create_relation_fk_from_pk("foreign_key_knuth_shuffle48.dat", fk_relation.data(), num_tuples, relation.data(), num_tuples);
    // writeToCSV("foreign_key_knuth_shuffle48.csv", fk_relation.data(), num_tuples);
    // std::cout << "Foreign key relation (48-bit shuffle) saved to foreign_key_knuth_shuffle48.csv\n";
 
    return 0;
}
