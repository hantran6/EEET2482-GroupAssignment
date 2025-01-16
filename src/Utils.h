#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils
{
    // Validation for user credentials
    bool isValidPassword(const std::string &password);
    bool isValidEmail(const std::string &email);
    bool isValidUsername(const std::string &username);

    std::string getCurrentDateTime();

    // Helper methods to print messages
    void showError(const std::string &message);
    void showInfo(const std::string &message);
    void showSuccess(const std::string &message);
    void showWarning(const std::string &message);

}

#endif // UTILS_H
