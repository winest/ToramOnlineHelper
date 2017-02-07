#pragma once
#include <map>
#include "Item.h"
#include "Calc.h"

typedef enum _PLAYER_PROPERTY
{
    PLAYER_LV = 0 ,

    PLAYER_STR ,
    PLAYER_DEX ,
    PLAYER_INT ,
    PLAYER_VIT ,
    PLAYER_AGI ,

    PLAYER_CRT ,
    PLAYER_TEC ,
    PLAYER_LUK ,
    PLAYER_MEN ,

    PLAYER_PROPERTY_COUNT
} PLAYER_PROPERTY;

class CPlayer
{
    public :
        CPlayer() 
        {
            this->Reset( FALSE );
        }
        virtual ~CPlayer() {}

    public :
        VOID Reset( BOOL aClearName );
        VOID SetName( std::string aName );
        CONST CHAR * GetName();
        BOOL SetProperty( PLAYER_PROPERTY aProp , INT aPropValue );
        INT GetProperty( PLAYER_PROPERTY aProp );
        BOOL SetEquipment( CEquipment * aEquip );
        CEquipment * GetEquipment( ITEM_TYPE aItemType );
        INT GetTotalBonus( BONUS_TYPE aBonusType );

    private :
        std::string m_strName;
        std::map<PLAYER_PROPERTY , INT> m_mapProps;
        std::map<ITEM_TYPE , CEquipment *> m_mapEquips; 
 };