#ifndef USER_H 
#define USER_H

#include <string>

using namespace std;

enum class UserRole { Member, Admin };

class User{
    private:
        string username;
        string password;
        string fullName;
        string phoneNum;
        string email;
        string idType;
        string idNum;
        UserRole role;
    
    public:
        User();
        User(const string &username, const string &password, const string&fullName, const string &phoneNum, const string &email, const string &idType, const string &idNum, UserRole role = UserRole::Member);
        virtual ~User();

        // Getters
        string getUsername() const;
        string getPassword() const;
        string getFullName() const;
        string getPhoneNum() const;
        string getEmail() const;
        string getIdType() const;
        string getIdNum() const;
        UserRole getRole() const;

        // Methods
        virtual void displayProfile() const;
        virtual void updateProfile(); // ADD PROFILE PARAMS

        //Static utility methods
        static bool validatePassword(const string &password); // Ensure strong password policy
        
        
};

#endif


