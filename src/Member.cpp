#include "Member.h"
#include <iostream>

Member::Member(std::string username, std::string password, std::string fullName,
               std::string phoneNumber, std::string email, std::string idType,
               std::string idNumber, UserRole role = UserRole::Member)
    : User(username, password, fullName, phoneNumber, email, idType, idNumber, role),
      buyerRating(3.0), sellerRating(3.0) {
        buyerRatingList.push_back(buyerRating);
        sellerRatingList.push_back(sellerRating);
      }

/*void Member::placeBid(int itemId, int bidAmount)
{
    activeBids.push_back(itemId);
    std::cout << "Bid placed successfully!" << std::endl;
}
*/
// void Member::createListing(AuctionSystem &auctionSystem)
// {
//     std::string name, category, description, endDateTime;
//     int startingBid, bidIncrement, minRating;

//     std::cout << "Enter item name: ";
//     std::getline(std::cin, name);
//     std::cout << "Enter category: ";
//     std::getline(std::cin, category);
//     std::cout << "Enter description: ";
//     std::getline(std::cin, description);
//     std::cout << "Enter starting bid: ";
//     std::cin >> startingBid;
//     std::cout << "Enter bid increment: ";
//     std::cin >> bidIncrement;
//     std::cout << "Enter minimum buyer rating: ";
//     std::cin >> minRating;
//     std::cin.ignore(); // Clear buffer
//     std::cout << "Enter auction end date & time (YYYY-MM-DD HH:MM:SS): ";
//     std::getline(std::cin, endDateTime);

//     int id = auctionSystem.generateItemId();
//     std::string startDateTime = Utils::getCurrentDateTime();

//     Item newItem(id, name, category, description, startingBid, bidIncrement, username, minRating);
//     newItem.setStartDateTime(startDateTime);
//     newItem.setEndDateTime(endDateTime);

//     auctionSystem.addItem(newItem);
//     Utils::showSuccess("Item listing created successfully.");
// }

// void Member::editListing(AuctionSystem &auctionSystem)
// {
//     int itemId;
//     std::cout << "Enter item ID to edit: ";
//     std::cin >> itemId;
//     std::cin.ignore();

//     Item *item = auctionSystem.getItemById(itemId);
//     if (!item || item->getSellerUsername() != username)
//     {
//         Utils::showError("Item not found or you are not the seller.");
//         return;
//     }
//     if (item->getHasActiveBids())
//     {
//         Utils::showError("Cannot edit listing. Active bids exist.");
//         return;
//     }

//     std::string newName, newCategory, newDescription;
//     int newStartingBid, newBidIncrement, newMinRating;

//     std::cout << "Enter new item name: ";
//     std::getline(std::cin, newName);
//     std::cout << "Enter new category: ";
//     std::getline(std::cin, newCategory);
//     std::cout << "Enter new description: ";
//     std::getline(std::cin, newDescription);
//     std::cout << "Enter new starting bid: ";
//     std::cin >> newStartingBid;
//     std::cout << "Enter new bid increment: ";
//     std::cin >> newBidIncrement;
//     std::cout << "Enter new minimum buyer rating: ";
//     std::cin >> newMinRating;
//     std::cin.ignore();

//     item->setName(newName);
//     item->setCategory(newCategory);
//     item->setDescription(newDescription);
//     item->setStartingBid(newStartingBid);
//     item->setBidIncrement(newBidIncrement);
//     item->setMinRating(newMinRating);

//     Utils::showSuccess("Item listing updated successfully.");
// }

// void Member::removeListing(AuctionSystem &auctionSystem)
// {
//     int itemId;
//     std::cout << "Enter item ID to remove: ";
//     std::cin >> itemId;
//     std::cin.ignore();

//     Item *item = auctionSystem.getItemById(itemId);
//     if (!item || item->getSellerUsername() != username)
//     {
//         Utils::showError("Item not found or you are not the seller.");
//         return;
//     }
//     if (item->getHasActiveBids())
//     {
//         Utils::showError("Cannot remove listing. Active bids exist.");
//         return;
//     }

//     auctionSystem.removeItem(itemId);
//     Utils::showSuccess("Item listing removed successfully.");
// }

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

double Member::getBuyerRating() const {
    return buyerRating;
}

double Member::getSellerRating() const {
    return sellerRating;
}


void Member::setBuyerRating(double rating) { 
    buyerRating = rating; 
}

void Member::setSellerRating(double rating) { 
    sellerRating = rating; 
}

std::vector<double> Member::getBuyerRatingList() const {
    return buyerRatingList;
}
std::vector<double> Member::getSellerRatingList() const {
    return sellerRatingList;
}


double Member::getCreditPoints() const {   
    return creditPoints; 
}


void Member::topUpCredits(const double &amount) { 
    creditPoints += amount; 
}

void Member::placeBid(Bid bid) {
    
}
