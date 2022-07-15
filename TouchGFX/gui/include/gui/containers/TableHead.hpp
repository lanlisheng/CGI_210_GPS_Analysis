#ifndef TABLEHEAD_HPP
#define TABLEHEAD_HPP

#include <gui_generated/containers/TableHeadBase.hpp>

class TableHead : public TableHeadBase
{
public:
    TableHead();
    virtual ~TableHead() {}

    virtual void initialize();
protected:
};

#endif // TABLEHEAD_HPP
