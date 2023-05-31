#include "ESetErrors.h"
EUnpossibal::EUnpossibal() {};
void EUnpossibal::print_error() const
{
    cout << "Operation is unpossibal" << endl;
}

EUncorrectIndex::EUncorrectIndex() {};
void EUncorrectIndex::print_error() const
{
    cout << "Uncorrect index" << endl;
}