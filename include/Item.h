#ifndef ITEM_H 
#define ITEM_H

#include <string> 
#include "./include/Rating.h"
#include "./include/Auction.h"
    
class Item {
private: 
    // Attributes 
    int itemID; 
    std::string name;
    std::string category; 
    std::string description;
    bool hasActiveBid;  
    // int startingBid; 
    // int bidIncrement;
    // int minRatingThreshold;
    // int currentHighestBid;
    // bool hasActiveBid; 
    // Member currentHighestBidder;

public: 
    // Constructor
    Item(int itemID, std::string name, std::string category, std::string description, bool hasActiveBid);
    
    // Getters and setters 
    int getItemID();
    std::string getName();
    std::string getCategory(); 
    std::string getDescription();
    // int getStartingBid();
    // int getBidIncrement();
    // int getMinRatingThreshold();
    // int getCurrentHighestBid();
    bool getHasActiveBid();

    //setters
    int Item::setItemID(int id);
    std::string Item::setName(std::string name);  
    std::string Item::setCategory(std::string category); 
    std::string Item::setDescription(std::string desc); 
    // int Item::setStartingBid(int startbid);  
    // int Item::setBidIncrement(int increment); 
    // int Item::setMinRatingThreshold(int minThreshold);  
    // int Item::setCurrentHighestBid(int highestBid);  
    void Item::setHasActiveBid(bool status);
    
    // display item details
    void displayDetails(Auction &auction);
    // check if the listing can be edited or deleted 
    bool canAdjustListing();
    // create listing
    bool createListing(string newName, string newCategory, string newDescription);
    // delete Listing
    bool deleteListing();
    // edit listing 
    bool editListing(string newName, string newCategory, string  newDescription);
};

#endif 


