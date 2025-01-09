#ifndef RATING_H
#define RATING_H

class Rating {
private:
    // Member: rate 
    int ratingID;
    // Member rater;
    // Member rate;
    int score; // from 1 to 5  
    std::string role;

public: 
    Rating(int ratingID,int score, std::string role);
    // void calculateAverageRating(Member a);
    void getRatingDetails();
};

#endif 