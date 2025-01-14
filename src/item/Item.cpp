
#include "./include/Item.h"
#include "./include/Auction.h"
#include <iostream>


using namespace std;

    // Constructor
Item::Item(int itemID, string name, string category, string description, bool hasActiveBid)
    : itemID(itemID), name(name), category(category), description(description), hasActiveBid(hasActiveBid) {}

    // Getters
    int Item::getItemID() {return itemID;}
    string Item::getName()  {return name;}
    string Item::getCategory()  {return category;}
    string Item::getDescription()  {return description;}
    // int Item::getStartingBid()  {return startingBid;}
    // int Item::getBidIncrement()  {return bidIncrement;}
    // int Item::getMinRatingThreshold()  {return minRatingThreshold;}
    // int Item::getCurrentHighestBid()  {return currentHighestBid;}
    bool Item::getHasActiveBid() {return hasActiveBid;}

    // Setters
    int Item::setItemID(int id) {itemID = id;}
    std::string Item::setName(string name) {name = name;}
    std::string Item::setCategory(string category) {category = category;}
    std::string Item::setDescription(string desc) {description = desc;}
    // int Item::setStartingBid(int startbid) {startingBid = startbid;}
    // int Item::setBidIncrement(int increment) {bidIncrement = increment;}
    // int Item::setMinRatingThreshold(int minThreshold) {minRatingThreshold = minThreshold;}
    // int Item::setCurrentHighestBid(int highestBid) {currentHighestBid = highestBid;}
    void Item::setHasActiveBid(bool status) {hasActiveBid = status;} 

    // display items
    void Item::displayDetails(Auction &auction) {
    cout << "Item Name: " << name << "\nCategory: " << category
                 << "\nStarting Bid: " << auction.getCurrentHighestBid() << "\nCurrent Bidder: "
                 << auction.getHighestBidder().getFullName() << "\nEnd date and time: " // << add in later 
                << endl;
    }

     // check if the listing can be edited or deleted 
    bool Item::canAdjustListing() { 
        // return true if there are no active bids
        return !hasActiveBid; 
    }
    
    // create listing
    bool Item::createListing(string newName, string newCategory, string newDescription)  {
        // check if there are active bids 
        if (canAdjustListing()) {
            name = newName; 
            category = newCategory; 
            description = newDescription;

        // set hasActiveBid to false since no active bids yet when create a new listing
            hasActiveBid = false; 

            cout << "Item listing successfully created\n";
            cout << "Item name: " << name << endl; 
            cout << "Category: " << category << endl; 
            return true; 
        } else { 
            cout << "Active bids are placed on the item, hence can't create listing\n";
            return false; 
        }
    }

    // delete Listing
    bool Item::deleteListing() {
        if (Item::canAdjustListing()) {
            cout << "Listing for item " << name << "successfully removed\n";
            return true; 
        } else {
            cout << "Active bids are placed on this item, hence cannot remove the listing\n";
            return false; 
        }
    }
    // edit listing 
    bool Item::editListing(string newName, string newCategory, string newDescription)/*add in the other stuff*/ {
        if (canAdjustListing()) {
            name = newName; 
            category = newCategory; 
            description = newDescription; 
            // auction.getCurrentHighestBid() = newHighestBid;
            // auction.getCurrentHighestBidder() = newHighestBidder; 
            // add in the other stuff 
            return true; 
        } else {
            cout << "Active bids are placed on this item, hence cannot edit the listing\n";
            return false; 
        }
    }