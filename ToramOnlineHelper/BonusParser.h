#pragma once
#include <map>
#include <regex>
#include "CWGeneralUtils.h"
#include "CWString.h"


typedef enum _BONUS_TYPE
{
    BONUS_ATK_RATE ,
    BONUS_ATK ,
    BONUS_MATK_RATE ,
    BONUS_MATK ,
    BONUS_ELEMENT_ATK_RATE ,
    BONUS_WEAPON_ATK_RATE ,
    BONUS_WEAPON_ATK ,
    BONUS_FIRST_ATK_RATE ,
    BONUS_FIRST_ATK ,
    BONUS_POWER_RESIST_BREAKER_RATE ,
    BONUS_MAGIC_RESIST_BREAKER_RATE ,
    BONUS_SHORT_RANGE_ATK_RATE ,
    BONUS_LONG_RANGE_ATK_RATE ,

    BONUS_STR_RATE ,
    BONUS_STR ,
    BONUS_DEX_RATE ,
    BONUS_DEX ,
    BONUS_INT_RATE ,
    BONUS_INT ,
    BONUS_AGI_RATE ,
    BONUS_AGI ,
    BONUS_VIT_RATE ,
    BONUS_VIT , 
    
    BONUS_CRT_DAMAGE_RATE ,
    BONUS_CRT_DAMAGE ,
    BONUS_CRT_RATE ,
    BONUS_CRT ,

    BONUS_DEF_RATE ,
    BONUS_DEF ,
    BONUS_MDEF_RATE ,
    BONUS_MDEF ,
    BONUS_ELEMENT_DEF_RATE ,
    BONUS_ELEMENT_DEF ,

    BONUS_STABILITY_RATE ,

    BONUS_MAX_HP_RATE ,
    BONUS_MAX_HP ,
    BONUS_MAX_MP_RATE ,
    BONUS_MAX_MP ,
    BONUS_ATK_MP_RECOVER ,

    BONUS_ASPD_RATE ,
    BONUS_ASPD ,
    BONUS_CSPD_RATE ,
    BONUS_CSPD ,
    BONUS_MSPD_RATE ,
    BONUS_MSPD ,    
    
    BONUS_HIT_RATE ,
    BONUS_HIT ,
    BONUS_AVOID_RATE ,
    BONUS_AVOID ,

    BONUS_TYPE_COUNT
} BONUS_TYPE;

typedef struct _BonusProperty
{
    _BonusProperty() {}
    _BonusProperty(std::regex aRegex , std::string aDisplayFmt) : reText(aRegex) , strDisplayFmt(aDisplayFmt) {}
    std::regex reText;
    std::string strDisplayFmt;
} BonusProperty;


class CBonusParser
{
    
    public :
        static CBonusParser * GetInstasnce() { return &m_self; }
        virtual ~CBonusParser();

    protected :
        CBonusParser();

    public :
        BOOL Parse( std::string aProperty , std::map<BONUS_TYPE , INT> & aOutput );
        BOOL GetBonusDisplayString( BONUS_TYPE aBonusType , INT aBonusVal , IN OUT std::string & aStr );
        BOOL GetBonusDisplayString( std::map<BONUS_TYPE , INT> aBonusMap , IN OUT std::string & aStr );

    private :
        static CBonusParser m_self;
        std::map<BONUS_TYPE , BonusProperty> m_mapCheckProps;
};
