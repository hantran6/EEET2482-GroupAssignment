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

                // Conclude auctions and prompt for ratings
                autoConcludeAuctions(username);

                Member *member = dynamic_cast<Member *>(user);
                if (member)
                {
                    handleRatings(*member); // Prompt for ratings
                }

                return user; // Return the User* directly
            }
        }
    }
    Utils::showError("Invalid member credentials.");
    return nullptr;
}

void AuctionSystem::autoConcludeAuctions(const std::string &loggedInUsername)
{
    std::string currentDateTime = Utils::getCurrentDateTime();

    for (auto &item : items)
    {
        if (item.getIsActive() && Utils::isDateTimeInPast(item.getEndDateTime()))
        {
            // Conclude only if the logged-in user is involved
            if (item.getHighestBidder() == loggedInUsername || item.getSellerUsername() == loggedInUsername)
            {
                concludeAuction(item.getId());
            }
        }
    }
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

void AuctionSystem::viewLimitedDetails() const
{
    if (items.empty())
    {
        std::cout << "No items available.\n";
        return;
    }

    std::cout << "\n========== Limited Item Details ==========\n";
    for (const auto &item : items)
    {
        std::cout << "Item Name: " << item.getName() << "\n"
                  << "Item Category: " << item.getCategory() << "\n"
                  << "Item Description: " << item.getDescription() << "\n";
        std::cout << "---------------------------------------\n";
    }
    std::cout << "==========================================\n";
}

// Bids ====================================================================================================================
Member *AuctionSystem::getMemberByUsername(const std::string &username)
{
    for (auto *user : members) // Assuming members is a container of User*
    {
        // Use dynamic_cast to check if the User* is actually a Member*
        Member *member = dynamic_cast<Member *>(user);
        if (member && member->getUsername() == username) // Ensure the member is valid and matches the username
        {
            return member; // Return the pointer to the Member
        }
    }
    return nullptr; // Return nullptr if no matching member is found
}

void AuctionSystem::placeBid(int itemId, double bidAmount, Member &newBidder)
{
    Item *item = getItemById(itemId);
    if (item == nullptr)
    {
        Utils::showError("Item not found.");
        return;
    }

    // Check if the new bidder is the seller
    if (item->getSellerUsername() == newBidder.getUsername())
    {
        Utils::showError("You cannot bid on your own items.");
        return;
    }

    // Check if the new bidder is the highest bidder
    if (item->getHighestBidder() == newBidder.getUsername())
    {
        Utils::showError("You are currently the highest bidder! No need to bid again.");
        return;
    }

    // Check if the bid amount is valid (greater than the current bid + increment)
    if (bidAmount < (item->getCurrentBid() + item->getBidIncrement()))
    {
        Utils::showError("Bid amount is too low. Must be greater than the current bid + increment.");
        return;
    }

    // Check if the new bidder has sufficient credit points for this bid
    double totalActiveBids = 0.0;
    for (int activeBidId : newBidder.getActiveBids()) // Use the accessor method
    {
        Item *activeItem = getItemById(activeBidId);
        if (activeItem)
        {
            totalActiveBids += activeItem->getCurrentBid();
        }
    }

    if (newBidder.getCreditPoints() < (totalActiveBids + bidAmount))
    {
        Utils::showError("Insufficient credit points to place this bid.");
        return;
    }

    // Handle outbidding the current highest bidder
    std::string currentHighestBidder = item->getHighestBidder();
    if (!currentHighestBidder.empty() && currentHighestBidder != newBidder.getUsername())
    {
        Member *oldBidder = getMemberByUsername(currentHighestBidder);
        if (oldBidder)
        {
            oldBidder->removeActiveBid(itemId); // Use removeActiveBid method
        }
    }

    // Update the item's current bid and highest bidder
    item->setCurrentBid(bidAmount);
    item->setHighestBidder(newBidder.getUsername());

    // Add the item to the new bidder's activeBids if not already there
    if (!newBidder.hasActiveBid(itemId)) // Use hasActiveBid method
    {
        newBidder.addActiveBid(itemId); // Use addActiveBid method
    }

    Utils::showSuccess("Bid placed successfully!");
    saveItems("./data/items.csv"); // Save updated item data
}

void AuctionSystem::concludeAuction(int itemId)
{
    Item *item = getItemById(itemId);
    if (!item)
        return; // Item not found

    if (!item->getIsActive())
        return; // Already concluded

    item->setIsActive(false); // Mark auction as concluded

    if (item->getHighestBidder().empty())
    {
        Utils::showInfo("No bids placed. Auction concluded with no winner.");
        saveItems("./data/items.csv");
        return; // No further action needed
    }

    // Handle auctions with bids
    std::string highestBidderUsername = item->getHighestBidder();
    Member *seller = getMemberByUsername(item->getSellerUsername());
    Member *highestBidder = getMemberByUsername(highestBidderUsername);

    if (seller && highestBidder)
    {
        double winningBid = item->getCurrentBid();

        // Deduct from the highest bidder
        highestBidder->setCreditPoints(highestBidder->getCreditPoints() - winningBid);

        // Add to the seller
        seller->setCreditPoints(seller->getCreditPoints() + winningBid);

        Utils::showSuccess("Auction concluded: Credits transferred.");
    }

    saveItems("./data/items.csv");
}

// Rating =================================================================================================================
void AuctionSystem::handleRatings(Member &member)
{
    for (auto &item : items)
    {
        if (!item.getIsActive())
        {
            // Skip auctions without bids
            if (item.getHighestBidder().empty())
                continue;

            // If the user is the highest bidder, prompt to rate the seller
            if (item.getHighestBidder() == member.getUsername())
            {
                std::cout << "You won the auction for item: " << item.getName() << "!\n";
                Member *seller = getMemberByUsername(item.getSellerUsername());
                if (seller)
                {
                    int rating;
                    do
                    {
                        std::cout << "Please rate the seller " << seller->getFullName() << " (1-5): ";
                        std::cin >> rating;
                    } while (rating < 1 || rating > 5);
                    seller->addSellerRating(rating);
                }
            }

            // If the user is the seller, prompt to rate the highest bidder
            if (item.getSellerUsername() == member.getUsername())
            {
                std::cout << "Your item \"" << item.getName() << "\" was sold!\n";
                Member *buyer = getMemberByUsername(item.getHighestBidder());
                if (buyer)
                {
                    int rating;
                    do
                    {
                        std::cout << "Please rate the buyer (1-5): ";
                        std::cin >> rating;
                    } while (rating < 1 || rating > 5);
                    buyer->addBuyerRating(rating);
                }
            }
        }
    }

    saveUsers("./data/users.csv");
}

// Database ================================================================================================================
std::vector<int> deserializeRatings(const std::string &ratingsString)
{
    std::vector<int> ratings;

    // Remove enclosing quotes if present
    std::string cleanString = ratingsString;
    if (cleanString.front() == '"' && cleanString.back() == '"')
    {
        cleanString = cleanString.substr(1, cleanString.size() - 2);
    }

    // Ensure the string is valid (starts with "[" and ends with "]")
    if (cleanString.size() < 2 || cleanString.front() != '[' || cleanString.back() != ']')
    {
        return ratings; // Return an empty vector if invalid
    }

    // Extract the content inside the brackets
    std::string content = cleanString.substr(1, cleanString.size() - 2);
    std::istringstream ss(content);
    std::string token;

    // Split the content by commas and convert to integers
    while (std::getline(ss, token, ','))
    {
        try
        {
            ratings.push_back(std::stoi(token)); // Convert to int and add to vector
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error parsing rating: " << token << "\n";
        }
    }

    return ratings;
}

void AuctionSystem::loadUsers(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Error: Could not open file: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(inFile, line); // Skip header
    while (std::getline(inFile, line))
    {
        std::istringstream ss(line);
        std::vector<std::string> fields;
        std::string word;
        bool insideQuotes = false;
        std::string field;

        // Custom logic to handle quoted fields
        for (char c : line)
        {
            if (c == '"')
            {
                insideQuotes = !insideQuotes;
            }
            else if (c == ',' && !insideQuotes)
            {
                fields.push_back(field);
                field.clear();
            }
            else
            {
                field += c;
            }
        }
        fields.push_back(field);

        if (fields.size() == 13)
        { // Ensure all fields are present
            UserRole role = (fields[12] == "Admin") ? UserRole::Admin : UserRole::Member;

            if (role == UserRole::Member)
            {
                Member *member = new Member(fields[0], fields[1], fields[2], fields[3], fields[4],
                                            fields[5], fields[6], role);
                member->setCreditPoints(std::stod(fields[7]));
                member->setBuyerRating(std::stod(fields[8]));
                member->setSellerRating(std::stod(fields[9]));
                member->setSellerRatings(deserializeRatings(fields[10]));
                member->setBuyerRatings(deserializeRatings(fields[11]));
                members.push_back(member); // Store Member object
            }
            else if (role == UserRole::Admin)
            {
                Admin *admin = new Admin(fields[0], fields[1], role);
                members.push_back(admin); // Store Admin object
            }
        }
        else
        {
            std::cerr << "Error: Invalid line format in users.csv: " << line << "\n";
        }
    }

    inFile.close();
}

std::string serializeRatings(const std::vector<int> &ratings)
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < ratings.size(); ++i)
    {
        oss << ratings[i];
        if (i < ratings.size() - 1)
        {
            oss << ","; // Add a comma between ratings
        }
    }
    oss << "]";
    return oss.str();
}

