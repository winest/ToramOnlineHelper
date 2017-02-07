#include "stdafx.h"
#include "BonusParser.h"
using namespace std;

CBonusParser CBonusParser::m_self;

CBonusParser::CBonusParser()
{
    m_mapCheckProps.insert( make_pair(BONUS_ATK_RATE , BonusProperty( regex( "^(A|ATK)([+-]?[0-9]+)%$" , regex::icase ) , "A%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_ATK , BonusProperty( regex( "^(A|ATK)([+-]?[0-9]+)$" , regex::icase ) , "A%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MATK_RATE , BonusProperty( regex( "^(MA|MATK)([+-]?[0-9]+)%$" , regex::icase ) , "MA%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MATK , BonusProperty( regex( "^(MA|MATK)([+-]?[0-9]+)$" , regex::icase ) , "MA%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_ELEMENT_ATK_RATE , BonusProperty( regex( "^(ElementAtk|屬性ATK)([+-]?[0-9]+)%$" , regex::icase ) , "ElementAtk%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_WEAPON_ATK_RATE , BonusProperty( regex( "^(WeaponAtk|武器ATK)([+-]?[0-9]+)%$" , regex::icase ) , "武器ATK%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_WEAPON_ATK , BonusProperty( regex( "^(WeaponAtk|武器ATK)([+-]?[0-9]+)$" , regex::icase ) , "武器ATK%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_FIRST_ATK_RATE , BonusProperty( regex( "^(FirstAtk|拔刀攻擊)([+-]?[0-9]+)%$" , regex::icase ) , "拔刀攻擊%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_FIRST_ATK , BonusProperty( regex( "^(FirstAtk|拔刀攻擊)([+-]?[0-9]+)$" , regex::icase ) , "拔刀攻擊%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_POWER_RESIST_BREAKER_RATE , BonusProperty( regex( "^(PowerResistBreaker|物理貫穿)([+-]?[0-9]+)%$" , regex::icase ) , "物理貫穿%d%%" )) );
    //m_mapCheckProps.insert( make_pair(BONUS_MAGIC_RESIST_BREAKER_RATE , BonusProperty( regex( "^(MagicResistBreaker|魔法貫穿)([+-]?[0-9]+)%$" , regex::icase ) , "魔法貫穿%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_SHORT_RANGE_ATK_RATE , BonusProperty( regex( "^(ShortRangeAtk|近距離威力)([+-]?[0-9]+)%$" , regex::icase ) , "近距離威力%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_LONG_RANGE_ATK_RATE , BonusProperty( regex( "^(LongRangeAtk|遠距離威力)([+-]?[0-9]+)%$" , regex::icase ) , "遠距離威力%d%%" )) );
    
    m_mapCheckProps.insert( make_pair(BONUS_STR_RATE , BonusProperty( regex( "^(S|STR)([+-]?[0-9]+)%$" , regex::icase ) , "S%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_STR , BonusProperty( regex( "^(S|STR)([+-]?[0-9]+)$" , regex::icase ) , "S%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_DEX_RATE , BonusProperty( regex( "^(D|DEX)([+-]?[0-9]+)%$" , regex::icase ) , "D%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_DEX , BonusProperty( regex( "^(D|DEX)([+-]?[0-9]+)$" , regex::icase ) , "D%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_INT_RATE , BonusProperty( regex( "^(I|INT)([+-]?[0-9]+)%$" , regex::icase ) , "I%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_INT , BonusProperty( regex( "^(I|INT)([+-]?[0-9]+)$" , regex::icase ) , "I%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_AGI_RATE , BonusProperty( regex( "^(AGI)([+-]?[0-9]+)%$" , regex::icase ) , "Agi%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_AGI , BonusProperty( regex( "^(AGI)([+-]?[0-9]+)$" , regex::icase ) , "Agi%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_VIT_RATE , BonusProperty( regex( "^(V|VIT)([+-]?[0-9]+)%$" , regex::icase ) , "V%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_VIT , BonusProperty( regex( "^(V|VIT)([+-]?[0-9]+)$" , regex::icase ) , "V%d" )) );

    m_mapCheckProps.insert( make_pair(BONUS_CRT_DAMAGE_RATE , BonusProperty( regex( "^(CD)([+-]?[0-9]+)%$" , regex::icase ) , "Cd%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_CRT_DAMAGE , BonusProperty( regex( "^(CD)([+-]?[0-9]+)$" , regex::icase ) , "Cd%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_CRT_RATE , BonusProperty( regex( "^(C|CR)([+-]?[0-9]+)%$" , regex::icase ) , "C%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_CRT , BonusProperty( regex( "^(C|CR)([+-]?[0-9]+)$" , regex::icase ) , "C%d" )) );
    
    m_mapCheckProps.insert( make_pair(BONUS_DEF_RATE , BonusProperty( regex( "^(DEF)([+-]?[0-9]+)%$" , regex::icase ) , "Def%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_DEF , BonusProperty( regex( "^(DEF)([+-]?[0-9]+)$" , regex::icase ) , "Def%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MDEF_RATE , BonusProperty( regex( "^(MDEF)([+-]?[0-9]+)%$" , regex::icase ) , "MDef%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MDEF , BonusProperty( regex( "^(MDEF)([+-]?[0-9]+)$" , regex::icase ) , "MDef%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_ELEMENT_DEF_RATE , BonusProperty( regex( "^(ElementDef|屬性DEF)([+-]?[0-9]+)%$" , regex::icase ) , "ElementDef%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_ELEMENT_DEF , BonusProperty( regex( "^(ElementDef|屬性DEF)([+-]?[0-9]+)$" , regex::icase ) , "ElementDef%d" )) );
    
    m_mapCheckProps.insert( make_pair(BONUS_STABILITY_RATE , BonusProperty( regex( "^(Stability|穩定率)([+-]?[0-9]+)%$" , regex::icase ) , "穩定率%d%%" )) );

    m_mapCheckProps.insert( make_pair(BONUS_MAX_HP_RATE , BonusProperty( regex( "^(HP|MaxHp)([+-]?[0-9]+)%$" , regex::icase ) , "HP%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MAX_HP , BonusProperty( regex( "^(HP|MaxHp)([+-]?[0-9]+)$" , regex::icase ) , "HP%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MAX_MP_RATE , BonusProperty( regex( "^(MP|MaxMp)([+-]?[0-9]+)%$" , regex::icase ) , "MP%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MAX_MP , BonusProperty( regex( "^(MP|MaxMp)([+-]?[0-9]+)$" , regex::icase ) , "MP%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_ATK_MP_RECOVER , BonusProperty( regex( "^(AtkMpRecover|攻擊回復)([+-]?[0-9]+)$" , regex::icase ) , "攻擊回復%d" )) );
    
    m_mapCheckProps.insert( make_pair(BONUS_ASPD_RATE , BonusProperty( regex( "^(ASPD|攻擊速度)([+-]?[0-9]+)%$" , regex::icase ) , "攻擊速度%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_ASPD , BonusProperty( regex( "^(ASPD|攻擊速度)([+-]?[0-9]+)$" , regex::icase ) , "攻擊速度%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_CSPD_RATE , BonusProperty( regex( "^(CSPD|詠唱速度)([+-]?[0-9]+)%$" , regex::icase ) , "詠唱速度%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_CSPD , BonusProperty( regex( "^(CSPD|詠唱速度)([+-]?[0-9]+)$" , regex::icase ) , "詠唱速度%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MSPD_RATE , BonusProperty( regex( "^(MSPD|MotionSpeed|行動速度)([+-]?[0-9]+)%$" , regex::icase ) , "行動速度%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_MSPD , BonusProperty( regex( "^(MSPD|MotionSpeed|行動速度)([+-]?[0-9]+)$" , regex::icase ) , "行動速度%d" )) );
 
    m_mapCheckProps.insert( make_pair(BONUS_HIT_RATE , BonusProperty( regex( "^(Hit|命中)([+-]?[0-9]+)%$" , regex::icase ) , "命中%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_HIT , BonusProperty( regex( "^(Hit|命中)([+-]?[0-9]+)$" , regex::icase ) , "命中%d" )) );
    m_mapCheckProps.insert( make_pair(BONUS_AVOID_RATE , BonusProperty( regex( "^(Avoid|迴避)([+-]?[0-9]+)%$" , regex::icase ) , "迴避%d%%" )) );
    m_mapCheckProps.insert( make_pair(BONUS_AVOID , BonusProperty( regex( "^(Avoid|迴避)([+-]?[0-9]+)$" , regex::icase ) , "迴避%d" )) );
}

CBonusParser::~CBonusParser()
{
    m_mapCheckProps.clear();
}

BOOL CBonusParser::Parse( std::string aProperty , std::map<BONUS_TYPE , INT> & aOutput )
{
    BOOL bRet = FALSE;
    aOutput.clear();
    vector<std::string> vecProps;
    CWUtils::SplitStringA( aProperty , vecProps , " .,;" );

    smatch smProps;
    for ( size_t i = 0 ; i < vecProps.size() ; i++ )
    {
        BOOL bFound = FALSE;
        for ( INT prop = 0 ; prop < BONUS_TYPE_COUNT ; prop++ )
        {
            if ( regex_match( vecProps[i] , smProps , m_mapCheckProps[(BONUS_TYPE)prop].reText ) && smProps.size() >= 3 )
            {
                aOutput[(BONUS_TYPE)prop] = atoi( smProps[2].str().c_str() );
                bFound = TRUE;
                bRet = TRUE;
                break;
            }
        }

        if ( bFound == FALSE )
        {
            wprintf_s( L"Unknown property found: %hs\n" , vecProps[i].c_str() );
        }
    }

    string strDisplay;
    this->GetBonusDisplayString( aOutput , strDisplay );
    wprintf_s( L"CBonusParser::Parse() get %hs\n" , strDisplay.c_str() );
    
    return bRet;
}

BOOL CBonusParser::GetBonusDisplayString( BONUS_TYPE aBonusType , INT aBonusVal , IN OUT std::string & aStr )
{
    return CWUtils::FormatStringA( aStr , m_mapCheckProps[aBonusType].strDisplayFmt.c_str() , aBonusVal );
}

BOOL CBonusParser::GetBonusDisplayString( std::map<BONUS_TYPE , INT> aBonusMap , IN OUT std::string & aStr )
{
    aStr.clear();
    string strTmp;
    for ( auto it = aBonusMap.begin() ; it != aBonusMap.end() ; it++ )
    {
        if ( it->second != 0 )
        {
            this->GetBonusDisplayString( it->first , it->second , strTmp );
            aStr.append( strTmp );
        }
    }
    return TRUE;
}


