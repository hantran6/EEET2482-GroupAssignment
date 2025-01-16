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
    void addItem(const Item &item);

    // Items
    // Item& getItemById(int id);
    // void removeItem(int id);

    // Getter
    const std::vector<User *> &getMembers() const;

    int generateItemId();
};

#endif // AUCTIONSYSTEM_H
