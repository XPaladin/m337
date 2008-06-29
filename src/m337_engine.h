#include <string>
#include <vector>

#include "wengine/wengine.h"

using namespace std;

class m337_engine: public wengine
{
    protected:
        static const int game_tic = 10;

    public:
        ~m337_engine();

    protected:
        void main_loop();
};

