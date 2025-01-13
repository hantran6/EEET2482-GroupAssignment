#ifndef ITEM_H 
#define ITEM_H

#include <string> 
#include "./include/Rating.h"
    
class Item {
private: 
    // Attributes 
    int itemID; 
    Member seller;
    std::string name;
    std::string category; 
    std::string description; 
    int startingBid; 
    int bidIncrement;
    int minRatingThreshold;
    int currentHighestBid;
    // Member currentHighestBidder;

public: 
    // Constructor
    Item(int id, std::string name, std::string category, std::string description, int startingBid, int bidIncrement, int minRatingThreshold, int currentHighestBid);
    
    // Getters and setters 
    int getItemID();
    std::string getName();
    std::string getCategory(); 
    std::string getDescription();
    int getStartingBid();
    int getBidIncrement();
    int getMinRatingThreshold();
    int getCurrentHighestBid();
    Member getSeller();

    //setters
    int Item::setItemID(int id);
    std::string Item::setName(std::string name);  
    std::string Item::setCategory(std::string category); 
    std::string Item::setDescription(std::string desc); 
    int Item::setStartingBid(int startbid);  
    int Item::setBidIncrement(int increment); 
    int Item::setMinRatingThreshold(int minThreshold);  
    int Item::setCurrentHighestBid(int highestBid);  

    //display
    void displayDetails();
    //placeBid
    void placeBid();
    //displayItems
    void displayItems();
    //createListing
    void createListing(); 

    // update new details 
    // void updateListing(map<string, string>& details);

    //deleteListing
    bool deleteListing();
};

#endif 


