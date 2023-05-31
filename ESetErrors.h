#ifndef ESetErrors_h
#define ESetErrors_h

#include <iostream>
using namespace std;
#include <stdio.h>
class ESetErrors
{
public: virtual void print_error() const = 0;
};

class EUnpossibal : public ESetErrors
{
public:
    EUnpossibal();
    void print_error() const;
};
class EUncorrectIndex : public ESetErrors
{
public:
    EUncorrectIndex();
    void print_error() const;
};

#endif