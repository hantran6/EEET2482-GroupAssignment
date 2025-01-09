
#include "./include/Item.hpp"
#include <iostream>

using namespace std;

    // Constructor
Item::Item(int id, std::string name, std::string category, std::string description,
    int startingBid, int bidIncrement, int minRatingThreshold, int currentHighestBid)
    :itemID(id), name(name), category(category), description(description),
    startingBid(startingBid), bidIncrement(bidIncrement), minRatingThreshold(minRatingThreshold), currentHighestBid(currentHighestBid) {}

    // Getters
    int Item::getItemID() {return itemID;}
    string Item::getName()  {return name;}
    string Item::getCategory()  {return category;}
    string Item::getDescription()  {return description;}
    int Item::getStartingBid()  {return startingBid;}
    int Item::getBidIncrement()  {return bidIncrement;}
    int Item::getMinRatingThreshold()  {return minRatingThreshold;}
    int Item::getCurrentHighestBid()  {return currentHighestBid;}


    // Setters
    int Item::setItemID(int id) {itemID = id;}
    std::string Item::setName(string name) {name = name;}
    std::string Item::setCategory(string category) {category = category;}
    std::string Item::setDescription(string desc) {description = desc;}
    int Item::setStartingBid(int startbid) {startingBid = startbid;}
    int Item::setBidIncrement(int increment) {bidIncrement = increment;}
    int Item::setMinRatingThreshold(int minThreshold) {minRatingThreshold = minThreshold;}
    int Item::setCurrentHighestBid(int highestBid) {currentHighestBid = highestBid;}

    //displayItems
    void Item::displayDetails() {
    cout << "Item Name: " << name << "\nCategory: " << category
                << "\nDescription: " << description << "\nStarting Bid: " << startingBid
                << "\nBid Increment: " << bidIncrement << "\nMin Rating Threshold: " << minRatingThreshold 
                << "\nCurrent Highest Bid: " << currentHighestBid
                << endl;
    }
    
    //placeBid
    void Item::placeBid()
    {
        // if(Member.getPoints() > cred) {bid placed}
    }
    //createListing ? constructor ?
    void Item::createListing() {}