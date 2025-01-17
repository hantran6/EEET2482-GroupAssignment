#include "AuctionSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

AuctionSystem::AuctionSystem() {}

// Users ================================================================================================================
// Getter for members
const std::vector<User *> &AuctionSystem::getMembers() const
{
    return members;
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
    newMember->setCreditPoints(0.0); // Initialize with zero credits

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

// Items ================================================================================================================
// Getter for items
const std::vector<Item> &AuctionSystem::getItems() const
{
    return items;
}

void AuctionSystem::addItem(const Item &item)
{
    items.push_back(item);
    saveItems("./data/items.csv");
}

void AuctionSystem::removeItem(int itemId)
{
    auto it = std::remove_if(items.begin(), items.end(),
                             [itemId](const Item &item)
                             { return item.getId() == itemId; });

    if (it != items.end())
    {
        items.erase(it, items.end());
        saveItems("./data/items.csv");
    }
    else
    {
        Utils::showError("Item not found.");
    }
}

Item *AuctionSystem::getItemById(int id)
{
    for (auto &item : items)
    { // Iterate through the items vector
        if (item.getId() == id)
        {
            return &item; // Return a pointer to the matching item
        }
    }
    return nullptr; // Return nullptr if no item is found
}

std::vector<Item> AuctionSystem::searchItems(const std::string &name, const std::string &category, double minCredits, double maxCredits)
{
    std::vector<Item> results;
    for (const auto &item : items)
    {
        // Check if the item matches the search criteria
        bool matchesName = name.empty() || item.getName().find(name) != std::string::npos;
        bool matchesCategory = category.empty() || item.getCategory() == category;
        bool matchesCreditRange = item.getStartingBid() >= minCredits && item.getStartingBid() <= maxCredits;

        if (matchesName && matchesCategory && matchesCreditRange)
        {
            results.push_back(item);
        }
    }
    return results;
}

void AuctionSystem::viewItemDetails(int itemId)
{
    Item *item = getItemById(itemId);
    if (!item)
    {
        Utils::showError("Item not found.");
        return;
    }

    std::cout << "\n========== Items Details ==========\n";
    std::cout << "Item ID: " << item->getId() << "\n"
              << "Name: " << item->getName() << "\n"
              << "Category: " << item->getCategory() << "\n"
              << "Description: " << item->getDescription() << "\n"
              << "Starting Bid: " << item->getStartingBid() << " CP\n"
              << "Current Bid: " << item->getCurrentBid() << " CP\n"
              << "Highest Bidder: " << item->getHighestBidder() << "\n"
              << "Auction Ends At: " << item->getEndDateTime() << "\n"
              << "====================================\n";
}

int AuctionSystem::generateItemId()
{
    int maxId = 0;

    // Iterate through items to find the maximum ID
    for (const auto &item : items)
    {
        if (item.getId() > maxId)
        {
            maxId = item.getId();
        }
    }

    return maxId + 1; // Return the next available ID
}

// Database ================================================================================================================
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
                member->setCreditPoints(std::stod(fields[7]));
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
        if (user->getRole() == UserRole::Member)
        {
            Member *member = dynamic_cast<Member *>(user);
            outFile << member->getUsername() << "," << member->getPassword() << "," << member->getFullName() << ","
                    << member->getPhoneNumber() << "," << member->getEmail() << "," << member->getIdType() << ","
                    << member->getIdNumber() << "," << member->getCreditPoints() << "," << member->getBuyerRating() << ","
                    << member->getSellerRating() << ",Member\n";
        }
        else if (user->getRole() == UserRole::Admin)
        {
            outFile << user->getUsername() << "," << user->getPassword() << "," << user->getFullName() << ","
                    << user->getPhoneNumber() << "," << user->getEmail() << "," << user->getIdType() << ","
                    << user->getIdNumber() << ",0.0,0.0,0.0,Admin\n";
        }
    }

    outFile.close();
}

void AuctionSystem::loadItems(const std::string &filename)
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
            int id = std::stoi(fields[0]);
            std::string name = fields[1];
            std::string category = fields[2];
            std::string description = fields[3];
            double startingBid = std::stod(fields[4]);
            double bidIncrement = std::stod(fields[5]);
            double currentBid = std::stod(fields[6]);
            std::string highestBidder = fields[7];
            std::string seller = fields[8];
            double minRating = std::stod(fields[9]);
            std::string endDateTime = fields[10];

            // Create and populate the Item object
            Item item(id, name, category, description, startingBid, bidIncrement, seller, minRating);
            item.setCurrentBid(currentBid);
            item.setHighestBidder(highestBidder);
            item.setEndDateTime(endDateTime);

            // Add the item to the list
            items.push_back(item);

            // Debugging message
            std::cout << "Loaded item: " << name << " (ID: " << id << ")\n";
        }
    }
    inFile.close();
}

void AuctionSystem::saveItems(const std::string &filename)
{
    std::ofstream outFile(filename); // Open file in write mode
    if (!outFile)
    {
        std::cerr << "Error: Could not open file for saving items.\n";
        return;
    }

    // Write header
    outFile << "id,name,category,description,starting_bid,bid_increment,current_bid,highest_bidder,seller,min_rating,end_date_time\n";

    // Write all items in memory to the file
    for (const auto &item : items)
    {
        outFile << item.getId() << ","
                << item.getName() << ","
                << item.getCategory() << ","
                << item.getDescription() << ","
                << item.getStartingBid() << ","
                << item.getBidIncrement() << ","
                << item.getCurrentBid() << ","
                << item.getHighestBidder() << ","
                << item.getSellerUsername() << ","
                << item.getMinRating() << ","
                << item.getEndDateTime() << "\n";
    }

    outFile.close();
}