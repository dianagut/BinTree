#pragma once

#include <string>
#include <iostream>

class NodeData {
    friend std::ostream& operator<<(std::ostream& output, const NodeData& nd);

public:
    NodeData();
    ~NodeData();
    NodeData(const NodeData& nd);
    NodeData(const std::string& s);
    
    NodeData& operator=(const NodeData& rhs);
    bool operator==(const NodeData& p);
    bool operator!=(const NodeData& p);
    bool operator<(const NodeData& rhs);
    bool operator>(const NodeData& rhs);
    bool operator<=(const NodeData& rhs);
    bool operator>=(const NodeData& rhs);

    bool setData(std::istream& infile);
    std::string getData() { return data ;}
    
private:
    std::string data;
};
