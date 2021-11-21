#ifndef VECTOR_HPP
# define VECTOR_HPP

class vector
{
private:

public:
    vector();
    virtual ~vector();
    vector(vector const &other);
    vector &operator=(vector const &other);
};

#endif
