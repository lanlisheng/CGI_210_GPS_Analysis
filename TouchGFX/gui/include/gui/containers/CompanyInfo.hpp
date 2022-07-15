#ifndef COMPANYINFO_HPP
#define COMPANYINFO_HPP

#include <gui_generated/containers/CompanyInfoBase.hpp>

class CompanyInfo : public CompanyInfoBase
{
public:
    CompanyInfo();
    virtual ~CompanyInfo() {}

    virtual void initialize();
protected:
};

#endif // COMPANYINFO_HPP
