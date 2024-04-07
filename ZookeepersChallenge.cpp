#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

// Data structure to store animal details
struct Animal {
    string name;
    int age;
    char sex;
    string species;
    string color;
    int weight;
    string birthSeason;
    string origin;
    string arrivalDate;
};

// Function to extract essential details from arrivingAnimals.txt
vector<Animal> extractAnimalDetails(const string& filename) {
    vector<Animal> animals;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Animal animal;
        iss >> animal.age >> animal.sex >> animal.species >> animal.color >> animal.weight;
        iss.ignore(1); // Ignore comma
        getline(iss, animal.birthSeason, ',');
        getline(iss, animal.origin, ',');
        getline(iss, animal.arrivalDate);

        animals.push_back(animal);
    }

    file.close();
    return animals;
}

// Function to generate birthday based on birth season
string genBirthDay(const string& birthSeason) {
    if (birthSeason == "spring")
        return "03-15"; // Assuming a fixed birth date for animals born in spring
    else if (birthSeason == "summer")
        return "06-15"; // Assuming a fixed birth date for animals born in summer
    else if (birthSeason == "fall")
        return "09-15"; // Assuming a fixed birth date for animals born in fall
    else if (birthSeason == "winter")
        return "12-15"; // Assuming a fixed birth date for animals born in winter
    else
        return "00-00"; // Default birth date if birth season is not provided
}

// Function to assign unique IDs to animals
string genUniqueID(const string& species, int id) {
    ostringstream oss;
    oss << species.substr(0, 2) << setw(2) << setfill('0') << id;
    return oss.str();
}

// Function to write output to zooPopulation.txt
void writeZooPopulation(const vector<Animal>& animals) {
    ofstream outfile("zooPopulation.txt");
    if (!outfile.is_open()) {
        cerr << "Error opening output file." << endl;
        exit(1);
    }

    map<string, vector<Animal>> habitats; // Map to store animals grouped by species

    // Group animals by species
    for (const Animal& animal : animals) {
        habitats[animal.species].push_back(animal);
    }

    // Write population details to output file
    for (const auto& habitat : habitats) {
        outfile << habitat.first << " Habitat:" << endl;
        int id = 1;
        for (const Animal& animal : habitat.second) {
            outfile << genUniqueID(animal.species, id++) << "; " << animal.name << "; birth date "
                    << genBirthDay(animal.birthSeason) << "; " << animal.color << " color; "
                    << animal.sex << "; " << animal.weight << " pounds; from " << animal.origin
                    << "; arrived " << animal.arrivalDate << endl;
        }
        outfile << endl;
    }

    outfile.close();
}

int main() {
    vector<Animal> animals = extractAnimalDetails("arrivingAnimals.txt");
    // Assuming you also need to read animal names from a file
    // vector<string> animalNames = readAnimalNames("animalNames.txt");

    // Assign names to animals (assuming you have a function for this)
    // assignNames(animals, animalNames);

    writeZooPopulation(animals);

    return 0;
}
