#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
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
    bool hasActiveBids;
    std::string startDateTime;

public:
    Item(int id, const std::string &name, const std::string &category, const std::string &description,
         int startingBid, int bidIncrement, const std::string &sellerUsername, int minRating);

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
    bool getHasActiveBids() const;
    std::string getStartDateTime() const;

    // Setters
    void setName(const std::string &newName);
    void setCategory(const std::string &newCategory);
    void setDescription(const std::string &newDescription);
    void setStartingBid(const int &newStartingBid);
    void setBidIncrement(const int &newBidIncrement);
    void setMinRating(const int &newMinRating);

    void setCurrentBid(int bid);
    void setHighestBidder(const std::string &bidder);
    void setEndDateTime(const std::string &endTime);
    void setHasActiveBids(bool status);
    void setStartDateTime(const std::string &time);
};

#endif // ITEM_H