void AuctionSystem::saveUsers(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error: Could not open file for saving users.\n";
        return;
    }

    outFile << "username,password,full_name,phone,email,id_type,id_number,credit_points,buyer_rating,seller_rating,seller_ratings,buyer_ratings,role\n";

    for (const auto &user : members)
    {
        if (user->getRole() == UserRole::Member)
        {
            Member *member = dynamic_cast<Member *>(user);
            outFile << member->getUsername() << ","
                    << member->getPassword() << ","
                    << member->getFullName() << ","
                    << member->getPhoneNumber() << ","
                    << member->getEmail() << ","
                    << member->getIdType() << ","
                    << member->getIdNumber() << ","
                    << member->getCreditPoints() << ","
                    << member->getBuyerRating() << ","
                    << member->getSellerRating() << ","
                    << "\"" << serializeRatings(member->getSellerRatings()) << "\","
                    << "\"" << serializeRatings(member->getBuyerRatings()) << "\","
                    << "Member\n";
        }
        else if (user->getRole() == UserRole::Admin)
        {
            outFile << user->getUsername() << ","
                    << user->getPassword() << ","
                    << user->getFullName() << ","
                    << user->getPhoneNumber() << ","
                    << user->getEmail() << ","
                    << user->getIdType() << ","
                    << user->getIdNumber() << ","
                    << "0.0,0.0,0.0,\"[]\",\"[]\",Admin\n";
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

        if (fields.size() == 12)
        { // Ensure all fields are present
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
            bool isActive = fields[11] == "1";

            // Create and populate the Item object
            Item item(id, name, category, description, startingBid, bidIncrement, seller, minRating);
            item.setCurrentBid(currentBid);
            item.setHighestBidder(highestBidder);
            item.setEndDateTime(endDateTime);
            item.setIsActive(isActive);

            // Add the item to the list
            items.push_back(item);
        }
    }
    inFile.close();
}

void AuctionSystem::saveItems(const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error: Could not open file for saving items.\n";
        return;
    }

    outFile << "id,name,category,description,starting_bid,bid_increment,current_bid,highest_bidder,seller,min_rating,end_date_time,is_active\n";

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
                << item.getEndDateTime() << ","
                << (item.getIsActive() ? "1" : "0") << "\n";
    }

    outFile.close();
}
