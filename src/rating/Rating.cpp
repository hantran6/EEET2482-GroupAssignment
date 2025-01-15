#include "Rating.h"
#include <iostream>
#include <vector> 

using namespace std; 

// Constructor (assume the default rating for buyers and sellers is 3.0)
Rating::Rating(vector <int> sellerRatings = {}, vector <int> buyerRatings = {}, double sellerAverageRating = 3.0, double buyerAverageRating = 3.0)
: sellerRatings(sellerRatings), buyerRatings(buyerRatings), sellerAverageRating(3.0), buyerAverageRating(3.0) {}

// Getters  
double Rating::getSellerAverageRating() {return sellerAverageRating;}
double Rating::getBuyerAverageRating() {return buyerAverageRating;}
vector <int>& Rating::getBuyerRating() {return buyerRatings;}
vector <int>& Rating::getSellerRating() {return sellerRatings;}

// add seller ratings (to buyers)
void Rating::addSellerRating(int rating) {
    if (rating < 1 || rating > 5) {
        cerr << "Rating score must be between 1 to 5\n";
    } else {
        sellerRatings.push_back(rating);
        updateSellerAvgRating(); 
    }
}

// add buyer ratings 
void Rating::addBuyerRating(int rating) {
    if (rating < 1 || rating > 5) {
        cerr << "Rating score must be between 1 to 5\n";
    } else {
        buyerRatings.push_back(rating);
        updateBuyerAvgRating();
    }
}

// update the average buyer rating based on current ratings 
void Rating::updateBuyerAvgRating() {
    if (!buyerRatings.empty()) {
        double sum = 0.0; 
        // loop through all elements in the vector 
        for (int rating : buyerRatings) {
            sum += rating; 
        }
        buyerAverageRating = sum / buyerRatings.size();
    }
}

// update the average seller rating based on current ratings 
void Rating::updateSellerAvgRating() {
    if (!sellerRatings.empty()) {
        double sum = 0.0; 
        // loop through all elements in the ve"ctor 
        for (int rating : sellerRatings) {
            sum += rating; 
        }
        sellerAverageRating = sum / sellerRatings.size();
    }
}

// display the ratings 
void Rating::displayRating() { 
    cout << "Average Buyer Rating: " << buyerAverageRating << endl;
    cout << "Average Seller Rating: " << sellerAverageRating << endl; 
}