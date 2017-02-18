#ifndef LABEL_H_
#define LABEL_H_

#include <string>

namespace Venus { namespace Graphics { 

class Label {

private:

public:
    void drawString(std::string text, float x, float y, Font font);
};

}}

#endif