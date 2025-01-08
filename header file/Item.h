#ifndef ITEM_H 
#define ITEM_H

#include <string> 
#include "Rating.h"
    
class Item {

private: 
    // Attributes 
    int itemID; 
    double startingBid; 
    double currentBid; 
    int bidIncrement; 

    std::string name; 
    std::string category; 
    std::string description; 

public: 
    
    // Constructor
    Item(std::string name, std::string category, std::string description, double startingBid, double currentBid, double bidIncrement)
        : name(name), category(category), description(description),
        startingBid(startingBid), currentBid(currentBid), bidIncrement(bidIncrement) {}
  
    // Getters and setters 
    int getItemID();
    int getBidIncrement();
    double getStartingBid();
    double getCurrentBid();
    
    std::string getName();
    std::string getCategory(); 
    std::string getDescription();

    void setCurrentBid(double bid);
    void setCurrentBidder(std::string &bidder);
    
    void placeBid(int amount, std::string &bidder);
    void displayItems ();
    void createListing(); 
    
    // update new details 
    // void updateListing(std::map<std::string, std::string>& details);

    // check if meet the requirement to bid 
    bool isBidAllowed(int buyerRating, double buyerCP);
    
    // Delete a listing if no active bid available 
    bool deleteListing();
};

#endif 


