#include "Member.h"
#include "AuctionSystem.h"

#include <iostream>

Member::Member(std::string username, std::string password, std::string fullName,
               std::string phoneNumber, std::string email, std::string idType,
               std::string idNumber, UserRole role = UserRole::Member)
    : User(username, password, fullName, phoneNumber, email, idType, idNumber, role),
      buyerRating(3.0), sellerRating(3.0) {}

void Member::placeBid(int itemId, int bidAmount)
{
    activeBids.push_back(itemId);
    std::cout << "Bid placed successfully!" << std::endl;
}

void Member::viewMyListings(AuctionSystem &auctionSystem)
{
    // Get the list of items from the AuctionSystem
    const std::vector<Item> &items = auctionSystem.getItems();

    if (items.empty())
    {
        std::cout << "No listings available at the moment.\n";
        return;
    }

    std::cout << "\n========== My Listings ==========\n";

    bool hasListings = false; // Track if the user has any listings

    for (const auto &item : items)
    {
        // Check if the item belongs to the current user
        if (item.getSellerUsername() == this->username) // Compare seller username with current user's username
        {
            hasListings = true;
            // Display the details of the user's item
            std::cout << "Item ID: " << item.getId() << "\n"
                      << "Name: " << item.getName() << "\n"
                      << "Category: " << item.getCategory() << "\n"
                      << "Description: " << item.getDescription() << "\n"
                      << "Starting Bid: " << item.getStartingBid() << " CP\n"
                      << "Current Bid: " << (item.getCurrentBid() > 0 ? item.getCurrentBid() : item.getStartingBid()) << " CP\n"
                      << "Bid Increment: " << item.getBidIncrement() << " CP\n"
                      << "Minimum Buyer Rating: " << item.getMinRating() << "\n"
                      << "Auction Ends At: " << item.getEndDateTime() << "\n"
                      << "-----------------------------------------\n";
        }
    }

    if (!hasListings)
    {
        std::cout << "You have no active listings.\n";
    }
}

void Member::createListing(AuctionSystem &auctionSystem)
{
    std::string name, category, description, endDateTime;
    int startingBid, bidIncrement, minRating;

    std::cin.ignore(); // Clear buffer before reading inputs

    std::cout << "Enter item name: ";
    std::getline(std::cin, name);

    std::cout << "Enter category: ";
    std::getline(std::cin, category);

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    std::cout << "Enter starting bid: ";
    std::cin >> startingBid;
    std::cin.ignore(); // Clear buffer after numeric input

    std::cout << "Enter bid increment: ";
    std::cin >> bidIncrement;
    std::cin.ignore(); // Clear buffer after numeric input

    std::cout << "Enter minimum buyer rating: ";
    std::cin >> minRating;
    std::cin.ignore(); // Clear buffer after numeric input

    std::cout << "Enter auction end date & time (YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, endDateTime);

    // Automatically set the ID and start date & time
    int id = auctionSystem.generateItemId();
    std::string startDateTime = Utils::getCurrentDateTime(); // Fetch the current date and time

    // Create the new item
    Item newItem(id, name, category, description, startingBid, bidIncrement, username, minRating);
    newItem.setStartDateTime(startDateTime); // Automatically set start date & time
    newItem.setEndDateTime(endDateTime);     // Set the user-provided end date & time

    // Add the new item to the auction system
    auctionSystem.addItem(newItem);

    Utils::showSuccess("Item listing created successfully.");
}

