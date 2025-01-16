#ifndef MENUS_H
#define MENUS_H

#include "AuctionSystem.h"
#include "Member.h"
#include "Admin.h"
#include "Utils.h"

// General
void displayWelcomeScreen();
void saveAndExit(AuctionSystem &auctionSystem);

// Guest
void displayGuestMenu(AuctionSystem &auctionSystem);

// Members
void displayMemberMenu(AuctionSystem &auctionSystem, Member &member);
void displayUpdateProfileMenu(Member &member);

// Admin
void displayAdminMenu(AuctionSystem &auctionSystem, Admin &admin);

#endif // MENUS_H
