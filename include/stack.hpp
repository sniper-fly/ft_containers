#ifndef STACK_HPP
# define STACK_HPP

class stack
{
private:

public:
    stack();
    virtual ~stack();
    stack(stack const &other);
    stack &operator=(stack const &other);
};

#endif
