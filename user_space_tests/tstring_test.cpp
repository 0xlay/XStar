#include "pch.h"

template <typename Type>
void CheckTStringBuffers(Type&& object)
{
    using namespace xstar;
    
    tstring bufForIstream;

    tstringbuf tStrBuf;
    tstringstream tStrStream;
    tostringstream tOStrStream;
    tistringstream tIStrStream;

    tStrStream << object;
    tOStrStream << object;
    tIStrStream >> bufForIstream;
}

TEST(TStringTests, TString__Test)
{
    using namespace xstar;

#pragma warning(push)
#pragma warning(disable : 26444)
    tstring($T"Hello world");
#pragma warning(pop)

    auto tStr = $T"Hello world"_ts;
    auto constTCharPointer = $T"Hello world";

    EXPECT_EQ(typeid(tStr), typeid(tstring));
    EXPECT_EQ(typeid(constTCharPointer), typeid(const tchar*));
    
    CheckTStringBuffers(tStr);
    CheckTStringBuffers(constTCharPointer);
}

TEST(TStringTests, TStringView__Test)
{
    using namespace xstar;
    
    tstring_view($T"Hello world");
    auto tStrView = $T"Hello world"_tsv;

    EXPECT_EQ(typeid(tStrView), typeid(tstring_view));
    
    CheckTStringBuffers(tStrView);
}

TEST(TStringTests, TChar__Test)
{
    using namespace xstar;
 
    auto symbol = $Tc('x');
    
    EXPECT_EQ(typeid(symbol), typeid(tchar));
	
    CheckTStringBuffers(symbol);
}

TEST(TStringTests, ToTString_Test)
{
    using namespace xstar;

    tstring result = to_tstring(2021);

    EXPECT_EQ(result, $T"2021");
}