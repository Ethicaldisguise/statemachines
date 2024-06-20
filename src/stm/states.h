#include <memory>
namespace stm
{
    class state {
        void setoutput(const char &through, std::shared_ptr<state> &to) = 0; 
    }
} // namespace stm