void Member::editListing(AuctionSystem &auctionSystem)
{
    int itemId;
    std::cout << "Enter item ID to edit: ";
    std::cin >> itemId;
    std::cin.ignore();

    Item *item = auctionSystem.getItemById(itemId);
    if (!item || item->getSellerUsername() != username)
    {
        Utils::showError("Item not found or you are not the seller.");
        return;
    }
    if (item->getHasActiveBids())
    {
        Utils::showError("Cannot edit listing. Active bids exist.");
        return;
    }

    std::string newName, newCategory, newDescription;
    int newStartingBid = -1, newBidIncrement = -1, newMinRating = -1;

    std::cout << "\nTo retain the old value, leave the field blank and press Enter.\n";
    std::cout << "To reset the value, type N/A.\n\n";

    std::cout << "Enter new item name (current: " << item->getName() << "): ";
    std::getline(std::cin, newName);
    if (newName.empty())
        newName = item->getName();

    std::cout << "Enter new category (current: " << item->getCategory() << "): ";
    std::getline(std::cin, newCategory);
    if (newCategory.empty())
        newCategory = item->getCategory();

    std::cout << "Enter new description (current: " << item->getDescription() << "): ";
    std::getline(std::cin, newDescription);
    if (newDescription.empty())
        newDescription = item->getDescription();

    std::cout << "Enter new starting bid (current: " << item->getStartingBid() << "): ";
    std::string startingBidInput;
    std::getline(std::cin, startingBidInput);
    if (startingBidInput.empty())
        newStartingBid = static_cast<int>(item->getStartingBid());
    else if (startingBidInput == "N/A")
        newStartingBid = 0; // Default value for N/A
    else
        newStartingBid = std::stoi(startingBidInput);

    std::cout << "Enter new bid increment (current: " << item->getBidIncrement() << "): ";
    std::string bidIncrementInput;
    std::getline(std::cin, bidIncrementInput);
    if (bidIncrementInput.empty())
        newBidIncrement = static_cast<int>(item->getBidIncrement());
    else if (bidIncrementInput == "N/A")
        newBidIncrement = 0; // Default value for N/A
    else
        newBidIncrement = std::stoi(bidIncrementInput);

    std::cout << "Enter new minimum buyer rating (current: " << item->getMinRating() << "): ";
    std::string minRatingInput;
    std::getline(std::cin, minRatingInput);
    if (minRatingInput.empty())
        newMinRating = static_cast<int>(item->getMinRating());
    else if (minRatingInput == "N/A")
        newMinRating = 1; // Default minimum rating for N/A
    else
        newMinRating = std::stoi(minRatingInput);

    // Update item attributes
    item->setName(newName);
    item->setCategory(newCategory);
    item->setDescription(newDescription);
    item->setStartingBid(newStartingBid);
    item->setBidIncrement(newBidIncrement);
    item->setMinRating(newMinRating);

    // Save changes to the database
    auctionSystem.saveItems("./data/items.csv");

    Utils::showSuccess("Item listing updated successfully.");
}

void Member::removeListing(AuctionSystem &auctionSystem)
{
    int itemId;
    std::cout << "Enter item ID to remove: ";
    std::cin >> itemId;
    std::cin.ignore();

    Item *item = auctionSystem.getItemById(itemId);
    if (!item || item->getSellerUsername() != username)
    {
        Utils::showError("Item not found or you are not the seller.");
        return;
    }
    if (item->getHasActiveBids())
    {
        Utils::showError("Cannot remove listing. Active bids exist.");
        return;
    }

    auctionSystem.removeItem(itemId);
    Utils::showSuccess("Item listing removed and database updated successfully.");
}

// void Member::rateTransaction(const std::string &role, double rating)
// {
//     if (role == "buyer")
//     {
//         buyerRating = (buyerRating + rating) / 2.0;
//     }
//     else if (role == "seller")
//     {
//         sellerRating = (sellerRating + rating) / 2.0;
//     }
// }

void Member::viewProfile() const
{
    std::cout << "\n========== Your Profile ==========\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Full Name: " << fullName << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Credit Points: " << creditPoints << "\n";
    std::cout << "Buyer Rating: " << buyerRating << "\n";
    std::cout << "Seller Rating: " << sellerRating << "\n";
    std::cout << "==================================\n";
}

void Member::updateFullName(const std::string &newFullName)
{
    fullName = newFullName;
    Utils::showSuccess("Full name updated successfully.");
}

void Member::updatePhoneNumber(const std::string &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
    Utils::showSuccess("Phone number updated successfully.");
}

void Member::updateEmail(const std::string &newEmail)
{
    if (Utils::isValidEmail(newEmail)) // Validation here
    {
        email = newEmail;
        Utils::showSuccess("Email updated successfully.");
    }
    else
    {
        Utils::showError("Failed to update email. Invalid format.");
    }
}

void Member::updatePassword(const std::string &newPassword)
{
    if (Utils::isValidPassword(newPassword)) // Validation here
    {
        password = newPassword;
        Utils::showSuccess("Password updated successfully.");
    }
    else
    {
        Utils::showError("Failed to update password. Invalid format.");
    }
}

double Member::getBuyerRating() const
{
    return buyerRating;
}

double Member::getSellerRating() const
{
    return sellerRating;
}
