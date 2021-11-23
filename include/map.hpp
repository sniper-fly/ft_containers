#ifndef MAP_HPP
# define MAP_HPP

class map
{
private:

public:
    map();
    virtual ~map();
    map(map const &other);
    map &operator=(map const &other);
};

#endif
