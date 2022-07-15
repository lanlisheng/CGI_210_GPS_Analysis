#ifndef DATACOLLECT_ELEMENT_HPP
#define DATACOLLECT_ELEMENT_HPP

#include <gui_generated/containers/DataCollect_ElementBase.hpp>

class DataCollect_Element : public DataCollect_ElementBase
{
public:
    DataCollect_Element();
    virtual ~DataCollect_Element() {}

    virtual void initialize();
protected:
};

#endif // DATACOLLECT_ELEMENT_HPP
