#ifndef BST_EXCEPTS_
#define BST_EXCEPTS_

#include <iostream>

namespace bst {
    // Class for exceptions handling
    // Message is chosen in constructor
    class Exceptions {
        std::string reason;
    public:
        Exceptions( int );
        friend std::ostream& operator<< ( std::ostream&, const Exceptions& );
    };

}

bst::Exceptions::Exceptions( int i ) {
    switch ( i ) {
    case 1:
        reason = "Bst_Empty";
        break;
    case 2:
        reason = "No_Key_Found";
        break;
    case 3:
        reason = "Key_Already_Used";
        break;
    default:
        reason = "Not_Known";
        break;
    }
}
namespace bst {
    std::ostream& operator<< ( std::ostream& os, const bst::Exceptions& exception ) {
        os << exception.reason << std::endl;
        return os;
    }
}

#endif