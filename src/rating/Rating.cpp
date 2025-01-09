#include "Rating.h"
#include <iostream>

Rating::Rating(int id,int score, std::string role)
    : ratingID(id), score(score), role(role) {}

void Rating::getRatingDetails()
{
    std::cout << "Rating ID: " << ratingID << "\n"
            << "Score: " << score << "\n"
            << "Role: " << role << std::endl;
}
