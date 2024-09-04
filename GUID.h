#include <array>
#include <string>
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
using namespace std;

struct GUID
{
    // store generated chars
    array<unsigned char, 16> data;

    // able to compare 2 GUID
    bool operator==(const GUID &other) const
    {
        return data == other.data;
    }

    // convert guid into string
    std::string toString() const
    {
        std::ostringstream oss;
        for (size_t i = 0; i < data.size(); ++i)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
            if (i == 3 || i == 5 || i == 7 || i == 9)
            {
                oss << "-";
            }
        }
        return oss.str();
    }
};

// able to cout the GUID
std::ostream &operator<<(std::ostream &os, const GUID &guid)
{
    for (const auto &byte : guid.data)
    {
        os << std::hex << static_cast<int>(byte);
    }
    return os;
}

// create GUID
GUID createGUID()
{
    GUID guid;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (auto &byte : guid.data)
    {
        byte = static_cast<unsigned char>(dis(gen));
    }

    return guid;
}
