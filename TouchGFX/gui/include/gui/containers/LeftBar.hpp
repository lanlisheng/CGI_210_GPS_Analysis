#ifndef LEFTBAR_HPP
#define LEFTBAR_HPP

#include <gui_generated/containers/LeftBarBase.hpp>

class LeftBar : public LeftBarBase
{
public:
    LeftBar();
    virtual ~LeftBar() {}

    virtual void initialize();
protected:
};

#endif // LEFTBAR_HPP
