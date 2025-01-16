#include "AuctionSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>

AuctionSystem::AuctionSystem() {}

// Users ================================================================================================================
void AuctionSystem::loadUsers(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Error: Could not open file: " << filename << "\n";
        return;
    }

    std::string line, word;
    std::getline(inFile, line); // Skip header
    while (std::getline(inFile, line))
    {
        std::istringstream ss(line);
        std::vector<std::string> fields;
        while (std::getline(ss, word, ','))
        {
            fields.push_back(word);
        }

        if (fields.size() == 11) // Ensure all fields are present
        {
            UserRole role = (fields[10] == "Admin") ? UserRole::Admin : UserRole::Member;

            if (role == UserRole::Member)
            {
                Member *member = new Member(fields[0], fields[1], fields[2], fields[3], fields[4],
                                            fields[5], fields[6], role);
                member->topUpCredits(std::stoi(fields[7]));
                member->setBuyerRating(std::stod(fields[8]));
                member->setSellerRating(std::stod(fields[9]));
                members.push_back(member); // Store Member object
            }
            else if (role == UserRole::Admin)
            {
                Admin *admin = new Admin(fields[0], fields[1], role);
                members.push_back(admin); // Store Admin object
            }
        }
    }

    inFile.close();
}

void AuctionSystem::saveUsers(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error: Could not open file for saving users.\n";
        return;
    }

    outFile << "username,password,full_name,phone,email,id_type,id_number,credit_points,buyer_rating,seller_rating,role\n";

    for (const auto &user : members)
    {
        outFile << user->getUsername() << "," << user->getPassword() << "," << user->getFullName() << ","
                << user->getPhoneNumber() << "," << user->getEmail() << "," << user->getIdType() << ","
                << user->getIdNumber() << "," << user->getCreditPoints() << "," << user->getBuyerRating() << ","
                << user->getSellerRating() << "," << (user->getRole() == UserRole::Admin ? "Admin" : "Member") << "\n";
    }

    outFile.close();
}

void AuctionSystem::registerMember()
{
    std::string username, password, fullName, phone, email, idType, idNumber;

    // Ensure the username meets the standard
    do
    {
        std::cout << "Enter username: ";
        std::cin.ignore();
        std::getline(std::cin, username);
    } while (!Utils::isValidUsername(username));

    // Check if the username already exists
    for (const auto &existingMember : members)
    {
        if (existingMember->getUsername() == username)
        {
            Utils::showError("Username already exists. Please try another.");
            return;
        }
    }

    // Ensure the password meets the standard
    do
    {
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
    } while (!Utils::isValidPassword(password));

    std::cout << "Enter full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone);

    do
    {
        std::cout << "Enter email: ";
        std::getline(std::cin, email);
    } while (!Utils::isValidEmail(email));

    // Check if the email already exists
    for (const auto &existingMember : members)
    {
        if (existingMember->getEmail() == email)
        {
            Utils::showError("Email already exists. Please try another.");
            return;
        }
    }

    std::cout << "Enter ID type (e.g., Citizen ID, Passport): ";
    std::getline(std::cin, idType);

    std::cout << "Enter ID number: ";
    std::getline(std::cin, idNumber);

    // Create a new member object
    Member *newMember = new Member(username, password, fullName, phone, email, idType, idNumber, UserRole::Member);
    newMember->setBuyerRating(3.0);
    newMember->setSellerRating(3.0);

    members.push_back(newMember); // Add to members list
    Utils::showSuccess("Registration successful! Please log in as a member to access more features.");

    saveUsers("./data/users.csv"); // Save the updated list, real time updates
}

User *AuctionSystem::loginMember()
{
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (auto &user : members) // `user` is a pointer to User
    {
        if (user->getUsername() == username && user->getPassword() == password)
        {
            if (user->getRole() == UserRole::Member)
            {
                Utils::showSuccess("Login successful! Welcome, " + username);
                return user; // Return the User* directly
            }
        }
    }
    Utils::showError("Invalid member credentials.");
    return nullptr;
}

User *AuctionSystem::loginAdmin()
{
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    for (auto &user : members) // `user` is a pointer to User
    {
        if (user->getUsername() == username && user->getPassword() == password)
        {
            if (user->getRole() == UserRole::Admin)
            {
                Utils::showSuccess("Login successful! Welcome, Administrator");
                return user; // Return the User* directly
            }
        }
    }
    Utils::showError("Invalid admin credentials.");
    return nullptr;
}

const std::vector<User *> &AuctionSystem::getMembers() const
{
    return members;
}
// Items ================================================================================================================
void AuctionSystem::loadItems(const std::string &filename)
{
    // Implementation is similar to loadUsers
}

void AuctionSystem::saveItems(const std::string &filename)
{
    // Implementation is similar to saveUsers
}

void AuctionSystem::addItem(const Item &item)
{
    items.push_back(item);
}

int AuctionSystem::generateItemId()
{
    static int nextItemId = 1; // Static variable to persist the value across calls
    return nextItemId++;
}

