#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    int id;
    std::string name;
    std::string category;
    std::string description;
    int startingBid;
    int bidIncrement;
    int currentBid;
    std::string highestBidder;
    std::string sellerUsername;
    int minRating;
    std::string endDateTime;

public:
    Item(int id, const std::string& name, const std::string& category, const std::string& description,
         int startingBid, int bidIncrement, const std::string& sellerUsername, int minRating);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    std::string getDescription() const;
    int getStartingBid() const;
    int getBidIncrement() const;
    int getCurrentBid() const;
    std::string getHighestBidder() const;
    std::string getSellerUsername() const;
    int getMinRating() const;
    std::string getEndDateTime() const;

    // Setters
    void setCurrentBid(int bid);
    void setHighestBidder(const std::string& bidder);
    void setEndDateTime(const std::string& endTime);
};

#endif // ITEM_H
