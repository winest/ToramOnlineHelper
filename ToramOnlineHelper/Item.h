#pragma once
#include "BonusParser.h"

typedef enum _ITEM_TYPE
{
    ITEM_MAIN_WEAPON = 0 ,
    ITEM_SUB_WEAPON ,
    ITEM_ARMOR ,
    ITEM_ADDITIONAL_EQUIPMENT ,
    ITEM_SPECIAL_EQUIPMENT ,

    ITEM_GENERAL_XTAL ,
    ITEM_WEAPON_XTAL ,
    ITEM_ARMOR_XTAL ,
    ITEM_ADDITIONAL_EQUIPMENT_XTAL ,
    ITEM_SPECIAL_EQUIPMENT_XTAL ,

    ITEM_TYPE_COUNT
} ITEM_TYPE;
BOOL GetItemNameByType( ITEM_TYPE aItemType , std::string & aOutput );

typedef enum _EQUIP_TYPE
{
    EQUIP_EMPTY ,
    EQUIP_KNUCKLE ,
    EQUIP_ONE_HAND_SWORD ,
    EQUIP_TWO_HAND_SWORD ,
    EQUIP_DUAL_SWORD ,
    EQUIP_BOW ,
    EQUIP_BOWGUN ,
    EQUIP_ROD ,
    EQUIP_MAGICAL_DEVICE ,
    EQUIP_HALBERD ,

    EQUIP_ARROW ,
    EQUIP_SHIELD ,
    EQUIP_KNIFE ,

    EQUIP_ARMOR ,
    EQUIP_ADDITIONAL_EQUIPMENT ,
    EQUIP_SPECIAL_EQUIPMENT
} EQUIP_TYPE;



class CItem
{
    public :
        CItem( ITEM_TYPE aItemType ) : m_nItemType(aItemType)
        {
            for ( INT i = 0 ; i < BONUS_TYPE_COUNT ; i++ )
            {
                m_mapBonus[(BONUS_TYPE)i] = 0;
            }
        }
        virtual ~CItem() {}

    public :
        ITEM_TYPE GetItemType();

        VOID SetName( std::string aName );
        CONST CHAR * GetName();

        BOOL ParseBonus( std::string aProp );
        INT GetBonusValue( BONUS_TYPE aBonusType );

        virtual std::string ToString();

    protected :
        ITEM_TYPE m_nItemType;
        std::string m_strName;
        std::map<BONUS_TYPE , INT> m_mapBonus;
};



class CXtal : public CItem
{
    public :
        CXtal( ITEM_TYPE aItemType ) : CItem( aItemType ) {}
        virtual ~CXtal() {}

    public :
        virtual std::string ToString();
};


#define EQUIP_MAX_SLOT_CNT 2
class CEquipment : public CItem
{
    public :
        CEquipment( ITEM_TYPE aItemType , EQUIP_TYPE aEquipType ) : CItem(aItemType) , m_nEquipType(aEquipType)
        {
            ZeroMemory( m_pXtals , sizeof(m_pXtals) ); 
        }
        virtual ~CEquipment() {}

    public :
        EQUIP_TYPE GetEquipType();
        BOOL SetProperty( INT aAtkOrDef , INT aRefineLv , INT aStability );
        BOOL GetProperty( INT & aAtkOrDef , INT & aRefineLv , INT & aStability );
        BOOL SetXtal( INT aSlotIndex , CXtal * aXtal );
        CXtal * GetXtal( INT aSlotIndex );

        virtual std::string ToString();

    protected :
        EQUIP_TYPE m_nEquipType;
        INT m_nAtkOrDef;
        INT m_nRefineLv;
        INT m_nStability;
        CXtal * m_pXtals[EQUIP_MAX_SLOT_CNT];
};