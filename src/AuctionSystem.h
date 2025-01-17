#ifndef AUCTIONSYSTEM_H
#define AUCTIONSYSTEM_H

#include <vector>
#include "User.h"
#include "Item.h"
#include "Utils.h"
#include "Admin.h"
#include "Member.h"

class AuctionSystem
{
private:
    std::vector<User *> members;
    std::vector<Item> items;

public:
    AuctionSystem();

    // Data loading and saving
    void loadUsers(const std::string &filename);
    void saveUsers(const std::string &filename);
    void loadItems(const std::string &filename);
    void saveItems(const std::string &filename);

    // Core functionality
    void registerMember();
    User *loginMember();
    User *loginAdmin();

    // Items
    void addItem(const Item &item);
    void removeItem(int id);

    void viewItemDetails(int itemId);
    Item *getItemById(int id);
    std::vector<Item> searchItems(const std::string &name, const std::string &category, double minCredits, double maxCredits);

    void checkExpiredAuctions(Member &member);
    void placeBid(int itemId, double bidAmount, Member &newBidder);
    Member *getMemberByUsername(const std::string &username);

    // Getters for database access
    const std::vector<User *> &getMembers() const;
    const std::vector<Item> &getItems() const;

    int generateItemId();
    void setCurrentUser();
};

#endif // AUCTIONSYSTEM_H
