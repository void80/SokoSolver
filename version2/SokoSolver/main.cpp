
#include <iostream>

struct Element
{
public:
    
private: 
    constexpr Element(bool hasPlayer, bool hasGoal, bool hasBox)
        : hasPlayer(hasPlayer)
        , hasGoal(hasGoal)
        , hasBox(hasBox)
    {
    }

public:
    bool const hasPlayer;
    bool const hasGoal;
    bool const hasBox;

public:
    template<bool HAS_PLAYER, bool HAS_GOAL, bool HAS_BOX>
    static constexpr Element create()
    {
        static_assert(!HAS_PLAYER || !HAS_BOX, "Element can not have Player and Box at the same time");
        return Element(HAS_PLAYER, HAS_GOAL, HAS_BOX);
    }

};



static constexpr Element BOX = Element::create<false, false, true>();
static Element PLAYER = Element::create<true, false, false>();



int main(int, char**)
{
    //Element<true, true, false> thing;
    //Element<true, false, true> thing2;
    Element box1 = Element::create<false, false, true>();
    //Element box2 = Element::create<true, false, true>();
    char c[BOX.hasPlayer ? 1 : 10];
    // char c2[PLAYER.hasPlayer ? 1 : 10];
    // BOX.hasPlayer = false;
        
    std::cout << "That's all, folks!\n";
    return 0;
}

